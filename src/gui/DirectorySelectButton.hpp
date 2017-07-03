/**
 * @file
 * Contains DirectorySelectButton class responsible for implementing a
 * directory selection push button
 * */
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

#include <QColor>
#include <QPushButton>

#ifndef CAROUSEL_GUI_DIRECTORYSELECTBUTTON_H
#define CAROUSEL_GUI_DIRECTORYSELECTBUTTON_H

class DirectorySelectButton : public QPushButton {
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)

 public:
  DirectorySelectButton();

  DirectorySelectButton(QWidget* parent);

  void setColor(QColor color);

  inline QColor color() { return m_color; }

 private:
  QColor m_color;
};

#endif
