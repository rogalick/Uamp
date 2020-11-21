#include "Player.h"

Player::~Player() {}

bool Player::isPlaying() const { return m_isPlaying; }

void Player::setIsPlaying(bool isPlaying) { m_isPlaying = isPlaying; }

void Player::play() {
    QMediaPlayer::play();
    m_isPlaying = true;
}

void Player::pause() {
    QMediaPlayer::pause();
    m_isPlaying = false;
}

void Player::stop() {
    QMediaPlayer::stop();
    m_isPlaying = false;
}
