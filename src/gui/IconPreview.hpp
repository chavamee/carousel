/**
 * @file
 * Contains IconPreview class which provides file previews in the form of icons.
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

#ifndef CAROUSEL_GUI_ICONPREVIEW_H
#define CAROUSEL_GUI_ICONPREVIEW_H

#include <QLabel>

#include "FilePreview.hpp"

/**
 * Provides an icon based file preview.
 */
class IconPreview : public FilePreview {
 public:
  /**
   * Constructor
   */
  IconPreview(QWidget* parent);

  /**
   * Show a preview of the given file
   *
   * @param file The file to preview.
   */
  void Show(QFileInfo file) override;

 private:
  QLabel* m_label;
};

#endif  // CAROUSEL_GUI_ICONPREVIEW_H
