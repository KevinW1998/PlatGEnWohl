/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */


#include "../ui_mainwindow.h"
#include "../mainwindow.h"




// World tool box show/hide
void MainWindow::on_WorldToolBox_visibilityChanged(bool visible)
{
        ui->actionWLDToolBox->setChecked(visible);
}

void MainWindow::on_actionWLDToolBox_triggered()
{
    if(ui->actionWLDToolBox->isChecked())
    {
        ui->WorldToolBox->setVisible(true);
        ui->WorldToolBox->raise();
    }
    else
        ui->WorldToolBox->setVisible(false);
}



