/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *Main;
    QWidget *Loginpage;
    QWidget *formLayoutWidget;
    QFormLayout *Login;
    QLabel *login;
    QLineEdit *logini;
    QLabel *password;
    QLineEdit *passwordi;
    QCheckBox *Remember;
    QPushButton *loginb;
    QSpacerItem *verticalSpacer_2;
    QPushButton *forgotten;
    QSpacerItem *verticalSpacer;
    QPushButton *create;
    QLabel *Title;
    QGraphicsView *Gameview;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        Main = new QWidget(MainWindow);
        Main->setObjectName(QString::fromUtf8("Main"));
        Main->setEnabled(true);
        sizePolicy.setHeightForWidth(Main->sizePolicy().hasHeightForWidth());
        Main->setSizePolicy(sizePolicy);
        Loginpage = new QWidget(Main);
        Loginpage->setObjectName(QString::fromUtf8("Loginpage"));
        Loginpage->setGeometry(QRect(0, 0, 800, 600));
        sizePolicy.setHeightForWidth(Loginpage->sizePolicy().hasHeightForWidth());
        Loginpage->setSizePolicy(sizePolicy);
        formLayoutWidget = new QWidget(Loginpage);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 10, 434, 301));
        Login = new QFormLayout(formLayoutWidget);
        Login->setSpacing(6);
        Login->setContentsMargins(2, 2, 2, 2);
        Login->setObjectName(QString::fromUtf8("Login"));
        Login->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
        Login->setLabelAlignment(Qt::AlignCenter);
        Login->setFormAlignment(Qt::AlignCenter);
        Login->setContentsMargins(0, 0, 0, 0);
        login = new QLabel(formLayoutWidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setAlignment(Qt::AlignCenter);

        Login->setWidget(0, QFormLayout::LabelRole, login);

        logini = new QLineEdit(formLayoutWidget);
        logini->setObjectName(QString::fromUtf8("logini"));

        Login->setWidget(0, QFormLayout::FieldRole, logini);

        password = new QLabel(formLayoutWidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setAlignment(Qt::AlignCenter);

        Login->setWidget(1, QFormLayout::LabelRole, password);

        passwordi = new QLineEdit(formLayoutWidget);
        passwordi->setObjectName(QString::fromUtf8("passwordi"));
        passwordi->setEchoMode(QLineEdit::Password);

        Login->setWidget(1, QFormLayout::FieldRole, passwordi);

        Remember = new QCheckBox(formLayoutWidget);
        Remember->setObjectName(QString::fromUtf8("Remember"));
        Remember->setEnabled(true);
        Remember->setCursor(QCursor(Qt::PointingHandCursor));
        Remember->setLayoutDirection(Qt::LeftToRight);

        Login->setWidget(2, QFormLayout::FieldRole, Remember);

        loginb = new QPushButton(formLayoutWidget);
        loginb->setObjectName(QString::fromUtf8("loginb"));

        Login->setWidget(3, QFormLayout::FieldRole, loginb);

        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->setItem(4, QFormLayout::SpanningRole, verticalSpacer_2);

        forgotten = new QPushButton(formLayoutWidget);
        forgotten->setObjectName(QString::fromUtf8("forgotten"));

        Login->setWidget(5, QFormLayout::SpanningRole, forgotten);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Login->setItem(6, QFormLayout::SpanningRole, verticalSpacer);

        create = new QPushButton(formLayoutWidget);
        create->setObjectName(QString::fromUtf8("create"));

        Login->setWidget(7, QFormLayout::SpanningRole, create);

        Title = new QLabel(Loginpage);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setGeometry(QRect(360, 10, 161, 61));
        QFont font;
        font.setPointSize(20);
        Title->setFont(font);
        Title->setTextFormat(Qt::AutoText);
        Title->setScaledContents(false);
        Title->setAlignment(Qt::AlignCenter);
        Gameview = new QGraphicsView(Main);
        Gameview->setObjectName(QString::fromUtf8("Gameview"));
        Gameview->setGeometry(QRect(0, 0, 800, 600));
        MainWindow->setCentralWidget(Main);
        Gameview->raise();
        Loginpage->raise();
        QWidget::setTabOrder(logini, passwordi);
        QWidget::setTabOrder(passwordi, Remember);
        QWidget::setTabOrder(Remember, loginb);
        QWidget::setTabOrder(loginb, forgotten);
        QWidget::setTabOrder(forgotten, create);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        logini->setInputMask(QString());
        logini->setText(QString());
        password->setText(QApplication::translate("MainWindow", "Password", 0, QApplication::UnicodeUTF8));
        passwordi->setInputMask(QString());
        passwordi->setText(QString());
        Remember->setText(QApplication::translate("MainWindow", "Remember me", 0, QApplication::UnicodeUTF8));
        loginb->setText(QApplication::translate("MainWindow", "Login", 0, QApplication::UnicodeUTF8));
        forgotten->setText(QApplication::translate("MainWindow", "Forgotten your password ?", 0, QApplication::UnicodeUTF8));
        create->setText(QApplication::translate("MainWindow", "Not registered ? Create your account now !", 0, QApplication::UnicodeUTF8));
        Title->setText(QApplication::translate("MainWindow", "Court of God", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
