#ifndef TEMPLATEPARSERDLG_H
#define TEMPLATEPARSERDLG_H

#include <QDialog>
#include <QVariant>
#include <QProcess>
#include <QThread>
#include <QTimer>
#include <QFile>
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
//        QString program(MAKER_NAME /*"G:\\Projects\\Qt\\tmaker.exe"*/);
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

protected:
    void closeEvent(QCloseEvent *);

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

    void on_tmplToolButton_clicked();

    void on_browsePushButton_clicked();

    void on_savePushButton_clicked();

    void end();

    void ok();

    void make();

    void processFinished(int, QProcess::ExitStatus);

    void selectType(){m_changed = true;}

    void on_nameLineEdit_textChanged(const QString &arg1);

private:
    void setTag(int type, bool checked, const QString &name = QString());

    void addTag(const QCheckBox *check);

    void updateWnd(void);

    bool deleteDir(const QString &dirName, bool delSelf = true);

    void mkTempDir(void);

    bool moveTo(QString &fileName, QString dirName, bool overwrite = true);

    void change(void);

    void lock(void);

    void unlock(void);

    static void redirect(int line, const QString &message);

    Ui::TemplateParserDlg *ui;

    QVariantMap m_xcmb, m_tags;
    QString m_dirName, m_picFile, m_pkgFile, m_pkgName, m_tmpDir, m_tmpFile, m_wndTitle;

    PSD_LAYERS_INFO *m_pInfo;
    QSize m_bkSize;

    static QProcess m_tmaker;
    PsdParserThread m_parser;
    CryptThread m_maker;
    QTimer m_timer;

    FILE *m_pkg, *m_pic;

    bool m_finished, m_make, m_opened, m_changed;
    static ZipUsage m_usage;
};

#endif // TEMPLATEPARSERDLG_H
