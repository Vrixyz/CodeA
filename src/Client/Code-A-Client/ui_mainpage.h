/********************************************************************************
** Form generated from reading UI file 'mainpage.ui'
**
** Created: Wed Feb 13 20:47:25 2013
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPAGE_H
#define UI_MAINPAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_MainPage
{
public:
    QPushButton *pushButton;
    QTabWidget *tabWidget;
    QWidget *news;
    QWebView *webView;
    QWidget *server;
    QTableWidget *tableWidget;
    QTextBrowser *textBrowser_2;
    QWidget *success;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_2;
    QProgressBar *progressBar;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QWidget *MainPage)
    {
        if (MainPage->objectName().isEmpty())
            MainPage->setObjectName(QString::fromUtf8("MainPage"));
        MainPage->resize(800, 600);
        pushButton = new QPushButton(MainPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 95, 31));
        tabWidget = new QTabWidget(MainPage);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(40, 50, 341, 531));
        news = new QWidget();
        news->setObjectName(QString::fromUtf8("news"));
        webView = new QWebView(news);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setGeometry(QRect(20, 10, 301, 471));
        webView->setUrl(QUrl(QString::fromUtf8("http://gamecodea.wordpress.com/")));
        tabWidget->addTab(news, QString());
        server = new QWidget();
        server->setObjectName(QString::fromUtf8("server"));
        tableWidget = new QTableWidget(server);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 311, 271));
        tableWidget->horizontalHeader()->setDefaultSectionSize(154);
        textBrowser_2 = new QTextBrowser(server);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(10, 290, 311, 192));
        tabWidget->addTab(server, QString());
        success = new QWidget();
        success->setObjectName(QString::fromUtf8("success"));
        tabWidget->addTab(success, QString());
        textBrowser = new QTextBrowser(MainPage);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(410, 80, 351, 461));
        pushButton_2 = new QPushButton(MainPage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 40, 141, 31));
        progressBar = new QProgressBar(MainPage);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(570, 40, 191, 31));
        progressBar->setValue(24);
        lineEdit = new QLineEdit(MainPage);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(410, 550, 351, 31));
        label = new QLabel(MainPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(415, 10, 331, 21));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(MainPage);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainPage);
    } // setupUi

    void retranslateUi(QWidget *MainPage)
    {
        MainPage->setWindowTitle(QApplication::translate("MainPage", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainPage", "Menu", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(news), QApplication::translate("MainPage", "News", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainPage", "Server Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainPage", "Population", 0, QApplication::UnicodeUTF8));
        textBrowser_2->setHtml(QApplication::translate("MainPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Server :</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">ip :</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">slots :</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -"
                        "qt-block-indent:0; text-indent:0px;\">status :</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">port :</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">players :</p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(server), QApplication::translate("MainPage", "Server", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(success), QApplication::translate("MainPage", "Success", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainPage", "Auto Matchmaking", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainPage", "User Login", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainPage: public Ui_MainPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPAGE_H
