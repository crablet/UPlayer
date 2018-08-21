#pragma once
#include <QString>
#include <utility>
#include "UPlayer.h"

class SongInfo
{
public:
    SongInfo() = default;
    
    SongInfo(const QString &SN)
        : SongName(SN)
    {
    }

    SongInfo(const QString &SongName, const QString &Singer, SearchEngine Source)
        : SongName(SongName), Singer(Singer), Source(Source)
    {
    }

    SongInfo(const SongInfo &rhs)
        : SongName(rhs.SongName), Singer(rhs.Singer), Source(rhs.Source)
    {
    }

    SongInfo(SongInfo &&rhs) noexcept
    {
        SongName = std::move(rhs.SongName);
        Singer = std::move(rhs.Singer);
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
            Source = std::move(rhs.Source);
        }

        return *this;
    }

    ~SongInfo() = default;

public:
    QString SongName;
    QString Singer;
    SearchEngine Source;
};
