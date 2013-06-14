#ifndef TEMPLATEPARSERDLG_H
#define TEMPLATEPARSERDLG_H

#include <QDialog>
#include <QVariant>
#include <QProcess>
#include <QThread>
#include <QTimer>
#include "psdparser.h"

#define MAKER_NAME  "tmaker.exe"

class QCheckBox;

class PsdParserThread : public QThread
{
public:
    void initLayersInfo(PSD_LAYERS_INFO *pInfo){m_pInfo = pInfo;}

protected:
    void run()
    {
        psd_to_png(m_pInfo);
        emit finished();
        //wait();
        exit();
    }

private:
    PSD_LAYERS_INFO *m_pInfo;
};

class CryptThread : public QThread
{
public:
    void crypt(bool enc, const QString &arg)
    {
        m_encrypt = enc;
        m_arg = arg;
    }

protected:
    void run();
//    {
//        QString program(MAKER_NAME /*"G:\\Projects\\Qt\\GitHub\\tmaker.exe"*/);
//        program += m_encrypt ? QString(" -e ") : QString(" -d ");
//        program.append(m_arg);
//        QProcess::execute(program);
//        emit finished();
//        //wait();
//        exit();
//    }

private:
    bool m_encrypt;
    QString m_arg;
};

namespace Ui {
class TemplateParserDlg;
}

class TemplateParserDlg : public QDialog
{
    Q_OBJECT
    
public:
    explicit TemplateParserDlg(QWidget *parent = 0);
    ~TemplateParserDlg();

    enum ZipUsage{ZipUsageCompress,
                  ZipUsageAppend,
                  ZipUsageRemove,
                  ZipUsageUncompress,
                  ZipUsageList,
                  ZipUsageRead,
                  ZipUsageEncrypt,
                  ZipUsageDecrypt
                 };

    static void useZip(ZipUsage usage, const QString &arguments, bool block = false);

signals:
    
private slots:
    void on_typeChildrenCheckBox_clicked();

    void on_typePictorialCheckBox_clicked();

    void on_typeWeddingCheckBox_clicked();

    void on_styleFramelessCheckBox_clicked();

    void on_styleFrameCheckBox_clicked();

    void on_styleNonmaskCheckBox_clicked();

    void on_styleMaskCheckBox_clicked();

    void on_colorBlackCheckBox_clicked();

    void on_colorWhiteCheckBox_clicked();

    void on_colorGrayCheckBox_clicked();

    void on_colorCoffeeCheckBox_clicked();

    void on_colorRedCheckBox_clicked();

    void on_colorPinkCheckBox_clicked();

    void on_colorOrangeCheckBox_clicked();

    void on_colorYellowCheckBox_clicked();

    void on_colorCyanCheckBox_clicked();

    void on_colorGreenCheckBox_clicked();

    void on_colorBlueCheckBox_clicked();

    void on_colorPurpleCheckBox_clicked();

    void on_psdToolButton_clicked();

    void on_browsePushButton_clicked();

    void on_savePushButton_clicked();

    void end();

    void ok();

    void make();

    void processFinished(int, QProcess::ExitStatus);

    void on_tmplToolButton_clicked();

private:
    void addTag(const QCheckBox *check);

    bool deleteDir(const QString &dirName, bool delSelf = true);

    void moveTo(QString &fileName, QString dirName, bool overwrite = true);

    void change(void);

    Ui::TemplateParserDlg *ui;

    QVariantMap m_xcmb, m_tagsMap;
    QString m_dirName, m_psdFile, m_psdPic, m_pkgFile, m_tmpDir, m_tmpFile;

    PSD_LAYERS_INFO *m_pInfo;
    QSize m_bkSize;
    int m_landscapeCount, m_portraitCount;

    static QProcess m_tmaker;
    PsdParserThread m_parser;
    CryptThread m_maker;
    QTimer m_timer;
    bool m_finished, m_make;
    ZipUsage m_usage;
};

#endif // TEMPLATEPARSERDLG_H
