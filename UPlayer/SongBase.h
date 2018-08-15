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
    SongBase() = default;
    virtual ~SongBase() = default;  
    // "Effective C++": Item07
    // "Declare destructors virtual in polymorphic base classes."

    virtual void WriteUrlFile() = 0;
    virtual void CloseUrlFile() = 0;
    virtual void WriteSongDetailFile() = 0;
    virtual void CloseSongDetailFile() = 0;
    virtual void PlaySong(const QModelIndex&) = 0;

    bool IsVaild() const noexcept
    {
        return Succeed;
    }

    const QString& GetSongName() const noexcept
    {
        return SongName;
    }

    int GetStatus() const noexcept
    {
        return Status;
    }

private:
    bool Succeed;
    QString SongName;
    int Status;

    QFile *SongDetailFile, *UrlFile;
    QNetworkAccessManager *SongFileNetworkManager,
                          *UrlFileNetworkManager;
    QNetworkReply *UrlFileReply, *SongFileReply;
    QUrl AllSongUrl, ASongUrl;
};
