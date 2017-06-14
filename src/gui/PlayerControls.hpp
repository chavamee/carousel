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

#ifndef CAROUSEL_GUI_PLAYERCONTROLS_H
#define CAROUSEL_GUI_PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>

class QAbstractButton;

class PlayerControls : public QWidget {
  Q_OBJECT

 public:
  PlayerControls(QWidget* parent = 0);

  inline QMediaPlayer::State State() const { return m_playerState; }
  inline bool IsMuted() const { return m_playerMuted; }

 public slots:
  void SetState(QMediaPlayer::State state);
  void SetMuted(bool muted);

 signals:
  void Play();
  void Pause();

  void ChangeMuting(bool muting);

 private slots:
  void playClicked();
  void muteClicked();

 private:
  QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
  bool m_playerMuted = false;
  QAbstractButton* m_playButton = nullptr;
  QAbstractButton* m_muteButton = nullptr;
};

#endif  // CAROUSEL_GUI_PLAYERCONTROLS_H
