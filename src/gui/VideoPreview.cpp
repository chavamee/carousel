/*
 * Carousel
 * Copyright (C) 2017 Jorge Martinez Hernandez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <QMediaContent>
#include <QMediaService>
#include <QtWidgets>

#include "PlayerControls.hpp"
#include "VideoPreview.hpp"

VideoPreview::VideoPreview(QWidget *parent) : FilePreview(parent) {
  m_player = new QMediaPlayer(this);

  connect(m_player, SIGNAL(durationChanged(qint64)),
          SLOT(durationChanged(qint64)));
  connect(m_player, SIGNAL(positionChanged(qint64)),
          SLOT(positionChanged(qint64)));
  connect(m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this,
          SLOT(statusChanged(QMediaPlayer::MediaStatus)));
  connect(m_player, SIGNAL(videoAvailableChanged(bool)), this,
          SLOT(videoAvailableChanged(bool)));

  m_videoWidget = new VideoWidget(this);
  m_player->setVideoOutput(m_videoWidget);
  m_player->setVolume(50);

  m_slider = new QSlider(Qt::Horizontal, this);
  m_slider->setRange(0, m_player->duration() / 1000);

  connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));

  m_controls = new PlayerControls(this);
  m_controls->SetState(m_player->state());
  m_controls->SetMuted(m_controls->IsMuted());

  connect(m_controls, SIGNAL(Play()), m_player, SLOT(play()));
  connect(m_controls, SIGNAL(Pause()), m_player, SLOT(pause()));
  connect(m_controls, SIGNAL(ChangeMuting(bool)), m_player, SLOT(setMuted(bool)));

  connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), m_controls,
          SLOT(SetState(QMediaPlayer::State)));
  connect(m_player, SIGNAL(mutedChanged(bool)), m_controls, SLOT(SetMuted(bool)));

  m_fullScreenButton = new QPushButton(tr("FullScreen"), this);
  m_fullScreenButton->setCheckable(true);

  auto displayLayout = new QHBoxLayout;
  displayLayout->addWidget(m_videoWidget);

  auto controlLayout = new QHBoxLayout;
  controlLayout->addWidget(m_controls);
  controlLayout->addStretch(1);
  controlLayout->addWidget(m_fullScreenButton);

  auto layout = new QVBoxLayout;
  layout->addLayout(displayLayout);

  auto hLayout = new QHBoxLayout;
  hLayout->addWidget(m_slider);

  layout->addLayout(hLayout);
  layout->addLayout(controlLayout);

  setLayout(layout);

  if (not IsPlayerAvailable()) {
    QMessageBox::warning(
        this, tr("Service not available"),
        tr("The QMediaPlayer object does not have a valid service.\n"
           "Please check the media service plugins are installed."));

    m_controls->setEnabled(false);
    m_fullScreenButton->setEnabled(false);
  }
}

void VideoPreview::Show(QFileInfo file) {
  m_player->stop();
  m_player->setMedia(QMediaContent());

  m_controls->SetState(QMediaPlayer::StoppedState);
  m_controls->SetMuted(false);

  m_player->setMedia(QUrl::fromLocalFile(file.absoluteFilePath()));

  QWidget::show();
}

void VideoPreview::focusOutEvent(QFocusEvent* event) {
  if (event->lostFocus()) {
    m_player->stop();
  }
}

bool VideoPreview::IsPlayerAvailable() const { return m_player->isAvailable(); }

void VideoPreview::durationChanged(qint64 duration) {
  m_duration = duration / 1000;
  m_slider->setMaximum(duration / 1000);
}

void VideoPreview::positionChanged(qint64 progress) {
  if (not m_slider->isSliderDown()) {
    m_slider->setValue(progress / 1000);
  }
  updateDurationInfo(progress / 1000);
}

void VideoPreview::seek(int seconds) { m_player->setPosition(seconds * 1000); }

void VideoPreview::statusChanged(QMediaPlayer::MediaStatus status) {
  handleCursor(status);

  switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::EndOfMedia:
      QApplication::alert(this);
      break;
  }
}

void VideoPreview::handleCursor(QMediaPlayer::MediaStatus status) {
#ifndef QT_NO_CURSOR
  if (status == QMediaPlayer::LoadingMedia ||
      status == QMediaPlayer::BufferingMedia ||
      status == QMediaPlayer::StalledMedia) {
    setCursor(QCursor(Qt::BusyCursor));
  } else {
    unsetCursor();
  }
#endif
}

void VideoPreview::videoAvailableChanged(bool available) {
  if (!available) {
    disconnect(m_fullScreenButton, SIGNAL(clicked(bool)), m_videoWidget,
               SLOT(setFullScreen(bool)));
    disconnect(m_videoWidget, SIGNAL(fullScreenChanged(bool)),
               m_fullScreenButton, SLOT(setChecked(bool)));
    m_videoWidget->setFullScreen(false);
  } else {
    connect(m_fullScreenButton, SIGNAL(clicked(bool)), m_videoWidget,
            SLOT(setFullScreen(bool)));
    connect(m_videoWidget, SIGNAL(fullScreenChanged(bool)), m_fullScreenButton,
            SLOT(setChecked(bool)));

    if (m_fullScreenButton->isChecked()) {
      m_videoWidget->setFullScreen(true);
    }
  }
}

void VideoPreview::updateDurationInfo(qint64 currentInfo) {
  QString tStr;
  if (currentInfo > 0 || m_duration > 0) {
    QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
                      currentInfo % 60, (currentInfo * 1000) % 1000);
    QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
                    m_duration % 60, (m_duration * 1000) % 1000);
    QString format = "mm:ss";
    if (m_duration > 3600) {
      format = "hh:mm:ss";
    }
    tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
  }
}
