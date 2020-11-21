#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_playListModel = new QStandardItemModel(this);
    ui->playlistview->setModel(m_playListModel);
    m_playListModel->setHorizontalHeaderLabels(
        QStringList() << tr("Audio Track") << tr("File Path"));
    ui->playlistview->hideColumn(1);
    ui->playlistview->verticalHeader()->setVisible(false);
    ui->playlistview->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistview->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playlistview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistview->horizontalHeader()->setStretchLastSection(true);

    m_player = std::make_unique<Player>();
    m_playlistCtrl = std::make_unique<PlaylistCtrl>();

    radio_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist();

    m_player->setPlaylist(m_playlist);
    m_player->setVolume(70);
    radio_player->setVolume(70);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(70);

    connect(m_player.get(), &QMediaPlayer::mediaStatusChanged,
            [this](QMediaPlayer::MediaStatus status) {
                GetMetaData(m_player.get());
                if (status == QMediaPlayer::LoadedMedia) {
                    qInfo()
                        << m_player->metaData("Title").toString(); // need test
                    qInfo() << m_player->metaData("AlbumArtist").toString();
                    qInfo() << m_player->metaData("Composer").toString();
                    qInfo() << m_player->metaData("Author").toString();
                }
            });

    //    radio = new QRadioTuner;
    //    connect(radio, SIGNAL(frequencyChanged(int)), this,
    //    SLOT(freqChanged(int))); if (radio->isBandSupported(QRadioTuner::FM))
    //    {
    //        radio->setBand(QRadioTuner::FM);
    //        radio->setFrequency(100);
    //        radio->setVolume(100);
    //        radio->start();
    //    }

    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [&](int index) {
        ui->currentTrack->setText(
            m_playListModel->data(m_playListModel->index(index, 0)).toString());
    });
    QObject::connect(m_player.get(), SIGNAL(durationChanged(qint64)), this,
                     SLOT(trackDurationChanged(qint64)));
    QObject::connect(m_player.get(), SIGNAL(positionChanged(qint64)), this,
                     SLOT(trackPositionChanged(qint64)));
    m_player->setNotifyInterval(10);
}

void MainWindow::GetMetaData(QMediaPlayer *player) {
    // Get the list of keys there is metadata available for
    QStringList metadatalist = player->availableMetaData();

    // Get the size of the list
    int list_size = metadatalist.size();

    // qDebug() << player->isMetaDataAvailable() << list_size;

    // Define variables to store metadata key and value
    QString metadata_key;
    QVariant var_data;

    for (int indx = 0; indx < list_size; indx++) {
        // Get the key from the list
        metadata_key = metadatalist.at(indx);

        // Get the value for the key
        var_data = player->metaData(metadata_key);

        qDebug() << metadata_key << var_data.toString();
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_playListModel;
    delete m_playlist;
}

void MainWindow::on_addTrack_clicked() {
    QStringList files = QFileDialog::getOpenFileNames(
        this, tr("Open files"), QString(),
        tr("Audio Files (*.mp3 *.m4a *.flac *.ogg)"));

    foreach (QString filePath, files) {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl::fromLocalFile(filePath));
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
    m_playlist->setCurrentIndex(index.row());
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

void MainWindow::on_but_prev_clicked() { m_playlist->previous(); }

void MainWindow::on_but_next_clicked() { m_playlist->next(); }

void MainWindow::on_button_rewind_clicked() {
    m_player->setPosition(m_player->position() - 10000);
}

void MainWindow::on_button_forward_clicked() {
    m_player->setPosition(m_player->position() + 10000);
}

void MainWindow::on_RadioROKS_clicked() {
    radio_player->setMedia((QUrl("https://online.radioroks.ua/RadioROKS")));
    on_Play_clicked();
}

void MainWindow::on_HitFM_clicked() {
    radio_player->setMedia(QUrl("https://online.hitfm.ua/HitFM"));
    on_Play_clicked();
}

void MainWindow::on_RadioJazz_clicked() {
    radio_player->setMedia(QUrl("https://online.radiojazz.ua/RadioJazz_HD"));
    on_Play_clicked();
}

void MainWindow::on_KissFM_clicked() {
    radio_player->setMedia(QUrl("https://online.kissfm.ua/KissFM"));
    on_Play_clicked();
}

void MainWindow::on_Stop_clicked() { radio_player->stop(); }

void MainWindow::on_Play_clicked() {
    m_player->pause();
    radio_player->play();
}
