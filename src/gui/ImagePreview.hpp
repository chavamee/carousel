/**
 * @file
 * Contains ImagePreview class responsible for providing previews for image
 * files.
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

#ifndef CAROUSEL_GUI_IMAGEPREVIEW_H
#define CAROUSEL_GUI_IMAGEPREVIEW_H

#include <QLabel>

#include "FilePreview.hpp"

/**
 * Provides previews for image files
 */
class ImagePreview : public FilePreview {
 public:
  /**
   * Constructor
   */
  ImagePreview(QWidget* parent);

  /**
   * Show a preview for the given file.
   *
   * If the provide file is not an image, nothing will be rendered.
   *
   * @param file The file to preview.
   */
  void Show(QFileInfo file) override;

 private:
  QLabel* m_label;
};

#endif  // CAROUSEL_GUI_IMAGEPREVIEW_H
