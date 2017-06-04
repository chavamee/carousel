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

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "../gui/MainWindow.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("chavamee");
  QCoreApplication::setApplicationName("Carousel");
  QCoreApplication::setApplicationVersion(QT_VERSION_STR);

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::applicationName());
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("directory", "A directory to open");
  parser.process(app);

  QString argDirectory;
  if (not parser.positionalArguments().isEmpty()) {
    argDirectory = parser.positionalArguments().first();
  }

  MainWindow mainWin{argDirectory};
  mainWin.show();

  return app.exec();
}
