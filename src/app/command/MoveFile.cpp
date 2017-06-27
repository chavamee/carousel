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

#include "FileCommand.hpp"
#include "MoveFile.hpp"

MoveFile::MoveFile(const QFileInfo& file, QString to)
    : m_file(file),
      m_origin(file.absolutePath()),
      m_destination(std::move(to)) {}

void MoveFile::Exec() {
  if (not m_file.exists()) {
    throw FileCommandException("File does not exist");
  }

  if (not QDir(m_destination).exists()) {
    throw FileCommandException("Destination does not exist");
  }

  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (QFile::exists(full_destination_path)) {
    throw FileCommandException("File already exists");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(full_destination_path)) {
    throw FileCommandException("Failed to move file");
  }

  m_file = QFileInfo(file);
}

void MoveFile::Undo() {
  if (not m_file.exists()) {
    throw FileCommandException("Moved file no longer exists");
  }

  if (not QDir(m_origin).exists()) {
    throw FileCommandException("Origin does not exist");
  }

  QString full_destination_path = m_origin + "/" + m_file.fileName();
  if (QFile::exists(full_destination_path)) {
    throw FileCommandException("File already exists");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(full_destination_path)) {
    throw FileCommandException("Failed to undo move");
  }

  m_file = QFileInfo(file);
}

bool MoveFile::IsReversible() {
  QString full_destination_path = m_destination + "/" + m_file.fileName();
  return QFile::exists(full_destination_path);
}
