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

    connect(ui.SearshSongBox, SIGNAL(returnPressed()), this, SLOT(SearchSong()));

    connect(ui.SongListWidget, SIGNAL(doubleClicked(const QModelIndex&)),
        this, SLOT(PlaySong(const QModelIndex&)));

    connect(ui.SongCandidateList, SIGNAL(doubleClicked(const QModelIndex&)),
        this, SLOT(PlaySong(const QModelIndex&)));
}

void UPlayer::SearchSong()
{
    auto SongName = ui.SearshSongBox->text();
    if (!SongName.isEmpty())
    {
        auto Engine = ui.SearchEngineBox->currentData();
        if (Engine == static_cast<int>(SearchEngine::Music163))
        {
            // CAUTION!!! YOU SHOULD NEW!!!
            Music163Player = new Music163(ui);
            Music163Player->SearchSong(SongName);
        }
        else if (Engine == static_cast<int>(SearchEngine::Kugou))
        {
            // TODO
        }
        else if (Engine == static_cast<int>(SearchEngine::Xiami))
        {
            // TODO
        }
    }
}

//void UPlayer::WriteUrlFile()
//{
//    auto Engine = ui.SearchEngineBox->currentData();
//    if (Engine == static_cast<int>(SearchEngine::Music163))
//    {
//        Music163Player->WriteUrlFile();
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Kugou))
//    {
//        // TODO
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Xiami))
//    {
//        // TODO
//    }
//}
//
//void UPlayer::CloseUrlFile()
//{
//    auto Engine = ui.SearchEngineBox->currentData();
//    if (Engine == static_cast<int>(SearchEngine::Music163))
//    {
//        Music163Player->CloseUrlFile();
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Kugou))
//    {
//        // TODO
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Xiami))
//    {
//        // TODO
//    }
//}
//
//void UPlayer::WriteSongDetailFile()
//{
//    auto Engine = ui.SearchEngineBox->currentData();
//    if (Engine == static_cast<int>(SearchEngine::Music163))
//    {
//        Music163Player->WriteSongDetailFile();
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Kugou))
//    {
//        // TODO
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Xiami))
//    {
//        // TODO
//    }
//}
//
//void UPlayer::CloseSongDetailFile()
//{
//    auto Engine = ui.SearchEngineBox->currentData();
//    if (Engine == static_cast<int>(SearchEngine::Music163))
//    {
//        Music163Player->CloseSongDetailFile();
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Kugou))
//    {
//        // TODO
//    }
//    else if (Engine == static_cast<int>(SearchEngine::Xiami))
//    {
//        // TODO
//    }
//}
//
void UPlayer::PlaySong(const QModelIndex &Index)
{
    auto Engine = ui.SearchEngineBox->currentData();
    if (Engine == static_cast<int>(SearchEngine::Music163))
    {
        // This function should implement at this place.
        Music163Player->PlaySong(Index);
    }
    else if (Engine == static_cast<int>(SearchEngine::Kugou))
    {
        // TODO
    }
    else if (Engine == static_cast<int>(SearchEngine::Xiami))
    {
        // TODO
    }
}
