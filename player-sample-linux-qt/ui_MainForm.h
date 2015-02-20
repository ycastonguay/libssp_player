/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->resize(800, 600);
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainForm->setStatusBar(statusbar);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "MainForm", 0));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
