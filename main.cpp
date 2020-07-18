#include "temp_hum.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    temp_hum w;
    w.show();
    return a.exec();
}
