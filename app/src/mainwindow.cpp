#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      m_player(std::make_unique<Player>()),
      m_playlistCtrl(std::make_unique<PlaylistCtrl>()) {
    ui->setupUi(this);
    m_playListModel = new QStandardItemModel(this);
    m_playListModel->setHorizontalHeaderLabels(
        QStringList() << tr("Audio Track") << tr("File Path"));

    ui->playlistview->setModel(m_playListModel);
    ui->playlistview->hideColumn(1);
    ui->playlistview->verticalHeader()->setVisible(false);
    ui->playlistview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistview->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistview->horizontalHeader()->setStretchLastSection(true);

    m_player->setPlaylist(m_playlistCtrl->getCurrentPlaylist());

    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(70);

    QObject::connect(m_player.get(), SIGNAL(durationChanged(qint64)), this,
                     SLOT(trackDurationChanged(qint64)));

    QObject::connect(m_player.get(), SIGNAL(positionChanged(qint64)), this,
                     SLOT(trackPositionChanged(qint64)));
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_playListModel;
}

void MainWindow::on_addTrack_clicked() {
    QStringList files = QFileDialog::getOpenFileNames(
        this, tr("Open files"), QString(),
        tr("Audio Files (*.mp3 *.m4a *.flac *.ogg *.wav)"));

    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlistCtrl->appendAudioToCurrentPlaylist(filePath);
    }
}

void MainWindow::on_button_play_clicked() {
    if (m_player->isPlaying() == false) {
        m_player->play();
        ui->button_play->setText("Pause");
    } else {
        m_player->pause();
        ui->button_play->setText("Play");
    }
}

void MainWindow::on_button_stop_clicked() {
    m_player->stop();
    ui->button_play->setText("Play");
}

void MainWindow::on_playlistview_doubleClicked(const QModelIndex &index) {
    m_playlistCtrl->getCurrentPlaylist()->setCurrentIndex(index.row());
    on_button_play_clicked();
}

void MainWindow::trackDurationChanged(qint64 position) {
    double duration = position / 1000;
    int min = int(duration / 60);
    int sec = int(duration - min * 60);
    ui->trackDuration->setText(QString::number(min) + ":" +
                               QString::number(sec));
    ui->sliderTrackDuration->setMaximum(int(position));
}

void MainWindow::trackPositionChanged(qint64 position) {
    double duration = position / 1000;
    int min = int(duration / 60);
    int sec = int(duration - min * 60);
    ui->currentTrackTime->setText(QString::number(min) + ":" +
                                  QString::number(sec));
    ui->sliderTrackDuration->setValue(int(position));
}

void MainWindow::on_volumeSlider_valueChanged(int value) {
    m_player->setVolume(value);
}

void MainWindow::on_sliderTrackDuration_sliderMoved(int position) {
    QObject::disconnect(m_player.get(), SIGNAL(positionChanged(qint64)), this,
                        SLOT(trackPositionChanged(qint64)));
    slidePostion = position;
}

void MainWindow::on_sliderTrackDuration_sliderReleased() {
    m_player->setPosition(slidePostion);
    QObject::connect(m_player.get(), SIGNAL(positionChanged(qint64)), this,
                     SLOT(trackPositionChanged(qint64)));
}

void MainWindow::on_but_prev_clicked() {
    m_playlistCtrl->getCurrentPlaylist()->previous();
}

void MainWindow::on_but_next_clicked() {
    m_playlistCtrl->getCurrentPlaylist()->next();
}

void MainWindow::on_button_rewind_clicked() {
    m_player->setPosition(m_player->position() - 10000);
}

void MainWindow::on_button_forward_clicked() {
    m_player->setPosition(m_player->position() + 10000);
}
