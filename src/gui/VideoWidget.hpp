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

#ifndef CAROUSEL_GUI_VIDEOWIDGET_H
#define CAROUSEL_GUI_VIDEOWIDGET_H

#include <QVideoWidget>

class VideoWidget : public QVideoWidget {
  Q_OBJECT

 public:
  VideoWidget(QWidget *parent = 0);

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
};

#endif  // CAROUSEL_GUI_VIDEOWIDGET_H
