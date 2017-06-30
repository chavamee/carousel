/**
 * @file
 * Contains Previewers class responsible for detecting file types and
 * creating previewers appropriate for those types.
 *
 * Previewers lazily initializes the concrete previewers. In other words,
 * a previewer for a certain FileType will not be created until the first
 * time it is used. When it is created, the object is stored and retrieved
 * when it is need again.
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

#ifndef CAROUSEL_GUI_PREVIEWERS_H
#define CAROUSEL_GUI_PREVIEWERS_H

#include <QFileInfo>
#include <QMimeType>
#include <QWidget>

#include "FilePreview.hpp"

class Previewers {
  /**
   * Enumeration identifying general file media types.
   */
  enum class FileType { Unkown, Image, Video, Audio, Text };

 public:
  /**
   * Get a preview appropriate for the given file.
   *
   * This functions initializes the previewer for the first time if it wasn't
   * created on a previous call. If it is already created, it simply returns the
   * corresponding previewer.
   *
   * @param parent The parent widget for the previewer
   * @param file The file to preview
   */
  FilePreview* GetPreviewForFile(QWidget* parent, const QFileInfo& file);

 private:
  bool isImage(const QMimeType& type);
  bool isVideo(const QMimeType& type);
  bool isAudio(const QMimeType& type);

  static std::map<FileType, FilePreview*> m_previewers;
};

#endif  // CAROUSEL_GUI_PREVIEWERS_H
