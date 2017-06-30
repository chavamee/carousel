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

using std::string;

Directory::Directory(const QString& path) : m_directory(path) {
  if (not m_directory.exists()) {
    throw std::runtime_error(string("Could not find directory with path: ") +
                             path.toStdString());
  }

  m_files = m_directory.entryInfoList(QDir::Files);
}

Directory::Directory(const Directory& other)
    : m_directory(other.m_directory), m_files(other.m_files) {}

Directory::Directory(Directory&& other) noexcept
    : m_directory(other.m_directory), m_files(std::move(other.m_files)) {}

Directory& Directory::operator=(Directory other) {
  m_directory.swap(other.m_directory);
  m_files.swap(other.m_files);
  return *this;
}

QFileInfo Directory::Next() {
  if (m_index < static_cast<size_type>(m_files.size()) - 1) {
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

bool Directory::ResetToFile(const QFileInfo& file) {
  int interm_index = m_files.indexOf(file);
  if (interm_index == -1) {
    m_index = not m_files.empty() ? m_files.size() - 1 : 0;
    return false;
  }

  m_index = interm_index;

  return true;
}

void Directory::ResetToPos(size_type pos) {
  if (pos >= static_cast<size_type>(m_files.size())) {
    std::runtime_error("Position out of bounds");
  }
  m_index = pos;
}
