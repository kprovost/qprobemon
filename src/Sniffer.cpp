#include "Sniffer.h"

SnifferP_t Sniffer::create(const QString &interface)
{
    SnifferP_t sniff(new Sniffer(interface));
    return sniff;
}

Sniffer::Sniffer(const QString &interface)
    : QObject(),
      m_interface(interface)
{

}

Sniffer::~Sniffer()
{

}
