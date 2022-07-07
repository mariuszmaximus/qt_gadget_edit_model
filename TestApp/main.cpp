#include "selectitemforedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SelectItemForEdit w;
    w.show();
    return a.exec();
}
