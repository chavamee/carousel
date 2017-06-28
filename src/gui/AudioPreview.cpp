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

#include "AudioPreview.hpp"
#include "PlayerControls.hpp"

AudioPreview::AudioPreview(QWidget* parent) : FilePreview(parent) {
  m_player = new QMediaPlayer(this);

  connect(m_player, SIGNAL(durationChanged(qint64)),
          SLOT(durationChanged(qint64)));
  connect(m_player, SIGNAL(positionChanged(qint64)),
          SLOT(positionChanged(qint64)));
  connect(m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this,
          SLOT(statusChanged(QMediaPlayer::MediaStatus)));

  m_player->setVolume(50);

  m_controls = new PlayerControls(*m_player, this);
  m_controls->SetState(m_player->state());
  m_controls->SetMuted(m_controls->IsMuted());

  connect(m_controls, SIGNAL(Play()), m_player, SLOT(play()));
  connect(m_controls, SIGNAL(Pause()), m_player, SLOT(pause()));
  connect(m_controls, SIGNAL(ChangeMuting(bool)), m_player,
          SLOT(setMuted(bool)));
  connect(m_controls, SIGNAL(SliderMoved(int)), this, SLOT(seekBy(int)));
  connect(m_controls, SIGNAL(SliderReleased()), this, SLOT(seekEnd()));

  connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), m_controls,
          SLOT(SetState(QMediaPlayer::State)));
  connect(m_player, SIGNAL(mutedChanged(bool)), m_controls,
          SLOT(SetMuted(bool)));

  auto layout = new QHBoxLayout;
  layout->addWidget(m_controls);

  setLayout(layout);

  if (not IsPlayerAvailable()) {
    QMessageBox::warning(
        this, tr("Service not available"),
        tr("The QMediaPlayer object does not have a valid service.\n"
           "Please check the media service plugins are installed."));

    m_controls->setEnabled(false);
  }
}

void AudioPreview::Show(QFileInfo file) {
  m_player->stop();
  m_player->setMedia(QMediaContent());

  m_controls->SetState(QMediaPlayer::StoppedState);
  m_controls->SetMuted(false);
  m_controls->show();

  m_player->setMedia(QUrl::fromLocalFile(file.absoluteFilePath()));

  QWidget::show();
}

void AudioPreview::focusOutEvent(QFocusEvent *event) {
  if (event->lostFocus()) {
    m_player->stop();
  }
}

bool AudioPreview::IsPlayerAvailable() const { return m_player->isAvailable(); }

void AudioPreview::durationChanged(qint64 duration) {
  m_duration = duration / 1000;
  m_controls->SetMaximumDuration(duration / 1000);
}

void AudioPreview::positionChanged(qint64 progress) {
  if (not m_controls->IsSliderDown()) {
    m_controls->SetPosition(progress / 1000);
  }
  updateDurationInfo(progress / 1000);
}

void AudioPreview::seekBy(int seconds) { m_currentPosition.storeRelease(seconds * 1000); }

void AudioPreview::seekEnd() {
  int position = m_currentPosition.loadAcquire();
  m_player->setPosition(position);
}

void AudioPreview::statusChanged(QMediaPlayer::MediaStatus status) {
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

void AudioPreview::handleCursor(QMediaPlayer::MediaStatus status) {
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

void AudioPreview::updateDurationInfo(qint64 currentInfo) {
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
