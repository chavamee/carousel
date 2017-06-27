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

#include <stdexcept>
#include <utility>

#include "Command.hpp"

/**
 * Defines an object to be thrown as an exception of a FileCommand.
 */
class FileCommandException : public std::runtime_error {
 public:
  FileCommandException(const char* what_arg)
      : std::runtime_error(what_arg), m_what(what_arg) {}

  virtual const char* what() const noexcept { return m_what; }

 private:
  const char* m_what = nullptr;
};

/**
 * Provides an interface for filesystem specific
 * command execution and undo-ability.
 */
template <class T>
class FileCommand : public Command {
 public:
  template <typename... Args>
  FileCommand(QFileInfo file, Args&&... args)
      : m_command(file, std::forward<Args>(args)...) {}

  /**
   * Execute a command
   */
  void Exec() override { m_command.Exec(); }

  /**
   * Undo command
   */
  void Undo() override { m_command.Undo(); }

  /**
   * Check if the command is reversible.
   *
   * @return true if the command can be undone,
   *         false otherwise
   */
  bool IsReversible() override { return m_command.IsReversible(); }

 private:
  T m_command;
};

#endif  // CAROUSEL_APP_COMMAND_FILECOMMAND_H
