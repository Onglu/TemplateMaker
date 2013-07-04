#include "TemplateParserDlg.h"
#include "ui_TemplateParserDlg.h"
#include "json.h"
#include <QDebug>
#include <QFileDialog>
#include <QUuid>
#include <QSettings>
#include <QDateTime>
#include <QMessageBox>

#define CHANGED_SUFFIX  " *"
#define TEMP_FOLDER     "tlpt"
#define TEMP_FILE       "/DDECF6B7F103CFC11B2.png"
#define PREVIEW_PICTURE "preview.png"
#define PKG_FMT         ".xcmb"
#define PKG_PASSWORD    "123123"
#define PKG_LEN_FIXED   21
#define PKG_ENCRYPT     0
#define LOG_TRACE       0

using namespace QtJson;

QProcess TemplateParserDlg::m_tmaker;
TemplateParserDlg::ZipUsage TemplateParserDlg::m_usage = TemplateParserDlg::ZipUsageCompress;

TemplateParserDlg::TemplateParserDlg(QWidget *parent) :
    QDialog(parent, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint),
    ui(new Ui::TemplateParserDlg),
    m_pInfo(NULL),
    m_pkg(NULL),
    m_pic(NULL),
    m_finished(false),
    m_make(false),
    m_opened(false),
    m_changed(false)
{
    ui->setupUi(this);

    m_wndTitle = windowTitle();

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

    connect(ui->wpCoverRadioButton, SIGNAL(clicked()), SLOT(selectType()));
    connect(ui->wpPageRadioButton, SIGNAL(clicked()), SLOT(selectType()));

    connect(&m_timer, SIGNAL(timeout()), SLOT(end()));
    connect(&m_parser, SIGNAL(finished()), SLOT(ok()), Qt::BlockingQueuedConnection);

#if PKG_ENCRYPT
    connect(&m_maker, SIGNAL(finished()), SLOT(make()), Qt::BlockingQueuedConnection);
#endif

    connect(&m_tmaker, SIGNAL(finished(int,QProcess::ExitStatus)), SLOT(processFinished(int,QProcess::ExitStatus)));

#if LOG_TRACE
    QFile file(QDir::tempPath() + "/tlpt/.message.log");
    if (file.open(QIODevice::WriteOnly))
    {
        file.close();
    }
#endif

    //QFile::copy("C:\\Users\\Onglu\\Desktop\\test\\branch.png", "G:\\Images\\PSD\\branch.png");
}

TemplateParserDlg::~TemplateParserDlg()
{
//    if (m_opened && !m_pkgFile.isEmpty())
//    {
//        hide();
//        useZip(ZipUsageEncrypt, m_pkgFile + " " + PKG_PASSWORD);
//    }

    if (m_timer.isActive())
    {
        m_timer.stop();
    }

    psd_release(m_pInfo);

    deleteDir(tr("%1/%2").arg(QDir::tempPath()).arg(TEMP_FOLDER), false);

    if (QFile::exists(m_tmpFile))
    {
        redirect(__LINE__, m_tmpFile);
        QFile::remove(m_tmpFile);
    }

    unlock();

    delete ui;
}

void TemplateParserDlg::redirect(int line, const QString &message)
{
#if LOG_TRACE
    //QFile file(QDir::tempPath() + "/tlpt/.message.log");
    QFile file("message.log");
    if (file.open(QIODevice::Text | QIODevice::Append))
    {
        char buf[270] = {0};
        snprintf(buf, 270, "%d: %s\n", line, message.toStdString().c_str());
        file.write(buf);
        file.close();
    }
#else
    qDebug() << __FILE__ << line << message;
#endif
}

