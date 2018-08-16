#pragma once

#include "SongBase.h"

class Music163 final : public SongBase
{
public:
    Music163()
    {
        SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite);
        UrlFile->open(QIODevice::Text | QIODevice::ReadWrite);
    }
    ~Music163() = default;

    void SearchSong(const QString&) override;
    void WriteSongDetailFile() override;
    void CloseSongDetailFile() override;
    void WriteUrlFile() override;
    void CloseUrlFile() override;
    void PlaySong(const QModelIndex&) override;
};
