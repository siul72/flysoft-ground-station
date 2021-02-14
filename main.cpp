#include "flysoftgroundstation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FlysoftGroundStation w;
    w.show();
    return a.exec();
}
