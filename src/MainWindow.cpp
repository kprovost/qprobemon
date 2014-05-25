#include "MainWindow.h"

MainWindow::MainWindow(InterfaceManagerP_t im, QWidget *parent)
    : QWidget(parent),
      m_interface(im)
{
    m_ifaceName = new QLabel(QString("Interface: %1").arg(im->getInterfaceName()));
    m_channelList = new QComboBox();

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_ifaceName, 0, 0);
    m_layout->addWidget(m_channelList, 0, 1);

    setLayout(m_layout);

    updateChannelList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateChannelList()
{
    m_channelList->clear();

    ChannelList_t channels = m_interface->getChannels();

    foreach(int channel, channels)
    {
        m_channelList->addItem(QString("%1").arg(channel));
    }
}
