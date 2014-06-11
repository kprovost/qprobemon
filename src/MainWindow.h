#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTreeView>
#include <QStatusBar>
#include <QMenu>
#include <QMenuBar>

#include "InterfaceManager.h"
#include "ProbesModel.h"
#include "ProbeStore.h"

class MainWindow : public QWidget
{
    Q_OBJECT;

public:
    MainWindow(InterfaceManagerP_t im, ProbeStore &store,
            ProbeStore &noBroadcastStore, QWidget *parent = NULL);
    ~MainWindow();

private:
    void setupMenu();
    void updateChannelList();

    QGridLayout *m_layout;

    QLabel *m_ifaceName;
    QComboBox *m_channelList;
    QTreeView *m_tree;
    ProbesModel *m_model;
    QStatusBar *m_statusbar;

    QMenuBar *m_menubar;
    QMenu *m_fileMenu;
    QAction *m_quitAction;

    InterfaceManagerP_t m_interface;

signals:
    void quit();

private slots:
    void channelChange(int index);
    void redraw();
    void quit(bool checked);
};
