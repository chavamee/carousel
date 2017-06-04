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

#include "RenameFile.hpp"

RenameFile::RenameFile(QFileInfo info, QString newName)
    : m_file(info), m_originalName(info.fileName()), m_newName(newName) {}

void RenameFile::Exec() {
  if (not m_file.exists()) {
    throw std::runtime_error("File does not exist");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(m_file.absolutePath() + "/" + m_newName)) {
    throw std::runtime_error("Failed to rename file");
  }

  m_file = QFileInfo(file);
}

void RenameFile::Undo() {
  if (not m_file.exists()) {
    throw std::runtime_error("File does not exist");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(m_file.absolutePath() + "/" + m_originalName)) {
    throw std::runtime_error("Failed to rename file");
  }

  m_file = QFileInfo(file);
}
