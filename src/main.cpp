#include <QApplication>
#include <QStringList>
#include <iostream>

#include "InterfaceManager.h"
#include "MainWindow.h"

void usage(const QString &appName)
{
    std::cerr << "Usage: " << appName.toStdString() << " <wifi interface>"
        << std::endl;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    QStringList args = app.arguments();

    QString appName = args.at(0);
    args.removeAt(0);

    if (args.size() < 1)
    {
        usage(appName);
        return 1;
    }

    QString interface = args.at(0);
    InterfaceManagerP_t im = InterfaceManager::create(interface);
    if (! im)
    {
        std::cerr << "Unable to open interface " << interface.toStdString()
            << std::endl;
        return 1;
    }

    mainWindow.show();

    return app.exec();
}
