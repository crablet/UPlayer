#include "SongBase.h"


void SongBase::SongPositionChanged(qint64 Position)
{
    if (ui->ProcessBarSlider->isSliderDown())
    {
        return;
    }
    else
    {
        ui->ProcessBarSlider->setSliderPosition(Position);

        auto Secs = Position / 1000 % 60;
        auto Mins = Position / 1000 / 60;
        PositionTime = QString::asprintf("%lld:%lld", Mins, Secs);

        ui->ProcessInfoLabel->setText(PositionTime + '/' + DurationTime);
    }
}

void SongBase::SongDurationChanged(qint64 Duration)
{
    ui->ProcessBarSlider->setMaximum(Duration);

    auto Secs = Duration / 1000 % 60;
    auto Mins = Duration / 1000 / 60;
    DurationTime = QString::asprintf("%lld:%lld", Mins, Secs);

    ui->ProcessInfoLabel->setText(PositionTime + '/' + DurationTime);
}

void SongBase::SongSliderPositionChanged(qint64 Value)
{
    Player->setPosition(Value);
}
