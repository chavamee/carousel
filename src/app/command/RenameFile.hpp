/**
 * @file
 * Contains RenameFile responsible for file system rename commands.
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

#ifndef CAROUSEL_APP_COMMAND_RENAMEFILE_H
#define CAROUSEL_APP_COMMAND_RENAMEFILE_H

#include <QFileInfo>

#include "FileCommand.hpp"

class RenameFile : public FileCommand {
 public:
  /**
   * Constructor
   *
   * @param file the file to rename
   * @param newName new name to rename the file to
   */
  RenameFile(QFileInfo file, QString newName);

  /**
   * Execute command and rename file.
   */
  void Exec() override;

  /**
   * Undo command and rename file to original name.
   */
  void Undo() override;

  /**
   * Check if the command is reversible.
   */
  inline bool IsReversible() override { return m_file.exists(); }

  /**
   * Check if the command modifies the file directly.
   *
   * @return this always returns true
   */
  inline bool Modifies() override { return true; }

  /**
   * Get the command's file.
   *
   * @return the command's file
   */
  inline QFileInfo File() { return m_file; }

 private:
  QFileInfo m_file;
  QString m_originalName;
  QString m_newName;
};

#endif  // CAROUSEL_APP_COMMAND_RENAMEFILE_H
