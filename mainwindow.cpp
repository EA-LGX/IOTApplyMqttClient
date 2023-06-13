#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QTimer>

// Json 解析
#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    initView();    // 初始化视图
    initSlots();   // 初始化槽函数
    initGPIO();
}

MainWindow::~MainWindow() {
    setBeepState(0);
    delete ui;
    delete timer;
}

void MainWindow::initView() {
    // 初始化 MQTT信息
    ui->lineEditHost->setText("11723856a8.st1.iotda-device.cn-south-1.myhuaweicloud.com");
    ui->spinBoxPort->setValue(1883);
    ui->lineEditHost_client_id->setText("648028beb5afea0c91ba57e4_AICharger_0_0_2023060717");
    ui->lineEditHost_user_name->setText("648028beb5afea0c91ba57e4_AICharger");
    ui->lineEditHost_password->setText("1839ad0861ce8e89b4c8819c69de5dd9de27d821893f3751fc127c1a84ca9e9b");
    ui->lineEditTopic->setText("$oc/devices/648028beb5afea0c91ba57e4_AICharger/sys/properties/report");
    ui->lineEditMessage->setText("{\"services\":[{\"service_id\":\"BasicServer\",\"properties\":{\"Temperature\":30,\"Humidity\":34}}]}");
    m_client = new QMqttClient(this);
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPort(ui->spinBoxPort->value());
    m_client->setClientId(ui->lineEditHost_client_id->text());
    m_client->setUsername(ui->lineEditHost_user_name->text());
    m_client->setPassword(ui->lineEditHost_password->text());
}

void MainWindow::initSlots() {
    // 日志状态改变
    connect(m_client, &QMqttClient::stateChanged, this, &MainWindow::updateLogStateChange);
    // 断开连接
    connect(m_client, &QMqttClient::disconnected, this, &MainWindow::brokerDisconnected);
    // 收到消息
    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray& message, const QMqttTopicName& topic) {
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" Received Topic: ")
            + topic.name()
            + QLatin1String(" Message: ")
            + message
            + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);

        // message转为QString
        QString messageStr = QString::fromUtf8(message);

        //message={"paras":{"LightCmd":"ON"},"service_id":"BasicServer","command_name":"SwitchControl"}
        //message={"paras":{"BeepCmd":"ON"},"service_id":"BasicServer","command_name":"SwitchControl"}
        //将message转为json对象
        QJsonDocument jsonDoc = QJsonDocument::fromJson(messageStr.toUtf8());
        QJsonObject jsonObj = jsonDoc.object();
        QString statusKey, statusValue;
        if (jsonObj.value("command_name").toString().contains("LEDControl")) {
            //控制灯
            statusKey = "LightStatus";
            QJsonObject parasObj = jsonObj.value("paras").toObject();
            if (parasObj.value("LightCmd").toString().contains("ON")) {
                //打开LED
                setLEDState(1);
                ui->pushButton_led->setText("关灯");
                ui->editLog->insertPlainText("ON");
                statusValue = "ON";
            }
            else {
                setLEDState(0);
                ui->pushButton_led->setText("开灯");
                ui->editLog->insertPlainText("OFF");
                statusValue = "OFF";
            }
        }
        else {
            //控制蜂鸣器
            statusKey = "BeepStatus";
            QJsonObject parasObj = jsonObj.value("paras").toObject();
            if (parasObj.value("BeepCmd").toString().contains("ON")) {
                //打开蜂鸣器
                setBeepState(1);
                ui->pushButton_alarm->setText("关闭警报");
                ui->editLog->insertPlainText("ON");
                statusValue = "ON";
            }
            else {
                setBeepState(0);
                ui->pushButton_alarm->setText("打开警报");
                ui->editLog->insertPlainText("OFF");
                statusValue = "OFF";
            }
        }

        //接收到消息后，做出响应
        QString topicStr = topic.name();
        QString request_id = topicStr.mid(topicStr.lastIndexOf("=") + 1);
        QString responseTopic = "$oc/devices/648028beb5afea0c91ba57e4_AICharger/sys/commands/response/request_id=" + request_id;
        QString responseBody = "{\"result_code\":0,\"response_name\":\"COMMAND_RESPONSE\",\"paras\":{\"result\":\"success\"}}";
        if (m_client->publish(responseTopic, responseBody.toUtf8()) == -1)
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
        // 更新状态
        QString jsonStr = "{\"services\":[{\"service_id\":\"BasicServer\",\"properties\":{\"%1\":\"%2\"}}]}";
        jsonStr = jsonStr.arg(statusKey).arg(statusValue);
        if (m_client->publish(ui->lineEditTopic->text(), jsonStr.toUtf8()) == -1)
            QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
        ui->editLog->insertPlainText(jsonStr);

        });


    // Ping 响应
    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        ui->buttonPing->setEnabled(true);
        const QString content = QDateTime::currentDateTime().toString()
            + QLatin1String(" PingResponse")
            + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
        });

    // 连接信息文本框监听
    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setClientPort);
    connect(ui->lineEditHost_client_id, &QLineEdit::textChanged, m_client, &QMqttClient::setClientId);
    connect(ui->lineEditHost_user_name, &QLineEdit::textChanged, m_client, &QMqttClient::setUsername);
    connect(ui->lineEditHost_password, &QLineEdit::textChanged, m_client, &QMqttClient::setPassword);
    updateLogStateChange();

    // 定时器
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(send_sim_data()));
    // 定时器开关
    connect(ui->pushButton_sim_data, &QPushButton::clicked, this, &MainWindow::on_button_sim_data_clicked);
    // LED开关
    connect(ui->pushButton_led, &QPushButton::clicked, this, &MainWindow::on_buttonLED_clicked);
    // 蜂鸣器开关
    connect(ui->pushButton_alarm, &QPushButton::clicked, this, &MainWindow::on_buttonAlarm_clicked);
    // 清理日志
    connect(ui->button_clean, &QPushButton::clicked, this, [=]() {
        ui->editLog->clear();
        });
}