bool TemplateParserDlg::deleteDir(const QString &dirName, bool delSelf)
{
    //qDebug() << __FILE__ << __LINE__ << dirName;

    QDir directory(dirName);
    if (dirName.isEmpty() || !directory.exists())
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
            if (!deleteDir(filePath))
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

inline void TemplateParserDlg::mkTempDir()
{
    if (!m_xcmb.contains("id"))
    {
        return;
    }

    QString tmpDir(QDir::tempPath() + "/tlpt"), id = m_xcmb["id"].toString();
    QDir dir(tmpDir);

    if (!dir.exists())
    {
        dir.mkdir(tmpDir);
    }

    dir.mkdir(id);
    m_tmpDir = QDir::toNativeSeparators(QString("%1/%2/").arg(tmpDir).arg(id));
}

bool TemplateParserDlg::moveTo(QString &fileName, QString dirName, bool overwrite)
{
    QFile file(fileName);
    if (!file.exists())
    {
        return false;
    }

    QChar sep = QDir::separator();
    QString tl(sep), oldDir, name = fileName.right(fileName.length() - fileName.lastIndexOf(sep) - 1);
    if (tl != dirName.right(1))
    {
        dirName = QDir::toNativeSeparators(dirName) + tl;
    }

    oldDir = fileName.left(fileName.lastIndexOf(QDir::separator()) + 1);
    QDir dir(dirName);
    if (!dir.exists() || oldDir == dirName)
    {
        return false;
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
            return false;
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

    return true;
}

void TemplateParserDlg::change()
{
#if PKG_ENCRYPT
    if (!m_make)
    {
        useZip(ZipUsageAppend, m_pkgFile + " " + m_tmpFile, true);
        if (QFile::exists(m_tmpFile))
        {
            QFile::remove(m_tmpFile);
        }
        m_tmpFile.clear();
    }

    ui->psdToolButton->setEnabled(false);
    ui->tmplToolButton->setEnabled(false);
    ui->frame->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);

    m_finished = false;
    m_make = !m_make;
    m_maker.crypt(m_make, m_pkgFile + " " + PKG_PASSWORD);
    m_maker.start();
    m_timer.start(m_make ? 30 : 50);
#else
    if (!m_xcmb.isEmpty())
    {
        useZip(ZipUsageAppend, m_pkgFile + " " + m_tmpFile, true);
        if (QFile::exists(m_tmpFile))
        {
            QFile::remove(m_tmpFile);
        }
        m_tmpFile.clear();

        setWindowTitle(tr("%1 - %2").arg(m_wndTitle).arg(m_pkgFile));

        if (QMessageBox::AcceptRole == QMessageBox::information(this, tr("保存成功"), tr("相册模板包已经保存成功！"), tr("确定")))
        {
            qDebug() << __FILE__ << __LINE__ << m_pkgFile << m_picFile;
            lock();
        }
    }
    else
    {
        useZip(ZipUsageRead, m_pkgFile + " page.dat");
    }
#endif
}

inline void TemplateParserDlg::lock()
{
    if (m_pkg)
    {
        fclose(m_pkg);
    }

    m_pkg = fopen(m_pkgFile.toStdString().c_str(), "rb");

    if (m_pic)
    {
        fclose(m_pic);
    }

    m_pic = fopen(m_picFile.toStdString().c_str(), "rb");
}

void TemplateParserDlg::unlock()
{
    if (m_pkg)
    {
        fclose(m_pkg);
        m_pkg = NULL;
    }

    if (m_pic)
    {
        fclose(m_pic);
        m_pic = NULL;
    }
}

void TemplateParserDlg::make()
{
    if (!m_finished)
    {
        m_finished = true;
        //qDebug() << __FILE__ << __LINE__ << m_make;

        if (!m_make)
        {
            if (m_xcmb.size())
            {
                useZip(ZipUsageAppend, m_pkgFile + " " + m_tmpFile, true);
                useZip(ZipUsageEncrypt, m_pkgFile + " " + PKG_PASSWORD, true);
            }
            else
            {
                useZip(ZipUsageRead, m_pkgFile + " page.dat");
            }

            //qDebug() << __FILE__ << __LINE__ << program;

            if (QFile::exists(m_tmpFile))
            {
                QFile::remove(m_tmpFile);
            }

            m_tmpFile.clear();
        }

        //m_maker.quit();
    }
}

void CryptThread::run()
{
    TemplateParserDlg::useZip(m_encrypt ? TemplateParserDlg::ZipUsageEncrypt : TemplateParserDlg::ZipUsageDecrypt,
                              m_arg,
                              true);
    emit finished();
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
            moveTo(m_picFile, m_tmpDir);
            deleteDir(content.mid(9));
            qDebug() << __FILE__ << __LINE__ << m_tmpDir << content.mid(9);
        }

        if (ZipUsageAppend == m_usage && !m_pkgFile.isEmpty())
        {
            qDebug() << __FILE__ << __LINE__ << m_pkgFile;
        }

        if (content.startsWith("data:"))
        {
            bool ok;
            QString data = content.mid(5);
            //qDebug() << __FILE__ << __LINE__ << data;

            if (data.isEmpty())
            {
                ui->psdToolButton->setEnabled(true);
                ui->tmplToolButton->setEnabled(true);
                redirect(__LINE__, "empty data");
                return;
            }

            m_xcmb = QtJson::parse(data, ok).toMap();
            QVariantMap bkSize = m_xcmb["size"].toMap();
            m_bkSize.setWidth(bkSize["width"].toInt());
            m_bkSize.setHeight(bkSize["height"].toInt());
            //qDebug() << __FILE__ << __LINE__ << m_xcmb;

            #if !PKG_ENCRYPT
            m_finished = true;
            end();

            mkTempDir();

            QVariantList tags = m_xcmb["tags"].toList();
            foreach (const QVariant &tag, tags)
            {
                QVariantMap data = tag.toMap();
                QString name = data["name"].toString();
                QString type = data["type"].toString();
                //qDebug() << __FILE__ << __LINE__ << name << ":" << type;

                if (tr("风格") != type)
                {
                    if (tr("种类") == type)
                    {
                        setTag(1, true, name);
                    }
                    else if (tr("版式") == type)
                    {
                        setTag(2, true, name);
                    }
                    else if (tr("色系") == type)
                    {
                        setTag(3, true, name);
                    }

                    m_tags.insert(name, type);
                }
                else
                {
                    ui->styleLineEdit->setText(name);
                }
            }

            //useZip(ZipUsageRead, m_pkgFile + " " + m_xcmb["name"].toString() + ".jpg");
            useZip(ZipUsageRead, m_pkgFile + " preview.png");
            #endif
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

    deleteDir(m_tmpDir);
    m_tmpDir.clear();

    m_pkgFile.clear();
    m_pkgName.clear();

    m_xcmb.clear();
    m_tags.clear();

    fileName = QDir::toNativeSeparators(fileName);
    setWindowTitle(tr("%1 - %2").arg(m_wndTitle).arg(fileName));

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

        QString uuid = QUuid::createUuid().toString().mid(1, 36);
        strcpy(m_pInfo->layers[i].lid, uuid.toStdString().c_str());
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

    ui->psdToolButton->setEnabled(false);
    ui->tmplToolButton->setEnabled(false);
    ui->wpCoverRadioButton->setChecked(false);
    ui->wpPageRadioButton->setChecked(false);

    ui->frame->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);

    ui->pictureLabel->clear();
    ui->sizeLabel->setText(tr("模板大小：0x0"));

    ui->styleLineEdit->clear();
    ui->nameLineEdit->clear();

    setTag(1, false);
    setTag(2, false);
    setTag(3, false);

    m_changed = true;
    m_finished = m_make = false;
    m_parser.initLayersInfo(m_pInfo);
    m_parser.start();
    m_timer.start(60);
}

