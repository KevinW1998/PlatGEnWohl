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
#include <QtMath>

#include "item_block.h"
#include "item_bgo.h"
#include "item_npc.h"
#include "item_water.h"

#include "../common_features/mainwinconnect.h"
#include "lvl_item_placing.h"


void LvlScene::keyReleaseEvent ( QKeyEvent * keyEvent )
{
    QList<QGraphicsItem*> selectedList = selectedItems();
    LevelData historyBuffer;
    bool deleted=false;

    QString objType;
    switch(keyEvent->key())
    {
    case (Qt::Key_Delete): //Delete action
        if(selectedList.isEmpty()) break;

        for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
        {

                objType=(*it)->data(0).toString();

                if(!(*it)->isVisible()) continue;  //Invisible items can't be deleted

                //remove data from main array before deletion item from scene
                if( objType=="Block" )
                {
                    historyBuffer.blocks.push_back(((ItemBlock*)(*it))->blockData);
                    ((ItemBlock *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="BGO" )
                {
                    historyBuffer.bgo.push_back(((ItemBGO*)(*it))->bgoData);
                    ((ItemBGO *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="NPC" )
                {
                    historyBuffer.npc.push_back(((ItemNPC*)(*it))->npcData);
                    ((ItemNPC *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
                else
                if( objType=="Water" )
                {
                    historyBuffer.water.push_back(((ItemWater*)(*it))->waterData);
                    ((ItemWater *)(*it))->removeFromArray();
                    if((*it)) delete (*it);
                    deleted=true;
                }
        }
        if(deleted) addRemoveHistory(historyBuffer);

        break;
    case (Qt::Key_Escape):
        if(!IsMoved)
            this->clearSelection();
        if(pResizer!=NULL )
            MainWinConnect::pMainWin->on_cancelResize_clicked();
            //setSectionResizer(false, false);
        break;
    case (Qt::Key_Enter):
    case (Qt::Key_Return):

        if(pResizer!=NULL )
            MainWinConnect::pMainWin->on_applyResize_clicked();
            //setSectionResizer(false, true);
        break;

    default:
        break;
    }
    QGraphicsScene::keyReleaseEvent(keyEvent);
}

void LvlScene::openProps()
{
    LevelBlock dummyBlock;
    dummyBlock.array_id=0;

    LevelBGO dummyBgo;
    dummyBgo.array_id=0;

    LevelNPC dummyNPC;
    dummyNPC.array_id=0;

    QList<QGraphicsItem * > items = this->selectedItems();
    if((!items.isEmpty())&&(items.size()==1))
    {
        if(items.first()->data(0).toString()=="Block")
        {
            MainWinConnect::pMainWin->LvlItemProps(0,
                          ((ItemBlock *)items.first())->blockData,
                          dummyBgo,
                          dummyNPC);
        }
        else
        if(items.first()->data(0).toString()=="BGO")
        {
            MainWinConnect::pMainWin->LvlItemProps(1,
                              dummyBlock,
                              ((ItemBGO *)items.first())->bgoData,
                              dummyNPC);
        }
        else
        if(items.first()->data(0).toString()=="NPC")
        {
            MainWinConnect::pMainWin->LvlItemProps(2,
                              dummyBlock,
                              dummyBgo,
                              ((ItemNPC *)items.first())->npcData);
        }
        else
        MainWinConnect::pMainWin->LvlItemProps(-1, dummyBlock, dummyBgo, dummyNPC);
    }
    else
    {
        MainWinConnect::pMainWin->LvlItemProps(-1, dummyBlock, dummyBgo, dummyNPC);
    }

    QGraphicsScene::selectionChanged();
}

static QPointF drawStartPos = QPoint(0,0);

void LvlScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    WriteToLog(QtDebugMsg, QString("Mouse pressed -> [%1, %2] contextMenuOpened=%3, DrawMode=%4").arg(mouseEvent->scenePos().x()).arg(mouseEvent->scenePos().y())
               .arg(contextMenuOpened).arg(DrawMode));

if(contextMenuOpened) return;

    switch(EditingMode)
    {
        case MODE_PlacingNew:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
                cursor->setPos( QPointF(applyGrid( mouseEvent->scenePos().toPoint(),
                                                   LvlPlacingItems::gridSz,
                                                   LvlPlacingItems::gridOffset)));
            }
            placeItemUnderCursor();
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
            break;
        }
        case MODE_DrawSquare:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
                drawStartPos = QPointF(applyGrid( mouseEvent->scenePos().toPoint(),
                                                  LvlPlacingItems::gridSz,
                                                  LvlPlacingItems::gridOffset));
                cursor->setPos( drawStartPos );
                cursor->setVisible(true);

                QPoint hw = applyGrid( mouseEvent->scenePos().toPoint(),
                                       LvlPlacingItems::gridSz,
                                       LvlPlacingItems::gridOffset);

                QSize hs = QSize( (long)fabs(drawStartPos.x() - hw.x()),  (long)fabs( drawStartPos.y() - hw.y() ) );
                ((QGraphicsRectItem *)cursor)->setRect(0,0, hs.width(), hs.height());
            }

            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
            break;

        }
        case MODE_Resizing:
        {
            QGraphicsScene::mousePressEvent(mouseEvent);
            return;
        }
        case MODE_Erasing:
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }

            if(cursor){
               cursor->show();
               cursor->setPos(mouseEvent->scenePos());
            }

            QGraphicsScene::mousePressEvent(mouseEvent);

            QList<QGraphicsItem*> selectedList = selectedItems();
            if (!selectedList.isEmpty())
            {
                removeItemUnderCursor();
                EraserEnabled=true;
            }
            break;
        }
        case MODE_PasteFromClip: //Pasta
        {
            if( mouseEvent->buttons() & Qt::RightButton )
            {
                MainWinConnect::pMainWin->on_actionSelect_triggered();
                return;
            }
            PasteFromBuffer = true;
            break;
        }
        default:
        {
            if((disableMoveItems) && (mouseEvent->buttons() & Qt::LeftButton)
                && (Qt::ControlModifier != QApplication::keyboardModifiers()))
            { return; }

            QGraphicsScene::mousePressEvent(mouseEvent);

            break;
        }
    }
    haveSelected=(!selectedItems().isEmpty());

}


void LvlScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //WriteToLog(QtDebugMsg, QString("Mouse moved -> [%1, %2]").arg(mouseEvent->scenePos().x()).arg(mouseEvent->scenePos().y()));
    if(contextMenuOpened) return;

    switch(EditingMode)
    {
    case MODE_PlacingNew:
        {
            this->clearSelection();
            if(cursor) cursor->setPos( QPointF(applyGrid( mouseEvent->scenePos().toPoint(),
                                                         LvlPlacingItems::gridSz,
                                                         LvlPlacingItems::gridOffset)));
                       cursor->show();
            if( mouseEvent->buttons() & Qt::LeftButton ) placeItemUnderCursor();
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            break;
        }
    case MODE_DrawSquare:
        {

            QPoint hw = applyGrid( mouseEvent->scenePos().toPoint(),
                                   LvlPlacingItems::gridSz,
                                   LvlPlacingItems::gridOffset);

            QSize hs = QSize( (long)fabs(drawStartPos.x() - hw.x()),  (long)fabs( drawStartPos.y() - hw.y() ) );

            if(cursor)
            {
                ((QGraphicsRectItem *)cursor)->setRect(0,0, hs.width(), hs.height());
                ((QGraphicsRectItem *)cursor)->setPos(
                            ((hw.x() < drawStartPos.x() )? hw.x() : drawStartPos.x()),
                            ((hw.y() < drawStartPos.y() )? hw.y() : drawStartPos.y())
                            );
            }
        }
    case MODE_Resizing:
        {
            this->clearSelection();
            QGraphicsScene::mouseMoveEvent(mouseEvent);
            return;
        break;
        }
    case MODE_Erasing:
        {
            if(cursor) cursor->setPos(mouseEvent->scenePos());
            if (EraserEnabled)// Remove All items, placed under Cursor
                removeItemUnderCursor();
            break;
        }
    default:
        if(cursor) cursor->setPos(mouseEvent->scenePos());
        break;
    }

    haveSelected=(!selectedItems().isEmpty());
    if(haveSelected)
    {
        if(!IsMoved)
        {
            IsMoved = true;
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void LvlScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(contextMenuOpened)
    {
        contextMenuOpened = false; //bug protector
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }

    switch(EditingMode)
    {
    case MODE_DrawSquare:
        {

        if(cursor)
        {
            if(placingItem==PLC_Water)
            {
                LvlPlacingItems::waterSet.quicksand = (LvlPlacingItems::waterType==1);

                LvlPlacingItems::waterSet.x = cursor->scenePos().x();
                LvlPlacingItems::waterSet.y = cursor->scenePos().y();
                LvlPlacingItems::waterSet.w = ((QGraphicsRectItem *)cursor)->rect().width();
                LvlPlacingItems::waterSet.h = ((QGraphicsRectItem *)cursor)->rect().height();
                //here define placing water item.
                LvlData->water_array_id++;

                LvlPlacingItems::waterSet.array_id = LvlData->water_array_id;
                LvlData->water.push_back(LvlPlacingItems::waterSet);

                placeWater(LvlPlacingItems::waterSet, true);
                LevelData plWater;
                plWater.water.push_back(LvlPlacingItems::waterSet);
                addPlaceHistory(plWater);

            }
            else
            if(placingItem==PLC_Block){
                long x = cursor->scenePos().x();
                long y = cursor->scenePos().y();
                long width = ((QGraphicsRectItem *)cursor)->rect().width();
                long height = ((QGraphicsRectItem *)cursor)->rect().height();
                int repWidth = width/32;
                int repHeight = height/32;
                for(int i = 0; i < repWidth; i++){
                    for(int j = 0; j < repHeight; j++){
                        LvlPlacingItems::blockSet.x = x + i * 32;
                        LvlPlacingItems::blockSet.y = y + i * 32;

                        LvlData->blocks_array_id++;

                        LvlPlacingItems::blockSet.array_id = LvlData->blocks_array_id;

                        LvlData->blocks.push_back(LvlPlacingItems::blockSet);
                        placeBlock(LvlPlacingItems::blockSet, true);
                    }
                }
            }
        cursor->hide();
        }
        break;
        }
    default:
        break;
    }


    if(DrawMode)
    {
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }

            int gridSize=32, offsetX=0, offsetY=0;//, gridX, gridY, i=0;

            QPoint sourcePos;

            cursor->hide();

            haveSelected = false;

            QString ObjType;
            int collisionPassed = false;

            //History
            LevelData historyBuffer; bool deleted=false;
            LevelData historySourceBuffer;

            if(PasteFromBuffer)
            {
                paste( LvlBuffer, mouseEvent->scenePos().toPoint() );
                PasteFromBuffer = false;
                IsMoved=false;
                MainWinConnect::pMainWin->on_actionSelect_triggered();
            }


            QList<QGraphicsItem*> selectedList = selectedItems();

            // check for grid snap
            if ((!selectedList.isEmpty())&&(IsMoved))
            {

                // correct selected items' coordinates
                for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
                {
                    if(EditingMode==MODE_Erasing)
                    {

                        if(!(*it)->isVisible()) continue; //Invisible items can't be deleted

                        //remove data from main array before deletion item from scene
                        if( (*it)->data(0).toString()=="Block" )
                        {
                            historyBuffer.blocks.push_back(((ItemBlock*)(*it))->blockData);
                            ((ItemBlock *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="BGO" )
                        {
                            historyBuffer.bgo.push_back(((ItemBGO*)(*it))->bgoData);
                            ((ItemBGO *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="NPC" )
                        {
                            historyBuffer.npc.push_back(((ItemNPC*)(*it))->npcData);
                            ((ItemNPC *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        else
                        if( (*it)->data(0).toString()=="Water" )
                        {
                            historyBuffer.water.push_back(((ItemWater*)(*it))->waterData);
                            ((ItemWater *)(*it))->removeFromArray();
                            deleted=true;
                        }
                        removeItem((*it));
                        continue;
                    }

                    gridSize = 32;
                    offsetX = 0;
                    offsetY = 0;
                    ObjType = (*it)->data(0).toString();

                    //(*it)->setZValue(Z);
                    if( ObjType == "NPC")
                    {
                        gridSize = ((ItemNPC *)(*it))->gridSize;
                        offsetX = ((ItemNPC *)(*it))->localProps.grid_offset_x;
                        offsetY = ((ItemNPC *)(*it))->localProps.grid_offset_y;
                    }
                    else
                    if( ObjType == "BGO")
                    {
                        gridSize = ((ItemBGO *)(*it))->gridSize;
                        offsetX = ((ItemBGO *)(*it))->gridOffsetX;
                        offsetY = ((ItemBGO *)(*it))->gridOffsetY;
                    }else
                    if( ObjType == "Water")
                    {
                        gridSize = 16;
                    }else
                    if( ObjType == "Door_enter")
                        gridSize = 16 ;
                    else
                    if( ObjType == "Door_exit")
                        gridSize = 16 ;
                    else
                    if( ObjType == "player1")
                    {
                        offsetY = 2;
                        gridSize = 2 ;
                    }
                    else
                    if( ObjType == "player2")
                    {
                        offsetY = 2;
                        gridSize = 2 ;
                    }

                    ////////////////////Apply to GRID/////////////////////////////////
                    (*it)->setPos( QPointF(
                                       applyGrid( (*it)->scenePos().toPoint(),
                                                      gridSize,
                                                      QPoint(offsetX, offsetY)
                                                  )
                                           )
                                  );
                    //////////////////////////////////////////////////////////////////
                }

                if((EditingMode==MODE_Erasing)&&(deleted))
                {
                    addRemoveHistory(historyBuffer);
                }
                EraserEnabled = false;


                // Check collisions
                //Only if collision ckecking enabled
                if(!PasteFromBuffer)

                for (QList<QGraphicsItem*>::iterator it = selectedList.begin(); it != selectedList.end(); it++)
                {
                    ObjType = (*it)->data(0).toString();

                    WriteToLog(QtDebugMsg, QString(" >>Check collision with \"%1\"").arg(ObjType));

                    if( ObjType == "NPC")
                    {
                        sourcePos = QPoint(  ((ItemNPC *)(*it))->npcData.x, ((ItemNPC *)(*it))->npcData.y);
                    }
                    else
                    if( ObjType == "Block")
                    {
                        sourcePos = QPoint(  ((ItemBlock *)(*it))->blockData.x, ((ItemBlock *)(*it))->blockData.y);
                        //WriteToLog(QtDebugMsg, QString(" >>Check collision for Block"));
                    }
                    else
                    if( ObjType == "BGO")
                    {
                        sourcePos = QPoint(  ((ItemBGO *)(*it))->bgoData.x, ((ItemBGO *)(*it))->bgoData.y);
                    }
                    else
                    if( ObjType == "Water")
                    {
                        sourcePos = QPoint(  ((ItemWater *)(*it))->waterData.x, ((ItemWater *)(*it))->waterData.y);
                    }

                    //Check position
                    if( sourcePos == QPoint((long)((*it)->scenePos().x()), ((long)(*it)->scenePos().y())))
                    {
                        IsMoved=false;
                        WriteToLog(QtDebugMsg, QString(" >>Collision skiped, posSource=posCurrent"));
                        continue;
                    }

                    if(opts.collisionsEnabled)
                    { //check Available to collisions checking
                        if( itemCollidesWith((*it)) )
                        {
                            collisionPassed = false;
                            (*it)->setPos(QPointF(sourcePos));
                            (*it)->setSelected(false);
                            /*
                            WriteToLog(QtDebugMsg, QString("Moved back %1 %2")
                                       .arg((long)(*it)->scenePos().x())
                                       .arg((long)(*it)->scenePos().y()) );*/
                        }
                        else
                        {
                            collisionPassed = true;
                        }
                    }

                    if((collisionPassed) || (!opts.collisionsEnabled))
                    {
                        if( ObjType == "Block")
                        {
                            //WriteToLog(QtDebugMsg, QString(" >>Collision passed"));
                            //Applay move into main array
                            historySourceBuffer.blocks.push_back(((ItemBlock *)(*it))->blockData);
                            ((ItemBlock *)(*it))->blockData.x = (long)(*it)->scenePos().x();
                            ((ItemBlock *)(*it))->blockData.y = (long)(*it)->scenePos().y();
                            ((ItemBlock *)(*it))->arrayApply();
                            historyBuffer.blocks.push_back(((ItemBlock *)(*it))->blockData);
                            LvlData->modified = true;
                        }
                        else
                        if( ObjType == "BGO")
                        {
                            //Applay move into main array
                            historySourceBuffer.bgo.push_back(((ItemBGO *)(*it))->bgoData);
                            ((ItemBGO *)(*it))->bgoData.x = (long)(*it)->scenePos().x();
                            ((ItemBGO *)(*it))->bgoData.y = (long)(*it)->scenePos().y();
                            ((ItemBGO *)(*it))->arrayApply();
                            historyBuffer.bgo.push_back(((ItemBGO *)(*it))->bgoData);
                            LvlData->modified = true;
                        }
                        else
                        if( ObjType == "NPC")
                        {
                            //Applay move into main array
                            historySourceBuffer.npc.push_back(((ItemNPC *)(*it))->npcData);
                            ((ItemNPC *)(*it))->npcData.x = (long)(*it)->scenePos().x();
                            ((ItemNPC *)(*it))->npcData.y = (long)(*it)->scenePos().y();
                            ((ItemNPC *)(*it))->arrayApply();
                            historyBuffer.npc.push_back(((ItemNPC *)(*it))->npcData);
                            LvlData->modified = true;
                        }
                        else
                        if( ObjType == "Water")
                        {
                            //Applay move into main array
                            historySourceBuffer.water.push_back(((ItemWater *)(*it))->waterData);
                            ((ItemWater *)(*it))->waterData.x = (long)(*it)->scenePos().x();
                            ((ItemWater *)(*it))->waterData.y = (long)(*it)->scenePos().y();
                            ((ItemWater *)(*it))->arrayApply();
                            historyBuffer.water.push_back(((ItemWater *)(*it))->waterData);
                            LvlData->modified = true;
                        }
                    }
                }

                if((EditingMode==MODE_Selecting)&&(IsMoved)) addMoveHistory(historySourceBuffer, historyBuffer);

                IsMoved = false;

                QGraphicsScene::mouseReleaseEvent(mouseEvent);
                return;
           }
     EraserEnabled = false;
     QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void LvlScene::placeItemUnderCursor()
{
    LevelData newData;
    bool wasPlaced=false;
    if( itemCollidesWith(cursor) )
    {
        return;
    }
    else
    {
        if(placingItem == PLC_Block)
        {
            LvlPlacingItems::blockSet.x = cursor->scenePos().x();
            LvlPlacingItems::blockSet.y = cursor->scenePos().y();

            LvlData->blocks_array_id++;
            LvlPlacingItems::blockSet.array_id = LvlData->blocks_array_id;

            LvlData->blocks.push_back(LvlPlacingItems::blockSet);
            placeBlock(LvlPlacingItems::blockSet, true);
            newData.blocks.push_back(LvlPlacingItems::blockSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_BGO)
        {
            LvlPlacingItems::bgoSet.x = cursor->scenePos().x();
            LvlPlacingItems::bgoSet.y = cursor->scenePos().y();

            LvlData->bgo_array_id++;
            LvlPlacingItems::bgoSet.array_id = LvlData->bgo_array_id;

            LvlData->bgo.push_back(LvlPlacingItems::bgoSet);
            placeBGO(LvlPlacingItems::bgoSet, true);
            newData.bgo.push_back(LvlPlacingItems::bgoSet);
            wasPlaced=true;
        }
        else
        if(placingItem == PLC_NPC)
        {
            LvlPlacingItems::npcSet.x = cursor->scenePos().x();
            LvlPlacingItems::npcSet.y = cursor->scenePos().y();

            LvlData->npc_array_id++;
            LvlPlacingItems::npcSet.array_id = LvlData->npc_array_id;

            LvlData->npc.push_back(LvlPlacingItems::npcSet);
            placeNPC(LvlPlacingItems::npcSet, true);
            newData.npc.push_back(LvlPlacingItems::npcSet);
            wasPlaced=true;
        }
    }
    if(wasPlaced)
    {
        LvlData->modified = true;
        addPlaceHistory(newData);
    }

    if(opts.animationEnabled) stopAnimation();
    if(opts.animationEnabled) startBlockAnimation();

}


void LvlScene::removeItemUnderCursor()
{
    if(contextMenuOpened) return;

    QGraphicsItem * findItem;
    bool removeIt=true;
    findItem = itemCollidesCursor(cursor);
    if(findItem)
    {
        if(findItem->data(0).toString()=="Block")
        {
            if((lock_block)|| (((ItemBlock *)findItem)->isLocked) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="BGO")
        {
            if( (lock_bgo) || ((((ItemBGO *)findItem)->isLocked)) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="NPC")
        {
            if( (lock_npc) || ((((ItemNPC *)findItem)->isLocked)) )
            removeIt=false;
        }
        else
        if(findItem->data(0).toString()=="Water")
        {
            if( (lock_water) || ((((ItemWater *)findItem)->isLocked)) )
            removeIt=false;
        }
        else
        if(((findItem->data(0).toString()=="Door_enter")||(findItem->data(0).toString()=="Door_exit"))&&
                (lock_door))
            removeIt=false;

        if(!findItem->isVisible()) //Invisible items can't be deleted
            removeIt=false;

        if(removeIt)
        {
            LevelData removedItems;
            bool deleted=false;
            //remove data from main array before deletion item from scene
            if( findItem->data(0).toString()=="Block" )
            {
                removedItems.blocks.push_back(((ItemBlock *)findItem)->blockData);
                ((ItemBlock *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="BGO" )
            {
                removedItems.bgo.push_back(((ItemBGO *)findItem)->bgoData);
                ((ItemBGO *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="NPC" )
            {
                removedItems.npc.push_back(((ItemNPC *)findItem)->npcData);
                ((ItemNPC *)findItem)->removeFromArray();
                deleted=true;
            }
            else
            if( findItem->data(0).toString()=="Water" )
            {
                removedItems.water.push_back(((ItemWater *)findItem)->waterData);
                ((ItemWater *)findItem)->removeFromArray();
                deleted=true;
            }
            removeItem(findItem);
            delete findItem;
            if(deleted)addRemoveHistory(removedItems);
        }
    }
}


void LvlScene::setSectionResizer(bool enabled, bool accept)
{
    if((enabled)&&(pResizer==NULL))
    {
        int x = LvlData->sections[LvlData->CurSection].size_left;
        int y = LvlData->sections[LvlData->CurSection].size_top;
        int w = LvlData->sections[LvlData->CurSection].size_right;
        int h = LvlData->sections[LvlData->CurSection].size_bottom;

        pResizer = new ItemResizer( QSize((long)fabs(x-w), (long)fabs(y-h)), Qt::green, 32 );
        this->addItem(pResizer);
        pResizer->setPos(x, y);
        pResizer->type=0;
        pResizer->_minSize = QSizeF(800, 608);
        this->setFocus(Qt::ActiveWindowFocusReason);
        //DrawMode=true;
        MainWinConnect::pMainWin->activeLvlEditWin()->changeCursor(5);
    }
    else
    {
        if(pResizer!=NULL)
        {
            if(accept)
            {
                WriteToLog(QtDebugMsg, QString("SECTION RESIZE -> to %1 x %2").arg(pResizer->_width).arg(pResizer->_height));
                long l = pResizer->pos().x();
                long t = pResizer->pos().y();
                long r = l+pResizer->_width;
                long b = t+pResizer->_height;
                long oldL = LvlData->sections[LvlData->CurSection].size_left;
                long oldR = LvlData->sections[LvlData->CurSection].size_right;
                long oldT = LvlData->sections[LvlData->CurSection].size_top;
                long oldB = LvlData->sections[LvlData->CurSection].size_bottom;
                LvlData->sections[LvlData->CurSection].size_left = l;
                LvlData->sections[LvlData->CurSection].size_right = r;
                LvlData->sections[LvlData->CurSection].size_top = t;
                LvlData->sections[LvlData->CurSection].size_bottom = b;

                addResizeSectionHistory(LvlData->CurSection, oldL, oldT, oldR, oldB, l, t, r, b);

                ChangeSectionBG(LvlData->sections[LvlData->CurSection].background);
                drawSpace();
            }
            delete pResizer;
            pResizer = NULL;
            MainWinConnect::pMainWin->on_actionSelect_triggered();
            //resetResizingSection=true;
        }
        DrawMode=false;
    }
}

void LvlScene::SwitchEditingMode(int EdtMode)
{
    //int EditingMode; // 0 - selecting,  1 - erasing, 2 - placeNewObject
                     // 3 - drawing water/sand zone, 4 - placing from Buffer
    //bool EraserEnabled;
    //bool PasteFromBuffer;

    //bool DrawMode; //Placing/drawing on map, disable selecting and dragging items

    //bool disableMoveItems;

    //bool contextMenuOpened;
    EraserEnabled=false;
    PasteFromBuffer=false;
    DrawMode=false;
    disableMoveItems=false;

    switch(EdtMode)
    {
    case MODE_PlacingNew:
        DrawMode=true;
        setSectionResizer(false, false);

        break;
    case MODE_DrawSquare:
        resetCursor();
        setSectionResizer(false, false);
        DrawMode=true;
        break;

    case MODE_Resizing:
        resetCursor();
        DrawMode=true;
        disableMoveItems=true;
        break;

    case MODE_PasteFromClip:
        resetCursor();
        setSectionResizer(false, false);
        disableMoveItems=true;
        break;

    case MODE_Erasing:
        resetCursor();
        setSectionResizer(false, false);
        break;

    case MODE_SelectingOnly:
        resetCursor();
        setSectionResizer(false, false);
        disableMoveItems=true;
        break;
    case MODE_Selecting:
    default:
        resetCursor();
        setSectionResizer(false, false);
        break;
    }
    EditingMode = EdtMode;

}
