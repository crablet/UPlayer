#include "UPlayer.h"
#include "Music163.h"

UPlayer::UPlayer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    InitUI();
}

void UPlayer::InitUI()
{
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui.MinimizeButton, SIGNAL(clicked(bool)), this, SLOT(MinimizeWindow()));
    connect(ui.MaximizeButton, SIGNAL(clicked(bool)), this, SLOT(MaximizeWindow()));
    connect(ui.CloseButton, SIGNAL(clicked(bool)), this, SLOT(CloseWindow()));
}
