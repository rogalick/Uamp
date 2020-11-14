#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QFileDialog>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QRadioTuner>
#include <QStandardItemModel>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

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
    QMediaPlayer *m_player;
    QMediaPlaylist *m_playlist;
    bool play = false;
    int slidePostion = 0;
    QRadioTuner *radio;
};

#endif // MAINWINDOW_H
