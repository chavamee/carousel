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

#include <QKeyEvent>
#include <QMouseEvent>

#include "VideoWidget.hpp"

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent) {
  setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, Qt::black);
  setPalette(palette);

  setAttribute(Qt::WA_OpaquePaintEvent);
}

void VideoWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Escape && isFullScreen()) {
    setFullScreen(false);
    event->accept();
  } else if (event->key() == Qt::Key_Enter &&
             event->modifiers() & Qt::Key_Alt) {
    setFullScreen(not isFullScreen());
    event->accept();
  } else {
    QVideoWidget::keyPressEvent(event);
  }
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event) {
  setFullScreen(not isFullScreen());
  event->accept();
}

void VideoWidget::mousePressEvent(QMouseEvent *event) {
  QVideoWidget::mousePressEvent(event);
}
