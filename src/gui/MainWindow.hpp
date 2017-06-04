/**
 * @file
 * Contains MainWindow class; a reimplementation of QMainWindow and responsible
 * for managing state for the Carousel widget.
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

#ifndef CAROUSEL_GUI_MAINWINDOW_H
#define CAROUSEL_GUI_MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>

#include <memory>

#include "Carousel.hpp"

class Directory;

/**
 * Reimplementation of QMainWindow and responsible for manging state
 * of the Carousel widget.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * Constructor
   */
  MainWindow(QString directoryPath = QString());

 protected:
  /**
   * Reimplementation of QMainWindow's closeEvent.
   *
   * @param event The close event object
   */
  void closeEvent(QCloseEvent *event) override;

 private slots:
  /**
   * Open action handler slot.
   */
  void open();

  /**
   * About action handler slot.
   */
  void about();

  /**
   * Undo action handler slot.
   */
  void undo();

  /**
   * Redo action handler slot.
   */
  void redo();

 private:
  /**
   * Create the MainWindow's action objects.
   */
  void createActions();

  /**
   * Create the MainWindow's status bar.
   */
  void createStatusBar();

  /**
   * Create initial splash view widget.
   */
  void createSplashView();

  QSharedPointer<Directory> m_currentDirectory;
  Carousel *m_carousel = nullptr;
};

#endif  // CAROUSEL_GUI_MAINWINDOW_H
