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

#include "palgenwidget.h"

#include <QPaintEvent>
#include <QPainter>

PalGenWidget::PalGenWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(128*8, 128);
}

void PalGenWidget::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setPen(QPen(QBrush(), 0));

    const int m = 36;

    for (int r = 0; r != 8; ++r)
    {
        for (int g = 0; g != 8; ++g)
        {
            for (int b = 0; b != 8; ++b)
            {
                painter.setBrush(QBrush(QColor(r * m, g * m, b * m)));
                painter.drawRect(r * 16 + b * 16 * 8, g * 16, 16, 16);
            }
        }
    }
}

void PalGenWidget::mousePressEvent(QMouseEvent *event)
{
    int b = event->x() / 128;
    int r = (event->x() % 128) / 16;
    int g = event->y() / 16;

    emit directRGB(r, g, b);
}
