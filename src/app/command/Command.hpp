/**
 * @file
 * Contains Command which provides an interface for Command execution and
 * undo-ability.
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

#ifndef CAROUSEL_APP_COMMAND_COMMAND_H
#define CAROUSEL_APP_COMMAND_COMMAND_H

/**
 * Provides an interface for Command execution and undo-ability.
 */
class Command {
 public:
  /**
   * Execute the command
   */
  virtual void Exec() = 0;

  /**
   * Undo the command execution.
   */
  virtual void Undo() = 0;

  /**
   * Check if the command is reversible.
   *
   * @return true if the command can be undone,
   *         false otherwise
   */
  virtual bool IsReversible() = 0;
};

#endif  // CAROUSEL_APP_COMMAND_COMMAND_H
