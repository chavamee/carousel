/**
 * @file
 * Contains CopyFile responsible for file system copy commands.
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

#ifndef CAROUSEL_APP_COMMAND_COPYFILE_H
#define CAROUSEL_APP_COMMAND_COPYFILE_H

#include <QFileInfo>

#include "FileCommand.hpp"

/**
 * Responsible for file system copy commands.
 */
class CopyFile : public FileCommand {
 public:
  /**
   * Constructor
   *
   * @param file the file to copy
   * @param to   path to copy the file to
   */
  CopyFile(QFileInfo file, QString to);

  /**
   * Execute command and copy file.
   *
   * The call will throw if copying fails.
   */
  void Exec() override;

  /**
   * Undo command by remove the created copy.
   *
   * The call will throw if removing the copy fails.
   */
  void Undo() override;

  /**
   * Check if the command can be reversed.
   */
  bool IsReversible() override;

  /**
   * Check if the command modifies the original file.
   *
   * @return CopyFile will always return false.
   */
  inline bool Modifies() override { return false; }

 private:
  QFileInfo m_file;
  QString m_origin;
  QString m_destination;
};

#endif  // CAROUSEL_APP_COMMAND_COPYFILE_H
