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

#ifndef PALGENMIXWIDGET_H
#define PALGENMIXWIDGET_H

#include <QWidget>

namespace Ui {
class PalGenMixWidget;
}

class PalGenMixWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PalGenMixWidget(QWidget *parent = nullptr);
    ~PalGenMixWidget();

    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void colorSelected(int r, int g, int b);

private slots:
    void on_redSlider_valueChanged(int value);

    void on_greenSlider_valueChanged(int value);

    void on_blueSlider_valueChanged(int value);

    void on_colorPicker_pressed();

    void on_updateButton_clicked();

    void on_colorPickerA_pressed();

    void on_colorPickerB_pressed();

    void on_colorEditA_textChanged(const QString &arg1);

    void on_colorEditB_textChanged(const QString &arg1);

    void on_colorCount_valueChanged(int arg1);

    void on_colorEdit_textEdited(const QString &arg1);

private:
    void updateColor();
    void updateGradient();
    void updateScreenImage();

    QImage screenImage;
    Ui::PalGenMixWidget *ui;
};

#endif // PALGENMIXWIDGET_H
