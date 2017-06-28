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

#ifndef CAROUSEL_GUI_VIDEOPREVIEW_H
#define CAROUSEL_GUI_VIDEOPREVIEW_H

#include <QMediaPlayer>

#include "FilePreview.hpp"
#include "VideoWidget.hpp"

class QLabel;
class QMediaPlayer;
class QPushButton;
class QSlider;
class QVideoWidget;

class PlayerControls;

class VideoPreview : public FilePreview {
  Q_OBJECT

 public:
  VideoPreview(QWidget* parent);

  void Show(QFileInfo file) override;

  bool IsPlayerAvailable() const;

 protected:
  void focusOutEvent(QFocusEvent* event);

 signals:
  void FullScreenChanged(bool fullScreen);

 private slots:
  void durationChanged(qint64 duration);
  void positionChanged(qint64 progress);

  void seekBy(int seconds);
  void seekEnd();

  void statusChanged(QMediaPlayer::MediaStatus status);
  void videoAvailableChanged(bool available);

 private:
  void handleCursor(QMediaPlayer::MediaStatus status);
  void updateDurationInfo(qint64 currentInfo);

  QMediaPlayer* m_player = nullptr;
  VideoWidget* m_videoWidget = nullptr;
  PlayerControls* m_controls = nullptr;
  QPushButton* m_fullScreenButton = nullptr;
  qint64 m_duration = 0;
  QAtomicInt m_currentPosition;
};

#endif  // CAROUSEL_GUI_VIDEOPREVIEW_H
