#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMqttClient>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void updateLogStateChange();        // 更新日志状态
    void brokerDisconnected();          // 断开连接
    void setClientPort(int p);          // 设置客户端端口
    void on_buttonQuit_clicked();       // 退出
    void on_buttonConnect_clicked();    // 连接
    void on_buttonPublish_clicked();    // 发布
    void on_buttonSubscribe_clicked();  // 订阅
    void on_buttonPing_clicked();       // ping
    void on_button_sim_data_clicked();  // 发送模拟数据
    void on_buttonLED_clicked();        // LED
    void on_buttonAlarm_clicked();      // 蜂鸣器
    void send_sim_data();               // 发送模拟数据

private:
    void initView();                    // 初始化视图
    void initSlots();                   // 初始化槽函数
    void setBeepState(int on);          // 设置蜂鸣器状态
    void setLEDState(int on);           // 设置LED状态
    void initGPIO();                    // 初始化GPIO

    Ui::MainWindow* ui;
    QMqttClient* m_client;
    QTimer* timer;
};

#endif // MAINWINDOW_H
