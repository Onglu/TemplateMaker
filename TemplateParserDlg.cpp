#include "TemplateParserDlg.h"
#include "ui_TemplateParserDlg.h"
#include "json.h"
#include <QDebug>
#include <QFileDialog>
#include <QUuid>
#include <QSettings>
#include <QDateTime>
#include <QBuffer>
#include <QMessageBox>

#define TEMP_FILE       "/DDECF6B7F103CFC11B2.png"
#define PKG_FMT         ".xcmb"
#define PKG_PASSWORD    "123123"

using namespace QtJson;

TemplateParserDlg::TemplateParserDlg(QWidget *parent) :
    QDialog(parent, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint),
    ui(new Ui::TemplateParserDlg),
    m_pInfo(NULL),
    m_finished(false),
    m_landscapeCount(0),
    m_portraitCount(0),
    m_make(false)
{
    ui->setupUi(this);

    //ui->tmplToolButton->setEnabled(false);
    ui->frame->setEnabled(false);
    //ui->tmplToolButton->hide();
    ui->progressBar->hide();

    QSettings settings("Jizhiyou", "TemplateParser");
    m_dirName = settings.value("dir_name").toString();
    if (m_dirName.isEmpty())
    {
        m_dirName = QDir::toNativeSeparators(QDir::homePath()) + "\\";
    }

    connect(&m_timer, SIGNAL(timeout()), SLOT(end()));
    connect(&m_parser, SIGNAL(finished()), SLOT(ok()), Qt::BlockingQueuedConnection);
    connect(&m_maker, SIGNAL(finished()), SLOT(make()), Qt::BlockingQueuedConnection);
    connect(&m_tmaker, SIGNAL(finished(int,QProcess::ExitStatus)), SLOT(processFinished(int,QProcess::ExitStatus)));
}

TemplateParserDlg::~TemplateParserDlg()
{
    if (m_timer.isActive())
    {
        m_timer.stop();
    }

    psd_release(m_pInfo);

    deleteDir(m_tmpDir);

    delete ui;
}

bool TemplateParserDlg::deleteDir(const QString &dirName, bool delSelf)
{
    qDebug() << __FILE__ << __LINE__ << dirName;
    QDir directory(dirName);
    if (!directory.exists())
    {
        return true;
    }

    QStringList files = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    QList<QString>::iterator f = files.begin();
    bool error = false;

    while (f != files.end())
    {
        QString filePath = QDir::convertSeparators(directory.path() + '/' + (*f));
        QFileInfo fi(filePath);
        if (fi.isFile() || fi.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                error = true;
            }
        }
        else if (fi.isDir())
        {
            if (!deleteDir(filePath));
            {
                error = true;
            }
        }
        ++f;
    }

    if (delSelf)
    {
        return directory.rmdir(QDir::convertSeparators(directory.path()));
    }

    return error;
}

void TemplateParserDlg::moveTo(QString &fileName, QString dirName, bool overwrite)
{
    QFile file(fileName);
    if (!file.exists())
    {
        return;
    }

    QChar sep = QDir::separator();
    QString tl(sep), old, name = fileName.right(fileName.length() - fileName.lastIndexOf(sep) - 1);
    if (tl != dirName.right(1))
    {
        dirName = QDir::toNativeSeparators(dirName) + tl;
    }

    old = fileName.left(fileName.lastIndexOf(QDir::separator()) + 1);
    QDir dir(dirName);
    if (!dir.exists() || old == dirName)
    {
        return;
    }

    if (!overwrite)
    {
        if (dir.exists(name))
        {
            QMessageBox::warning(this,
                                 tr("保存失败"),
                                 tr("该目录下已经存在一个同名的相册模板包，请更名后再重新进行保存！"),
                                 tr("确定")
                                 );
            return;
        }
    }

    name = dirName + name;

    if (overwrite)
    {
        dir.remove(name);
    }

    if (file.copy(name))
    {
        file.remove();
        fileName = name;
    }
}

inline void TemplateParserDlg::change()
{
    if (!m_make)
    {
        //useZip(ZipUsageAppend, m_pkgFile + " " + m_tmpFile);
        QString program(MAKER_NAME);
        program += QString(" -a ") + m_pkgFile + " " + m_tmpFile;
        QProcess::execute(program);
    }

    if (QFile::exists(m_tmpFile))
    {
        QFile::remove(m_tmpFile);
    }

    m_tmpFile.clear();

    //m_pkgFile = QString("G:\\Images\\PSD\\MP_C_P2_201306091748_777.xcmb");

    m_finished = false;
    m_make = !m_make;
    ui->frame->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    m_maker.crypt(m_make, m_pkgFile + " " + PKG_PASSWORD);
    m_maker.start();
    m_timer.start(30);
}

