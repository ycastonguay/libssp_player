/********************************************************************************
** Form generated from reading UI file 'PlayerForm.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERFORM_H
#define UI_PLAYERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_PlayerForm
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *lblStatus;
    QPushButton *btnPlay;
    QLabel *lblPlaylist;
    QLabel *lblFilePath;
    QLabel *lblPosition;
    QPushButton *btnPause;
    QPushButton *btnStop;
    QPushButton *btnPrevious;
    QPushButton *btnNext;
    QLabel *lblTitle;
    QLabel *lblVersion;

    void setupUi(QDialog *PlayerForm)
    {
        if (PlayerForm->objectName().isEmpty())
            PlayerForm->setObjectName(QStringLiteral("PlayerForm"));
        PlayerForm->resize(463, 300);
        buttonBox = new QDialogButtonBox(PlayerForm);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 421, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lblStatus = new QLabel(PlayerForm);
        lblStatus->setObjectName(QStringLiteral("lblStatus"));
        lblStatus->setGeometry(QRect(10, 70, 381, 18));
        btnPlay = new QPushButton(PlayerForm);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));
        btnPlay->setGeometry(QRect(10, 190, 85, 27));
        lblPlaylist = new QLabel(PlayerForm);
        lblPlaylist->setObjectName(QStringLiteral("lblPlaylist"));
        lblPlaylist->setGeometry(QRect(10, 90, 381, 18));
        lblFilePath = new QLabel(PlayerForm);
        lblFilePath->setObjectName(QStringLiteral("lblFilePath"));
        lblFilePath->setGeometry(QRect(10, 110, 381, 18));
        lblPosition = new QLabel(PlayerForm);
        lblPosition->setObjectName(QStringLiteral("lblPosition"));
        lblPosition->setGeometry(QRect(10, 130, 381, 18));
        btnPause = new QPushButton(PlayerForm);
        btnPause->setObjectName(QStringLiteral("btnPause"));
        btnPause->setGeometry(QRect(100, 190, 85, 27));
        btnStop = new QPushButton(PlayerForm);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        btnStop->setGeometry(QRect(190, 190, 85, 27));
        btnPrevious = new QPushButton(PlayerForm);
        btnPrevious->setObjectName(QStringLiteral("btnPrevious"));
        btnPrevious->setGeometry(QRect(280, 190, 85, 27));
        btnNext = new QPushButton(PlayerForm);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setGeometry(QRect(370, 190, 85, 27));
        lblTitle = new QLabel(PlayerForm);
        lblTitle->setObjectName(QStringLiteral("lblTitle"));
        lblTitle->setGeometry(QRect(10, 10, 381, 18));
        lblVersion = new QLabel(PlayerForm);
        lblVersion->setObjectName(QStringLiteral("lblVersion"));
        lblVersion->setGeometry(QRect(10, 30, 381, 18));

        retranslateUi(PlayerForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), PlayerForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PlayerForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(PlayerForm);
    } // setupUi

    void retranslateUi(QDialog *PlayerForm)
    {
        PlayerForm->setWindowTitle(QApplication::translate("PlayerForm", "libssp_player", 0));
        lblStatus->setText(QApplication::translate("PlayerForm", "[Status]", 0));
        btnPlay->setText(QApplication::translate("PlayerForm", "Play", 0));
        lblPlaylist->setText(QApplication::translate("PlayerForm", "[Playlist]", 0));
        lblFilePath->setText(QApplication::translate("PlayerForm", "[File path]", 0));
        lblPosition->setText(QApplication::translate("PlayerForm", "[Position]", 0));
        btnPause->setText(QApplication::translate("PlayerForm", "Pause", 0));
        btnStop->setText(QApplication::translate("PlayerForm", "Stop", 0));
        btnPrevious->setText(QApplication::translate("PlayerForm", "Previous", 0));
        btnNext->setText(QApplication::translate("PlayerForm", "Next", 0));
        lblTitle->setText(QApplication::translate("PlayerForm", "libssp_player - QT Sample", 0));
        lblVersion->setText(QApplication::translate("PlayerForm", "[Version]", 0));
    } // retranslateUi

};

namespace Ui {
    class PlayerForm: public Ui_PlayerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERFORM_H
