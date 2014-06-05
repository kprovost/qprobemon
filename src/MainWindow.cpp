#include "MainWindow.h"

MainWindow::MainWindow(InterfaceManagerP_t im, ProbeStore &store, QWidget *parent)
    : QWidget(parent),
      m_interface(im)
{
    m_ifaceName = new QLabel(QString("Interface: %1").arg(im->getInterfaceName()));
    m_channelList = new QComboBox();

    m_model = new ProbesModel(store);
    m_tree = new QTreeView();
    m_tree->setModel(m_model);

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_ifaceName, 0, 0);
    m_layout->addWidget(m_channelList, 0, 1);
    m_layout->addWidget(m_tree, 1, 0, 1, 2);

    setLayout(m_layout);

    connect(m_channelList, SIGNAL(currentIndexChanged(int)),
            this, SLOT(channelChange(int)));
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
        m_channelList->addItem(QString("%1").arg(channel), QVariant(channel));
    }
}

void  MainWindow::channelChange(int index)
{
    QVariant channel = m_channelList->itemData(index);
    m_interface->setChannel(channel.toInt());
}
