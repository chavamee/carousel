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

#include "FileCommand.hpp"
#include "RenameFile.hpp"

RenameFile::RenameFile(const QFileInfo& file, QString newName)
    : m_file(file),
      m_originalName(file.fileName()),
      m_newName(std::move(newName)) {}

void RenameFile::Exec() {
  if (not m_file.exists()) {
    throw FileCommandException("File does not exist");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(m_file.absolutePath() + "/" + m_newName)) {
    throw FileCommandException("Failed to rename file");
  }

  m_file = QFileInfo(file);
}

void RenameFile::Undo() {
  if (not m_file.exists()) {
    throw FileCommandException("File does not exist");
  }

  QFile file(m_file.absoluteFilePath());
  if (not file.rename(m_file.absolutePath() + "/" + m_originalName)) {
    throw FileCommandException("Failed to rename file");
  }

  m_file = QFileInfo(file);
}
