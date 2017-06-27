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

#include "HardRemoveFile.hpp"
#include "FileCommand.hpp"

HardRemoveFile::HardRemoveFile(const QFileInfo& file) : m_file(file) {}

void HardRemoveFile::Exec() {
  if (not m_file.exists()) {
    throw FileCommandException("File does not exist");
  }

  if (not QFile(m_file.absoluteFilePath()).remove()) {
    throw FileCommandException("Failed to remove file");
  }
}
