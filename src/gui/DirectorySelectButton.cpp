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

#include "DirectorySelectButton.hpp"

DirectorySelectButton::DirectorySelectButton() : QPushButton(nullptr) {}

DirectorySelectButton::DirectorySelectButton(QWidget* parent)
    : QPushButton(parent) {}

void DirectorySelectButton::setColor(QColor color) {
  m_color = color;
  const QString startingButtonStyle =
    "QPushButton:hover { \
          background: rgb(112, 112, 112, 255) \
     } \
     QPushButton { \
          border:none; \
          margin: 0px; padding: 0px; \
          background: rgb(%1, %2, %3, %4); \
     }";

    setStyleSheet(startingButtonStyle
                      .arg(color.red())
                      .arg(color.green())
                      .arg(color.blue())
                      .arg(color.alpha()));
}
