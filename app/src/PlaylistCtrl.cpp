#include "PlaylistCtrl.h"

QMediaPlaylist *PlaylistCtrl::getCurrentPlaylist() const {
    return m_currentPlaylist;
}

void PlaylistCtrl::setCurrentPlaylist(QMediaPlaylist *playlist) {
    if (!m_playlists.contains(playlist)) {
        m_playlists.push_back(playlist);
    }
    m_currentPlaylist = playlist;
}
