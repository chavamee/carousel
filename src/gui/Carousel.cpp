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

#include <QFileDialog>
#include <QFileInfo>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>

#include <memory>
#include <string>

#include "../app/command/CopyFile.hpp"
#include "../app/command/FileCommand.hpp"
#include "../app/command/HardRemoveFile.hpp"
#include "../app/command/MoveFile.hpp"
#include "../app/command/RenameFile.hpp"
#include "../app/command/SoftRemoveFile.hpp"
#include "Carousel.hpp"
#include "Previewers.hpp"

using std::unique_ptr;
using std::make_unique;
using std::make_tuple;

Carousel::Carousel(QWidget* parent, QSharedPointer<Directory> directory)
    : QWidget(parent), m_directory(directory) {
  createGrid();
  setFocusPolicy(Qt::StrongFocus);
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Carousel::createGrid() {
  m_grid = new QGridLayout;

  auto northButton = new QPushButton;
  northButton->setFocusPolicy(Qt::NoFocus);
  connect(northButton, SIGNAL(clicked()), this, SLOT(northButtonPushed()));
  m_grid->addWidget(northButton, 0, 1, 1, 1, Qt::AlignCenter);
  m_directories[Direction::North] = make_tuple("", northButton);

  auto southButton = new QPushButton;
  southButton->setFocusPolicy(Qt::NoFocus);
  connect(southButton, SIGNAL(clicked()), this, SLOT(southButtonPushed()));
  m_grid->addWidget(southButton, 2, 1, 1, 1, Qt::AlignCenter);
  m_directories[Direction::South] = make_tuple("", southButton);

  auto eastButton = new QPushButton;
  eastButton->setFocusPolicy(Qt::NoFocus);
  connect(eastButton, SIGNAL(clicked()), this, SLOT(eastButtonPushed()));
  m_grid->addWidget(eastButton, 1, 2, 1, 1, Qt::AlignCenter);
  m_directories[Direction::East] = make_tuple("", eastButton);

  auto westButton = new QPushButton;
  westButton->setFocusPolicy(Qt::NoFocus);
  connect(westButton, SIGNAL(clicked()), this, SLOT(westButtonPushed()));
  m_grid->addWidget(westButton, 1, 0, 1, 1, Qt::AlignCenter);
  m_directories[Direction::West] = make_tuple("", westButton);

  auto vlayout = new QVBoxLayout;
  m_filePreview = Previewers::GetPreviewForFile(this, m_directory->Current());
  m_filePreview->setGeometry(QRect(x(), y(), width() * 0.5, height() * 0.5));
  vlayout->addWidget(m_filePreview);
  m_filePreview->Show(m_directory->Current());

  auto hlayout = new QHBoxLayout;
  m_nameEdit = new QLineEdit;
  m_nameEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  m_nameEdit->setFocusPolicy(Qt::ClickFocus);
  hlayout->addWidget(m_nameEdit);
  m_nameEdit->setText(m_directory->Current().fileName());

  m_confirmNameEditButton = new QPushButton;
  m_confirmNameEditButton->setFocusPolicy(Qt::NoFocus);
  m_confirmNameEditButton->setSizePolicy(QSizePolicy::Minimum,
                                         QSizePolicy::Minimum);
  connect(m_confirmNameEditButton, SIGNAL(clicked()), this,
          SLOT(confirmNameEditPushed()));
  hlayout->addWidget(m_confirmNameEditButton);

  vlayout->addLayout(hlayout);

  m_grid->addLayout(vlayout, 1, 1, 1, 1, Qt::AlignCenter);

  setLayout(m_grid);
}

void Carousel::northButtonPushed() { buttonPushed(Direction::North); }

void Carousel::southButtonPushed() { buttonPushed(Direction::South); }

void Carousel::eastButtonPushed() { buttonPushed(Direction::East); }

void Carousel::westButtonPushed() { buttonPushed(Direction::West); }

void Carousel::confirmNameEditPushed() {
  if (m_nameEdit->text() == m_directory->Current().fileName()) {
    return;
  }

  auto currentFile = m_directory->Current();
  try {
    unique_ptr<RenameFile> command =
        make_unique<RenameFile>(currentFile, m_nameEdit->text());
    command->Exec();
    workingDirectoryModified();

    if (command->IsReversible()) {
      m_commandStack.Add(std::move(command), currentFile);
    }
  } catch (std::exception& e) {
  }
}

void Carousel::undo() {
  Command* command = nullptr;
  QFileInfo file;
  std::tie(command, file) = m_commandStack.Undo();
  try {
    if (command->IsReversible()) {
      command->Undo();
    }
  } catch (std::exception& e) {
  }

  if (typeid(command) != typeid(FileCommand<CopyFile>)) {
    workingDirectoryModified(&file);
  } else {
    workingDirectoryModified();
  }
}

void Carousel::redo() {
  Command* command = nullptr;
  QFileInfo file;
  std::tie(command, file) = m_commandStack.Redo();
  try {
    command->Exec();
  } catch (std::exception& e) {
  }

  if (typeid(*command) != typeid(FileCommand<CopyFile>)) {
    workingDirectoryModified();
  }
}

void Carousel::buttonPushed(Direction direction) {
  QString destinationPath = QFileDialog::getExistingDirectory(this);
  if (not destinationPath.isEmpty()) {
    if (destinationPath == m_directory->AbsolutePath()) {
      QMessageBox::warning(
          this, "Carousel",
          "Cannot select the same directory as the working directory");
      return;
    }

    std::get<0>(m_directories[direction]) = destinationPath;
    std::get<1>(m_directories[direction])
        ->setText(QFileInfo(destinationPath).fileName());
  }
}

void Carousel::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Left:
      fileUpdated(m_directory->Prev());
      break;
    case Qt::Key_Right:
      fileUpdated(m_directory->Next());
      break;
    case Qt::Key_J:
      processDirectionalCommandKey(Direction::South, event);
      break;
    case Qt::Key_H:
      processDirectionalCommandKey(Direction::West, event);
      break;
    case Qt::Key_K:
      processDirectionalCommandKey(Direction::North, event);
      break;
    case Qt::Key_L:
      processDirectionalCommandKey(Direction::East, event);
      break;
    case Qt::Key_R:
      processRemoveKey(event);
      break;
  }
}

