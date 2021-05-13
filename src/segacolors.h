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

#ifndef SEGACOLORS_H
#define SEGACOLORS_H

#include <QString>
#include <QColor>
#include <cmath>


inline QString rgb3ToHex(uint32_t r, uint32_t g, uint32_t b)
{
    uint32_t rgb = (r << 1) | (g << 5) | (b << 9);

    const int digits = 3;

    QString s = QString(digits, '0') + QString::number(rgb, 16);
    s = s.right(digits);

    return "0x" + s;
}

inline void hexToRgb3(uint32_t &r, uint32_t &g, uint32_t &b, QString s)
{
    QStringList l = s.split("x", QString::SkipEmptyParts, Qt::CaseInsensitive);
    uint col = 0;
    if (l.size() > 0)
    {
        col = l[l.size() - 1].toUInt(nullptr, 16);
    }

    r = (col >> 1) & 7;
    g = (col >> 5) & 7;
    b = (col >> 9) & 7;
}

inline QColor rgbToQColor(uint32_t r, uint32_t g, uint32_t b)
{
    const int m = 36;
    return QColor(r * m, g * m, b * m);
}

inline int interp(int a, int b, double r)
{
    return a + std::floor((b - a) * r + 0.5);
}

#endif // SEGACOLORS_H
