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

#include <QtWidgets>

#include "npcedit.h"
#include "./ui_npcedit.h"
#include "../file_formats/file_formats.h"




void npcedit::on_ResetNPCData_clicked()
{
    NpcData = StartNPCData; //Restore first version
    setDataBoxes();
    documentNotModified();
}



////////////////////////////////////////////////////////////////
void npcedit::on_en_GFXOffsetX_clicked()
{
    if(ui->en_GFXOffsetX->isChecked())
    {
        ui->GFXOffSetX->setEnabled(true);
        NpcData.en_gfxoffsetx=true;
    }
    else
    {
        ui->GFXOffSetX->setEnabled(false);
        NpcData.en_gfxoffsetx=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_en_GFXOffsetY_clicked()
{
    if(ui->en_GFXOffsetY->isChecked())
    {
        ui->GFXOffSetY->setEnabled(true);
        NpcData.en_gfxoffsety=true;
    }
    else
    {
        ui->GFXOffSetY->setEnabled(false);
        NpcData.en_gfxoffsety=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_GFXw_clicked()
{
    if(ui->En_GFXw->isChecked())
    {
        ui->GFXw->setEnabled(true);
        NpcData.en_gfxwidth=true;
    }
    else
    {
        ui->GFXw->setEnabled(false);
        NpcData.en_gfxwidth=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_GFXh_clicked()
{
    if(ui->En_GFXh->isChecked())
    {
        ui->GFXh->setEnabled(true);
        NpcData.en_gfxheight=true;
    }
    else
    {
        ui->GFXh->setEnabled(false);
        NpcData.en_gfxheight=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Frames_clicked()
{
    if(ui->En_Frames->isChecked())
    {
        ui->Frames->setEnabled(true);
        NpcData.en_frames=true;
    }
    else
    {
        ui->Frames->setEnabled(false);
        NpcData.en_frames=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Framespeed_clicked()
{
    if(ui->En_Framespeed->isChecked())
    {
        ui->Framespeed->setEnabled(true);
        NpcData.en_framespeed=true;
    }
    else
    {
        ui->Framespeed->setEnabled(false);
        NpcData.en_framespeed=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Framestyle_clicked()
{
    if(ui->En_Framestyle->isChecked())
    {
        ui->FrameStyle->setEnabled(true);
        NpcData.en_framestyle=true;
    }
    else
    {
        ui->FrameStyle->setEnabled(false);
        NpcData.en_framestyle=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_IsForeground_clicked()
{
    if(ui->En_IsForeground->isChecked())
    {
        ui->IsForeground->setEnabled(true);
        NpcData.en_foreground=true;
    }
    else
    {
        ui->IsForeground->setEnabled(false);
        NpcData.en_foreground=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_GrabSide_clicked()
{
    if(ui->En_GrabSide->isChecked())
    {
        ui->GrabSide->setEnabled(true);
        NpcData.en_grabside=true;
    }
    else
    {
        ui->GrabSide->setEnabled(false);
        NpcData.en_grabside=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_GrabTop_clicked()
{
    if(ui->En_GrabTop->isChecked())
    {
        ui->GrabTop->setEnabled(true);
        NpcData.en_grabtop=true;
    }
    else
    {
        ui->GrabTop->setEnabled(false);
        NpcData.en_grabtop=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_JumpHurt_clicked()
{
    if(ui->En_JumpHurt->isChecked())
    {
        ui->JumpHurt->setEnabled(true);
        NpcData.en_jumphurt=true;
    }
    else
    {
        ui->JumpHurt->setEnabled(false);
        NpcData.en_jumphurt=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_DontHurt_clicked()
{
    if(ui->En_DontHurt->isChecked())
    {
        ui->DontHurt->setEnabled(true);
        NpcData.en_nohurt=true;
    }
    else
    {
        ui->DontHurt->setEnabled(false);
        NpcData.en_nohurt=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Score_clicked()
{
    if(ui->En_Score->isChecked())
    {
        ui->Score->setEnabled(true);
        NpcData.en_score=true;
    }
    else
    {
        ui->Score->setEnabled(false);
        NpcData.en_score=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoEat_clicked()
{
    if(ui->En_NoEat->isChecked())
    {
        ui->NoEat->setEnabled(true);
        NpcData.en_noyoshi=true;
    }
    else
    {
        ui->NoEat->setEnabled(false);
        NpcData.en_noyoshi=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoFireball_clicked()
{
    if(ui->En_NoFireball->isChecked())
    {
        ui->NoFireball->setEnabled(true);
        NpcData.en_nofireball=true;
    }
    else
    {
        ui->NoFireball->setEnabled(false);
        NpcData.en_nofireball=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoIceball_clicked()
{
    if(ui->En_NoIceball->isChecked())
    {
        ui->NoIceball->setEnabled(true);
        NpcData.en_noiceball=true;
    }
    else
    {
        ui->NoIceball->setEnabled(false);
        NpcData.en_noiceball=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Width_clicked()
{
    if(ui->En_Width->isChecked())
    {
        ui->Width->setEnabled(true);
        NpcData.en_width=true;
    }
    else
    {
        ui->Width->setEnabled(false);
        NpcData.en_width=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Height_clicked()
{
    if(ui->En_Height->isChecked())
    {
        ui->Height->setEnabled(true);
        NpcData.en_height=true;
    }
    else
    {
        ui->Height->setEnabled(false);
        NpcData.en_height=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_Speed_clicked()
{
    if(ui->En_Speed->isChecked())
    {
        ui->Speed->setEnabled(true);
        NpcData.en_speed=true;
    }
    else
    {
        ui->Speed->setEnabled(false);
        NpcData.en_speed=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_PlayerBlock_clicked()
{
    if(ui->En_PlayerBlock->isChecked())
    {
        ui->PlayerBlock->setEnabled(true);
        NpcData.en_playerblock=true;
    }
    else
    {
        ui->PlayerBlock->setEnabled(false);
        NpcData.en_playerblock=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_PlayerBlockTop_clicked()
{
    if(ui->En_PlayerBlockTop->isChecked())
    {
        ui->PlayerBlockTop->setEnabled(true);
        NpcData.en_playerblocktop=true;
    }
    else
    {
        ui->PlayerBlockTop->setEnabled(false);
        NpcData.en_playerblocktop=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NPCBlock_clicked()
{
    if(ui->En_NPCBlock->isChecked())
    {
        ui->NPCBlock->setEnabled(true);
        NpcData.en_npcblock=true;
    }
    else
    {
        ui->NPCBlock->setEnabled(false);
        NpcData.en_npcblock=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NPCBlockTop_clicked()
{
    if(ui->En_NPCBlockTop->isChecked())
    {
        ui->NPCBlockTop->setEnabled(true);
        NpcData.en_npcblocktop=true;
    }
    else
    {
        ui->NPCBlockTop->setEnabled(false);
        NpcData.en_npcblocktop=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoBlockCollision_clicked()
{
    if(ui->En_NoBlockCollision->isChecked())
    {
        ui->NoBlockCollision->setEnabled(true);
        NpcData.en_noblockcollision=true;
    }
    else
    {
        ui->NoBlockCollision->setEnabled(false);
        NpcData.en_noblockcollision=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoGravity_clicked()
{
    if(ui->En_NoGravity->isChecked())
    {
        ui->NoGravity->setEnabled(true);
        NpcData.en_nogravity=true;
    }
    else
    {
        ui->NoGravity->setEnabled(false);
        NpcData.en_nogravity=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_TurnCliff_clicked()
{
    if(ui->En_TurnCliff->isChecked())
    {
        ui->TurnCliff->setEnabled(true);
        NpcData.en_cliffturn=true;
    }
    else
    {
        ui->TurnCliff->setEnabled(false);
        NpcData.en_cliffturn=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_En_NoHammer_clicked()
{
    if(ui->En_NoHammer->isChecked())
    {
        ui->NoHammer->setEnabled(true);
        NpcData.en_nohammer=true;
    }
    else
    {
        ui->NoHammer->setEnabled(false);
        NpcData.en_nohammer=false;
    }
    documentWasModified();
}

////////////////////////////////////////////////////////////////
void npcedit::on_GFXOffSetX_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.gfxoffsetx = arg1;
}


////////////////////////////////////////////////////////////////
void npcedit::on_GFXOffSetY_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.gfxoffsety = arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_GFXw_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.gfxwidth = arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_GFXh_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.gfxheight = arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Frames_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.frames = arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Framespeed_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.framespeed=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_FrameStyle_currentIndexChanged(int index)
{
    documentWasModified();
    NpcData.framestyle=index;
}

////////////////////////////////////////////////////////////////
void npcedit::on_IsForeground_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.foreground=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_GrabSide_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.grabside=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_GrabTop_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.grabtop=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_JumpHurt_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.jumphurt=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_DontHurt_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.nohurt=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Score_currentIndexChanged(int index)
{
    documentWasModified();
    NpcData.score=index;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoEat_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.noyoshi=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoFireball_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.nofireball=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoIceball_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.noiceball=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Width_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.width=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Height_valueChanged(int arg1)
{
    documentWasModified();
    NpcData.height=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_Speed_valueChanged(double arg1)
{
    documentWasModified();
    NpcData.speed = arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_PlayerBlock_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.playerblock=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_PlayerBlockTop_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.playerblocktop=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NPCBlock_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.npcblock=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NPCBlockTop_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.npcblocktop=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoBlockCollision_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.noblockcollision=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoGravity_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.nogravity=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_TurnCliff_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.cliffturn=arg1;
}

////////////////////////////////////////////////////////////////
void npcedit::on_NoHammer_stateChanged(int arg1)
{
    documentWasModified();
    NpcData.nohammer=arg1;
}
////////////////////////////////////////////////////////////////
