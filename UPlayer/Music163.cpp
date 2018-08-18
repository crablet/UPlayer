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
                    auto Songs = ResultObj.value("song");
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
}

void Music163::CloseSongDetailFile()
{
}