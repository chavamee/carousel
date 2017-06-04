/**
 * @file
 * Contains FilePreview base class which provides an interface for QWidget
 * impemantations that provide file specific previews.
 */
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

#ifndef CAROUSEL_GUI_FILEPREVIEW_H
#define CAROUSEL_GUI_FILEPREVIEW_H

#include <QFileInfo>
#include <QWidget>

/**
 * Provides an interface for QWidget impemantations
 * that provide file specific previews.
 */
class FilePreview : public QWidget {
 public:
  /**
   * Constructor
   */
  FilePreview(QWidget* parent = nullptr) : QWidget(parent) {}

  /**
   * Show a preview for a given file.
   *
   * @param file The file to preview
   */
  virtual void Show(QFileInfo file) = 0;
};

#endif  // CAROUSEL_GUI_FILEPREVIEW_H
