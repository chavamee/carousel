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

PlayerControls::PlayerControls(QWidget *parent) : QWidget(parent) {
  m_playButton = new QToolButton(this);
  m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

  connect(m_playButton, SIGNAL(clicked()), this, SLOT(playClicked()));

  m_muteButton = new QToolButton(this);
  m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

  connect(m_muteButton, SIGNAL(clicked()), this, SLOT(muteClicked()));

  auto layout = new QHBoxLayout;
  layout->addWidget(m_playButton);
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

void PlayerControls::muteClicked() { emit ChangeMuting(!m_playerMuted); }
