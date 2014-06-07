#include <QApplication>
#include <QStringList>
#include <iostream>

#include "InterfaceManager.h"
#include "Sniffer.h"
#include "ProbeRequestFilter.h"
#include "MainWindow.h"
#include "ProbeStore.h"

void usage(const QString &appName)
{
    std::cerr << "Usage: " << appName.toStdString() << " <wifi interface>"
        << std::endl;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

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

    if (! im->monitor())
    {
        return 1;
    }

    SnifferP_t sniff = Sniffer::create(interface);
    if (! sniff)
    {
        std::cerr << "Unable to sniff on interface " << interface.toStdString()
            << std::endl;
        return 1;
    }

    ProbeRequestFilter filter;

    QObject::connect(sniff.data(), SIGNAL(received(PacketP_t)),
            &filter, SLOT(received(PacketP_t)));

    ProbeStore store;

    QObject::connect(&filter, SIGNAL(probeRequest(ProbeRequestP_t)),
                &store, SLOT(probeRequest(ProbeRequestP_t)));

    MainWindow mainWindow(im, store);
    mainWindow.show();

    QObject::connect(&mainWindow, SIGNAL(quit()),
            &app, SLOT(quit()));

    return app.exec();
}
