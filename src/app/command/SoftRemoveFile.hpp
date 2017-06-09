/**
 * @file
 * Contains SoftRemoveFile responsible for file system trashing commands.
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

#ifndef CAROUSEL_APP_COMMAND_SOFTREMOVEFILE_H
#define CAROUSEL_APP_COMMAND_SOFTREMOVEFILE_H

#include <memory>

#include "MoveFile.hpp"

/**
 * Responsible for file system trashing commands.
 *
 * This command does not remove a file permanently but
 * rather moves it to the system's trash directory.
 */
class SoftRemoveFile : public Command {
 public:
  /**
   * Constructor
   *
   * @param file the file to remove
   */
  SoftRemoveFile(const QFileInfo& file);

  /**
   * Execute command and remove file.
   */
  void Exec() override;

  /**
   * Undo command and restore file.
   */
  void Undo() override;

  /**
   * Check if the command is reversible.
   *
   * @return true if the command can be undone,
   *         false otherwise
   */
  bool IsReversible() override;

 private:
  std::unique_ptr<MoveFile> m_moveCommand;
  QString m_trashDirectory;
};

#endif  // CAROUSEL_APP_COMMAND_SOFTREMOVEFILE_H
