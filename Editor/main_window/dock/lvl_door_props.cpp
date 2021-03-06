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


#include "../../ui_mainwindow.h"
#include "../../mainwindow.h"


void MainWindow::setDoorsToolbox()
{
    int WinType = activeChildWindow();

    if (WinType==1)
    {
        ui->WarpList->clear();
        foreach(LevelDoors door, activeLvlEditWin()->LvlData.doors)
        {
            ui->WarpList->addItem(QString("%1: x%2y%3 <=> x%4y%5")
           .arg(door.array_id).arg(door.ix).arg(door.iy).arg(door.ox).arg(door.oy),
                                  door.array_id);
        }
    }

}



void MainWindow::setDoorData(long index)
{
    int WinType = activeChildWindow();
    if (WinType==1)
    {
        if(index<activeLvlEditWin()->LvlData.doors.size())
        {
            foreach(LevelDoors door, activeLvlEditWin()->LvlData.doors)
            {
                if(door.array_id == (unsigned long)ui->WarpList->currentData().toInt() )
                {
                    ui->WarpAllowNPC->setEnabled(true);
                    ui->WarpAllowNPC->setChecked(door.allownpc);

                    ui->WarpLock->setEnabled(true);
                    ui->WarpLock->setChecked(door.locked);

                    ui->WarpNoYoshi->setEnabled(true);
                    ui->WarpNoYoshi->setChecked(door.noyoshi);

                    ui->WarpType->setEnabled(true);
                    ui->WarpType->setCurrentIndex(door.type);

                    ui->WarpEntrancePlaced->setChecked(door.isSetIn);
                    ui->WarpExitPlaced->setChecked(door.isSetOut);

                    ui->WarpNeedAStars->setEnabled(true);
                    ui->WarpNeedAStars->setValue(door.stars);

                    ui->WarpEntranceGrp->setEnabled(  door.type==1 );
                    ui->WarpExitGrp->setEnabled( door.type==1 );

                    switch(door.idirect)
                    { //Entrance direction: [3] down, [1] up, [2] left, [4] right
                    case 1:
                        ui->Entr_Up->setChecked(true);
                        break;
                    case 2:
                        ui->Entr_Left->setChecked(true);
                        break;
                    case 3:
                        ui->Entr_Down->setChecked(true);
                        break;
                    case 4:
                        ui->Entr_Right->setChecked(true);
                        break;
                    default:
                        ui->Entr_Down->setChecked(true);
                        break;
                    }


                    switch(door.odirect)
                    { //Exit direction: [1] down [3] up [4] left [2] right
                    case 1:
                        ui->Exit_Down->setChecked(true);
                        break;
                    case 2:
                        ui->Exit_Right->setChecked(true);
                        break;
                    case 3:
                        ui->Exit_Up->setChecked(true);
                        break;
                    case 4:
                        ui->Exit_Left->setChecked(true);
                        break;
                    default:
                        ui->Exit_Up->setChecked(true);
                        break;
                    }

                    ui->WarpToMapX->setEnabled(true);
                    ui->WarpToMapX->setText((door.world_x!=-1)?QString::number(door.world_x):"");

                    ui->WarpToMapY->setEnabled(true);
                    ui->WarpToMapY->setText((door.world_y!=-1)?QString::number(door.world_y):"");


                    ui->WarpLevelExit->setEnabled(true);
                    ui->WarpLevelExit->setChecked( door.lvl_o );

                    ui->WarpLevelEntrance->setEnabled(true);
                    ui->WarpLevelEntrance->setChecked( door.lvl_i );

                    ui->WarpSetEntrance->setEnabled( ((!door.lvl_o) && (!door.lvl_i)) || ((door.lvl_o) && (!door.lvl_i)) );
                    ui->WarpSetExit->setEnabled( ((!door.lvl_o) && (!door.lvl_i)) || ((door.lvl_i)) );

                    ui->WarpLevelFile->setEnabled(true);

                    ui->WarpLevelFile->setText( door.lname );

                    break;
                }
            }
        }
        else
        {
            ui->WarpRemove->setEnabled(false);

            ui->WarpSetEntrance->setEnabled(false);
            ui->WarpSetExit->setEnabled(false);

            ui->WarpNoYoshi->setEnabled(false);
            ui->WarpNoYoshi->setChecked(false);
            ui->WarpAllowNPC->setEnabled(false);
            ui->WarpAllowNPC->setChecked(false);
            ui->WarpLock->setEnabled(false);
            ui->WarpLock->setChecked(false);

            ui->WarpType->setEnabled(false);
            ui->WarpType->setCurrentIndex(0);
            ui->WarpNeedAStars->setEnabled(false);
            ui->WarpNeedAStars->setValue(0);

            ui->WarpEntranceGrp->setEnabled(false);
            ui->WarpExitGrp->setEnabled(false);

            ui->WarpToMapX->setEnabled(false);
            ui->WarpToMapX->setText("");
            ui->WarpToMapY->setEnabled(false);
            ui->WarpToMapY->setText("");

            ui->WarpLevelExit->setEnabled(false);
            ui->WarpLevelExit->setChecked(false);
            ui->WarpLevelEntrance->setEnabled(false);
            ui->WarpLevelEntrance->setChecked(false);
            ui->WarpLevelFile->setEnabled(false);
            ui->WarpLevelFile->setText("");
        }
    }
}

void MainWindow::on_WarpList_currentIndexChanged(int index)
{
    setDoorData(index);
}
