#include "Music163.h"

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
        auto Obj = Doc.object();
        if (Obj.contains("result"))
        {
            auto Result = Obj.value("result");
            if (Result.isObject())
            {
                auto ResultObj = Result.toObject();
                if (ResultObj.contains("songs"))
                {
                    auto Songs = ResultObj.value("songs");
                    if (Songs.isArray())
                    {
                        auto SongsArr = Songs.toArray();
                        for (const auto &r : SongsArr)
                        {
                            auto SongObj = r.toObject();
                            auto ID = SongObj.value("id").toVariant().toString();

                            auto Item = new QListWidgetItem();
                            Item->setData(Qt::UserRole, ID);
                            Item->setText(SongObj.value("name").toString());
                            
                            // How to add "pointer ui"?
                            ui->SongCandidateList->addItem(Item);
                            qDebug() << ID;
                        }
                    }
                }
            }
        }
    }
}

void Music163::PlaySong(const QModelIndex &Index)
{
    auto ID = Index.data(Qt::UserRole).toString();
    ui->SongInfoLabel->setText(ID);

    ASongUrl = QUrl::fromUserInput("http://v1.hitokoto.cn/nm/url/" + ID);
    SongFileReply = SongFileNetworkManager->get(QNetworkRequest(ASongUrl));

    connect(SongFileReply, SIGNAL(readyRead()), this, SLOT(WriteSongDetailFile()));
    connect(SongFileReply, SIGNAL(finished()), this, SLOT(CloseSongDetailFile()));
}

void Music163::SearchSong(const QString &SongName)
{
    AllSongUrl = QUrl::fromUserInput("http://v1.hitokoto.cn/nm/search/"
               + QUrl::toPercentEncoding(SongName)
               + "/?type=SONG");
    UrlFileReply = UrlFileNetworkManager->get(QNetworkRequest(AllSongUrl));

    // Check it is useful?
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

                Player->setMedia(QUrl(Url));
                Player->play();
                qDebug() << Url;
            }
        }
    }
}