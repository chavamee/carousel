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

#include "CommandStack.hpp"

using namespace std;

CommandStack::CommandStack() {}

void CommandStack::Add(unique_ptr<Command> command) {
  if (std::begin(m_stack) + m_index != std::end(m_stack)) {
    Trim();
  }
  m_stack.insert(std::begin(m_stack) + m_index, std::move(command));
  m_index += 1;
}

Command& CommandStack::Current() { return *m_stack.at(m_index); }

Command& CommandStack::Redo() {
  if (m_index < m_stack.size() - 1) {
    m_index += 1;
  }
  return *m_stack.at(m_index);
}

Command& CommandStack::Undo() {
  if (m_index > 0) {
    m_index -= 1;
  }
  return *m_stack.at(m_index);
}

Command& CommandStack::Get(size_type pos) { return *m_stack.at(pos); }

void CommandStack::Trim() {
  if (m_stack.empty()) {
    return;
  }
  m_stack.erase(std::begin(m_stack) + m_index + 1, std::end(m_stack));
}
