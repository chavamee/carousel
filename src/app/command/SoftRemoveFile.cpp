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

#include "SoftRemoveFile.hpp"

SoftRemoveFile::SoftRemoveFile(const QFileInfo& file) {
  if (QDir(QDir::homePath() + "/.Trash").exists()) {
    m_trashDirectory = QDir::homePath() + "/.Trash";
  } else if (QDir(QDir::homePath() + "/.local/share/Trash").exists()) {
    m_trashDirectory = QDir::homePath() + "/.local/share/Trash";
  } else {
    QDir shareDirectory(QDir::homePath() + "/.local/share/");
    if (not shareDirectory.mkdir("Trash")) {
      throw std::runtime_error("Could not find or create trash directory");
    }

    m_trashDirectory = QDir::homePath() + "/.local/share/Trash";
  }

  m_moveCommand = std::make_unique<MoveFile>(file, m_trashDirectory);
}

void SoftRemoveFile::Exec() { m_moveCommand->Exec(); }

void SoftRemoveFile::Undo() { m_moveCommand->Undo(); }

bool SoftRemoveFile::IsReversible() { return m_moveCommand->IsReversible(); }
