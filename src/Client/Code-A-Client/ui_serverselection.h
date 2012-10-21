/********************************************************************************
** Form generated from reading UI file 'serverselection.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSELECTION_H
#define UI_SERVERSELECTION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverselection
{
public:

    void setupUi(QWidget *serverselection)
    {
        if (serverselection->objectName().isEmpty())
            serverselection->setObjectName(QString::fromUtf8("serverselection"));
        serverselection->resize(400, 300);

        retranslateUi(serverselection);

        QMetaObject::connectSlotsByName(serverselection);
    } // setupUi

    void retranslateUi(QWidget *serverselection)
    {
        serverselection->setWindowTitle(QApplication::translate("serverselection", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serverselection: public Ui_serverselection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSELECTION_H
