#ifndef PLAYLISTCTRL_H
#define PLAYLISTCTRL_H

#include "DBCtrl.h"
#include <QMediaPlaylist>
#include <QtCore>

class PlaylistCtrl {
public:
    PlaylistCtrl();

    QMediaPlaylist *getCurrentPlaylist() const;
    void setCurrentPlaylist(QMediaPlaylist *playlist);

    void appendAudioToCurrentPlaylist(const QString &filepath);
    void removeAudioFromCurrentPlaylist(int index);

    void uploadPlaylists(); // upload from database

private:
    QVector<QMediaPlaylist *> m_playlists;
    QMediaPlaylist *m_currentPlaylist;
    std::unique_ptr<DBCtrl> m_db; // database
};

#endif // PLAYLISTCTRL_H