void TemplateParserDlg::processFinished(int ret, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(ret);

    if (exitStatus == QProcess::CrashExit)
    {
        //qDebug() << __FILE__ << __LINE__ << "Crash Exit";
    }
    else
    {
        QByteArray out = m_tmaker.readAllStandardOutput();
        QString content(out);
        m_tmaker.close();

        if (content.startsWith("compress:"))
        {
            moveTo(m_psdPic, m_tmpDir);
            deleteDir(content.mid(9));
        }

        if (ZipUsageAppend == m_usage && !m_tmpFile.isEmpty())
        {
            qDebug() << __FILE__ << __LINE__ << m_tmpFile;
            //access();
        }

        if (content.startsWith("data:"))
        {
            QString data = content.mid(5);
            qDebug() << __FILE__ << __LINE__ << data;
        }

        if (content.startsWith("picture:"))
        {
            QString name = content.mid(8);
            QString file = QDir::toNativeSeparators(name);
            QPixmap pix(file);

            //qDebug() << __FILE__ << __LINE__ << file << pix.isNull();

            if (!pix.isNull())
            {
                pix = pix.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                ui->pictureLabel->setPixmap(pix);
            }

            QFile::remove(file);
        }
    }
}

void TemplateParserDlg::on_psdToolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), m_dirName, tr("PSD文档 (*.psd)"));
    if (fileName.isEmpty())
    {
        return;
    }

    fileName = QDir::toNativeSeparators(fileName);
    if (m_psdFile != fileName)
    {
        ui->psdToolButton->setEnabled(false);
        ui->tmplToolButton->setEnabled(false);

        m_psdFile = fileName;
        m_dirName = fileName.left(fileName.lastIndexOf(QDir::separator()) + 1);
        QSettings settings("Jizhiyou", "TemplateParser");
        settings.setValue("dir_name", m_dirName);
        //qDebug() << __FILE__ << __LINE__ << fileName << m_dirName;

        psd_release(m_pInfo);
        m_pInfo = (PSD_LAYERS_INFO *)calloc(1, sizeof(PSD_LAYERS_INFO));
        strcpy(m_pInfo->file, fileName.toStdString().c_str());
        psd_parse(m_pInfo);

        for (int i = 0; i < m_pInfo->count; i++)
        {
            if (!strlen(m_pInfo->layers[i].name))
            {
                continue;
            }

            if (m_pInfo->layers[i].canvas)
            {
                m_bkSize = QSize(m_pInfo->layers[i].bound.width, m_pInfo->layers[i].bound.height);
            }

            //qDebug() << m_pInfo->layers[i].name << m_pInfo->layers[i].angle;

            QString uuid = QUuid::createUuid().toString().mid(1, 36);
            strcpy(m_pInfo->layers[i].lid, uuid.toStdString().c_str());
        }

        if (!m_xcmb.isEmpty())
        {
            m_xcmb.clear();
        }

        m_xcmb.insert("id", QUuid::createUuid().toString().mid(1, 36));
        m_xcmb.insert("ver", "1.0");
        m_xcmb.insert("backgroundColor", "#FFFFFFFF");

        int start = fileName.lastIndexOf('\\') + 1;
        int end = fileName.lastIndexOf(".psd", -1, Qt::CaseInsensitive);
        QString name = fileName.mid(start, end - start);
        m_xcmb.insert("name", name);
        deleteDir(m_dirName + name + "_png", false);

        QVariantMap bkSize;
        bkSize.insert("width", m_bkSize.width());
        bkSize.insert("height", m_bkSize.height());
        m_xcmb.insert("size", bkSize);
        qDebug() << bkSize;

        ui->frame->setEnabled(false);
        ui->progressBar->setVisible(true);
        ui->progressBar->setValue(0);

        m_finished = false;
        m_parser.initLayersInfo(m_pInfo);
        m_parser.start();
        m_timer.start(60);
    }
}

