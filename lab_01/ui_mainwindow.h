/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *MoveZ;
    QLabel *label_2;
    QLineEdit *MoveY;
    QPushButton *MoveButton;
    QLineEdit *MoveX;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QLabel *label_kz;
    QPushButton *ScaleButton;
    QLineEdit *ScaleZ;
    QLineEdit *ScaleY;
    QLineEdit *ScaleX;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QLineEdit *RotateY;
    QLabel *label_x;
    QPushButton *RotateButton;
    QLineEdit *RotateZ;
    QLabel *label_y;
    QLabel *label_z;
    QLineEdit *RotateX;
    QGraphicsView *graphicsView;
    QPushButton *OpenButton;
    QLineEdit *in_filename;
    QLineEdit *out_filename;
    QPushButton *LoadData;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_4;
    QLabel *label_8;
    QLabel *label_4;
    QLineEdit *RelCenterY;
    QLineEdit *RelCenterZ;
    QLineEdit *RelCenterX;
    QLabel *label_7;
    QLabel *label_9;
    QFrame *line;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1037, 505);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(671, 120, 336, 71));
        gridLayout_3 = new QGridLayout(layoutWidget);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        gridLayout_3->addWidget(label_3, 0, 4, 1, 1);

        MoveZ = new QLineEdit(layoutWidget);
        MoveZ->setObjectName("MoveZ");

        gridLayout_3->addWidget(MoveZ, 0, 5, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        gridLayout_3->addWidget(label_2, 0, 2, 1, 1);

        MoveY = new QLineEdit(layoutWidget);
        MoveY->setObjectName("MoveY");

        gridLayout_3->addWidget(MoveY, 0, 3, 1, 1);

        MoveButton = new QPushButton(layoutWidget);
        MoveButton->setObjectName("MoveButton");

        gridLayout_3->addWidget(MoveButton, 1, 0, 1, 6);

        MoveX = new QLineEdit(layoutWidget);
        MoveX->setObjectName("MoveX");

        gridLayout_3->addWidget(MoveX, 0, 1, 1, 1);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(671, 210, 336, 71));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_kz = new QLabel(layoutWidget1);
        label_kz->setObjectName("label_kz");
        label_kz->setFont(font);

        gridLayout_2->addWidget(label_kz, 0, 4, 1, 1);

        ScaleButton = new QPushButton(layoutWidget1);
        ScaleButton->setObjectName("ScaleButton");

        gridLayout_2->addWidget(ScaleButton, 1, 0, 1, 6);

        ScaleZ = new QLineEdit(layoutWidget1);
        ScaleZ->setObjectName("ScaleZ");

        gridLayout_2->addWidget(ScaleZ, 0, 5, 1, 1);

        ScaleY = new QLineEdit(layoutWidget1);
        ScaleY->setObjectName("ScaleY");

        gridLayout_2->addWidget(ScaleY, 0, 3, 1, 1);

        ScaleX = new QLineEdit(layoutWidget1);
        ScaleX->setObjectName("ScaleX");

        gridLayout_2->addWidget(ScaleX, 0, 1, 1, 1);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName("label_5");
        label_5->setFont(font);

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(671, 300, 336, 71));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        RotateY = new QLineEdit(layoutWidget2);
        RotateY->setObjectName("RotateY");

        gridLayout->addWidget(RotateY, 0, 3, 1, 1);

        label_x = new QLabel(layoutWidget2);
        label_x->setObjectName("label_x");
        label_x->setFont(font);

        gridLayout->addWidget(label_x, 0, 0, 1, 1);

        RotateButton = new QPushButton(layoutWidget2);
        RotateButton->setObjectName("RotateButton");

        gridLayout->addWidget(RotateButton, 1, 0, 1, 6);

        RotateZ = new QLineEdit(layoutWidget2);
        RotateZ->setObjectName("RotateZ");

        gridLayout->addWidget(RotateZ, 0, 5, 1, 1);

        label_y = new QLabel(layoutWidget2);
        label_y->setObjectName("label_y");
        label_y->setFont(font);

        gridLayout->addWidget(label_y, 0, 2, 1, 1);

        label_z = new QLabel(layoutWidget2);
        label_z->setObjectName("label_z");
        label_z->setFont(font);

        gridLayout->addWidget(label_z, 0, 4, 1, 1);

        RotateX = new QLineEdit(layoutWidget2);
        RotateX->setObjectName("RotateX");

        gridLayout->addWidget(RotateX, 0, 1, 1, 1);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(9, 9, 651, 451));
        graphicsView->setMinimumSize(QSize(600, 400));
        OpenButton = new QPushButton(centralwidget);
        OpenButton->setObjectName("OpenButton");
        OpenButton->setGeometry(QRect(890, 400, 111, 24));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OpenButton->sizePolicy().hasHeightForWidth());
        OpenButton->setSizePolicy(sizePolicy);
        in_filename = new QLineEdit(centralwidget);
        in_filename->setObjectName("in_filename");
        in_filename->setGeometry(QRect(671, 400, 211, 24));
        out_filename = new QLineEdit(centralwidget);
        out_filename->setObjectName("out_filename");
        out_filename->setGeometry(QRect(671, 430, 211, 24));
        LoadData = new QPushButton(centralwidget);
        LoadData->setObjectName("LoadData");
        LoadData->setGeometry(QRect(890, 430, 111, 24));
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName("layoutWidget_2");
        layoutWidget_2->setGeometry(QRect(670, 20, 336, 61));
        gridLayout_4 = new QGridLayout(layoutWidget_2);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget_2);
        label_8->setObjectName("label_8");
        label_8->setFont(font);

        gridLayout_4->addWidget(label_8, 1, 2, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        RelCenterY = new QLineEdit(layoutWidget_2);
        RelCenterY->setObjectName("RelCenterY");

        gridLayout_4->addWidget(RelCenterY, 1, 3, 1, 1);

        RelCenterZ = new QLineEdit(layoutWidget_2);
        RelCenterZ->setObjectName("RelCenterZ");

        gridLayout_4->addWidget(RelCenterZ, 1, 5, 1, 1);

        RelCenterX = new QLineEdit(layoutWidget_2);
        RelCenterX->setObjectName("RelCenterX");

        gridLayout_4->addWidget(RelCenterX, 1, 1, 1, 1);

        label_7 = new QLabel(layoutWidget_2);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        gridLayout_4->addWidget(label_7, 1, 4, 1, 1);

        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName("label_9");
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_9, 0, 0, 1, 6);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(670, 90, 331, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1037, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "dx:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "dz:", nullptr));
        MoveZ->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "dy:", nullptr));
        MoveY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        MoveButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\275\320\276\321\201", nullptr));
        MoveX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_kz->setText(QCoreApplication::translate("MainWindow", "kz:", nullptr));
        ScaleButton->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\321\210\321\202\320\260\320\261\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        ScaleZ->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        ScaleY->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        ScaleX->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ky:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "kx:", nullptr));
        RotateY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_x->setText(QCoreApplication::translate("MainWindow", "ox:", nullptr));
        RotateButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\262\320\276\321\200\320\276\321\202", nullptr));
        RotateZ->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_y->setText(QCoreApplication::translate("MainWindow", "oy:", nullptr));
        label_z->setText(QCoreApplication::translate("MainWindow", "oz:", nullptr));
        RotateX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        OpenButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\244\320\260\320\271\320\273", nullptr));
        in_filename->setText(QCoreApplication::translate("MainWindow", "./data/std_data.txt", nullptr));
        out_filename->setText(QCoreApplication::translate("MainWindow", "./data/new_figure.txt", nullptr));
        LoadData->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "y:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "x:", nullptr));
        RelCenterY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        RelCenterZ->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        RelCenterX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "z:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\275\320\276\321\201\320\270\321\202\320\265\320\273\321\214\320\275\321\213\320\271 \321\206\320\265\320\275\321\202\321\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
