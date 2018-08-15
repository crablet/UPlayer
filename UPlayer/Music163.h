#pragma once

#include "SongBase.h"

class Music163 final : public SongBase
{
public:
    Music163() = default;
    ~Music163() = default;

    void WriteSongDetailFile() override;
    void CloseSongDetailFile() override;
    void WriteUrlFile() override;
    void CloseUrlFile() override;
};