void TemplateParserDlg::on_tmplToolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("选择文件"), m_dirName, tr("相册模板 (*.xcmb)"));
    if (fileName.isEmpty())
    {
        return;
    }

    fileName = QDir::toNativeSeparators(fileName);
    if (m_pkgFile == fileName)
    {
        return;
    }

    setWindowTitle(tr("%1 - %2").arg(m_wndTitle).arg(fileName));

    QString filePath = fileName.left(fileName.lastIndexOf(QDir::separator()));
    ui->pathLineEdit->setText(filePath);
    m_dirName = filePath.append(QDir::separator());

    QString name = fileName.mid(m_dirName.length(), fileName.length() - m_dirName.length() - strlen(PKG_FMT));
    if (PKG_LEN_FIXED < name.length())
    {
        m_pkgName = name.right(name.length() - PKG_LEN_FIXED);
    }
    else
    {
        m_pkgName.clear();
    }
    ui->nameLineEdit->setText(m_pkgName);

    m_pkgFile = fileName;
    int pos = fileName.lastIndexOf(PKG_FMT, -1, Qt::CaseInsensitive);
    if (-1 != pos)
    {
        m_picFile = fileName.replace(pos, strlen(PKG_FMT), ".png");
    }

    m_changed = m_make = m_opened = true;
    m_xcmb.clear();
    m_tags.clear();

    ui->psdToolButton->setEnabled(false);
    ui->tmplToolButton->setEnabled(false);
    ui->wpCoverRadioButton->setChecked(false);
    ui->wpPageRadioButton->setChecked(false);
    ui->styleLineEdit->clear();

    setTag(1, false);
    setTag(2, false);
    setTag(3, false);

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
        ui->sizeLabel->setText(tr("模板大小：%1x%2").arg(m_bkSize.width()).arg(m_bkSize.height()));

        if (!m_xcmb.contains("pagetype"))
        {
            if (720 == m_bkSize.width())
            {
                if (1080 == m_bkSize.height())
                {
                    ui->wpCoverRadioButton->setChecked(true);
                }

                if (1280 == m_bkSize.height())
                {
                    ui->wpPageRadioButton->setChecked(true);
                }
            }
        }
        else
        {
            int page = m_xcmb["pagetype"].toInt();
            if (1 == page)
            {
                ui->wpCoverRadioButton->setChecked(true);
            }
            else
            {
                ui->wpPageRadioButton->setChecked(true);
            }
        }
    }
    else
    {
        if (m > ++v)
        {
            ui->progressBar->setValue(v);
            QString pro = m_parser.isRunning() ? tr("解析进度：") : tr("生成进度：");
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
        QString tmplDir = file.replace(pos, 4, "_png"), tmplName = m_xcmb["name"].toString();
        tmplDir.append("\\");
        m_picFile = QString("%1%2.psd.png").arg(tmplDir).arg(tmplName);

        mkTempDir();
        m_pkgFile = QString("%1%2%3").arg(m_tmpDir).arg(tmplName).arg(PKG_FMT);
        redirect(__LINE__, m_pkgFile);

        QVariantList list;
        int landscapeCount = 0, portraitCount = 0;

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

            QString name = tmplDir + QString("%1.png").arg(m_pInfo->layers[i].lid);
            QImage img(name);

            if (m_pInfo->layers[i].type)
            {
                if ((int)m_pInfo->layers[i].angle)
                {
                    img = img.transformed(QTransform().rotate(-1 * m_pInfo->layers[i].angle));
                    m_pInfo->layers[i].actual.width = img.width();
                    m_pInfo->layers[i].actual.height = img.height();
                }

                if (LT_Photo == m_pInfo->layers[i].type)
                {
                    if (orientation)
                    {
                        landscapeCount++;
                    }
                    else
                    {
                        portraitCount++;
                    }

                    QFile::remove(name);
                    pos = name.lastIndexOf("png", -1, Qt::CaseInsensitive);
                    name.replace(pos, 3, "jpg");
                    img.save(name);
                    //qDebug() << __FILE__ << __LINE__ << name;
                }

                if (LT_Mask == m_pInfo->layers[i].type && QString(m_pInfo->layers[i].name).contains("lmask", Qt::CaseInsensitive))
                {
                    QVector<QRgb> rgbVector = img.colorTable();
                    for (int i = 0; i < rgbVector.size(); ++i)
                    {
                        QColor clr(rgbVector.at(i));
                        clr.setAlpha((clr.red() + clr.blue() + clr.green()) / 3);
                        img.setColor(i, clr.rgba());
                    }
                }
            }

            if (name.endsWith("png"))
            {
                img.save(name, "png", 0);
            }

            //qDebug() << __FILE__ << __LINE__ << name;
            //qDebug() << __FILE__ << __LINE__ << m_pInfo->layers[i].type << m_pInfo->layers[i].name << m_pInfo->layers[i].lid;

            QVariantMap frame;
            frame.insert("width", m_pInfo->layers[i].actual.width);
            frame.insert("height", m_pInfo->layers[i].actual.height);
            frame.insert("x", m_pInfo->layers[i].center.x);
            frame.insert("y", m_pInfo->layers[i].center.y);
            layer.insert("frame", frame);
            list << layer;
        }

        m_xcmb.insert("layers", list);
        m_xcmb.insert("landscapeCount", landscapeCount);
        m_xcmb.insert("portraitCount", portraitCount);

        qDebug() << __FILE__ << __LINE__ << m_picFile << tmplDir + PREVIEW_PICTURE;
        QPixmap pix(m_picFile);
        if (!pix.isNull())
        {
            ui->pictureLabel->setPixmap(pix.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            QString picFile = m_picFile;
            m_picFile = tmplDir + PREVIEW_PICTURE;
            QFile::rename(picFile, m_picFile);
        }

        if (list.size())
        {
            useZip(ZipUsageCompress, m_pkgFile + " " + tmplDir);
        }
    }

    m_finished = true;
    m_parser.quit();
}

