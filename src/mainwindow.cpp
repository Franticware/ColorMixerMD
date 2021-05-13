/*
 * ColorMixerMD
 * Copyright (c) 2021 Vojtěch Salajka
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "palgenwidget.h"
#include "palgenmixwidget.h"

#include <QLayout>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QVBoxLayout);

    PalGenWidget* palGenWidget = new PalGenWidget(this);
    PalGenMixWidget* palGenMixWidget = new PalGenMixWidget(this);

    ui->centralwidget->layout()->addWidget(palGenWidget);
    ui->centralwidget->layout()->addWidget(palGenMixWidget);

    connect(palGenWidget, &PalGenWidget::directRGB, palGenMixWidget, &PalGenMixWidget::colorSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}