void TemplateParserDlg::on_tmplToolButton_clicked()
{
    //useZip(ZipUsageUncompress, tr("E:\\images\\ex\\MP_C_P2_201306082012_kll.zip"));
    //useZip(ZipUsageRead, tr("E:\\images\\ex\\MP_C_P2_201306082012_kll.zip page.dat"));
    //useZip(ZipUsageEncrypt, tr("E:\\images\\ex\\MP_C_P2_201306082012_kll.zip 123456"));
    //useZip(ZipUsageDecrypt, tr("E:\\images\\ex\\MP_C_P2_201306082012_kll.zip 123456"));
    //useZip(ZipUsageRead, tr("E:\\images\\ex\\MP_C_P2_201306082012_kll.zip psd.png"));

    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), m_dirName, tr("相册模板 (*.xcmb)"));
    if (fileName.isEmpty())
    {
        return;
    }

    m_make = true;
    m_pkgFile = fileName;
    change();
}

void TemplateParserDlg::end()
{
    int v = ui->progressBar->value();
    const int m = ui->progressBar->maximum();

    if (m_finished)
    {
        m_timer.stop();

        if (m != v)
        {
            ui->progressBar->setValue(m);
        }

        ui->psdToolButton->setEnabled(true);
        ui->tmplToolButton->setEnabled(true);
        ui->frame->setEnabled(true);
        ui->progressBar->setVisible(false);

        ui->sizeLabel->setText(tr("模板画布大小：%1x%2").arg(m_bkSize.width()).arg(m_bkSize.height()));
        if (720 == m_bkSize.width() && 1280 == m_bkSize.height())
        {
            ui->wpCoverRadioButton->setChecked(true);
        }
    }
    else
    {
        if (m > ++v)
        {
            ui->progressBar->setValue(v);
            QString pro = m_parser.isRunning() || !m_make ? tr("解析进度：") : tr("生成进度：");
            ui->progressBar->setFormat(tr("%1%2%").arg(pro).arg(100 * v / m));
        }
    }
}

