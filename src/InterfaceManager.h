#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QList>

#include "iwlib.h"

class InterfaceManager;

typedef QSharedPointer<InterfaceManager> InterfaceManagerP_t;
typedef QList<int> ChannelList_t;

class InterfaceManager : public QObject
{
    Q_OBJECT;

public:
    static InterfaceManagerP_t create(const QString &interface);

    ~InterfaceManager();

    bool open();
    void close();

    ChannelList_t getChannels();
    const QString& getInterfaceName() const { return m_interface; }

private:
    InterfaceManager(const QString &interface);

    const QString &m_interface;
    int m_iw_fd;
    wireless_config m_old_config;
};
