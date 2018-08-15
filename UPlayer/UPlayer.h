#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UPlayer.h"

class UPlayer : public QMainWindow
{
    Q_OBJECT

public:
    UPlayer(QWidget *parent = Q_NULLPTR);

private:
    Ui::UPlayerClass ui;
};
