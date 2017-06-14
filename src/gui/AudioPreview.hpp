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

#ifndef CAROUSEL_GUI_AUDIOPREVIEW_H
#define CAROUSEL_GUI_AUDIOPREVIEW_H

#include <QMediaPlayer>

#include "FilePreview.hpp"

class QLabel;
class QMediaPlayer;
class QPushButton;
class QSlider;

class PlayerControls;

class AudioPreview : public FilePreview {
  Q_OBJECT

 public:
  AudioPreview(QWidget* parent);

  void Show(QFileInfo file) override;

  bool IsPlayerAvailable() const;

 protected:
  void focusOutEvent(QFocusEvent* event);

 signals:
  void FullScreenChanged(bool fullScreen);

 private slots:
  void durationChanged(qint64 duration);
  void positionChanged(qint64 progress);

  void seek(int seconds);

  void statusChanged(QMediaPlayer::MediaStatus status);

 private:
  void handleCursor(QMediaPlayer::MediaStatus status);
  void updateDurationInfo(qint64 currentInfo);

  QMediaPlayer* m_player = nullptr;
  PlayerControls* m_controls = nullptr;
  QSlider* m_slider = nullptr;
  qint64 m_duration = 0;
};

#endif
