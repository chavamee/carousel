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

#include <QFileIconProvider>
#include <QPixmap>
#include <QVBoxLayout>

#include "IconPreview.hpp"

IconPreview::IconPreview(QWidget* parent)
    : FilePreview(parent), m_label(new QLabel(this)) {
  QVBoxLayout* layout = new QVBoxLayout;
  m_label->setGeometry(geometry());
  m_label->setMinimumHeight(geometry().height());
  m_label->setMinimumWidth(geometry().width());
  layout->addWidget(m_label);
  setLayout(layout);
}

void IconPreview::Show(QFileInfo file) {
  QIcon icon = QFileIconProvider().icon(file);
  m_label->setPixmap(icon.pixmap(48, 48));
  show();
}
