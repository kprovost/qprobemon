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

    const QString& getInterfaceName() const { return m_interface; }

    bool monitor();

    ChannelList_t getChannels();
    bool setChannel(const int channel);

private:
    InterfaceManager(const QString &interface);

    bool open();
    void close();

    bool setIfState(struct ifreq &ifr);
    bool getIfState(struct ifreq &ifr);
    bool ifDown();
    bool ifUp();
    bool isIfUp();

    bool getRange(iwrange &range);

    const QString &m_interface;
    int m_iw_fd;
    wireless_config m_old_config;
    bool m_old_isUp;
};
