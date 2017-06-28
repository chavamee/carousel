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

#include <QAudio>
#include <QBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QStyle>
#include <QToolButton>

#include "PlayerControls.hpp"

PlayerControls::PlayerControls(const QMediaPlayer& player, QWidget* parent)
    : QWidget(parent) {
  m_playButton = new QToolButton(this);
  m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

  connect(m_playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

  m_muteButton = new QToolButton(this);
  m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

  connect(m_muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

  m_slider = new QSlider(Qt::Horizontal, this);
  m_slider->setRange(0, player.duration() / 1000);

  connect(m_slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderMoved(int)));
  connect(m_slider, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));

  auto layout = new QHBoxLayout;
  layout->addWidget(m_playButton);
  layout->addWidget(m_slider);
  layout->addWidget(m_muteButton);
  setLayout(layout);
}

void PlayerControls::SetState(QMediaPlayer::State state) {
  if (state != m_playerState) {
    m_playerState = state;

    switch (state) {
      case QMediaPlayer::PlayingState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
      case QMediaPlayer::StoppedState:
      case QMediaPlayer::PausedState:
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
  }
}

void PlayerControls::SetMuted(bool muted) {
  if (muted != m_playerMuted) {
    m_playerMuted = muted;

    m_muteButton->setIcon(style()->standardIcon(
        muted ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
  }
}

void PlayerControls::SetMaximumDuration(qint64 duration) {
  m_slider->setMaximum(duration);
}

void PlayerControls::SetPosition(qint64 position) {
  m_slider->setValue(position);
}

void PlayerControls::playClicked() {
  switch (m_playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
      emit Play();
      break;
    case QMediaPlayer::PlayingState:
      emit Pause();
      break;
  }
}

void PlayerControls::sliderMoved(int seconds) { emit SliderMoved(seconds); }

void PlayerControls::sliderReleased() { emit SliderReleased(); }

void PlayerControls::muteClicked() { emit ChangeMuting(!m_playerMuted); }
