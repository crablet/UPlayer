#pragma once

#include "SongBase.h"
#include "UPlayer.h"

class Music163 final : public SongBase
{
public:
    Music163() = default;
    Music163(Ui::UPlayerClass &Ui)  // Enable class Music163 to operator the UI.
    {
        ui = &Ui;
        SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite);
        UrlFile->open(QIODevice::Text | QIODevice::ReadWrite);
    }
    ~Music163() = default;

public slots:
    void SearchSong(const QString&) override;
    void WriteSongDetailFile() override;
    void CloseSongDetailFile() override;
    void WriteUrlFile() override;
    void CloseUrlFile() override;
    void PlaySong(const QModelIndex&) override;
};
