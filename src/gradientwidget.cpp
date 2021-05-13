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

#include "gradientwidget.h"

#include <QPainter>
#include <QPen>

#include "segacolors.h"

GradientWidget::GradientWidget(QWidget *parent) : QWidget(parent)
{
    m_r0 = 0;
    m_g0 = 0;
    m_b0 = 0;
    m_r1 = 0;
    m_g1 = 0;
    m_b1 = 0;
    m_count = 8;
}

void GradientWidget::updateValues(int r0, int g0, int b0, int r1, int g1, int b1, int count)
{
    m_r0 = r0;
    m_g0 = g0;
    m_b0 = b0;
    m_r1 = r1;
    m_g1 = g1;
    m_b1 = b1;
    m_count = count;
    if (m_count < 2) m_count = 2;

    update();
}

void GradientWidget::paintEvent(QPaintEvent *event)
{
    (void)event;
    QPainter painter(this);
    painter.setPen(QPen(QBrush(), 0));

    int h = height();
    int w = width();

    hexColors = "";

    for (int i = 0; i != m_count; ++i)
    {
        int x0 = i * w/m_count;
        int x1 = (i+1) * w/m_count;

        double ratio = double(i)/double(m_count - 1);
        int r = interp(m_r0, m_r1, ratio);
        int g = interp(m_g0, m_g1, ratio);
        int b = interp(m_b0, m_b1, ratio);

        hexColors += rgb3ToHex(r, g, b);
        hexColors += ", ";

        painter.setBrush(QBrush(rgbToQColor(r, g, b)));
        painter.drawRect(x0, 0, x1-x0, h);
    }
}
