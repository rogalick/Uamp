#ifndef PLAYER_H
#define PLAYER_H

#include <QMediaPlayer>

class Player : public QMediaPlayer {
public:
    Player() = default;
    ~Player();

    bool isPlaying() const;
    void setIsPlaying(bool isPlaying);

public Q_SLOTS:
    void play();
    void pause();
    void stop();

private:
    bool m_isPlaying = false;
};

#endif // PLAYER_H
