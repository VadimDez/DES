#include <QtGui/QApplication>
#include "des.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    des w;
    w.show();
    
    return a.exec();
}
