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

#include "MoveFile.hpp"

MoveFile::MoveFile(QFileInfo file, QString to)
    : m_file(file), m_origin(file.absolutePath()), m_destination(to) {}

void MoveFile::Exec() {
  if (not m_file.exists()) {
    throw std::runtime_error("File does not exist");
  }

  if (not QDir(m_destination).exists()) {
    throw std::runtime_error("Destination does not exist");
  }

  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (QFile::exists(full_destination_path)) {
    throw std::runtime_error("File already exists");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(full_destination_path)) {
    throw std::runtime_error("Failed to copy file");
  }

  m_file = QFileInfo(file);
}

void MoveFile::Undo() {
  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (not QFile::exists(full_destination_path)) {
    throw std::runtime_error("Copy no longer exists");
  }

  QFile file(full_destination_path);
  if (not QFile(full_destination_path)
              .rename(m_origin + "/" + m_file.fileName())) {
    throw std::runtime_error("Failed to undo copy");
  }

  m_file = QFileInfo(file);
}

bool MoveFile::IsReversible() {
  QString full_destination_path = m_destination + "/" + m_file.fileName();
  if (not QFile::exists(full_destination_path)) {
    return false;
  }
  return true;
}