void TemplateParserDlg::setTag(int type, bool checked, const QString &name)
{
    if (checked && name.isEmpty())
    {
        return;
    }

    if (1 == type)
    {
        if (!checked)
        {
            ui->typeChildrenCheckBox->setChecked(checked);
            ui->typePictorialCheckBox->setChecked(checked);
            ui->typeWeddingCheckBox->setChecked(checked);
        }
        else
        {
            if (name == ui->typeChildrenCheckBox->text())
            {
                ui->typeChildrenCheckBox->setChecked(checked);
            }
            else if (name == ui->typePictorialCheckBox->text())
            {
                ui->typePictorialCheckBox->setChecked(checked);
            }
            else if (name == ui->typeWeddingCheckBox->text())
            {
                ui->typeWeddingCheckBox->setChecked(checked);
            }
        }
    }
    else if (2 == type)
    {
        if (!checked)
        {
            ui->styleFramelessCheckBox->setChecked(checked);
            ui->styleFrameCheckBox->setChecked(checked);
            ui->styleNonmaskCheckBox->setChecked(checked);
            ui->styleMaskCheckBox->setChecked(checked);
        }
        else
        {
            if (name == ui->styleFramelessCheckBox->text())
            {
                ui->styleFramelessCheckBox->setChecked(checked);
            }
            else if (name == ui->styleFrameCheckBox->text())
            {
                ui->styleFrameCheckBox->setChecked(checked);
            }
            else if (name == ui->styleNonmaskCheckBox->text())
            {
                ui->styleNonmaskCheckBox->setChecked(checked);
            }
            else if (name == ui->styleMaskCheckBox->text())
            {
                ui->styleMaskCheckBox->setChecked(checked);
            }
        }
    }
    else if (3 == type)
    {
        if (!checked)
        {
            ui->colorBlackCheckBox->setChecked(checked);
            ui->colorWhiteCheckBox->setChecked(checked);
            ui->colorGrayCheckBox->setChecked(checked);
            ui->colorCoffeeCheckBox->setChecked(checked);
            ui->colorRedCheckBox->setChecked(checked);
            ui->colorPinkCheckBox->setChecked(checked);
            ui->colorOrangeCheckBox->setChecked(checked);
            ui->colorYellowCheckBox->setChecked(checked);
            ui->colorCyanCheckBox->setChecked(checked);
            ui->colorGreenCheckBox->setChecked(checked);
            ui->colorBlueCheckBox->setChecked(checked);
            ui->colorPurpleCheckBox->setChecked(checked);
        }
        else
        {
            if (name == ui->colorBlackCheckBox->text())
            {
                ui->colorBlackCheckBox->setChecked(checked);
            }
            else if (name == ui->colorWhiteCheckBox->text())
            {
                ui->colorWhiteCheckBox->setChecked(checked);
            }
            else if (name == ui->colorGrayCheckBox->text())
            {
                ui->colorGrayCheckBox->setChecked(checked);
            }
            else if (name == ui->colorCoffeeCheckBox->text())
            {
                ui->colorCoffeeCheckBox->setChecked(checked);
            }
            if (name == ui->colorRedCheckBox->text())
            {
                ui->colorRedCheckBox->setChecked(checked);
            }
            else if (name == ui->colorPinkCheckBox->text())
            {
                ui->colorPinkCheckBox->setChecked(checked);
            }
            else if (name == ui->colorOrangeCheckBox->text())
            {
                ui->colorOrangeCheckBox->setChecked(checked);
            }
            else if (name == ui->colorYellowCheckBox->text())
            {
                ui->colorYellowCheckBox->setChecked(checked);
            }
            if (name == ui->colorCyanCheckBox->text())
            {
                ui->colorCyanCheckBox->setChecked(checked);
            }
            else if (name == ui->colorGreenCheckBox->text())
            {
                ui->colorGreenCheckBox->setChecked(checked);
            }
            else if (name == ui->colorBlueCheckBox->text())
            {
                ui->colorBlueCheckBox->setChecked(checked);
            }
            else if (name == ui->colorPurpleCheckBox->text())
            {
                ui->colorPurpleCheckBox->setChecked(checked);
            }
        }
    }
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
        value = tr("版式");
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
        m_tags.insert(name, value);
    }
    else
    {
        m_tags.remove(name);
    }

    updateWnd();
}

