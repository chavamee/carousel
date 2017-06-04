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

#include "Directory.hpp"

using namespace std;

Directory::Directory(const QString& path) : m_directory(path) {
  if (not m_directory.exists()) {
    throw std::runtime_error(
        std::string("Could not find directory with path: ") +
        path.toStdString());
  }

  m_files = m_directory.entryInfoList(QDir::Files);
}

QFileInfo Directory::Next() {
  if (m_index < (size_type)m_files.size() - 1) {
    m_index += 1;
  }
  return m_files.at(m_index);
}

QFileInfo Directory::Prev() {
  if (m_index > 0) {
    m_index -= 1;
  }
  return m_files.at(m_index);
}

QFileInfo Directory::Current() { return m_files.at(m_index); }

bool Directory::ResetToFile(QFileInfo file) {
  int interm_index = m_files.indexOf(file);
  if (interm_index == -1) {
    m_index = m_files.size() > 0 ? m_files.size() - 1 : 0;
    return false;
  } else {
    m_index = interm_index;
  }

  return true;
}

void Directory::ResetToPos(size_type pos) {
  if (pos >= (size_type)m_files.size()) {
    std::runtime_error("Position out of bounds");
  }
  m_index = pos;
}
