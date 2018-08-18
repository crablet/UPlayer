#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include "ui_UPlayer.h"
#include "Music163.h"

class UPlayer : public QMainWindow
{
    Q_OBJECT

public:
    UPlayer(QWidget *parent = Q_NULLPTR);

private:
    Ui::UPlayerClass ui;

    Music163 *Music163Player;

    void InitUI();

private slots:
    void SearchSong();
    //void WriteUrlFile();
    //void CloseUrlFile();
    //void WriteSongDetailFile();
    //void CloseSongDetailFile();
    void PlaySong(const QModelIndex&);

    void MaximizeWindow()
    {
        if (isMaximized())
        {
            showNormal();
        }
        else
        {
            showMaximized();
        }
    }

    void MinimizeWindow()
    {
        showMinimized();
    }

    void CloseWindow()
    {
        std::exit(0);
    }

public:
    friend void Music163::CloseUrlFile();
};

enum class SearchEngine : int
{
    Music163 = 0,
    Kugou = 1,
    Xiami = 2,
};
