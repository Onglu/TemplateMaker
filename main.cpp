#include "TemplateParserDlg.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");    // utf-8 GB18030
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale() /*codec*/);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale() /*codec*/);

    TemplateParserDlg w;
    w.show();
    
    return a.exec();
}
