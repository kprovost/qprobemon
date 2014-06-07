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
    connect(m_model, SIGNAL(layoutChanged()),
            this, SLOT(redraw()));

    m_layout = new QGridLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_statusbar = new QStatusBar(this);

    setupMenu();

    m_layout->addWidget(m_ifaceName, 1, 0);
    m_layout->addWidget(m_channelList, 1, 1);
    m_layout->addWidget(m_tree, 2, 0, 1, 2);
    m_layout->addWidget(m_statusbar, 3, 0, 1, 2);

    setLayout(m_layout);

    connect(m_channelList, SIGNAL(currentIndexChanged(int)),
            this, SLOT(channelChange(int)));
    connect(m_model, SIGNAL(statusMessage(const QString&)),
            m_statusbar, SLOT(showMessage(const QString&)));
    updateChannelList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupMenu()
{
    m_menubar = new QMenuBar();
    m_layout->addWidget(m_menubar, 0, 0);
    m_fileMenu = m_menubar->addMenu("&File");
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

void MainWindow::channelChange(int index)
{
    QVariant channel = m_channelList->itemData(index);
    m_interface->setChannel(channel.toInt());
}

void MainWindow::redraw()
{
    m_tree->resizeColumnToContents(0);
    m_tree->resizeColumnToContents(1);
    m_tree->resizeColumnToContents(2);
    m_tree->resizeColumnToContents(3);
    m_tree->expandAll();
}
