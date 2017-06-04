/**
 * @file
 * Contains Carousel class responsible for directory selection and command
 * management.
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

#ifndef CAROUSEL_GUI_CAROUSEL_H
#define CAROUSEL_GUI_CAROUSEL_H

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSharedPointer>
#include <QWidget>

#include "../app/CommandStack.hpp"
#include "../app/Directory.hpp"
#include "FilePreview.hpp"

/**
 * Responsible for directory selection and command management.
 */
class Carousel : public QWidget {
  Q_OBJECT

  /**
   * Enumeration indication directions for command keys and directory widgets.
   */
  enum class Direction {
    None,
    North, /** Up */
    South, /** Down */
    East,  /** Left */
    West   /** Right */
  };

 public:
  /**
   * Constructor
   *
   * @param parent This widget's parent.
   * @param directory A working directory.
   *
   */
  Carousel(QWidget* parent, QSharedPointer<Directory> directory);

  /**
   * Undo a previous operation.
   */
  void undo();

  /**
   * Redo a previous undo.
   */
  void redo();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 private slots:
  /**
   * North (Up) directory selection button pushed slot
   */
  void northButtonPushed();

  /**
   * South (down) directory selection button pushed slot
   */
  void southButtonPushed();

  /**
   * East (Right) directory selection button pushed slot
   */
  void eastButtonPushed();

  /**
   * West (Left) directory selection button pushed slot.
   */
  void westButtonPushed();

  /**
   * Confirm name edit pushed slot.
   */
  void confirmNameEditPushed();

 private:
  /**
   * Create the primary grid.
   */
  void createGrid();

  /**
   * General callback directory selection button events.
   *
   * This is called by direction button pushed functions.
   *
   * @param direction The direction of the button pushed
   */
  void buttonPushed(Direction direction);

  /**
   * File selection callback.
   *
   * This is called when the current file changes.
   *
   * @param newFile The new selected file
   */
  void fileUpdated(QFileInfo newFile);

  /**
   * Update the gui when the working directory is modified.
   *
   * This updates the file preview and name line edit widgets.
   *
   * @param restoredFile If not null, the the file preview and name edit will
   *                     be updated for this file.
   */
  void workingDirectoryModified(QFileInfo* restoredFile = nullptr);

  /**
   * Further process a directional key
   *
   * @param direction The Direction corresponding to the key
   * @param event     The event for the key
   */
  void processDirectionalCommandKey(Direction direction, QKeyEvent* event);

  /**
   * Further process a remove key event
   *
   * @param event The event for the key
   */
  void processRemoveKey(QKeyEvent* event);

  QGridLayout* m_grid;
  QLineEdit* m_nameEdit;
  QPushButton* m_confirmNameEditButton;
  FilePreview* m_filePreview;
  std::map<Direction, std::tuple<QString, QPushButton*>> m_directories;

  QSharedPointer<Directory> m_directory;
  CommandStack m_commandStack;
};

#endif  // CAROUSEL_GUI_CAROUSEL_H