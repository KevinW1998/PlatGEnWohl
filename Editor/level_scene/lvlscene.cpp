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

#include "lvlscene.h"
#include "../edit_level/leveledit.h"

#include "item_block.h"
#include "item_bgo.h"
#include "item_npc.h"

LvlScene::LvlScene(dataconfigs &configs, LevelData &FileData, QObject *parent) : QGraphicsScene(parent)
{
    setItemIndexMethod(NoIndex);

    //Pointerss
    pConfigs = &configs; // Pointer to Main Configs
    LvlData = &FileData; //Ad pointer to level data

    //Options
    opts.animationEnabled = true;
    opts.collisionsEnabled = true;
    grid = true;

    //Indexes
    index_blocks = pConfigs->index_blocks; //Applaying blocks indexes
    index_bgo = pConfigs->index_bgo;
    index_npc = pConfigs->index_npc;

    //Editing mode
    EditingMode = 0;
    EraserEnabled = false;
    PasteFromBuffer = false;
    disableMoveItems = false;
    DrawMode=false;

    //Editing process flags
    IsMoved = false;
    haveSelected = false;

    placingItem=0;

    pResizer = NULL;

    contextMenuOpened = false;

    //Events flags
    resetPosition = false;
    /*
    wasPasted = false;  //call to cursor reset to normal select
    doCopy = false;     //call to copy
    doCut = false;      //call to cut
    SyncLayerList = false; //Call to refresh layer list
    resetResizingSection = false; //Reset resizing applying buttons
    */
    cursor = NULL;
    resetCursor();

    //set dummy images if target not exist or wrong
    uBlockImg = QPixmap(QApplication::applicationDirPath() + "/" + "data/unknown_block.gif");
    npcmask = QBitmap(QApplication::applicationDirPath() + "/" + "data/unknown_npcm.gif");
    uNpcImg = QPixmap(QApplication::applicationDirPath() + "/" + "data/unknown_npc.gif");
    uNpcImg.setMask(npcmask);
    uBgoImg = QPixmap(QApplication::applicationDirPath() + "/" + "data/unknown_bgo.gif");


    //set Default Z Indexes
    bgZ = -1000;
    blockZs = -150; // sizable blocks
    bgoZb = -100; // backround BGO

    blockZ = 1; // standart block
    playerZ = 5; //player Point

    bgoZf = 50; // foreground BGO

    npcZb = 20; // background NPC

    npcZs = 30; // standart NPC

    blockZl = 100; //LavaBlock
    npcZf = 150; // foreground NPC
    waterZ = 500;
    doorZ = 700;
    spaceZ1 = 1000; // interSection space layer
    spaceZ2 = 1020; // section Border

    //HistoryIndex
    historyIndex=0;

    historyChanged = false;

    //Locks
    lock_bgo=false;
    lock_block=false;
    lock_npc=false;
    lock_door=false;
    lock_water=false;

}

LvlScene::~LvlScene()
{
    uBGs.clear();
    uBGOs.clear();
    uBlocks.clear();
}




// ////////////////////Sort///////////////////////////

void LvlScene::sortBlockArray(QVector<LevelBlock > &blocks)
{
    LevelBlock tmp1;
    int total = blocks.size();
    long i;
    unsigned long ymin;
    long ymini;
    long sorted = 0;


        while(sorted < blocks.size())
        {
            ymin = blocks[sorted].array_id;
            ymini = sorted;

            for(i = sorted; i < total; i++)
            {
                if( blocks[i].array_id < ymin )
                {
                    ymin = blocks[i].array_id; ymini = i;
                }
            }
            tmp1 = blocks[ymini];
            blocks[ymini] = blocks[sorted];
            blocks[sorted] = tmp1;
            sorted++;
        }
}

void LvlScene::sortBlockArrayByPos(QVector<LevelBlock > &blocks)
{
    LevelBlock tmp1;
    int total = blocks.size();
    long i;
    long xmin;
    long xmini;
    long sorted = 0;


        while(sorted < blocks.size())
        {
            xmin = blocks[sorted].x;
            xmini = sorted;

            for(i = sorted; i < total; i++)
            {
                if( blocks[i].x < xmin )
                {
                    xmin = blocks[i].x; xmini = i;
                }
            }
            tmp1 = blocks[xmini];
            blocks[xmini] = blocks[sorted];
            blocks[sorted] = tmp1;
            sorted++;
        }
}

void LvlScene::sortBGOArray(QVector<LevelBGO > &bgos)
{
    LevelBGO tmp1;
    int total = bgos.size();
    long i;
    unsigned long ymin;
    unsigned long ymini;
    long sorted = 0;

        while(sorted < bgos.size())
        {
            ymin = bgos[sorted].array_id;
            ymini = sorted;

            for(i = sorted; i < total; i++)
            {
                if( bgos[i].array_id < ymin )
                {
                    ymin = bgos[i].array_id; ymini = i;
                }
            }
            tmp1 = bgos[ymini];
            bgos[ymini] = bgos[sorted];
            bgos[sorted] = tmp1;
            sorted++;
        }
}