void MainWindow::on_buttonLED_clicked() {
    QString LightStatus;
    if (ui->pushButton_led->text().contains("开灯")) {
        setLEDState(1);
        ui->pushButton_led->setText("关灯");
        LightStatus = "ON";
    }
    else {
        setLEDState(0);
        ui->pushButton_led->setText("开灯");
        LightStatus = "OFF";
    }

    // 更新状态
    // "{\"services\":[{\"service_id\":\"BasicData\",\"properties\":{\"luminance\":%1}}]}"转为JSON对象
    QString jsonStr = "{\"services\":[{\"service_id\":\"BasicServer\",\"properties\":{\"LightStatus\":\"%1\"}}]}";
    jsonStr = jsonStr.arg(LightStatus);
    if (m_client->publish(ui->lineEditTopic->text(), jsonStr.toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
    ui->editLog->insertPlainText(jsonStr);
}

void MainWindow::on_buttonAlarm_clicked() {
    QString AlarmStatus;
    if (ui->pushButton_alarm->text().contains("打开警报")) {
        setBeepState(1);
        ui->pushButton_alarm->setText("关闭警报");
        AlarmStatus = "ON";
    }
    else {
        setBeepState(0);
        ui->pushButton_alarm->setText("打开警报");
        AlarmStatus = "OFF";
    }
    // "{\"services\":[{\"service_id\":\"BasicData\",\"properties\":{\"luminance\":%1}}]}"转为JSON对象
    QString jsonStr = "{\"services\":[{\"service_id\":\"BasicServer\",\"properties\":{\"AlarmStatus\":\"%1\"}}]}";
    jsonStr = jsonStr.arg(AlarmStatus);
    if (m_client->publish(ui->lineEditTopic->text(), jsonStr.toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}

void MainWindow::on_buttonConnect_clicked() {
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditHost->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
        ui->lineEditHost_client_id->setEnabled(false);
        ui->lineEditHost_user_name->setEnabled(false);
        ui->lineEditHost_password->setEnabled(false);
        ui->buttonConnect->setText(tr("断开连接"));
        m_client->connectToHost();
    }
    else {
        ui->lineEditHost->setEnabled(true);
        ui->spinBoxPort->setEnabled(true);
        ui->buttonConnect->setText(tr("连接"));
        m_client->disconnectFromHost();
    }
}

void MainWindow::on_buttonQuit_clicked() {
    QApplication::quit();
}

void MainWindow::updateLogStateChange() {
    const QString content = QDateTime::currentDateTime().toString()
        + QLatin1String(": State Change")
        + QString::number(m_client->state())
        + QLatin1Char('\n');
    ui->editLog->insertPlainText(content);
}

void MainWindow::brokerDisconnected() {
    ui->lineEditHost->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->lineEditHost_client_id->setEnabled(true);
    ui->lineEditHost_user_name->setEnabled(true);
    ui->lineEditHost_password->setEnabled(true);
    ui->buttonConnect->setText(tr("连接"));
}

void MainWindow::setClientPort(int p) {
    m_client->setPort(p);
}

void MainWindow::on_buttonPublish_clicked() {
    if (m_client->publish(ui->lineEditTopic->text(), ui->lineEditMessage->text().toUtf8()) == -1)
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}

void MainWindow::on_buttonSubscribe_clicked() {
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}

void MainWindow::on_buttonPing_clicked() {
    ui->buttonPing->setEnabled(false);
    m_client->requestPing();
}

void MainWindow::on_button_sim_data_clicked() {
    timer->setInterval(ui->spinBoxPort_time->value() * 1000);
    timer->setSingleShot(false); // 周期性触发
    if (timer->isActive()) {
        timer->stop();
        ui->pushButton_sim_data->setText("模拟数据");
        ui->spinBoxPort_time->setEnabled(true);
    }
    else {
        timer->start();
        ui->pushButton_sim_data->setText("停止模拟");
        ui->spinBoxPort_time->setEnabled(false);
    }
}

void MainWindow::send_sim_data() {
    QString sendBody = "{\"services\":[{\"service_id\":\"BasicServer\",\"properties\":{\"Temperature\":%1,\"Humidity\":%2,\"LightStatus\":\"%3\",\"AlarmStatus\":\"%4\"}}]}";
    // 生成随机数，并且偏移量为-5~5
    static int tempRandom = 30;
    static int humiRandom = 50;
    QString LightStatus = "ON";
    QString AlarmStatus = "ON";
    if (ui->pushButton_led->text().contains("开灯")) {
        LightStatus = "OFF";
    }
    if (ui->pushButton_alarm->text().contains("打开警报")) {
        AlarmStatus = "OFF";
    }
    do {
        tempRandom += qrand() % 10 - 5;
        humiRandom += qrand() % 10 - 5;
    } while (tempRandom < 0 || tempRandom > 100 || humiRandom < 0 || humiRandom > 100);
    sendBody = sendBody.arg(tempRandom).arg(humiRandom).arg(LightStatus).arg(AlarmStatus);
    ui->lineEditMessage->setText(sendBody);

    if (m_client->publish(ui->lineEditTopic->text(), sendBody.toUtf8()) == -1)

        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
    else
        ui->editLog->insertPlainText("send message: " + sendBody + "\n");
}

void MainWindow::setBeepState(int on) {
#ifdef __arm__
    QString strFile = "/sys/class/gpio/gpio19/value";
    QFile file(strFile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/gpio/gpio19 export failed!";
        return;
    }

    file.write(1 == on ? "1" : "0");
    file.close();
#else
    qDebug() << "state" << on;
#endif
}

void MainWindow::setLEDState(int on) {
#ifdef __arm__
    QString strFile = "/sys/class/gpio/gpio132/value";
    QFile file(strFile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/leds/green/brightness export failed!";
        return;
    }

    file.write(1 == on ? "1" : "0");
    file.close();
#else
    qDebug() << "state" << on;
#endif
}

void MainWindow::initGPIO() {
#ifdef __arm__
    QFile file("/sys/class/gpio/export");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/gpio/export failed!";
        return;
    }
    file.write("19");
    file.write("132");
    file.close();
    //设置GPIO19,GPIO132为输出
    file.setFileName("/sys/class/gpio/gpio19/direction");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/gpio/gpio19/direction failed!";
        return;
    }
    file.write("out");
    file.close();
    file.setFileName("/sys/class/gpio/gpio132/direction");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/gpio/gpio132/direction failed!";
        return;
    }
    file.write("out");
#else
    qDebug() << "Not the ARM Platform";
#endif
}
