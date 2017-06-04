/**
 * @file
 * Contains FileCommand which provides an interface for filesystem specific
 * command execution and undo-ability.
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

#ifndef CAROUSEL_APP_COMMAND_FILECOMMAND_H
#define CAROUSEL_APP_COMMAND_FILECOMMAND_H

#include <QFileInfo>

#include "Command.hpp"

/**
 * Provides an interface for filesystem specific
 * command execution and undo-ability.
 */
class FileCommand : public Command {
 public:
  /**
   * Execute a command
   */
  virtual void Exec() = 0;

  /**
   * Undo command
   */
  virtual void Undo() = 0;

  /**
   * Check if the command is reversible.
   *
   * @return true if the command ca be undone,
   *         false otherwise
   */
  virtual bool IsReversible() = 0;

  /**
   * Check if the command modifies a file directly
   *
   * @return true if the command modifies a file,
   *         false otherwise
   */
  virtual bool Modifies() = 0;

  /**
   * Get the file the command works on.
   *
   * @return the file information from the command
   */
  virtual QFileInfo File() { return QFileInfo(); };
};

#endif  // CAROUSEL_APP_COMMAND_FILECOMMAND_H
