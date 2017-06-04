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

#include <QMimeDatabase>

#include "IconPreview.hpp"
#include "ImagePreview.hpp"
#include "Previewers.hpp"

std::map<Previewers::FileType, FilePreview*> Previewers::m_previewers;

FilePreview* Previewers::GetPreviewForFile(QWidget* parent, QFileInfo file) {
  QMimeDatabase mimeDatabase;
  const QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
  if (isImage(mimeType)) {
    if (Previewers::m_previewers[FileType::Image] != nullptr) {
      return Previewers::m_previewers[FileType::Image];
    } else {
      Previewers::m_previewers[FileType::Image] = new ImagePreview(parent);
      return Previewers::m_previewers[FileType::Image];
    }
  } else {
    FileType foundType = FileType::Unkown;
    if (Previewers::m_previewers[foundType] != nullptr) {
      return Previewers::m_previewers[foundType];
    } else {
      Previewers::m_previewers[foundType] = new IconPreview(parent);
      return Previewers::m_previewers[foundType];
    }
  }

  return nullptr;
}

bool Previewers::isImage(QMimeType type) {
  std::array<QString, 10> supported_image_mime_types = {
      "image/bmp",
      "image/gif",
      "image/jpeg",
      "image/png",
      "image/x-portable-graymap",
      "image/x-portable-bitmap",
      "image/x-portable-pixmap",
      "image/x-xbitmap",
      "image/x-xpixmap"};

  for (auto& imageType : supported_image_mime_types) {
    if (type.inherits(imageType)) {
      return true;
    }
  }

  return false;
}
