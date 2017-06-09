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

#ifndef CAROUSEL_APP_COMMAND_HARDREMOVEFILE_H
#define CAROUSEL_APP_COMMAND_HARDREMOVEFILE_H

#include <QFileInfo>

#include "Command.hpp"

/**
 * Responsible for file system remove commands.
 *
 * This command is inherently irreversible.
 */
class HardRemoveFile : public Command {
 public:
  /**
   * Constructor
   *
   * @param file the file to remove
   */
  HardRemoveFile(const QFileInfo& file);

  /**
   * Execute the command and remove file
   */
  void Exec() override;

  /**
   * Since HardRemoveFile is a permanent operation this is left empty.
   */
  void Undo() override {}

  /**
   * Check if the command is reversible.
   *
   * @return this will always return false.
   */
  bool IsReversible() override { return false; }

 private:
  QFileInfo m_file;
};

#endif  // CAROUSEL_APP_COMMAND_HARDREMOVEFILE_H
