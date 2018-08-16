#pragma once

#include <QString>
#include <QModelIndex>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class SongBase
{
public:
    SongBase()
        : SongDetailFile(new QFile(QString("SongDetail.txt"))),
          UrlFile(new QFile(QString("Url.txt"))),
          SongFileNetworkManager(new QNetworkAccessManager()),
          UrlFileNetworkManager(new QNetworkAccessManager())
    {

    }

    virtual ~SongBase() = default;  
    // "Effective C++": Item07
    // "Declare destructors virtual in polymorphic base classes."

    virtual void SearchSong(const QString&) = 0;
    virtual void WriteUrlFile() = 0;
    virtual void CloseUrlFile() = 0;
    virtual void WriteSongDetailFile() = 0;
    virtual void CloseSongDetailFile() = 0;
    virtual void PlaySong(const QModelIndex&) = 0;

    constexpr bool IsVaild() const noexcept
    {
        return Succeed;
    }

    const QString& GetSongName() const noexcept
    {
        return SongName;
    }

    constexpr int GetStatus() const noexcept
    {
        return Status;
    }

protected:
    bool Succeed;
    QString SongName;
    int Status;

    QFile *SongDetailFile, *UrlFile;
    QNetworkAccessManager *SongFileNetworkManager,
                          *UrlFileNetworkManager;
    QNetworkReply *UrlFileReply, *SongFileReply;
    QUrl AllSongUrl, ASongUrl;
};
