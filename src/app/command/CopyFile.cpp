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

#include <QDir>

#include "CopyFile.hpp"

CopyFile::CopyFile(const QFileInfo& file, QString to)
    : m_file(file),
      m_origin(file.absolutePath()),
      m_destination(std::move(to)) {}

void CopyFile::Exec() {
  if (not m_file.exists()) {
    throw std::runtime_error("File does not exist");
  }

  if (not QDir(m_destination).exists()) {
    throw std::runtime_error("Destination does not exist");
  }

  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (QFile(full_destination_path).exists()) {
    throw std::runtime_error("File already exists");
  }

  if (not QFile(m_file.absoluteFilePath()).copy(full_destination_path)) {
    throw std::runtime_error("Failed to copy file");
  }
}

void CopyFile::Undo() {
  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (not QFile::exists(full_destination_path)) {
    throw std::runtime_error("Copy no longer exists");
  }

  if (not QFile(full_destination_path).remove()) {
    throw std::runtime_error("Failed to undo copy");
  }
}

bool CopyFile::IsReversible() {
  QString full_destination_path = m_destination + "/" + m_file.fileName();
  return QFile::exists(full_destination_path);
}
