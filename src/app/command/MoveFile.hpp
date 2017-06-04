/**
 * @file
 * Contains HardRemoveFile responsible for file system remove commands.
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

#ifndef CAROUSEL_APP_COMMAND_MOVEFILE_H
#define CAROUSEL_APP_COMMAND_MOVEFILE_H

#include <QFileInfo>

#include "FileCommand.hpp"

/**
 * Responsible for file system remove commands.
 */
class MoveFile : public FileCommand {
 public:
  /**
   * Constructor
   *
   * @param file file to move
   * @param to   path to move the file to
   */
  MoveFile(QFileInfo file, QString to);

  /**
   * Execute command and move file.
   */
  void Exec() override;

  /**
   * Undo command and move file back.
   */
  void Undo() override;

  /**
   * Check if command is reversible
   *
   * @return true if the command can be undone,
   *         false otherwise
   */
  bool IsReversible() override;

  /**
   * Check if the command modifies the file directly.
   *
   * @return true if the command modifies it's file,
   *         false otherwise.
   */
  inline bool Modifies() override { return true; }

  /**
   * Return the command's file.
   *
   * @return the command file
   */
  inline QFileInfo File() { return m_file; }

 private:
  QFileInfo m_file;
  QString m_origin;
  QString m_destination;
};

#endif  // CAROUSEL_COMMAND_MOVEFILE_H
