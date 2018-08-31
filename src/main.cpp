#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <iostream>

QString loadStylesheet( QString filename ){
    QFile file(filename);
    if (!file.open(QFile::ReadOnly)){
        std::cout << file.errorString().toStdString() << std::endl;
    }
    QString stylesheet = QLatin1String(file.readAll());
    return stylesheet;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFontDatabase::addApplicationFont(":/fonts/RobotoCondensed-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/FontAwesome5.otf");

    //w.setWindowFlags(Qt::FramelessWindowHint);
    a.setStyleSheet(loadStylesheet(":/stylesheets/style.css"));
    w.show();

    return a.exec();
}
