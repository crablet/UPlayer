#pragma once

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QModelIndex>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QListWidget>
#include <QMediaPlayer>
#include "ui_UPlayer.h"
#include "SongInfo.h"

class UPlayer;

class SongBase : public QObject
{
    Q_OBJECT

public:
    SongBase()
        : SongDetailFile(new QFile(QString("SongDetail.txt"))),
          UrlFile(new QFile(QString("Url.txt"))),
          SongFileNetworkManager(new QNetworkAccessManager()),
          UrlFileNetworkManager(new QNetworkAccessManager()),
          Player(new QMediaPlayer())
    {
    }

    virtual ~SongBase() = default;  
    // "Effective C++": Item07
    // "Declare destructors virtual in polymorphic base classes."

public slots:
    virtual void SearchSong(const QString&) = 0;
    virtual void WriteUrlFile() = 0;
    virtual void CloseUrlFile() = 0;
    virtual void WriteSongDetailFile() = 0;
    virtual void CloseSongDetailFile() = 0;
    virtual void PlaySong(const QModelIndex&) = 0;

public:
    constexpr auto IsVaild() const noexcept
    {
        return Succeed;
    }

    const auto& GetSongName() const noexcept
    {
        return SongName;
    }

    constexpr auto GetStatus() const noexcept
    {
        return Status;
    }

public slots:
    void SongPositionChanged(qint64);   // emit when slider is dragged
    void SongDurationChanged(qint64);   // emit when song is playing
    void SongSliderPositionChanged(qint64); // emit when slider is dragged

protected:
    bool Succeed;
    QString SongName;
    int Status;

    QFile *SongDetailFile, *UrlFile;
    QNetworkAccessManager *SongFileNetworkManager,
                          *UrlFileNetworkManager;
    QNetworkReply *UrlFileReply, *SongFileReply;
    QUrl AllSongUrl, ASongUrl;

    QMediaPlayer *Player;

    QString PositionTime, DurationTime;

    Ui::UPlayerClass *ui;

public:
    friend class UPlayer;
};


