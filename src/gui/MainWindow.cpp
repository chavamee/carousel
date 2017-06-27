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

#include <QtWidgets>

#include "../app/Directory.hpp"
#include "Carousel.hpp"
#include "MainWindow.hpp"

using namespace std;

MainWindow::MainWindow(QString directoryPath) {
  createActions();
  createStatusBar();

  if (directoryPath.isEmpty()) {
    createSplashView();
  }

  setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::closeEvent(QCloseEvent *event) {}

void MainWindow::open() {
  QString directoryPath = QFileDialog::getExistingDirectory(this);
  if (not directoryPath.isEmpty()) {
    if (m_carousel != nullptr) {
      delete m_carousel;
    }

    Directory m_currentDirectory {directoryPath};
    m_carousel = new Carousel(this, m_currentDirectory);
    setCentralWidget(m_carousel);
  }
}

void MainWindow::undo() {
  if (m_carousel != nullptr) {
    m_carousel->undo();
  }
}

void MainWindow::redo() {
  if (m_carousel != nullptr) {
    m_carousel->redo();
  }
}

void MainWindow::about() {}

void MainWindow::createActions() {
  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  QToolBar *fileToolBar = addToolBar(tr("File"));
  const QIcon openIcon = QIcon::fromTheme("document-open");
  QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
  openAct->setShortcuts(QKeySequence::Open);
  openAct->setStatusTip(tr("Open an existing directory"));
  connect(openAct, &QAction::triggered, this, &MainWindow::open);
  fileMenu->addAction(openAct);
  fileToolBar->addAction(openAct);

  fileMenu->addSeparator();

  const QIcon exitIcon = QIcon::fromTheme("application-exit");
  QAction *exitAct =
      fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));

  QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
  QToolBar *editToolBar = addToolBar(tr("Edit"));
  const QIcon undoIcon = QIcon::fromTheme("edit-undo");
  QAction *undoAct = new QAction(undoIcon, tr("&Undo"), this);
  undoAct->setShortcuts(QKeySequence::Undo);
  undoAct->setStatusTip(tr("Undo last operation"));
  connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
  editMenu->addAction(undoAct);
  editToolBar->addAction(undoAct);

  const QIcon redoIcon = QIcon::fromTheme("edit-redo");
  QAction *redoAct = new QAction(redoIcon, tr("&Redo"), this);
  redoAct->setShortcuts(QKeySequence::Redo);
  redoAct->setStatusTip(tr("Redo last operation"));
  connect(redoAct, &QAction::triggered, this, &MainWindow::redo);
  editMenu->addAction(redoAct);
  editToolBar->addAction(redoAct);

  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
  QAction *aboutAct =
      helpMenu->addAction(tr("&About"), this, &MainWindow::about);
  aboutAct->setStatusTip(tr("Show the application's About box"));
}

void MainWindow::createStatusBar() { statusBar()->showMessage(tr("Ready")); }

void MainWindow::createSplashView() {
  QWidget *splash = new QWidget(this);
  QVBoxLayout *vlayout = new QVBoxLayout;

  QPushButton *button = new QPushButton("Open a directory...", splash);
  button->setFocusPolicy(Qt::NoFocus);
  button->setMaximumWidth(200);
  connect(button, SIGNAL(clicked()), this, SLOT(open()));
  vlayout->addWidget(button, 0, Qt::AlignCenter);
  splash->setLayout(vlayout);

  setCentralWidget(splash);
}
