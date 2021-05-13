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

#include "palgenmixwidget.h"
#include "ui_palgenmixwidget.h"

#include <QDebug>
#include <QPushButton>
#include <QWindow>
#include <QScreen>
#include <QObject>

#include "segacolors.h"

PalGenMixWidget::PalGenMixWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PalGenMixWidget)
{
    ui->setupUi(this);

    ui->redSlider->setTracking(true);
    ui->greenSlider->setTracking(true);
    ui->blueSlider->setTracking(true);

    ui->colorPicker->setCursor(Qt::CrossCursor);
    ui->colorPickerA->setCursor(Qt::CrossCursor);
    ui->colorPickerB->setCursor(Qt::CrossCursor);

    ui->colorPicker->installEventFilter(this);
    ui->colorPickerA->installEventFilter(this);
    ui->colorPickerB->installEventFilter(this);

    updateColor();
    updateGradient();
}

PalGenMixWidget::~PalGenMixWidget()
{
    delete ui;
}

void PalGenMixWidget::on_redSlider_valueChanged(int value)
{
    (void)value;
    updateColor();
}

void PalGenMixWidget::on_greenSlider_valueChanged(int value)
{
    (void)value;
    updateColor();
}

void PalGenMixWidget::on_blueSlider_valueChanged(int value)
{
    (void)value;
    updateColor();
}

void PalGenMixWidget::colorSelected(int r, int g, int b)
{
    ui->redSlider->setValue(r);
    ui->greenSlider->setValue(g);
    ui->blueSlider->setValue(b);

    updateColor();
}

void PalGenMixWidget::updateColor()
{
    QPalette pal = ui->colorWidget->palette();
    ui->colorWidget->setAutoFillBackground(true);
    pal.setColor(QPalette::Background, rgbToQColor(ui->redSlider->value(), ui->greenSlider->value(), ui->blueSlider->value()));
    ui->colorWidget->setPalette(pal);

    uint32_t r = ui->redSlider->value();
    uint32_t g = ui->greenSlider->value();
    uint32_t b = ui->blueSlider->value();

    ui->colorEdit->setText(rgb3ToHex(r, g, b));
}

void PalGenMixWidget::updateGradient()
{
    uint32_t r0, g0, b0, r1, g1, b1;
    hexToRgb3(r0, g0, b0, ui->colorEditA->text());
    hexToRgb3(r1, g1, b1, ui->colorEditB->text());

    ui->gradientWidget->updateValues(r0, g0, b0, r1, g1, b1, ui->colorCount->value());

    QString hexColors = "";
    int m_count = ui->colorCount->value();
    for (int i = 0; i != m_count; ++i)
    {

        double ratio = double(i)/double(m_count - 1);
        int r = interp(r0, r1, ratio);
        int g = interp(g0, g1, ratio);
        int b = interp(b0, b1, ratio);
        hexColors += rgb3ToHex(r, g, b);
        hexColors += ", ";
    }

    ui->gradientColors->setPlainText(hexColors);
}

void PalGenMixWidget::updateScreenImage()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        screen = window->screen();
    if (!screen)
        return;
    screenImage = screen->grabWindow(0).toImage();
}

void PalGenMixWidget::on_colorPicker_pressed()
{
    updateScreenImage();
}

bool PalGenMixWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

        if (obj->objectName() == ui->colorPicker->objectName())
        {
            QColor color = screenImage.pixelColor(mouseEvent->globalX(), mouseEvent->globalY());

            ui->redSlider->setValue(color.red() >> 5);
            ui->greenSlider->setValue(color.green() >> 5);
            ui->blueSlider->setValue(color.blue() >> 5);
        }
        else if (obj->objectName() == ui->colorPickerA->objectName())
        {
            QColor color = screenImage.pixelColor(mouseEvent->globalX(), mouseEvent->globalY());
            ui->colorEditA->setText(rgb3ToHex(color.red() >> 5, color.green() >> 5, color.blue() >> 5));
        }
        else if (obj->objectName() == ui->colorPickerB->objectName())
        {
            QColor color = screenImage.pixelColor(mouseEvent->globalX(), mouseEvent->globalY());
            ui->colorEditB->setText(rgb3ToHex(color.red() >> 5, color.green() >> 5, color.blue() >> 5));
        }
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}

void PalGenMixWidget::on_updateButton_clicked()
{
    QString t = ui->colorEdit->text().trimmed();
    uint32_t r;
    uint32_t g;
    uint32_t b;
    hexToRgb3(r, g, b, t);
    ui->redSlider->setValue(r);
    ui->greenSlider->setValue(g);
    ui->blueSlider->setValue(b);
    ui->updateButton->setText("Update");
    updateColor();
}

void PalGenMixWidget::on_colorPickerA_pressed()
{
    updateScreenImage();
}

void PalGenMixWidget::on_colorPickerB_pressed()
{
    updateScreenImage();
}

void PalGenMixWidget::on_colorEditA_textChanged(const QString &)
{
    updateGradient();
}

void PalGenMixWidget::on_colorEditB_textChanged(const QString &)
{
    updateGradient();
}

void PalGenMixWidget::on_colorCount_valueChanged(int)
{
    updateGradient();
}

void PalGenMixWidget::on_colorEdit_textEdited(const QString &arg1)
{
    (void)arg1;
    ui->updateButton->setText("Update *");
}
