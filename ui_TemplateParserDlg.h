/********************************************************************************
** Form generated from reading UI file 'TemplateParserDlg.ui'
**
** Created: Thu Jul 11 11:33:44 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPLATEPARSERDLG_H
#define UI_TEMPLATEPARSERDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TemplateParserDlg
{
public:
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *psdToolButton;
    QToolButton *tmplToolButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *pictureLabel;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *sizeLabel;
    QLabel *noteLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *wpCoverRadioButton;
    QRadioButton *wpPageRadioButton;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QCheckBox *typeChildrenCheckBox;
    QCheckBox *typePictorialCheckBox;
    QCheckBox *typeWeddingCheckBox;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QCheckBox *styleFramelessCheckBox;
    QCheckBox *styleFrameCheckBox;
    QCheckBox *styleNonmaskCheckBox;
    QCheckBox *styleMaskCheckBox;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLineEdit *styleLineEdit;
    QLabel *label_11;
    QLabel *label_6;
    QGridLayout *gridLayout_2;
    QCheckBox *colorPurpleCheckBox;
    QCheckBox *colorOrangeCheckBox;
    QCheckBox *colorPinkCheckBox;
    QCheckBox *colorGreenCheckBox;
    QLabel *label_7;
    QCheckBox *colorGrayCheckBox;
    QCheckBox *colorCoffeeCheckBox;
    QCheckBox *colorCyanCheckBox;
    QCheckBox *colorYellowCheckBox;
    QCheckBox *colorRedCheckBox;
    QCheckBox *colorWhiteCheckBox;
    QCheckBox *colorBlackCheckBox;
    QCheckBox *colorBlueCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLineEdit *pathLineEdit;
    QPushButton *browsePushButton;
    QLabel *label_9;
    QLineEdit *nameLineEdit;
    QLabel *label_10;
    QPushButton *savePushButton;
    QSpacerItem *verticalSpacer;
    QProgressBar *progressBar;

    void setupUi(QDialog *TemplateParserDlg)
    {
        if (TemplateParserDlg->objectName().isEmpty())
            TemplateParserDlg->setObjectName(QString::fromUtf8("TemplateParserDlg"));
        TemplateParserDlg->resize(816, 560);
        TemplateParserDlg->setMinimumSize(QSize(680, 560));
        gridLayout_4 = new QGridLayout(TemplateParserDlg);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        psdToolButton = new QToolButton(TemplateParserDlg);
        psdToolButton->setObjectName(QString::fromUtf8("psdToolButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(psdToolButton->sizePolicy().hasHeightForWidth());
        psdToolButton->setSizePolicy(sizePolicy);
        psdToolButton->setMinimumSize(QSize(0, 31));

        horizontalLayout_3->addWidget(psdToolButton);

        tmplToolButton = new QToolButton(TemplateParserDlg);
        tmplToolButton->setObjectName(QString::fromUtf8("tmplToolButton"));
        sizePolicy.setHeightForWidth(tmplToolButton->sizePolicy().hasHeightForWidth());
        tmplToolButton->setSizePolicy(sizePolicy);
        tmplToolButton->setMinimumSize(QSize(0, 31));

        horizontalLayout_3->addWidget(tmplToolButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 0, 1, 2);

        pictureLabel = new QLabel(TemplateParserDlg);
        pictureLabel->setObjectName(QString::fromUtf8("pictureLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pictureLabel->sizePolicy().hasHeightForWidth());
        pictureLabel->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        pictureLabel->setFont(font);
        pictureLabel->setFrameShape(QFrame::Box);
        pictureLabel->setFrameShadow(QFrame::Raised);
        pictureLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(pictureLabel, 1, 0, 1, 1);

        frame = new QFrame(TemplateParserDlg);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        sizeLabel = new QLabel(frame);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sizeLabel->sizePolicy().hasHeightForWidth());
        sizeLabel->setSizePolicy(sizePolicy3);
        sizeLabel->setMinimumSize(QSize(0, 20));
        sizeLabel->setFont(font);
        sizeLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        sizeLabel->setFrameShape(QFrame::NoFrame);
        sizeLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(sizeLabel);

        noteLabel = new QLabel(frame);
        noteLabel->setObjectName(QString::fromUtf8("noteLabel"));
        sizePolicy3.setHeightForWidth(noteLabel->sizePolicy().hasHeightForWidth());
        noteLabel->setSizePolicy(sizePolicy3);
        noteLabel->setMinimumSize(QSize(0, 16));
        noteLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        noteLabel->setFrameShape(QFrame::NoFrame);

        verticalLayout_2->addWidget(noteLabel);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy3.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy3);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        wpCoverRadioButton = new QRadioButton(groupBox);
        wpCoverRadioButton->setObjectName(QString::fromUtf8("wpCoverRadioButton"));

        verticalLayout->addWidget(wpCoverRadioButton);

        wpPageRadioButton = new QRadioButton(groupBox);
        wpPageRadioButton->setObjectName(QString::fromUtf8("wpPageRadioButton"));

        verticalLayout->addWidget(wpPageRadioButton);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        typeChildrenCheckBox = new QCheckBox(groupBox_2);
        typeChildrenCheckBox->setObjectName(QString::fromUtf8("typeChildrenCheckBox"));
        typeChildrenCheckBox->setMinimumSize(QSize(71, 0));
        typeChildrenCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout->addWidget(typeChildrenCheckBox);

        typePictorialCheckBox = new QCheckBox(groupBox_2);
        typePictorialCheckBox->setObjectName(QString::fromUtf8("typePictorialCheckBox"));
        typePictorialCheckBox->setMinimumSize(QSize(71, 0));
        typePictorialCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout->addWidget(typePictorialCheckBox);

        typeWeddingCheckBox = new QCheckBox(groupBox_2);
        typeWeddingCheckBox->setObjectName(QString::fromUtf8("typeWeddingCheckBox"));
        typeWeddingCheckBox->setMinimumSize(QSize(71, 0));
        typeWeddingCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout->addWidget(typeWeddingCheckBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        styleFramelessCheckBox = new QCheckBox(groupBox_2);
        styleFramelessCheckBox->setObjectName(QString::fromUtf8("styleFramelessCheckBox"));
        styleFramelessCheckBox->setMinimumSize(QSize(71, 0));
        styleFramelessCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout_2->addWidget(styleFramelessCheckBox);

        styleFrameCheckBox = new QCheckBox(groupBox_2);
        styleFrameCheckBox->setObjectName(QString::fromUtf8("styleFrameCheckBox"));
        styleFrameCheckBox->setMinimumSize(QSize(71, 0));
        styleFrameCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout_2->addWidget(styleFrameCheckBox);

        styleNonmaskCheckBox = new QCheckBox(groupBox_2);
        styleNonmaskCheckBox->setObjectName(QString::fromUtf8("styleNonmaskCheckBox"));
        styleNonmaskCheckBox->setMinimumSize(QSize(71, 0));
        styleNonmaskCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout_2->addWidget(styleNonmaskCheckBox);

        styleMaskCheckBox = new QCheckBox(groupBox_2);
        styleMaskCheckBox->setObjectName(QString::fromUtf8("styleMaskCheckBox"));
        styleMaskCheckBox->setMinimumSize(QSize(71, 0));
        styleMaskCheckBox->setMaximumSize(QSize(71, 16777215));

        horizontalLayout_2->addWidget(styleMaskCheckBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(6);
        gridLayout->setVerticalSpacing(3);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy4);
        label_5->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        styleLineEdit = new QLineEdit(groupBox_2);
        styleLineEdit->setObjectName(QString::fromUtf8("styleLineEdit"));

        gridLayout->addWidget(styleLineEdit, 0, 1, 1, 1);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy4.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy4);
        label_11->setMinimumSize(QSize(36, 20));
        label_11->setMaximumSize(QSize(36, 20));

        gridLayout->addWidget(label_11, 1, 0, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(161, 161, 161);"));

        gridLayout->addWidget(label_6, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        colorPurpleCheckBox = new QCheckBox(groupBox_2);
        colorPurpleCheckBox->setObjectName(QString::fromUtf8("colorPurpleCheckBox"));
        sizePolicy.setHeightForWidth(colorPurpleCheckBox->sizePolicy().hasHeightForWidth());
        colorPurpleCheckBox->setSizePolicy(sizePolicy);
        colorPurpleCheckBox->setMinimumSize(QSize(71, 0));
        colorPurpleCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorPurpleCheckBox, 2, 4, 1, 1);

        colorOrangeCheckBox = new QCheckBox(groupBox_2);
        colorOrangeCheckBox->setObjectName(QString::fromUtf8("colorOrangeCheckBox"));
        sizePolicy.setHeightForWidth(colorOrangeCheckBox->sizePolicy().hasHeightForWidth());
        colorOrangeCheckBox->setSizePolicy(sizePolicy);
        colorOrangeCheckBox->setMinimumSize(QSize(71, 0));
        colorOrangeCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorOrangeCheckBox, 1, 3, 1, 1);

        colorPinkCheckBox = new QCheckBox(groupBox_2);
        colorPinkCheckBox->setObjectName(QString::fromUtf8("colorPinkCheckBox"));
        sizePolicy.setHeightForWidth(colorPinkCheckBox->sizePolicy().hasHeightForWidth());
        colorPinkCheckBox->setSizePolicy(sizePolicy);
        colorPinkCheckBox->setMinimumSize(QSize(71, 0));
        colorPinkCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorPinkCheckBox, 1, 2, 1, 1);

        colorGreenCheckBox = new QCheckBox(groupBox_2);
        colorGreenCheckBox->setObjectName(QString::fromUtf8("colorGreenCheckBox"));
        sizePolicy.setHeightForWidth(colorGreenCheckBox->sizePolicy().hasHeightForWidth());
        colorGreenCheckBox->setSizePolicy(sizePolicy);
        colorGreenCheckBox->setMinimumSize(QSize(71, 0));
        colorGreenCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorGreenCheckBox, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        colorGrayCheckBox = new QCheckBox(groupBox_2);
        colorGrayCheckBox->setObjectName(QString::fromUtf8("colorGrayCheckBox"));
        sizePolicy.setHeightForWidth(colorGrayCheckBox->sizePolicy().hasHeightForWidth());
        colorGrayCheckBox->setSizePolicy(sizePolicy);
        colorGrayCheckBox->setMinimumSize(QSize(71, 0));
        colorGrayCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorGrayCheckBox, 0, 3, 1, 1);

        colorCoffeeCheckBox = new QCheckBox(groupBox_2);
        colorCoffeeCheckBox->setObjectName(QString::fromUtf8("colorCoffeeCheckBox"));
        sizePolicy.setHeightForWidth(colorCoffeeCheckBox->sizePolicy().hasHeightForWidth());
        colorCoffeeCheckBox->setSizePolicy(sizePolicy);
        colorCoffeeCheckBox->setMinimumSize(QSize(71, 0));
        colorCoffeeCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorCoffeeCheckBox, 0, 4, 1, 1);

        colorCyanCheckBox = new QCheckBox(groupBox_2);
        colorCyanCheckBox->setObjectName(QString::fromUtf8("colorCyanCheckBox"));
        sizePolicy.setHeightForWidth(colorCyanCheckBox->sizePolicy().hasHeightForWidth());
        colorCyanCheckBox->setSizePolicy(sizePolicy);
        colorCyanCheckBox->setMinimumSize(QSize(71, 0));
        colorCyanCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorCyanCheckBox, 2, 1, 1, 1);

        colorYellowCheckBox = new QCheckBox(groupBox_2);
        colorYellowCheckBox->setObjectName(QString::fromUtf8("colorYellowCheckBox"));
        sizePolicy.setHeightForWidth(colorYellowCheckBox->sizePolicy().hasHeightForWidth());
        colorYellowCheckBox->setSizePolicy(sizePolicy);
        colorYellowCheckBox->setMinimumSize(QSize(71, 0));
        colorYellowCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorYellowCheckBox, 1, 4, 1, 1);

        colorRedCheckBox = new QCheckBox(groupBox_2);
        colorRedCheckBox->setObjectName(QString::fromUtf8("colorRedCheckBox"));
        sizePolicy.setHeightForWidth(colorRedCheckBox->sizePolicy().hasHeightForWidth());
        colorRedCheckBox->setSizePolicy(sizePolicy);
        colorRedCheckBox->setMinimumSize(QSize(71, 0));
        colorRedCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorRedCheckBox, 1, 1, 1, 1);

        colorWhiteCheckBox = new QCheckBox(groupBox_2);
        colorWhiteCheckBox->setObjectName(QString::fromUtf8("colorWhiteCheckBox"));
        sizePolicy.setHeightForWidth(colorWhiteCheckBox->sizePolicy().hasHeightForWidth());
        colorWhiteCheckBox->setSizePolicy(sizePolicy);
        colorWhiteCheckBox->setMinimumSize(QSize(71, 0));
        colorWhiteCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorWhiteCheckBox, 0, 2, 1, 1);

        colorBlackCheckBox = new QCheckBox(groupBox_2);
        colorBlackCheckBox->setObjectName(QString::fromUtf8("colorBlackCheckBox"));
        sizePolicy.setHeightForWidth(colorBlackCheckBox->sizePolicy().hasHeightForWidth());
        colorBlackCheckBox->setSizePolicy(sizePolicy);
        colorBlackCheckBox->setMinimumSize(QSize(71, 0));
        colorBlackCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorBlackCheckBox, 0, 1, 1, 1);

        colorBlueCheckBox = new QCheckBox(groupBox_2);
        colorBlueCheckBox->setObjectName(QString::fromUtf8("colorBlueCheckBox"));
        sizePolicy.setHeightForWidth(colorBlueCheckBox->sizePolicy().hasHeightForWidth());
        colorBlueCheckBox->setSizePolicy(sizePolicy);
        colorBlueCheckBox->setMinimumSize(QSize(71, 0));
        colorBlueCheckBox->setMaximumSize(QSize(71, 16777215));

        gridLayout_2->addWidget(colorBlueCheckBox, 2, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 5, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy3.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy3);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 0, 0, 1, 1);

        pathLineEdit = new QLineEdit(groupBox_3);
        pathLineEdit->setObjectName(QString::fromUtf8("pathLineEdit"));
        pathLineEdit->setReadOnly(true);

        gridLayout_3->addWidget(pathLineEdit, 0, 1, 1, 1);

        browsePushButton = new QPushButton(groupBox_3);
        browsePushButton->setObjectName(QString::fromUtf8("browsePushButton"));

        gridLayout_3->addWidget(browsePushButton, 0, 2, 1, 1);

        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 1, 0, 1, 1);

        nameLineEdit = new QLineEdit(groupBox_3);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        gridLayout_3->addWidget(nameLineEdit, 1, 1, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(161, 161, 161);"));

        gridLayout_3->addWidget(label_10, 1, 2, 1, 1);


        verticalLayout_2->addWidget(groupBox_3);

        savePushButton = new QPushButton(frame);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));
        savePushButton->setMinimumSize(QSize(0, 31));

        verticalLayout_2->addWidget(savePushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout_4->addWidget(frame, 1, 1, 1, 1);

        progressBar = new QProgressBar(TemplateParserDlg);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(500);
        progressBar->setValue(0);

        gridLayout_4->addWidget(progressBar, 2, 0, 1, 2);


        retranslateUi(TemplateParserDlg);

        QMetaObject::connectSlotsByName(TemplateParserDlg);
    } // setupUi

    void retranslateUi(QDialog *TemplateParserDlg)
    {
        TemplateParserDlg->setWindowTitle(QApplication::translate("TemplateParserDlg", "\347\233\270\345\206\214\346\250\241\346\235\277\347\224\237\346\210\220\345\267\245\345\205\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        TemplateParserDlg->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        psdToolButton->setText(QApplication::translate("TemplateParserDlg", "\346\211\223\345\274\200PSD", 0, QApplication::UnicodeUTF8));
        tmplToolButton->setText(QApplication::translate("TemplateParserDlg", "\346\211\223\345\274\200\346\250\241\346\235\277", 0, QApplication::UnicodeUTF8));
        pictureLabel->setText(QApplication::translate("TemplateParserDlg", "\346\225\210\346\236\234\351\242\204\350\247\210\345\233\276", 0, QApplication::UnicodeUTF8));
        sizeLabel->setText(QApplication::translate("TemplateParserDlg", "\346\250\241\346\235\277\345\244\247\345\260\217\357\274\2320x0", 0, QApplication::UnicodeUTF8));
        noteLabel->setText(QApplication::translate("TemplateParserDlg", "\346\263\250\357\274\232\344\273\245\344\270\213\346\250\241\346\235\277\345\217\202\346\225\260\351\231\244\351\243\216\346\240\274\345\222\214\346\250\241\346\235\277\345\220\215\347\247\260\344\273\245\345\244\226\357\274\214\345\205\266\344\275\231\345\235\207\344\270\272\345\277\205\345\241\253\351\241\271\357\274\201", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TemplateParserDlg", "\346\250\241\346\235\277\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        wpCoverRadioButton->setText(QApplication::translate("TemplateParserDlg", "\346\211\213\346\234\272\345\260\201\351\235\242 Cover", 0, QApplication::UnicodeUTF8));
        wpPageRadioButton->setText(QApplication::translate("TemplateParserDlg", "\346\211\213\346\234\272\345\206\205\351\241\265 Page", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("TemplateParserDlg", "\346\250\241\346\235\277\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TemplateParserDlg", "\347\247\215\347\261\273\357\274\232", 0, QApplication::UnicodeUTF8));
        typeChildrenCheckBox->setText(QApplication::translate("TemplateParserDlg", "\345\204\277\347\253\245", 0, QApplication::UnicodeUTF8));
        typePictorialCheckBox->setText(QApplication::translate("TemplateParserDlg", "\345\206\231\347\234\237", 0, QApplication::UnicodeUTF8));
        typeWeddingCheckBox->setText(QApplication::translate("TemplateParserDlg", "\345\251\232\347\272\261", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TemplateParserDlg", "\347\211\210\345\274\217\357\274\232", 0, QApplication::UnicodeUTF8));
        styleFramelessCheckBox->setText(QApplication::translate("TemplateParserDlg", "\346\227\240\347\205\247\347\211\207\346\241\206", 0, QApplication::UnicodeUTF8));
        styleFrameCheckBox->setText(QApplication::translate("TemplateParserDlg", "\346\234\211\347\205\247\347\211\207\346\241\206", 0, QApplication::UnicodeUTF8));
        styleNonmaskCheckBox->setText(QApplication::translate("TemplateParserDlg", "\346\227\240\351\201\256\347\275\251", 0, QApplication::UnicodeUTF8));
        styleMaskCheckBox->setText(QApplication::translate("TemplateParserDlg", "\346\234\211\351\201\256\347\275\251", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TemplateParserDlg", "\351\243\216\346\240\274\357\274\232", 0, QApplication::UnicodeUTF8));
        label_11->setText(QString());
        label_6->setText(QApplication::translate("TemplateParserDlg", "\345\244\232\347\247\215\351\243\216\346\240\274\344\271\213\351\227\264\350\257\267\347\224\250\347\251\272\346\240\274\351\232\224\345\274\200", 0, QApplication::UnicodeUTF8));
        colorPurpleCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\264\253\350\211\262", 0, QApplication::UnicodeUTF8));
        colorOrangeCheckBox->setText(QApplication::translate("TemplateParserDlg", "\346\251\231\350\211\262       ", 0, QApplication::UnicodeUTF8));
        colorPinkCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\262\211\350\211\262", 0, QApplication::UnicodeUTF8));
        colorGreenCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\273\277\350\211\262", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("TemplateParserDlg", "\350\211\262\347\263\273\357\274\232", 0, QApplication::UnicodeUTF8));
        colorGrayCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\201\260\350\211\262", 0, QApplication::UnicodeUTF8));
        colorCoffeeCheckBox->setText(QApplication::translate("TemplateParserDlg", "\345\222\226\345\225\241\350\211\262", 0, QApplication::UnicodeUTF8));
        colorCyanCheckBox->setText(QApplication::translate("TemplateParserDlg", "\351\235\222\350\211\262", 0, QApplication::UnicodeUTF8));
        colorYellowCheckBox->setText(QApplication::translate("TemplateParserDlg", "\351\273\204\350\211\262", 0, QApplication::UnicodeUTF8));
        colorRedCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\272\242\350\211\262", 0, QApplication::UnicodeUTF8));
        colorWhiteCheckBox->setText(QApplication::translate("TemplateParserDlg", "\347\231\275\350\211\262", 0, QApplication::UnicodeUTF8));
        colorBlackCheckBox->setText(QApplication::translate("TemplateParserDlg", "\351\273\221\350\211\262", 0, QApplication::UnicodeUTF8));
        colorBlueCheckBox->setText(QApplication::translate("TemplateParserDlg", "\350\223\235\350\211\262", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("TemplateParserDlg", "\344\277\235\345\255\230\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("TemplateParserDlg", "\346\234\254\345\234\260\347\233\256\345\275\225\357\274\232", 0, QApplication::UnicodeUTF8));
        browsePushButton->setText(QApplication::translate("TemplateParserDlg", "\346\265\217\350\247\210...", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("TemplateParserDlg", "\346\250\241\346\235\277\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("TemplateParserDlg", "\357\274\210\345\217\257\347\234\201\347\225\245\357\274\211", 0, QApplication::UnicodeUTF8));
        savePushButton->setText(QApplication::translate("TemplateParserDlg", "\344\277\235\345\255\230\344\270\272\346\250\241\346\235\277", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TemplateParserDlg: public Ui_TemplateParserDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPLATEPARSERDLG_H
