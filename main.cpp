#include "thread_test/thread_test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    thread_test w;
    w.show();

    return a.exec();
}
