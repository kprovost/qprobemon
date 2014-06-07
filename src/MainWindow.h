#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTreeView>

#include "InterfaceManager.h"
#include "ProbesModel.h"
#include "ProbeStore.h"

class MainWindow : public QWidget
{
    Q_OBJECT;

public:
    MainWindow(InterfaceManagerP_t im, ProbeStore &store, QWidget *parent = NULL);
    ~MainWindow();

private:
    void updateChannelList();

    QGridLayout *m_layout;

    QLabel *m_ifaceName;
    QComboBox *m_channelList;
    QTreeView *m_tree;
    ProbesModel *m_model;

    InterfaceManagerP_t m_interface;

private slots:
    void channelChange(int index);
    void redraw();
};
