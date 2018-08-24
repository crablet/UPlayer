#pragma once
#include <QString>
#include <QVariant>
#include <QMetaType>
#include <utility>

enum class SearchEngine : int
{
    Music163 = 0,
    Kugou = 1,
    Xiami = 2,
};

class SongInfo
{
public:
    SongInfo() = default;
    
    SongInfo(const QString &SongName, const QString &ID)
        : SongName(SongName), ID(ID)
    {
    }

    SongInfo(const QString &SongName, const QString &Singer, const QString &ID, SearchEngine Source)
        : SongName(SongName), Singer(Singer), ID(ID), Source(Source)
    {
    }

    SongInfo(const SongInfo &rhs)
        : SongName(rhs.SongName), Singer(rhs.Singer), ID(rhs.ID), Source(rhs.Source)
    {
    }

    SongInfo(SongInfo &&rhs) noexcept
    {
        SongName = std::move(rhs.SongName);
        Singer = std::move(rhs.Singer);
        ID = std::move(rhs.ID);
        Source = std::move(rhs.Source);
    }

    SongInfo& operator=(const SongInfo &rhs)
    {
        if (this == &rhs)   // may be not necessary?
        {
            ;
        }
        else
        {
            SongName = rhs.SongName;
            Singer = rhs.Singer;
            ID = rhs.ID;
            Source = rhs.Source;
        }

        return *this;
    }

    SongInfo& operator=(SongInfo &&rhs) noexcept
    {
        if (this == &rhs)   // may be not necessary?
        {
            ;
        }
        else
        {
            SongName = std::move(rhs.SongName);
            Singer = std::move(rhs.Singer);
            ID = std::move(rhs.ID);
            Source = std::move(rhs.Source);
        }

        return *this;
    }

    ~SongInfo() = default;

public:
    QString SongName;
    QString Singer;
    QString ID;
    SearchEngine Source;
};

Q_DECLARE_METATYPE(SongInfo)
