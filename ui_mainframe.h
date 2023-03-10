/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *buttonOpen;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *buttonDeleteContents;
    QSpacerItem *horizontalSpacer;
    QToolButton *buttonShowList;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QPushButton *buttonSepiaTone;
    QSpinBox *spinHue;
    QDoubleSpinBox *spinSaturation;
    QLabel *label;
    QLabel *label_2;
    QWidget *tab_3;
    QPushButton *buttonOstu;
    QSpinBox *spinThd;
    QPushButton *buttonCustomThd;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *buttonDilation;
    QPushButton *buttonErosion;
    QLabel *label_6;
    QComboBox *Kernelsize;
    QPushButton *buttonLabeling;
    QLabel *label_7;
    QLabel *label_8;
    QWidget *tab_4;
    QPushButton *buttonHistoEq;
    QPushButton *buttonHistoMatching;
    QPushButton *buttonHistoMatchRef;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *buttonSnPNoise;
    QPushButton *buttonGaussianNoise;
    QDoubleSpinBox *spinNSigma;
    QLabel *label_13;
    QPushButton *pushButton_3;
    QLabel *label_14;
    QPushButton *buttonGaussianFiltering;
    QPushButton *buttonMedianFiltering;
    QDoubleSpinBox *spinFSigma;
    QLabel *label_15;
    QComboBox *BFkernelsize;
    QComboBox *MFkernelsize;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QWidget *tab;
    QPushButton *buttonCannyEdge;
    QSpinBox *spinLowThreshold;
    QSpinBox *spinHighThreshold;
    QDoubleSpinBox *spinSigma;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QPushButton *buttonCircleHT;
    QPushButton *buttonGeneralizedHT;
    QLabel *label_23;
    QPushButton *buttonOpticalFlow;
    QLabel *label_24;
    QSpinBox *spinWindowSize;
    QSpinBox *spinOpt;
    QPushButton *buttonOptNext;
    QWidget *tab_5;
    QListWidget *listWidget;

    void setupUi(QDialog *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(622, 461);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainFrame->sizePolicy().hasHeightForWidth());
        MainFrame->setSizePolicy(sizePolicy);
        MainFrame->setMinimumSize(QSize(0, 461));
        MainFrame->setModal(false);
        verticalLayout = new QVBoxLayout(MainFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(MainFrame);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 41));
        frame->setMaximumSize(QSize(16777215, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonOpen = new QToolButton(frame);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));
        buttonOpen->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonOpen->sizePolicy().hasHeightForWidth());
        buttonOpen->setSizePolicy(sizePolicy2);
        buttonOpen->setMinimumSize(QSize(41, 41));
        buttonOpen->setMaximumSize(QSize(41, 41));
        buttonOpen->setLayoutDirection(Qt::LeftToRight);
        buttonOpen->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOpen->setIcon(icon);
        buttonOpen->setIconSize(QSize(41, 41));
        buttonOpen->setCheckable(false);
        buttonOpen->setAutoRepeat(false);
        buttonOpen->setAutoExclusive(false);
        buttonOpen->setPopupMode(QToolButton::DelayedPopup);
        buttonOpen->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonOpen->setAutoRaise(false);

        horizontalLayout_3->addWidget(buttonOpen);

        toolButton_2 = new QToolButton(frame);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);
        toolButton_2->setMinimumSize(QSize(41, 41));
        toolButton_2->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(frame);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);
        toolButton_3->setMinimumSize(QSize(41, 41));
        toolButton_3->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_3);

        buttonDeleteContents = new QToolButton(frame);
        buttonDeleteContents->setObjectName(QString::fromUtf8("buttonDeleteContents"));
        sizePolicy2.setHeightForWidth(buttonDeleteContents->sizePolicy().hasHeightForWidth());
        buttonDeleteContents->setSizePolicy(sizePolicy2);
        buttonDeleteContents->setMinimumSize(QSize(41, 41));
        buttonDeleteContents->setMaximumSize(QSize(41, 41));
        buttonDeleteContents->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/1-21.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteContents->setIcon(icon1);
        buttonDeleteContents->setIconSize(QSize(41, 41));

        horizontalLayout_3->addWidget(buttonDeleteContents);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonShowList = new QToolButton(frame);
        buttonShowList->setObjectName(QString::fromUtf8("buttonShowList"));
        sizePolicy2.setHeightForWidth(buttonShowList->sizePolicy().hasHeightForWidth());
        buttonShowList->setSizePolicy(sizePolicy2);
        buttonShowList->setMinimumSize(QSize(41, 41));
        buttonShowList->setMaximumSize(QSize(41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/2-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonShowList->setIcon(icon2);
        buttonShowList->setIconSize(QSize(82, 41));

        horizontalLayout_3->addWidget(buttonShowList);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, -1, -1);
        tabWidget = new QTabWidget(MainFrame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(299, 394));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush1(QColor(255, 85, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush1);
        tabWidget->setPalette(palette);
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(31, 31));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        buttonSepiaTone = new QPushButton(tab_2);
        buttonSepiaTone->setObjectName(QString::fromUtf8("buttonSepiaTone"));
        buttonSepiaTone->setGeometry(QRect(30, 20, 201, 41));
        spinHue = new QSpinBox(tab_2);
        spinHue->setObjectName(QString::fromUtf8("spinHue"));
        spinHue->setGeometry(QRect(60, 70, 51, 26));
        spinHue->setMaximum(360);
        spinSaturation = new QDoubleSpinBox(tab_2);
        spinSaturation->setObjectName(QString::fromUtf8("spinSaturation"));
        spinSaturation->setGeometry(QRect(160, 70, 71, 26));
        spinSaturation->setMaximum(1.000000000000000);
        spinSaturation->setSingleStep(0.100000000000000);
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 31, 20));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 70, 21, 21));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        buttonOstu = new QPushButton(tab_3);
        buttonOstu->setObjectName(QString::fromUtf8("buttonOstu"));
        buttonOstu->setGeometry(QRect(50, 100, 181, 61));
        spinThd = new QSpinBox(tab_3);
        spinThd->setObjectName(QString::fromUtf8("spinThd"));
        spinThd->setGeometry(QRect(30, 50, 42, 22));
        spinThd->setMaximum(255);
        buttonCustomThd = new QPushButton(tab_3);
        buttonCustomThd->setObjectName(QString::fromUtf8("buttonCustomThd"));
        buttonCustomThd->setGeometry(QRect(120, 20, 161, 61));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 111, 21));
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 80, 291, 21));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(0, 160, 291, 21));
        buttonDilation = new QPushButton(tab_3);
        buttonDilation->setObjectName(QString::fromUtf8("buttonDilation"));
        buttonDilation->setGeometry(QRect(160, 220, 93, 29));
        buttonErosion = new QPushButton(tab_3);
        buttonErosion->setObjectName(QString::fromUtf8("buttonErosion"));
        buttonErosion->setGeometry(QRect(160, 250, 93, 29));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 220, 81, 20));
        Kernelsize = new QComboBox(tab_3);
        Kernelsize->addItem(QString());
        Kernelsize->addItem(QString());
        Kernelsize->setObjectName(QString::fromUtf8("Kernelsize"));
        Kernelsize->setGeometry(QRect(30, 240, 80, 26));
        buttonLabeling = new QPushButton(tab_3);
        buttonLabeling->setObjectName(QString::fromUtf8("buttonLabeling"));
        buttonLabeling->setGeometry(QRect(60, 300, 151, 51));
        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(0, 270, 291, 21));
        label_8 = new QLabel(tab_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 170, 271, 51));
        QFont font;
        font.setPointSize(24);
        label_8->setFont(font);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        buttonHistoEq = new QPushButton(tab_4);
        buttonHistoEq->setObjectName(QString::fromUtf8("buttonHistoEq"));
        buttonHistoEq->setGeometry(QRect(80, 10, 141, 41));
        buttonHistoMatching = new QPushButton(tab_4);
        buttonHistoMatching->setObjectName(QString::fromUtf8("buttonHistoMatching"));
        buttonHistoMatching->setGeometry(QRect(200, 70, 80, 41));
        buttonHistoMatchRef = new QPushButton(tab_4);
        buttonHistoMatchRef->setObjectName(QString::fromUtf8("buttonHistoMatchRef"));
        buttonHistoMatchRef->setGeometry(QRect(110, 70, 80, 41));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(0, 50, 291, 21));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(0, 110, 291, 21));
        label_11 = new QLabel(tab_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 60, 91, 51));
        QFont font1;
        font1.setPointSize(14);
        label_11->setFont(font1);
        label_12 = new QLabel(tab_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(0, 100, 291, 21));
        buttonSnPNoise = new QPushButton(tab_4);
        buttonSnPNoise->setObjectName(QString::fromUtf8("buttonSnPNoise"));
        buttonSnPNoise->setGeometry(QRect(80, 180, 181, 41));
        buttonGaussianNoise = new QPushButton(tab_4);
        buttonGaussianNoise->setObjectName(QString::fromUtf8("buttonGaussianNoise"));
        buttonGaussianNoise->setGeometry(QRect(160, 130, 101, 41));
        spinNSigma = new QDoubleSpinBox(tab_4);
        spinNSigma->setObjectName(QString::fromUtf8("spinNSigma"));
        spinNSigma->setGeometry(QRect(80, 150, 62, 25));
        label_13 = new QLabel(tab_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(90, 130, 41, 21));
        pushButton_3 = new QPushButton(tab_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 240, 91, 31));
        label_14 = new QLabel(tab_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(0, 220, 291, 21));
        buttonGaussianFiltering = new QPushButton(tab_4);
        buttonGaussianFiltering->setObjectName(QString::fromUtf8("buttonGaussianFiltering"));
        buttonGaussianFiltering->setGeometry(QRect(180, 280, 91, 31));
        buttonMedianFiltering = new QPushButton(tab_4);
        buttonMedianFiltering->setObjectName(QString::fromUtf8("buttonMedianFiltering"));
        buttonMedianFiltering->setGeometry(QRect(180, 320, 91, 31));
        spinFSigma = new QDoubleSpinBox(tab_4);
        spinFSigma->setObjectName(QString::fromUtf8("spinFSigma"));
        spinFSigma->setGeometry(QRect(100, 290, 62, 25));
        label_15 = new QLabel(tab_4);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(60, 290, 41, 21));
        BFkernelsize = new QComboBox(tab_4);
        BFkernelsize->addItem(QString());
        BFkernelsize->addItem(QString());
        BFkernelsize->setObjectName(QString::fromUtf8("BFkernelsize"));
        BFkernelsize->setGeometry(QRect(70, 243, 91, 31));
        BFkernelsize->setMaxVisibleItems(2);
        MFkernelsize = new QComboBox(tab_4);
        MFkernelsize->addItem(QString());
        MFkernelsize->addItem(QString());
        MFkernelsize->setObjectName(QString::fromUtf8("MFkernelsize"));
        MFkernelsize->setGeometry(QRect(70, 320, 91, 31));
        label_16 = new QLabel(tab_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 239, 61, 31));
        label_17 = new QLabel(tab_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 319, 61, 31));
        label_18 = new QLabel(tab_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 150, 61, 51));
        label_18->setFont(font1);
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        buttonCannyEdge = new QPushButton(tab);
        buttonCannyEdge->setObjectName(QString::fromUtf8("buttonCannyEdge"));
        buttonCannyEdge->setGeometry(QRect(170, 10, 121, 81));
        buttonCannyEdge->setFont(font1);
        spinLowThreshold = new QSpinBox(tab);
        spinLowThreshold->setObjectName(QString::fromUtf8("spinLowThreshold"));
        spinLowThreshold->setGeometry(QRect(100, 40, 61, 25));
        spinLowThreshold->setMaximum(255);
        spinHighThreshold = new QSpinBox(tab);
        spinHighThreshold->setObjectName(QString::fromUtf8("spinHighThreshold"));
        spinHighThreshold->setGeometry(QRect(100, 70, 61, 25));
        spinHighThreshold->setMaximum(255);
        spinSigma = new QDoubleSpinBox(tab);
        spinSigma->setObjectName(QString::fromUtf8("spinSigma"));
        spinSigma->setGeometry(QRect(100, 10, 62, 25));
        spinSigma->setSingleStep(0.100000000000000);
        label_19 = new QLabel(tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 10, 48, 21));
        label_20 = new QLabel(tab);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 40, 91, 21));
        label_21 = new QLabel(tab);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 70, 91, 21));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(0, 90, 291, 21));
        buttonCircleHT = new QPushButton(tab);
        buttonCircleHT->setObjectName(QString::fromUtf8("buttonCircleHT"));
        buttonCircleHT->setGeometry(QRect(30, 110, 101, 51));
        buttonGeneralizedHT = new QPushButton(tab);
        buttonGeneralizedHT->setObjectName(QString::fromUtf8("buttonGeneralizedHT"));
        buttonGeneralizedHT->setGeometry(QRect(160, 110, 101, 51));
        label_23 = new QLabel(tab);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(0, 160, 291, 21));
        buttonOpticalFlow = new QPushButton(tab);
        buttonOpticalFlow->setObjectName(QString::fromUtf8("buttonOpticalFlow"));
        buttonOpticalFlow->setGeometry(QRect(30, 190, 111, 41));
        QFont font2;
        font2.setPointSize(11);
        buttonOpticalFlow->setFont(font2);
        label_24 = new QLabel(tab);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 250, 81, 21));
        spinWindowSize = new QSpinBox(tab);
        spinWindowSize->setObjectName(QString::fromUtf8("spinWindowSize"));
        spinWindowSize->setGeometry(QRect(110, 250, 42, 22));
        spinWindowSize->setMinimum(1);
        spinOpt = new QSpinBox(tab);
        spinOpt->setObjectName(QString::fromUtf8("spinOpt"));
        spinOpt->setGeometry(QRect(210, 250, 42, 22));
        spinOpt->setMinimum(1);
        spinOpt->setMaximum(16);
        buttonOptNext = new QPushButton(tab);
        buttonOptNext->setObjectName(QString::fromUtf8("buttonOptNext"));
        buttonOptNext->setGeometry(QRect(190, 190, 75, 41));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());

        horizontalLayout->addWidget(tabWidget);

        listWidget = new QListWidget(MainFrame);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);
        listWidget->setMinimumSize(QSize(0, 394));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        QBrush brush6(QColor(120, 120, 120, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        QBrush brush7(QColor(240, 240, 240, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        listWidget->setPalette(palette1);
        QFont font3;
        font3.setPointSize(10);
        listWidget->setFont(font3);

        horizontalLayout->addWidget(listWidget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainFrame);

        tabWidget->setCurrentIndex(3);
        BFkernelsize->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
        MainFrame->setWindowTitle(QCoreApplication::translate("MainFrame", "Homeworks", nullptr));
#if QT_CONFIG(tooltip)
        buttonOpen->setToolTip(QCoreApplication::translate("MainFrame", "open an image file", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonOpen->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
#if QT_CONFIG(tooltip)
        buttonDeleteContents->setToolTip(QCoreApplication::translate("MainFrame", "close all forms", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonDeleteContents->setText(QString());
#if QT_CONFIG(tooltip)
        buttonShowList->setToolTip(QCoreApplication::translate("MainFrame", "show the list view", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonShowList->setText(QString());
        buttonSepiaTone->setText(QCoreApplication::translate("MainFrame", "Sephia Tone", nullptr));
        label->setText(QCoreApplication::translate("MainFrame", "Hue", nullptr));
        label_2->setText(QCoreApplication::translate("MainFrame", "Sat", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainFrame", "1", nullptr));
        buttonOstu->setText(QCoreApplication::translate("MainFrame", "Ostu's Thresholding \n"
"(automatic thresholding)", nullptr));
        buttonCustomThd->setText(QCoreApplication::translate("MainFrame", "Custom Thresholding", nullptr));
        label_3->setText(QCoreApplication::translate("MainFrame", "Threshold Value", nullptr));
        label_4->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        label_5->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        buttonDilation->setText(QCoreApplication::translate("MainFrame", "Dilation", nullptr));
        buttonErosion->setText(QCoreApplication::translate("MainFrame", "Erosion", nullptr));
        label_6->setText(QCoreApplication::translate("MainFrame", "Kernel size", nullptr));
        Kernelsize->setItemText(0, QCoreApplication::translate("MainFrame", "3 x 3", nullptr));
        Kernelsize->setItemText(1, QCoreApplication::translate("MainFrame", "5 x 5", nullptr));

        buttonLabeling->setText(QCoreApplication::translate("MainFrame", "Labeling", nullptr));
        label_7->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        label_8->setText(QCoreApplication::translate("MainFrame", "Thresholding First!", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainFrame", "2", nullptr));
        buttonHistoEq->setText(QCoreApplication::translate("MainFrame", "Histogram Equalization", nullptr));
        buttonHistoMatching->setText(QCoreApplication::translate("MainFrame", "Source\n"
"(Transform)", nullptr));
        buttonHistoMatchRef->setText(QCoreApplication::translate("MainFrame", "Target\n"
"(Reference)", nullptr));
        label_9->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        label_10->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        label_11->setText(QCoreApplication::translate("MainFrame", "Histogram \n"
"Matching", nullptr));
        label_12->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        buttonSnPNoise->setText(QCoreApplication::translate("MainFrame", "Salt && Pepper Noise", nullptr));
        buttonGaussianNoise->setText(QCoreApplication::translate("MainFrame", "Gaussian Noise", nullptr));
        label_13->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainFrame", "Box Filter", nullptr));
        label_14->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        buttonGaussianFiltering->setText(QCoreApplication::translate("MainFrame", "Gaussian Filter", nullptr));
        buttonMedianFiltering->setText(QCoreApplication::translate("MainFrame", "Median Filter", nullptr));
        label_15->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        BFkernelsize->setItemText(0, QCoreApplication::translate("MainFrame", "3 X 3", nullptr));
        BFkernelsize->setItemText(1, QCoreApplication::translate("MainFrame", "5 X 5", nullptr));

        MFkernelsize->setItemText(0, QCoreApplication::translate("MainFrame", "3 X 3", nullptr));
        MFkernelsize->setItemText(1, QCoreApplication::translate("MainFrame", "5 X 5", nullptr));

        label_16->setText(QCoreApplication::translate("MainFrame", "Kernel size", nullptr));
        label_17->setText(QCoreApplication::translate("MainFrame", "Kernel size", nullptr));
        label_18->setText(QCoreApplication::translate("MainFrame", " Add \n"
"Noise", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainFrame", "3", nullptr));
        buttonCannyEdge->setText(QCoreApplication::translate("MainFrame", "Canny Edge \n"
"Operator", nullptr));
        label_19->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        label_20->setText(QCoreApplication::translate("MainFrame", "Low Threshold", nullptr));
        label_21->setText(QCoreApplication::translate("MainFrame", "High Threshold", nullptr));
        label_22->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        buttonCircleHT->setText(QCoreApplication::translate("MainFrame", "Circle \n"
"Hough Transform", nullptr));
        buttonGeneralizedHT->setText(QCoreApplication::translate("MainFrame", "Generalized \n"
"Hough Transform", nullptr));
        label_23->setText(QCoreApplication::translate("MainFrame", "----------------------------------------------------------", nullptr));
        buttonOpticalFlow->setText(QCoreApplication::translate("MainFrame", "Optical Flow", nullptr));
        label_24->setText(QCoreApplication::translate("MainFrame", "Window Size", nullptr));
        buttonOptNext->setText(QCoreApplication::translate("MainFrame", "Next", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainFrame", "4", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainFrame", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
