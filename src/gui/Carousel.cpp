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
#include <QGridLayout>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QStackedWidget>
#include <QStyle>
#include <QToolButton>

#include <memory>
#include <string>

#include "../app/command/CopyFile.hpp"
#include "../app/command/FileCommand.hpp"
#include "../app/command/HardRemoveFile.hpp"
#include "../app/command/MoveFile.hpp"
#include "../app/command/RenameFile.hpp"
#include "../app/command/SoftRemoveFile.hpp"

#include "Carousel.hpp"
#include "DirectorySelectButton.hpp"

using std::unique_ptr;
using std::make_unique;
using std::make_tuple;

Carousel::Carousel(QWidget* parent) : QWidget(parent) {
  createGrid();
  setFocusPolicy(Qt::StrongFocus);
}

void Carousel::createGrid() {
  const QString buttonStyle = " QPushButton { \
                              }";
  m_grid = new QGridLayout;

  auto northButton = new DirectorySelectButton;
  northButton->setFocusPolicy(Qt::NoFocus);
  northButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  northButton->setStyleSheet(buttonStyle);
  northButton->setColor(QColor(73, 73, 73, 255));
  connect(northButton, SIGNAL(clicked()), this, SLOT(northButtonPushed()));
  m_grid->addWidget(northButton, 0, 0, 1, -1);
  m_directories[Direction::North] = make_tuple("", northButton);

  auto southButton = new DirectorySelectButton;
  southButton->setFocusPolicy(Qt::NoFocus);
  southButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  southButton->setStyleSheet(buttonStyle);
  southButton->setColor(QColor(73, 73, 73, 255));
  connect(southButton, SIGNAL(clicked()), this, SLOT(southButtonPushed()));
  m_grid->addWidget(southButton, 2, 0, 1, -1);
  m_directories[Direction::South] = make_tuple("", southButton);

  auto eastButton = new DirectorySelectButton;
  eastButton->setFocusPolicy(Qt::NoFocus);
  eastButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  eastButton->setStyleSheet(buttonStyle);
  eastButton->setColor(QColor(73, 73, 73, 255));
  connect(eastButton, SIGNAL(clicked()), this, SLOT(eastButtonPushed()));
  m_grid->addWidget(eastButton, 1, 2, 1, -1);
  m_directories[Direction::East] = make_tuple("", eastButton);

  auto westButton = new DirectorySelectButton;
  westButton->setFocusPolicy(Qt::NoFocus);
  westButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  westButton->setStyleSheet(buttonStyle);
  westButton->setColor(QColor(73, 73, 73, 255));
  connect(westButton, SIGNAL(clicked()), this, SLOT(westButtonPushed()));
  m_grid->addWidget(westButton, 1, 0, 1, 1);
  m_directories[Direction::West] = make_tuple("", westButton);

  m_centralText = new QLabel;

  m_centralStack = new QStackedWidget;
  m_centralStack->addWidget(m_centralText);

  auto hlayout = new QHBoxLayout;
  m_nameEdit = new QLineEdit;
  m_nameEdit->setFocusPolicy(Qt::ClickFocus);
  hlayout->addWidget(m_nameEdit);

  m_confirmNameEditButton = new QToolButton;
  m_confirmNameEditButton->setFocusPolicy(Qt::NoFocus);
  m_confirmNameEditButton->setIcon(
      style()->standardIcon(QStyle::SP_DialogApplyButton));
  connect(m_confirmNameEditButton, SIGNAL(clicked()), this,
          SLOT(confirmNameEditPushed()));

  hlayout->addWidget(m_confirmNameEditButton);

  auto vlayout = new QVBoxLayout;
  vlayout->addWidget(m_centralStack, 0, Qt::AlignCenter);
  vlayout->addLayout(hlayout);

  m_grid->addLayout(vlayout, 1, 1, 1, 1, Qt::AlignCenter);

  m_grid->setColumnStretch(0, 1);
  m_grid->setRowStretch(0, 8);

  m_grid->setColumnStretch(1, 0);
  m_grid->setRowStretch(1, 0);

  m_grid->setColumnStretch(2, 1);
  m_grid->setRowStretch(2, 8);

  setLayout(m_grid);
}

void Carousel::northButtonPushed() { buttonPushed(Direction::North); }

void Carousel::southButtonPushed() { buttonPushed(Direction::South); }

void Carousel::eastButtonPushed() { buttonPushed(Direction::East); }

void Carousel::westButtonPushed() { buttonPushed(Direction::West); }

