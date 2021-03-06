/*
 * Copyright (c) 2012-2015 Meltytech, LLC
 * Author: Dan Dennedy <dan@dennedy.org>
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
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "textviewerdialog.h"
#include "ui_textviewerdialog.h"
#include "settings.h"
#include <QFileDialog>

TextViewerDialog::TextViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextViewerDialog)
{
    ui->setupUi(this);
}

TextViewerDialog::~TextViewerDialog()
{
    delete ui;
}

void TextViewerDialog::setText(const QString &s)
{
    ui->plainTextEdit->setPlainText(s);
}

void TextViewerDialog::on_buttonBox_accepted()
{
    QString path = Settings.savePath();
    path.append("/.txt");
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Text"), path);
    if (!filename.isEmpty()) {
        QFile f(filename);
        f.open(QIODevice::WriteOnly | QIODevice::Text);
        f.write(ui->plainTextEdit->toPlainText().toUtf8());
        f.close();
    }
}