void Carousel::workingDirectoryModified(QFileInfo* restoredFile) {
  QFileInfo file;
  if (restoredFile != nullptr) {
    file = *restoredFile;
  } else {
    file = m_directory->Next();
  }
  m_directory = QSharedPointer<Directory>::create(m_directory->AbsolutePath());

  if (not m_directory->ResetToFile(file)) {
    m_directory->ResetToPos(0);
  }

  file = m_directory->Current();
  m_filePreview->hide();
  m_filePreview = Previewers::GetPreviewForFile(this, file);
  m_filePreview->Show(file);
  m_nameEdit->setText(m_directory->Current().fileName());
}

void Carousel::fileUpdated(QFileInfo newFile) {
  m_filePreview->hide();
  QLayoutItem* replacedItem = m_grid->replaceWidget(
      m_filePreview, Previewers::GetPreviewForFile(this, newFile));
  if (replacedItem != nullptr) {
    delete replacedItem;
  }

  m_filePreview = Previewers::GetPreviewForFile(this, newFile);
  m_filePreview->Show(newFile);
  m_nameEdit->setText(m_directory->Current().fileName());
}

void Carousel::processDirectionalCommandKey(Direction direction,
                                            QKeyEvent* event) {
  QString path = std::get<0>(m_directories[direction]);
  if (path.isEmpty()) {
    QMessageBox::warning(this, "Carousel", "Select a directory first");
    return;
  }

  if (not QDir(path).exists()) {
    QMessageBox::critical(this, "Carousel",
                          path + QString(" no longer exist."));
    return;
  }

  auto currentFile = m_directory->Current();
  unique_ptr<Command> command;
  if (event->text().at(0).isUpper()) {
    command = make_unique<FileCommand<CopyFile>>(currentFile, path);
  } else if (event->text().at(0).isLower()) {
    command = make_unique<FileCommand<MoveFile>>(currentFile, path);
  }

  if (command != nullptr) {
    try {
      command->Exec();
      if (typeid(*command) != typeid(FileCommand<CopyFile>)) {
        workingDirectoryModified();
      }

    } catch (std::exception& e) {
    }

    if (command->IsReversible()) {
      m_commandStack.Add(std::move(command), currentFile);
    }
  }
}

void Carousel::processRemoveKey(QKeyEvent* event) {
  auto currentFile = m_directory->Current();
  unique_ptr<Command> command;
  if (event->text().at(0).isLower()) {
    command = make_unique<FileCommand<SoftRemoveFile>>(currentFile);
  } else if (event->text().at(0).isUpper()) {
    QMessageBox msgBox;
    msgBox.setText("This action is permanent.");
    msgBox.setInformativeText("Continue?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if (msgBox.exec() == QMessageBox::Yes) {
      command = make_unique<FileCommand<HardRemoveFile>>(currentFile);
    } else {
      return;
    }
  }

  if (command != nullptr) {
    try {
      command->Exec();
      workingDirectoryModified();
    } catch (std::exception& e) {
    }

    if (command->IsReversible()) {
      m_commandStack.Add(std::move(command), currentFile);
    }
  }
}
