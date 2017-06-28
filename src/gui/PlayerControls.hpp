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

#include <QSlider>
#include <QMediaPlayer>
#include <QWidget>

class QAbstractButton;

class PlayerControls : public QWidget {
  Q_OBJECT

 public:
  PlayerControls(const QMediaPlayer& player, QWidget* parent = 0);

  inline QMediaPlayer::State State() const { return m_playerState; }
  inline bool IsMuted() const { return m_playerMuted; }
  void SetMaximumDuration(qint64 duration);
  void SetPosition(qint64 position);
  inline bool IsSliderDown() { m_slider->isSliderDown(); }

 public slots:
  void SetState(QMediaPlayer::State state);
  void SetMuted(bool muted);

 signals:
  void Play();
  void Pause();
  void SliderMoved(int);
  void SliderReleased();

  void ChangeMuting(bool muting);

 private slots:
  void playClicked();
  void muteClicked();
  void sliderMoved(int seconds);
  void sliderReleased();

 private:
  QMediaPlayer::State m_playerState = QMediaPlayer::StoppedState;
  bool m_playerMuted = false;
  QAbstractButton* m_playButton = nullptr;
  QAbstractButton* m_muteButton = nullptr;
  QSlider* m_slider = nullptr;
};

#endif  // CAROUSEL_GUI_PLAYERCONTROLS_H
