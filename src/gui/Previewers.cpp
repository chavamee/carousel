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
#include "VideoPreview.hpp"

std::map<Previewers::FileType, FilePreview*> Previewers::m_previewers;

FilePreview* Previewers::GetPreviewForFile(QWidget* parent,
                                           const QFileInfo& file) {
  QMimeDatabase mimeDatabase;
  const QMimeType mimeType = mimeDatabase.mimeTypeForFile(file);
  if (isImage(mimeType)) {
    if (Previewers::m_previewers[FileType::Image] == nullptr) {
      Previewers::m_previewers[FileType::Image] = new ImagePreview(parent);
    }

    return Previewers::m_previewers[FileType::Image];
  }

  if (isVideo(mimeType)) {
    if (Previewers::m_previewers[FileType::Video] == nullptr) {
      Previewers::m_previewers[FileType::Video] = new VideoPreview(parent);
    }

    return Previewers::m_previewers[FileType::Video];
  }

  if (Previewers::m_previewers[FileType::Unkown] == nullptr) {
    Previewers::m_previewers[FileType::Unkown] = new IconPreview(parent);
  }

  return Previewers::m_previewers[FileType::Unkown];
}

bool Previewers::isImage(const QMimeType& type) {
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

bool Previewers::isVideo(const QMimeType& type) {
  std::array<QString, 2> supported_video_mime_types = {"video/mp4",
                                                       "video/webm"};

  for (auto& videoType : supported_video_mime_types) {
    if (type.inherits(videoType)) {
      return true;
    }
  }

  return false;
}
