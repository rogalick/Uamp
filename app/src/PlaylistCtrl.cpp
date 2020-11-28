#include "PlaylistCtrl.h"
#include <algorithm>

PlaylistCtrl::PlaylistCtrl() : m_currentPlaylist(new QMediaPlaylist) {
    m_currentPlaylist->setPlaybackMode(QMediaPlaylist::Sequential);
}

QMediaPlaylist *PlaylistCtrl::getCurrentPlaylist() const {
    return m_currentPlaylist;
}

void PlaylistCtrl::setCurrentPlaylist(QMediaPlaylist *playlist) {
    if (!m_playlists.contains(playlist)) {
        m_playlists.push_back(playlist);
    }
    m_currentPlaylist = playlist;
}

void PlaylistCtrl::appendAudioToCurrentPlaylist(const QString &filepath) {
    m_currentPlaylist->addMedia(QUrl::fromLocalFile(filepath));
}

void PlaylistCtrl::removeAudioFromCurrentPlaylist(int index) {
    m_currentPlaylist->removeMedia(index);
}

void PlaylistCtrl::uploadPlaylists() {}