void Carousel::confirmNameEditPushed() {
  if (m_nameEdit->text() == m_directory.Current().fileName()) {
    // Nothing to do if the names are the same
    return;
  }

  auto currentFile = m_directory.Current();
  try {
    unique_ptr<RenameFile> command =
        make_unique<RenameFile>(currentFile, m_nameEdit->text());
    command->Exec();
    workingDirectoryModified();

    if (command->IsReversible()) {
      m_commandStack.Add(std::move(command), currentFile);
    }
  } catch (FileCommandException& e) {
    QMessageBox::critical(this, "Carousel", QString(e.what()));
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

    if (typeid(command) != typeid(FileCommand<CopyFile>)) {
      workingDirectoryModified(&file);
    } else {
      workingDirectoryModified();
    }
  } catch (FileCommandException& e) {
    QMessageBox::critical(this, "Carousel", QString(e.what()));
  }
}

void Carousel::redo() {
  Command* command = nullptr;
  QFileInfo file;
  std::tie(command, file) = m_commandStack.Redo();
  try {
    command->Exec();

    if (typeid(command) != typeid(FileCommand<CopyFile>)) {
      workingDirectoryModified();
    }
  } catch (FileCommandException& e) {
    QMessageBox::critical(this, "Carousel", QString(e.what()));
  }
}

void Carousel::setWorkingDirectory(Directory& directory) {
  m_directory = directory;

  if (m_directory.IsEmpty()) {
    m_centralStack->setCurrentWidget(m_centralText);
    m_centralText->setText("Directory is empty");

    return;
  }

  m_filePreview = m_previewers.GetPreviewForFile(this, m_directory.Current());
  if (m_centralStack->indexOf(m_filePreview) == -1) {
    m_centralStack->addWidget(m_filePreview);
  }
  m_centralStack->setCurrentWidget(m_filePreview);
  m_filePreview->Show(m_directory.Current());

  m_nameEdit->setText(m_directory.Current().fileName());
}

void Carousel::buttonPushed(Direction direction) {
  QString destinationPath = QFileDialog::getExistingDirectory(this);
  if (not destinationPath.isEmpty()) {
    if (destinationPath == m_directory.AbsolutePath()) {
      QMessageBox::warning(
          this, "Carousel",
          "Cannot select the same directory as the working directory");
      return;
    }

    auto& directory = m_directories[direction];
    std::get<0>(directory) = destinationPath;
    std::get<1>(directory)->setText(QFileInfo(destinationPath).fileName());
  }
}

void Carousel::keyPressEvent(QKeyEvent* event) {
  switch (event->key()) {
    case Qt::Key_Left:
      fileUpdated(m_directory.Prev());
      break;
    case Qt::Key_Right:
      fileUpdated(m_directory.Next());
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
    file = m_directory.Next();
  }

  m_directory = Directory{m_directory.AbsolutePath()};

  if (not m_directory.ResetToFile(file)) {
    m_directory.ResetToPos(0);
  }

  file = m_directory.Current();
  m_filePreview->hide();
  m_filePreview = m_previewers.GetPreviewForFile(this, file);
  m_filePreview->Show(file);
  m_nameEdit->setText(m_directory.Current().fileName());
}

void Carousel::fileUpdated(const QFileInfo& newFile) {
  m_filePreview->hide();
  m_filePreview = m_previewers.GetPreviewForFile(this, newFile);
  if (m_centralStack->indexOf(m_filePreview) == -1) {
    m_centralStack->addWidget(m_filePreview);
  }

  m_centralStack->setCurrentWidget(m_filePreview);

  m_filePreview->Show(newFile);
  m_nameEdit->setText(m_directory.Current().fileName());
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

  auto currentFile = m_directory.Current();
  unique_ptr<Command> command;
  if (event->text().at(0).isUpper()) {
    command = make_unique<FileCommand<CopyFile>>(currentFile, path);
  } else if (event->text().at(0).isLower()) {
    command = make_unique<FileCommand<MoveFile>>(currentFile, path);
  }

  DirectorySelectButton* button = std::get<1>(m_directories[direction]);
  QPropertyAnimation *animation = new QPropertyAnimation(button, "color");
  animation->setDuration(250);
  animation->setStartValue(QColor(73, 73, 73, 255));
  animation->setEndValue(QColor(240, 240, 240, 65));
  animation->start();

  animation->setDuration(250);
  animation->setStartValue(QColor(240, 240, 240, 65));
  animation->setEndValue(QColor(73, 73, 73, 255));
  animation->start();

  if (command != nullptr) {
    try {
      command->Exec();
      if (typeid(command) != typeid(FileCommand<CopyFile>)) {
        workingDirectoryModified();
      }

      if (command->IsReversible()) {
        m_commandStack.Add(std::move(command), currentFile);
      }
    } catch (FileCommandException& e) {
      QMessageBox::critical(this, "Carousel", QString(e.what()));
    }
  }
}

void Carousel::processRemoveKey(QKeyEvent* event) {
  auto currentFile = m_directory.Current();
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

      if (command->IsReversible()) {
        m_commandStack.Add(std::move(command), currentFile);
      }
    } catch (FileCommandException& e) {
      QMessageBox::critical(this, "Carousel", QString(e.what()));
    }
  }
}
