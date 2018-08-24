#include "Music163.h"
#include <QMessageBox>

void Music163::WriteUrlFile()
{
    UrlFile->write(UrlFileReply->readAll());
}

void Music163::CloseUrlFile()
{
    UrlFile->close();
    UrlFile->open(QIODevice::ReadOnly | QIODevice::Text);

    auto Str = UrlFile->readAll();

    // delete UrlFile;
    // UrlFile = nullptr;

    auto Doc = QJsonDocument::fromJson(Str);
    if (Doc.isObject())
    {
        auto SongsArr = Doc.object().value("result").toObject().value("songs").toArray();
        for (const auto &r : SongsArr)
        {
            auto SongObj = r.toObject();
            auto ID = SongObj.value("id").toVariant().toString();
            auto SongName = SongObj.value("name").toString();
            auto Singer = SongObj.value("artists").toArray()[0].toObject().value("name").toString();

            // TODO: check if NULL
            if (ID.isEmpty() || SongName.isEmpty() || Singer.isEmpty())
            {
                QMessageBox WarningBox;
                WarningBox.setWindowTitle("Error!");
                WarningBox.setText("Invalid JSON file.");
                WarningBox.exec();

                break;
            }
            auto Info = SongInfo(SongName, Singer, ID, SearchEngine::Music163);

            auto Item = new QListWidgetItem();
            Item->setData(Qt::UserRole, QVariant::fromValue(Info));
            Item->setText(SongName + '-' + Singer);

            // How to add "pointer ui"?
            ui->SongCandidateList->addItem(Item);
            qDebug() << ID;
        }
    }
    else
    {
        QMessageBox WarningBox;
        WarningBox.setWindowTitle("Error!");
        WarningBox.setText("Invalid JSON file.");
        WarningBox.exec();
    }
}

void Music163::PlaySong(const QModelIndex &Index)
{
    auto Info = Index.data(Qt::UserRole).value<SongInfo>();

    auto Singer = Info.Singer;
    auto SongName = Info.SongName;
    ui->SongInfoLabel->setText(SongName + '-' + Singer);
    ui->SongListWidget->addItem(SongName + '-' + Singer);

    auto ID = Info.ID;
    ASongUrl = QUrl::fromUserInput("http://v1.hitokoto.cn/nm/url/" + ID);
    SongFileReply = SongFileNetworkManager->get(QNetworkRequest(ASongUrl));

    connect(SongFileReply, SIGNAL(readyRead()), this, SLOT(WriteSongDetailFile()));
    connect(SongFileReply, SIGNAL(finished()), this, SLOT(CloseSongDetailFile()));
}

void Music163::SearchSong(const QString &SongName)
{
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


    AllSongUrl = QUrl::fromUserInput("http://v1.hitokoto.cn/nm/search/"
               + QUrl::toPercentEncoding(SongName)
               + "/?type=SONG");
    UrlFileReply = UrlFileNetworkManager->get(QNetworkRequest(AllSongUrl));

    // Check is it useful?
    connect(UrlFileReply, SIGNAL(readyRead()), this, SLOT(WriteUrlFile()));
    connect(UrlFileReply, SIGNAL(finished()), this, SLOT(CloseUrlFile()));
}

void Music163::WriteSongDetailFile()
{
    SongDetailFile->close();
    SongDetailFile->open(QIODevice::Text | QIODevice::Truncate | QIODevice::ReadWrite);
    SongDetailFile->write(SongFileReply->readAll());
}

void Music163::CloseSongDetailFile()
{
    SongDetailFile->close();
    SongDetailFile->open(QIODevice::ReadOnly);
    auto Str = SongDetailFile->readAll();

    SongDetailFile->close();
    SongDetailFile->open(QIODevice::Truncate);
    SongDetailFile->close();

    auto Doc = QJsonDocument::fromJson(Str);
    if (Doc.isObject())
    {
        auto DocObj = Doc.object();
        if (DocObj.contains("data"))
        {
            auto Data = DocObj.value("data");
            if (Data.isArray())
            {
                auto DataArr = Data.toArray();
                auto Url = DataArr[0].toObject().value("url").toString();

                connect(Player, SIGNAL(positionChanged(qint64)),
                    this, SLOT(SongPositionChanged(qint64)));
                connect(Player, SIGNAL(durationChanged(qint64)),
                    this, SLOT(SongDurationChanged(qint64)));

                Player->setMedia(QUrl(Url));
                Player->play();
                
                qDebug() << Url;
            }
        }
    }
}