inline void TemplateParserDlg::updateWnd()
{
    if (!m_changed)
    {
        m_changed = true;
    }

    QString title = windowTitle();
    if (CHANGED_SUFFIX != title.right(2))
    {
        setWindowTitle(title + CHANGED_SUFFIX);
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

void TemplateParserDlg::on_nameLineEdit_textChanged(const QString &arg1)
{
    if (m_pkgName != arg1)
    {
        updateWnd();
    }
}

void TemplateParserDlg::on_browsePushButton_clicked()
{
    m_dirName = QFileDialog::getExistingDirectory(this, tr("选择文件夹"), m_dirName);
    if (m_dirName.isEmpty())
    {
        return;
    }

    ui->pathLineEdit->setText(m_dirName);
    m_dirName.append(QDir::separator());

    QSettings settings("Jizhiyou", "TemplateParser");
    settings.setValue("dir_name", m_dirName);
}

void TemplateParserDlg::on_savePushButton_clicked()
{
    if (!m_changed || m_pkgFile.isEmpty())
    {
        return;
    }

    if (!ui->wpCoverRadioButton->isChecked() && !ui->wpPageRadioButton->isChecked())
    {
        QMessageBox::warning(this, tr("缺少类型"), tr("请选择一种模板类型！"), tr("确定"));
        return;
    }

    if (!ui->typeChildrenCheckBox->isChecked() && !ui->typePictorialCheckBox->isChecked() && !ui->typeWeddingCheckBox->isChecked())
    {
        QMessageBox::warning(this, tr("缺少种类"), tr("请选择一种模板种类！"), tr("确定"));
        return;
    }

    if (!ui->styleFramelessCheckBox->isChecked() && !ui->styleFrameCheckBox->isChecked()
       && !ui->styleNonmaskCheckBox->isChecked() && !ui->styleMaskCheckBox->isChecked())
    {
        QMessageBox::warning(this, tr("缺少版式"), tr("请选择一种模板版式！"), tr("确定"));
        return;
    }

    if (!ui->colorBlackCheckBox->isChecked() && !ui->colorWhiteCheckBox->isChecked()
       && !ui->colorGrayCheckBox->isChecked() && !ui->colorCoffeeCheckBox->isChecked()
       && !ui->colorRedCheckBox->isChecked() && !ui->colorPinkCheckBox->isChecked()
       && !ui->colorOrangeCheckBox->isChecked() && !ui->colorYellowCheckBox->isChecked()
       && !ui->colorCyanCheckBox->isChecked() && !ui->colorGreenCheckBox->isChecked()
       && !ui->colorBlueCheckBox->isChecked() && !ui->colorPurpleCheckBox->isChecked())
    {
        QMessageBox::warning(this, tr("缺少色系"), tr("请选择一种模板色系！"), tr("确定"));
        return;
    }

    QString savePath = ui->pathLineEdit->text();
    if (savePath.isEmpty())
    {
        if (QMessageBox::AcceptRole == QMessageBox::question(this,
                                                             tr("无效路径"),
                                                             tr("本地目录不能为空，请点击确定按钮进行选择，点击取消按钮则放弃本次操作。"),
                                                             tr("确定"),
                                                             tr("取消")))
        {
            on_browsePushButton_clicked();
        }

        return;
    }

    savePath.append(QDir::separator());

    QVariantList tagsList;
    QVariantMap::const_iterator iter = m_tags.constBegin();
    while (iter != m_tags.constEnd())
    {
        QVariantMap tagMap;
        tagMap.insert("name", iter.key());
        tagMap.insert("type", iter.value());
        tagsList << tagMap;
        //qDebug() << __FILE__ << __LINE__ << iter.key() << ":" << iter.value().toString();
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

    if (0 == m_xcmb["landscapeCount"].toInt() + m_xcmb["portraitCount"].toInt() &&
        QMessageBox::RejectRole == QMessageBox::question(this,
                                                         tr("无效路径"),
                                                         tr("该模板中未发现类型为照片的图层，请检查PSD文件中照片图层的命名格式是否\n符合“名称+@photo”规范？若要继续生成，请点击确定按钮，否则点击取消按钮放弃本次操作。"),
                                                         tr("确定"),
                                                         tr("取消")))
    {
        return;
    }

    int cover = ui->wpCoverRadioButton->isChecked() ? 1 : 0;
    m_xcmb.insert("pagetype", cover);

    QString name = ui->nameLineEdit->text();
    m_xcmb.insert("name", name);

    m_tmpFile = m_tmpDir + "page.dat";
    QFile jf(m_tmpFile);
    if (!jf.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QByteArray result = QtJson::serialize(m_xcmb);
    jf.write(result);
    jf.close();

    //qDebug() << __FILE__ << __LINE__ << m_tmpFile;

    int count = m_xcmb["landscapeCount"].toInt() + m_xcmb["portraitCount"].toInt();
    QDateTime dt = QDateTime::currentDateTime();
    QString tmplName = QString("MP_%1_P%2_%3_").arg(cover ? 'C' : 'P').arg(count).arg(dt.toString("yyyyMMddhhmm"));
    if (!name.isEmpty())
    {
        tmplName += name;
    }

    QString pkgFile = QString("%1%2%3").arg(savePath).arg(tmplName).arg(PKG_FMT);
    QFile file(pkgFile);

    redirect(__LINE__, savePath + ", " + tmplName + ", " + m_pkgFile + ", " + pkgFile);

    if (file.exists())
    {
        QMessageBox::warning(this,
                             tr("保存失败"),
                             tr("目录下已经存在一个同名的相册模板\"%2\"，请更名后再进行保存！").arg(savePath).arg(tmplName),
                             tr("确定"));
        return;
    }

    unlock();

    QString picFile = tr("%1%2.png").arg(savePath).arg(tmplName);
    qDebug() << __FILE__ << __LINE__ << m_picFile << picFile;
    //moveTo(m_picFile, savePath);
    //QFile::rename(m_picFile, picFile);

    if (QFile::exists(m_picFile))
    {
        QFile::rename(m_picFile, picFile);
    }
    else
    {
        QFile::copy(m_picFile, picFile);
    }

    m_picFile = picFile;

    //moveTo(m_pkgFile, savePath);
    //QFile::rename(m_pkgFile, pkgFile);

    if (QFile::exists(m_pkgFile))
    {
        QFile::rename(m_pkgFile, pkgFile);
    }
    else
    {
        QFile::copy(m_pkgFile, pkgFile);
    }

    m_pkgFile = pkgFile;

    m_changed = false;
    redirect(__LINE__, m_pkgFile);

#if PKG_ENCRYPT
    if (m_opened)
    {
        m_make = m_opened = false;
    }
#endif

    change();
}

void TemplateParserDlg::useZip(ZipUsage usage, const QString &arguments, bool block)
{
    if (arguments.isEmpty())
    {
        return;
    }

    QString program(MAKER_NAME);
    //QString program = QDir::toNativeSeparators(QCoreApplication::applicationDirPath() + MAKER_NAME);
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
    redirect(__LINE__, program);

    if (!block)
    {
        m_tmaker.start(program);
        m_tmaker.waitForFinished();
    }
    else
    {
        m_tmaker.execute(program);
    }
}


