#include <QApplication>
#include <QStringList>
#include <iostream>

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

    return app.exec();
}
