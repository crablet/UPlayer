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

        // Clear the file.
        if (SongDetailFile->isOpen())
        {
            SongDetailFile->close();
            SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
            SongDetailFile->close();
            SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
        }
        else
        {
            SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
            SongDetailFile->close();
            SongDetailFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
        }

        // Clear the file.
        if (UrlFile->isOpen())
        {
            UrlFile->close();
            UrlFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
            UrlFile->close();
            UrlFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
        }
        else
        {
            UrlFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
            UrlFile->close();
            UrlFile->open(QIODevice::Text | QIODevice::ReadWrite | QIODevice::Truncate);
        }

        connect(ui->ProcessBarSlider, SIGNAL(valueChanged(int)),
            this, SLOT(SongSliderPositionChanged(int)));
    }
    ~Music163() = default;

public:
    static auto& GetInstance(Ui::UPlayerClass &Ui)
    {
        static Music163 Instance(Ui);

        return Instance;
    }

    Music163(const Music163&) = delete;
    Music163& operator=(const Music163&) = delete;

public slots:
    void SearchSong(const QString&) override;
    void WriteSongDetailFile() override;
    void CloseSongDetailFile() override;
    void WriteUrlFile() override;
    void CloseUrlFile() override;
    void PlaySong(const QModelIndex&) override;
};
