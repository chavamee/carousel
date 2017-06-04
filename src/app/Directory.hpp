/**
 * @file
 * Contains Directory class responsible filesystem directory transversal.
 */
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

#ifndef CAROUSEL_APP_DIRECTORY_H
#define CAROUSEL_APP_DIRECTORY_H

#include <QDir>
#include <QFileInfo>
#include <string>

/**
 * Responsible filesystem directory transversal.
 *
 * Transversal works by keeping an index to the directory file list
 * and moving it forward and backwards as needed.
 */
class Directory {
 public:
  /**
   * Local alias for size_t
   */
  using size_type = std::size_t;

  /**
   * Constructor.
   *
   * If the given directory path does not exist or is invalid,
   * the constructor will throw.
   *
   * @param path path to a directory
   */
  Directory(const QString& path);

  /**
   * Return the next file in the directory.
   *
   * @return a file in the directory
   */
  QFileInfo Next();

  /**
   * Return the previous file in the directory.
   *
   * @return a file in the directory
   */
  QFileInfo Prev();

  /**
   * Return the current file in the directory.
   *
   * @return a file in the directory
   */
  QFileInfo Current();

  /**
   * Reset the list index to point to a file.
   *
   * @param file the file to reset the index to
   *
   * @return If the file exists return true,
   *         otherwise return false
   */
  bool ResetToFile(QFileInfo file);

  /**
   * Reset the index to the given position.
   *
   * It is up to the caller to ensure the position within the bounds
   * of the directory file list.
   *
   * @param pos position to reset to
   */
  void ResetToPos(size_type pos);

  /**
   * Get the size of the directory file list.
   *
   * @return size of the directory list
   */
  inline size_type Size() const { return m_files.size(); }

  /**
   * Check if the directory file list is empty
   *
   * @return true if it is empty, otherwise false
   */
  inline bool IsEmpty() const { return m_files.empty(); }

  /**
   * Get the absolute path of the directory.
   *
   * @return the absolute of this directory
   */
  inline QString AbsolutePath() const { return m_directory.absolutePath(); }

 private:
  QDir m_directory;
  QFileInfoList m_files;
  size_type m_index = 0;
};

#endif  // CAROUSEL_APP_DIRECTORY_H
