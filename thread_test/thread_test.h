#ifndef THREAD_TEST_H
#define THREAD_TEST_H

#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QTimer>
class workThread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void process(int val);
public:
    workThread(QObject* parent = 0);
    ~workThread();
    void setSomething();
    void getSomething();
    void setRunCount(int count);
    void run();
    void doSomething();
private:
    int m_runCount;
};
namespace Ui {
class thread_test;
}

class thread_test : public QWidget
{
    Q_OBJECT

public:
    explicit thread_test(QWidget *parent = 0);
    ~thread_test();

private slots:
    void on_pushButton_threadRun_clicked();

    void on_pushButton_threadQuit_clicked();

    void on_pushButton_threadTerminate_clicked();

    void on_pushButton_getSomething_clicked();

    void on_pushButton_setSomething_clicked();

    void on_pushButton_doSomething_clicked();

    void receiveMessage(const QString);

    void process(int);

    void on_thread_finish();

    void heartTimeout();

private:
    Ui::thread_test *ui;
    workThread* m_thread;
    QTimer* m_heart;
};

#endif // THREAD_TEST_H
