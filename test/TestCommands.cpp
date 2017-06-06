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

#include <QtTest/QtTest>

#include <app/command/HardRemoveFile.hpp>
#include <app/command/SoftRemoveFile.hpp>
#include <app/command/RenameFile.hpp>
#include <app/command/CopyFile.hpp>
#include <app/command/MoveFile.hpp>

const QString TempPath = "/tmp/";

class TestCommands : public QObject {
  Q_OBJECT
 private slots:
  void init() {
    QDir tmpDir(TempPath);
    if (tmpDir.exists(m_testDirName)) {
      QVERIFY(tmpDir.rmdir(m_testDirName));
    }

    QVERIFY(tmpDir.mkdir(m_testDirName) == true);

    QFile file(m_testFilePath);
    QVERIFY(file.open(QIODevice::ReadWrite) == true);
    QTextStream stream(&file);
    stream << "Hello, World!" << endl;
    file.close();
  }

  void cleanup() {
    m_testDir.removeRecursively();
  }

  void TestMoveCommand();
  void TestCopyCommand();
  void TestRenameCommand();
  void TestSoftRemoveCommand();
  void TestHardRemoveCommand();

 private:
  QString m_testDirName = "carousel.tests";
  QString m_testDirPath = TempPath + m_testDirName;
  QDir m_testDir = QDir(m_testDirPath);

  QString m_testFileName = "test.txt";
  QString m_testFilePath = m_testDirPath + "/" + m_testFileName;
  QFileInfo m_testFileInfo = QFileInfo(m_testFilePath);
};

void TestCommands::TestMoveCommand() {
  QString moveDirPath = m_testDirPath + "/move_dir";
  m_testDir.mkdir("move_dir");

  QDir moveDir(moveDirPath);

  MoveFile command(m_testFileInfo, moveDirPath);
  command.Exec();

  moveDir.refresh();
  m_testDir.refresh();
  QVERIFY(moveDir.exists(m_testFileName) == true);
  QVERIFY(m_testDir.exists(m_testFileName) == false);

  QVERIFY(command.IsReversible() == true);

  command.Undo();
  moveDir.refresh();
  m_testDir.refresh();
  QVERIFY(moveDir.exists(m_testFileName) == false);
  QVERIFY(m_testDir.exists(m_testFileName) == true);

  QVERIFY(command.Modifies() == true);
}

void TestCommands::TestCopyCommand() {
  QString copyDirPath = m_testDirPath + "/copy_dir";
  m_testDir.mkdir("copy_dir");

  QDir copyDir(copyDirPath);

  CopyFile command(m_testFileInfo, copyDirPath);
  command.Exec();

  copyDir.refresh();
  m_testDir.refresh();
  QVERIFY(copyDir.exists(m_testFileName) == true);
  QVERIFY(m_testDir.exists(m_testFileName) == true);

  QVERIFY(command.IsReversible() == true);

  command.Undo();
  copyDir.refresh();
  QVERIFY(copyDir.exists(m_testFileName) == false);

  QVERIFY(command.Modifies() == false);
}

void TestCommands::TestRenameCommand() {
  QString newName = "new_name.txt";
  RenameFile command(m_testFileInfo, newName);
  command.Exec();

  m_testDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == false);
  QVERIFY(m_testDir.exists(newName) == true);

  QVERIFY(command.IsReversible() == true);

  command.Undo();
  m_testDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == true);
  QVERIFY(m_testDir.exists(newName) == false);

  QVERIFY(command.Modifies() == true);
}

void TestCommands::TestSoftRemoveCommand() {
  QDir trashDir(QDir::homePath() + "/.local/share/Trash");
  SoftRemoveFile command(m_testFileInfo);
  command.Exec();

  m_testDir.refresh();
  trashDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == false);
  QVERIFY(trashDir.exists(m_testFileName) == true);

  QVERIFY(command.IsReversible() == true);

  command.Undo();
  m_testDir.refresh();
  trashDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == true);
  QVERIFY(trashDir.exists(m_testFileName) == false);

  QVERIFY(command.Modifies() == true);
}

void TestCommands::TestHardRemoveCommand() {
  HardRemoveFile command(m_testFileInfo);
  command.Exec();

  m_testDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == false);

  QVERIFY(command.IsReversible() == false);

  command.Undo();
  m_testDir.refresh();
  QVERIFY(m_testDir.exists(m_testFileName) == false);

  QVERIFY(command.Modifies() == true);
}

QTEST_MAIN(TestCommands)
#include "TestCommands.moc"
