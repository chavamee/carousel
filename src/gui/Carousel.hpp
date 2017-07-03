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

#include <QLabel>
#include <QWidget>

#include "../app/CommandStack.hpp"
#include "../app/Directory.hpp"

#include "FilePreview.hpp"
#include "Previewers.hpp"

class DirectorySelectButton;

class QStackedWidget;
class QGridLayout;
class QLineEdit;
class QPushButton;
class QToolButton;

class Previewers;

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
  Carousel(QWidget* parent);

  /**
   * Undo a previous operation.
   */
  void undo();

  /**
   * Redo a previous undo.
   */
  void redo();

  /**
   * Set the working directory.
   *
   * @param directory the new working directory
   */
  void setWorkingDirectory(Directory& directory);

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
  void fileUpdated(const QFileInfo& newFile);

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
   * Further process a directional key event
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

  QGridLayout* m_grid = nullptr;
  QLineEdit* m_nameEdit = nullptr;
  QToolButton* m_confirmNameEditButton = nullptr;
  QStackedWidget* m_centralStack = nullptr;
  QLabel* m_centralText = nullptr;

  FilePreview* m_filePreview = nullptr;
  std::map<Direction, std::tuple<QString, DirectorySelectButton*>>
      m_directories;

  Directory m_directory;
  CommandStack m_commandStack;
  Previewers m_previewers;
};

#endif  // CAROUSEL_GUI_CAROUSEL_H
