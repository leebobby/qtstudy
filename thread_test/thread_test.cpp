#include "thread_test.h"
#include "ui_thread_test.h"

workThread::workThread(QObject* parent):QThread(parent),m_runCount(20){}

workThread::~workThread()
{
    qDebug()<<"workThread::~workThread";
}
void workThread::setSomething()
{
    sleep(5);
    QString str = QString("%1->%2, thread id: %3.").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
    emit message(str);
}
void workThread::getSomething()
{
    sleep(3);
    emit message(QString("%1->%2, thread id: %3.").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

void workThread::setRunCount(int count)
{
    m_runCount = count;
    emit message(QString("%1->%2, thread id: %3.").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}
void workThread::run()
{
    int count = 0;
    QString str = QString("%1->%2, thread id: %3.").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId());
    emit message(str);
    while(1){
        sleep(1);
        ++count;
        emit process((float)count / m_runCount * 100);
        emit message(QString("workThread::run times:%1").arg(count));
        doSomething();
        if(m_runCount == count)
        {
            break;
        }
    }
}
void workThread::doSomething()
{
    msleep(500);
    emit message(QString("%1->%2, thread id: %3.").arg(__FUNCTION__).arg(__FILE__).arg((int)QThread::currentThreadId()));
}

thread_test::thread_test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::thread_test)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->progressBar_2->setValue(0);

    m_heart = new QTimer(this);
    connect(m_heart,SIGNAL(timeout()),this,SLOT(heartTimeout()));

    m_thread = new workThread(this);
    connect(m_thread,SIGNAL(message(QString)),this,SLOT(receiveMessage(QString)));
    connect(m_thread,SIGNAL(process(int)),this,SLOT(process(int)));
    connect(m_thread,SIGNAL(finished()),this,SLOT(on_thread_finish()));

    m_heart->start(1000);
}

thread_test::~thread_test()
{
    delete ui;
    qDebug()<<"start destory widget";
//    m_thread->stopImmediately();
    m_thread->wait();
    qDebug()<<"end destory widget";
}

void thread_test::heartTimeout()
{
    static int s_heartCount = 0;
    ++s_heartCount;
    if(s_heartCount > 100)
        s_heartCount = 0;
    ui->progressBar_2->setValue(s_heartCount);
}

void thread_test::receiveMessage(const QString str)
{
    qDebug()<<str;
}

void thread_test::process(int val)
{
    ui->progressBar->setValue(val);
}

void thread_test::on_thread_finish()
{
    qDebug()<<"workThread finish";
}

void thread_test::on_pushButton_threadRun_clicked()
{
    ui->progressBar->setValue(0);
    if(m_thread->isRunning())
        return ;
    m_thread->start();
}

void thread_test::on_pushButton_threadQuit_clicked()
{
    qDebug()<<"m_thread->quit() but not work";
    m_thread->quit();
}

void thread_test::on_pushButton_threadTerminate_clicked()
{
    m_thread->terminate();
}

void thread_test::on_pushButton_getSomething_clicked()
{
    m_thread->getSomething();
}

void thread_test::on_pushButton_setSomething_clicked()
{
    m_thread->setSomething();
}

void thread_test::on_pushButton_doSomething_clicked()
{
    m_thread->doSomething();
}