void TemplateParserDlg::ok()
{
    if (m_finished)
    {
        return;
    }

    QString file(m_pInfo->file);
    int pos = file.lastIndexOf(".psd", -1, Qt::CaseInsensitive);

    if (-1 != pos)
    {
        QString tmplDir = file.replace(pos, 4, "_png");
        m_psdPic = QString("%1\\%2.psd.png").arg(tmplDir).arg(m_xcmb["name"].toString());

        QString tmpDir(QDir::tempPath() + "/tlpt"), id = m_xcmb["id"].toString();
        QDir dir(tmpDir);
        if (!dir.exists())
        {
            dir.mkdir(tmpDir);
        }
        dir.mkdir(id);
        m_tmpDir = QDir::toNativeSeparators(QString("%1/%2/").arg(tmpDir).arg(id));
        m_pkgFile = QString("%1%2%3").arg(m_tmpDir).arg(id).arg(PKG_FMT);

        QVariantList list;

        /* add layers */
        for (int i = 0; i < m_pInfo->count; i++)
        {
            if (!strlen(m_pInfo->layers[i].lid) || !strlen(m_pInfo->layers[i].name))
            {
                continue;
            }

            QVariantMap layer;
            layer.insert("id", m_pInfo->layers[i].lid);
            layer.insert("name", QString(m_pInfo->layers[i].name));
            layer.insert("rotation", m_pInfo->layers[i].angle);
            layer.insert("opacity", QString("%1").arg(m_pInfo->layers[i].opacity));
            layer.insert("type", m_pInfo->layers[i].type);
            uchar orientation = m_pInfo->layers[i].actual.width > m_pInfo->layers[i].actual.height ? 1 : 0;
            layer.insert("orientation", orientation);

            if (strlen(m_pInfo->layers[i].mid))
            {
                layer.insert("maskLayer", m_pInfo->layers[i].mid);
            }

            if (m_pInfo->layers[i].type)
            {
                QString name = file + QString("\\%1.png").arg(m_pInfo->layers[i].lid);

                if (LT_Photo == m_pInfo->layers[i].type)
                {
                    if (orientation)
                    {
                        m_landscapeCount++;
                    }
                    else
                    {
                        m_portraitCount++;
                    }
                }

                if (LT_Mask == m_pInfo->layers[i].type && QString(m_pInfo->layers[i].name).contains("lmask", Qt::CaseInsensitive))
                {
                    QImage img(name);
                    QVector<QRgb> rgbVector = img.colorTable();

                    for (int i = 0; i < rgbVector.size(); ++i)
                    {
                        QColor clr(rgbVector.at(i));
                        clr.setAlpha((clr.red() + clr.blue() + clr.green()) / 3);
                        img.setColor(i, clr.rgba());
                    }

                    img.save(name);
                }

                if ((int)m_pInfo->layers[i].angle)
                {
                    QImage img(name);
                    img.transformed(QTransform().rotate(-1 * m_pInfo->layers[i].angle)).save(name);

                    QPixmap pix(name);
                    m_pInfo->layers[i].actual.width = pix.width();
                    m_pInfo->layers[i].actual.height = pix.height();
                }
            }

            //qDebug() << i << m_pInfo->layers[i].name << m_pInfo->layers[i].lid << m_pInfo->layers[i].opacity;

            QVariantMap frame;
            frame.insert("width", m_pInfo->layers[i].actual.width);
            frame.insert("height", m_pInfo->layers[i].actual.height);
            frame.insert("x", m_pInfo->layers[i].center.x);
            frame.insert("y", m_pInfo->layers[i].center.y);
            layer.insert("frame", frame);
            list << layer;
        }

        m_xcmb.insert("layers", list);
        m_xcmb.insert("landscapeCount", m_landscapeCount);
        m_xcmb.insert("portraitCount", m_portraitCount);

        QPixmap pix(m_psdPic);
        if (!pix.isNull())
        {
            ui->pictureLabel->setPixmap(pix.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }

        if (list.size())
        {
            useZip(ZipUsageCompress, m_pkgFile + " " + tmplDir);
        }
    }

    m_finished = true;
}

inline void TemplateParserDlg::addTag(const QCheckBox *cb)
{
    QString value, name = cb->objectName();

    if (name.startsWith("type"))
    {
        value = tr("种类");
    }
    else if (name.startsWith("style"))
    {
        value = tr("板式");
    }
    else if (name.startsWith("color"))
    {
        value = tr("色系");
    }
    else
    {
        return;
    }

    name = cb->text();

    if (cb->isChecked() && !value.isEmpty())
    {
        m_tagsMap.insert(name, value);
    }
    else
    {
        m_tagsMap.remove(name);
    }
}

void TemplateParserDlg::on_typeChildrenCheckBox_clicked()
{
    addTag(ui->typeChildrenCheckBox);
}

void TemplateParserDlg::on_typePictorialCheckBox_clicked()
{
    addTag(ui->typePictorialCheckBox);
}

void TemplateParserDlg::on_typeWeddingCheckBox_clicked()
{
    addTag(ui->typeWeddingCheckBox);
}

void TemplateParserDlg::on_styleFramelessCheckBox_clicked()
{
    addTag(ui->styleFramelessCheckBox);
}

void TemplateParserDlg::on_styleFrameCheckBox_clicked()
{
    addTag(ui->styleFrameCheckBox);
}

void TemplateParserDlg::on_styleNonmaskCheckBox_clicked()
{
    addTag(ui->styleNonmaskCheckBox);
}

void TemplateParserDlg::on_styleMaskCheckBox_clicked()
{
    addTag(ui->styleMaskCheckBox);
}

void TemplateParserDlg::on_colorBlackCheckBox_clicked()
{
    addTag(ui->colorBlackCheckBox);
}

void TemplateParserDlg::on_colorWhiteCheckBox_clicked()
{
    addTag(ui->colorWhiteCheckBox);
}

void TemplateParserDlg::on_colorGrayCheckBox_clicked()
{
    addTag(ui->colorGrayCheckBox);
}

void TemplateParserDlg::on_colorCoffeeCheckBox_clicked()
{
    addTag(ui->colorCoffeeCheckBox);
}

void TemplateParserDlg::on_colorRedCheckBox_clicked()
{
    addTag(ui->colorRedCheckBox);
}

void TemplateParserDlg::on_colorPinkCheckBox_clicked()
{
    addTag(ui->colorPinkCheckBox);
}

void TemplateParserDlg::on_colorOrangeCheckBox_clicked()
{
    addTag(ui->colorOrangeCheckBox);
}

void TemplateParserDlg::on_colorYellowCheckBox_clicked()
{
    addTag(ui->colorYellowCheckBox);
}

void TemplateParserDlg::on_colorCyanCheckBox_clicked()
{
    addTag(ui->colorCyanCheckBox);
}

void TemplateParserDlg::on_colorGreenCheckBox_clicked()
{
    addTag(ui->colorGreenCheckBox);
}

void TemplateParserDlg::on_colorBlueCheckBox_clicked()
{
    addTag(ui->colorBlueCheckBox);
}

void TemplateParserDlg::on_colorPurpleCheckBox_clicked()
{
    addTag(ui->colorPurpleCheckBox);
}

void TemplateParserDlg::on_browsePushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), m_dirName);
    if (dir.isEmpty())
    {
        return;
    }

    ui->pathLineEdit->setText(dir);
    m_dirName = dir.append('\\');

    QSettings settings("Jizhiyou", "TemplateParser");
    settings.setValue("dir_name", m_dirName);
    //qDebug() << __FILE__ << __LINE__ << dir;
}

