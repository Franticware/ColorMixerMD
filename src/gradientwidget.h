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

#ifndef GRADIENTWIDGET_H
#define GRADIENTWIDGET_H

#include <QWidget>
#include <cmath>

class GradientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GradientWidget(QWidget *parent = nullptr);

    void updateValues(int r0, int g0, int b0, int r1, int g1, int b1, int count);

    QString hexColors;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_r0, m_g0, m_b0, m_r1, m_g1, m_b1;
    int m_count;
};

#endif // GRADIENTWIDGET_H
