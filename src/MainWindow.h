#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

#include "InterfaceManager.h"

class MainWindow : public QWidget
{
    Q_OBJECT;

public:
    MainWindow(InterfaceManagerP_t im, QWidget *parent = NULL);
    ~MainWindow();

private:
    void updateChannelList();

    QGridLayout *m_layout;

    QLabel *m_ifaceName;
    QComboBox *m_channelList;

    InterfaceManagerP_t m_interface;

private slots:
    void  channelChange(int index);
};
