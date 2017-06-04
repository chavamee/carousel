#
# Carousel
# Copyright (C) 2017 Jorge Martinez Hernandez
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#

TEMPLATE = lib

CONFIG += staticlib

HEADERS += Directory.hpp \
  CommandStack.hpp \
  command/Command.hpp \
  command/FileCommand.hpp \
  command/CopyFile.hpp \
  command/MoveFile.hpp \
  command/RenameFile.hpp \
  command/SoftRemoveFile.hpp \
  command/HardRemoveFile.hpp

SOURCES += Directory.cpp \
  CommandStack.cpp \
  command/CopyFile.cpp \
  command/MoveFile.cpp \
  command/RenameFile.cpp \
  command/SoftRemoveFile.cpp \
  command/HardRemoveFile.cpp
