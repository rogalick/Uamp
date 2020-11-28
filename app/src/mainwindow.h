#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Player.h"
#include "PlaylistCtrl.h"
#include <QAudioProbe>
#include <QAudioRecorder>
#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QRadioTuner>
#include <QStandardItemModel>
#include <QWidget>

class radio;

namespace Ui {
// class radio;
class MainWindow;
} // namespace Ui

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void GetMetaData(QMediaPlayer *player);

    ~MainWindow();

private slots:
    void on_addTrack_clicked();

    void on_button_play_clicked();

    void on_button_stop_clicked();

    void on_playlistview_doubleClicked(const QModelIndex &index);

    void trackDurationChanged(qint64 position);

    void trackPositionChanged(qint64 position);

    void on_volumeSlider_valueChanged(int value);

    void on_sliderTrackDuration_sliderMoved(int position);

    void on_sliderTrackDuration_sliderReleased();

    void on_but_prev_clicked();

    void on_but_next_clicked();

    void on_button_rewind_clicked();

    void on_button_forward_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *m_playListModel;
    std::unique_ptr<Player> m_player;
    std::unique_ptr<PlaylistCtrl> m_playlistCtrl;
    bool play = false;
    int slidePostion = 0;
};

#endif // MAINWINDOW_H
