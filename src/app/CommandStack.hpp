/**
 * @file
 * Contains CommandStack class responsible for filesystem command management
 * and retrieval.
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

#ifndef CAROUSEL_APP_COMMANDSTACK_H
#define CAROUSEL_APP_COMMANDSTACK_H

#include <QFileInfo>

#include <memory>
#include <tuple>
#include <vector>

#include "command/Command.hpp"
/**
 * Responsible for command management and retrieval.
 */
class CommandStack {
 public:
  /**
   * Local alias of size_t
   */
  using size_type = std::size_t;

  /**
   * Add a command to the stack.
   *
   * @param command The command to add. The stack takes ownership.
   */
  void Add(std::unique_ptr<Command> command, const QFileInfo& file);

  /**
   * Get command reference that the stack index currently points to.
   *
   * @return command at stack index
   */
  std::tuple<Command*, QFileInfo> Current();

  /**
   * Move the stack index forward and return the object pointed by
   * the stack index.
   *
   * @return command object at stack index
   */
  std::tuple<Command*, QFileInfo> Redo();

  /**
   * Move the stack index backward and return the object pointed by
   * the stack index.
   *
   * @return command at stack index
   */
  std::tuple<Command*, QFileInfo> Undo();

  /**
   * Get command at a position in the stack.
   *
   * It is up to the caller to ensure that the position given is
   * within stack bounds. Otherwise, the call will throw.
   *
   * @param pos position of object to fetch
   *
   * @return command object at pos
   */
  std::tuple<Command*, QFileInfo> Get(size_type pos);

  /**
   * Erase objects past current stack index.
   */
  void Trim();

 private:
  std::vector<std::tuple<std::unique_ptr<Command>, QFileInfo>> m_stack;
  size_type m_index = 0;
};

#endif  // CAROUSEL_APP_COMMANDSTACK_H
