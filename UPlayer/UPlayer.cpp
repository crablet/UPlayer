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
    // Set custom minimize/maximize/close buttons.
    setWindowFlags(Qt::FramelessWindowHint);
    connect(ui.MinimizeButton, SIGNAL(clicked(bool)), this, SLOT(MinimizeWindow()));
    connect(ui.MaximizeButton, SIGNAL(clicked(bool)), this, SLOT(MaximizeWindow()));
    connect(ui.CloseButton, SIGNAL(clicked(bool)), this, SLOT(CloseWindow()));

    // Set SearchEngineBox(a QComboBox).
    ui.SearchEngineBox->addItem(u8"ÍøÒ×ÔÆ", static_cast<int>(SearchEngine::Music163));
    ui.SearchEngineBox->addItem(u8"¿á¹·", static_cast<int>(SearchEngine::Kugou));
    ui.SearchEngineBox->addItem(u8"ÏºÃ×", static_cast<int>(SearchEngine::Xiami));
}
