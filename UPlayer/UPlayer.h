#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include "ui_UPlayer.h"
#include "Music163.h"

class UPlayer : public QMainWindow
{
    Q_OBJECT

public:
    UPlayer(QWidget *parent = Q_NULLPTR);

private:
    Ui::UPlayerClass ui;

    Music163 Music163Player;

    void InitUI();

private slots:
    void MaximizeWindow()
    {
        if (isMaximized())
        {
            showNormal();
        }
        else
        {
            showMaximized();
        }
    }

    void MinimizeWindow()
    {
        showMinimized();
    }

    void CloseWindow()
    {
        std::exit(0);
    }
};