void TemplateParserDlg::on_savePushButton_clicked()
{
#if 1
    QVariantList tagsList;
    QVariantMap::const_iterator iter = m_tagsMap.constBegin();
    while (iter != m_tagsMap.constEnd())
    {
        QVariantMap tagMap;
        tagMap.insert("name", iter.key());
        tagMap.insert("type", iter.value());
        tagsList << tagMap;
        qDebug() << __FILE__ << __LINE__ << iter.key() << ":" << iter.value().toString();
        ++iter;
    }

    QString style = ui->styleLineEdit->text();
    if (!style.isEmpty())
    {
        QVariantMap tagMap;
        tagMap.insert("name", style);
        tagMap.insert("type", tr("风格"));
        tagsList << tagMap;
    }

    m_xcmb.insert("tags", tagsList);

    int cover = ui->wpCoverRadioButton->isChecked() ? 1 : 0;
    m_xcmb.insert("pagetype", cover);

    m_tmpFile = m_tmpDir + "page.dat";
    QFile jf(m_tmpFile);
    if (!jf.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QByteArray result = QtJson::serialize(m_xcmb);
    jf.write(result);
    jf.close();

    qDebug() << __FILE__ << __LINE__ << m_tmpFile;

    char type = ui->wpCoverRadioButton->isChecked() ? 'C' : 'P';
    QDateTime dt = QDateTime::currentDateTime();
    QString tmplName = QString("MP_%1_P%2_%3_").arg(type).arg(m_landscapeCount + m_portraitCount).arg(dt.toString("yyyyMMddhhmm"));
    QString name = ui->nameLineEdit->text();
    if (!name.isEmpty())
    {
        tmplName += name;
    }

    QString pkgFile = QString("%1%2%3").arg(m_dirName).arg(tmplName).arg(PKG_FMT);
    QFile file(pkgFile);
    if (file.exists())
    {
        QMessageBox::warning(this,
                             tr("保存失败"),
                             tr("目录\"%1\"下已经存在一个同名的相册模板\"%2\"，请更名后再重新进行保存！").arg(m_dirName).arg(tmplName),
                             tr("确定"));
        return;
    }

    //qDebug() << __FILE__ << __LINE__ << m_dirName << tmplName << m_pkgFile << pkgFile;
    moveTo(m_psdPic, m_dirName);
    moveTo(m_pkgFile, m_dirName);
    QFile::rename(m_pkgFile, pkgFile);
    m_pkgFile = pkgFile;
#endif

    change();
    //useZip(ZipUsageAppend, m_pkgFile + " " + m_tmpFile);
    //qDebug() << __FILE__ << __LINE__ << "new name:" << m_pkgFile;
    //ui->savePushButton->setEnabled(false);
}

inline void TemplateParserDlg::useZip(ZipUsage usage, const QString &arguments)
{
#if 1
    if (arguments.isEmpty())
    {
        return;
    }

    QString program("tmaker.exe");

    m_usage = usage;

    switch (usage)
    {
    case ZipUsageCompress:
        program += QString(" -c ");
        break;
    case ZipUsageAppend:
        program += QString(" -a ");
        break;
    case ZipUsageRemove:
        program += QString(" -x ");
        break;
    case ZipUsageUncompress:
        program += QString(" -u ");
        break;
    case ZipUsageList:
        program += QString(" -l ");
        break;
    case ZipUsageRead:
        program += QString(" -r ");
        break;
    case ZipUsageEncrypt:
        program += QString(" -e ");
        break;
    case ZipUsageDecrypt:
        program += QString(" -d ");
        break;
    default:
        return;
    }

    program += arguments;
    m_tmaker.start(program);
    //m_tmaker.waitForStarted();
    m_tmaker.waitForFinished();
#endif
}
