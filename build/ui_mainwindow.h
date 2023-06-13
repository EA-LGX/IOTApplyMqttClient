/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditHost;
    QLabel *label_client_id;
    QLineEdit *lineEditHost_client_id;
    QLabel *label_user_name;
    QLineEdit *lineEditHost_user_name;
    QLabel *label_password;
    QLineEdit *lineEditHost_password;
    QLabel *label_topic;
    QLineEdit *lineEditTopic;
    QLabel *label_4;
    QLineEdit *lineEditMessage;
    QGridLayout *gridLayout;
    QPushButton *buttonPing;
    QPushButton *buttonPublish;
    QSpinBox *spinBoxPort;
    QPushButton *pushButton_led;
    QPushButton *buttonConnect;
    QLabel *label_2;
    QPushButton *pushButton_alarm;
    QSpinBox *spinBoxPort_time;
    QPushButton *buttonSubscribe;
    QPushButton *pushButton_sim_data;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *editLog;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_clean;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonQuit;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 480);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        formLayout->setHorizontalSpacing(5);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEditHost = new QLineEdit(centralWidget);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditHost);

        label_client_id = new QLabel(centralWidget);
        label_client_id->setObjectName(QString::fromUtf8("label_client_id"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_client_id->sizePolicy().hasHeightForWidth());
        label_client_id->setSizePolicy(sizePolicy);
        label_client_id->setFrameShape(QFrame::NoFrame);

        formLayout->setWidget(4, QFormLayout::LabelRole, label_client_id);

        lineEditHost_client_id = new QLineEdit(centralWidget);
        lineEditHost_client_id->setObjectName(QString::fromUtf8("lineEditHost_client_id"));

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEditHost_client_id);

        label_user_name = new QLabel(centralWidget);
        label_user_name->setObjectName(QString::fromUtf8("label_user_name"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_user_name);

        lineEditHost_user_name = new QLineEdit(centralWidget);
        lineEditHost_user_name->setObjectName(QString::fromUtf8("lineEditHost_user_name"));

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEditHost_user_name);

        label_password = new QLabel(centralWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_password);

        lineEditHost_password = new QLineEdit(centralWidget);
        lineEditHost_password->setObjectName(QString::fromUtf8("lineEditHost_password"));

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEditHost_password);

        label_topic = new QLabel(centralWidget);
        label_topic->setObjectName(QString::fromUtf8("label_topic"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label_topic);

        lineEditTopic = new QLineEdit(centralWidget);
        lineEditTopic->setObjectName(QString::fromUtf8("lineEditTopic"));

        formLayout->setWidget(7, QFormLayout::FieldRole, lineEditTopic);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_4);

        lineEditMessage = new QLineEdit(centralWidget);
        lineEditMessage->setObjectName(QString::fromUtf8("lineEditMessage"));

        formLayout->setWidget(8, QFormLayout::FieldRole, lineEditMessage);


        horizontalLayout->addLayout(formLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonPing = new QPushButton(centralWidget);
        buttonPing->setObjectName(QString::fromUtf8("buttonPing"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonPing->sizePolicy().hasHeightForWidth());
        buttonPing->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(buttonPing, 1, 2, 1, 1);

        buttonPublish = new QPushButton(centralWidget);
        buttonPublish->setObjectName(QString::fromUtf8("buttonPublish"));
        sizePolicy1.setHeightForWidth(buttonPublish->sizePolicy().hasHeightForWidth());
        buttonPublish->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(buttonPublish, 2, 1, 1, 1);

        spinBoxPort = new QSpinBox(centralWidget);
        spinBoxPort->setObjectName(QString::fromUtf8("spinBoxPort"));
        sizePolicy1.setHeightForWidth(spinBoxPort->sizePolicy().hasHeightForWidth());
        spinBoxPort->setSizePolicy(sizePolicy1);
        spinBoxPort->setMaximum(99999);
        spinBoxPort->setValue(1883);

        gridLayout->addWidget(spinBoxPort, 0, 2, 1, 1);

        pushButton_led = new QPushButton(centralWidget);
        pushButton_led->setObjectName(QString::fromUtf8("pushButton_led"));

        gridLayout->addWidget(pushButton_led, 5, 1, 1, 1);

        buttonConnect = new QPushButton(centralWidget);
        buttonConnect->setObjectName(QString::fromUtf8("buttonConnect"));
        buttonConnect->setEnabled(true);
        sizePolicy1.setHeightForWidth(buttonConnect->sizePolicy().hasHeightForWidth());
        buttonConnect->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(buttonConnect, 1, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        pushButton_alarm = new QPushButton(centralWidget);
        pushButton_alarm->setObjectName(QString::fromUtf8("pushButton_alarm"));

        gridLayout->addWidget(pushButton_alarm, 5, 2, 1, 1);

        spinBoxPort_time = new QSpinBox(centralWidget);
        spinBoxPort_time->setObjectName(QString::fromUtf8("spinBoxPort_time"));
        sizePolicy1.setHeightForWidth(spinBoxPort_time->sizePolicy().hasHeightForWidth());
        spinBoxPort_time->setSizePolicy(sizePolicy1);
        spinBoxPort_time->setMaximum(99999);
        spinBoxPort_time->setValue(5);

        gridLayout->addWidget(spinBoxPort_time, 3, 2, 1, 1);

        buttonSubscribe = new QPushButton(centralWidget);
        buttonSubscribe->setObjectName(QString::fromUtf8("buttonSubscribe"));
        sizePolicy1.setHeightForWidth(buttonSubscribe->sizePolicy().hasHeightForWidth());
        buttonSubscribe->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(buttonSubscribe, 2, 2, 1, 1);

        pushButton_sim_data = new QPushButton(centralWidget);
        pushButton_sim_data->setObjectName(QString::fromUtf8("pushButton_sim_data"));
        sizePolicy1.setHeightForWidth(pushButton_sim_data->sizePolicy().hasHeightForWidth());
        pushButton_sim_data->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_sim_data, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        editLog = new QPlainTextEdit(groupBox);
        editLog->setObjectName(QString::fromUtf8("editLog"));

        horizontalLayout_2->addWidget(editLog);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        button_clean = new QPushButton(centralWidget);
        button_clean->setObjectName(QString::fromUtf8("button_clean"));

        horizontalLayout_3->addWidget(button_clean);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonQuit = new QPushButton(centralWidget);
        buttonQuit->setObjectName(QString::fromUtf8("buttonQuit"));

        horizontalLayout_3->addWidget(buttonQuit);


        verticalLayout->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        label->setText(QApplication::translate("MainWindow", "Host:", nullptr));
        lineEditHost->setText(QString());
        label_client_id->setText(QApplication::translate("MainWindow", "ClientID:", nullptr));
        lineEditHost_client_id->setText(QString());
        label_user_name->setText(QApplication::translate("MainWindow", "UserName:", nullptr));
        lineEditHost_user_name->setText(QString());
        label_password->setText(QApplication::translate("MainWindow", "Password:", nullptr));
        lineEditHost_password->setText(QString());
        label_topic->setText(QApplication::translate("MainWindow", "Topic:", nullptr));
        lineEditTopic->setText(QApplication::translate("MainWindow", "qtmqtt/topic1", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Message:", nullptr));
        lineEditMessage->setText(QApplication::translate("MainWindow", "This is a test message", nullptr));
        buttonPing->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
        buttonPublish->setText(QApplication::translate("MainWindow", "\345\217\221\345\270\203", nullptr));
        pushButton_led->setText(QApplication::translate("MainWindow", "\345\274\200\347\201\257", nullptr));
        buttonConnect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        pushButton_alarm->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\350\255\246\346\212\245", nullptr));
        buttonSubscribe->setText(QApplication::translate("MainWindow", "\350\256\242\351\230\205", nullptr));
        pushButton_sim_data->setText(QApplication::translate("MainWindow", "\345\256\232\346\227\266\345\217\221\351\200\201", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        button_clean->setText(QApplication::translate("MainWindow", "\346\270\205\347\220\206", nullptr));
        buttonQuit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
