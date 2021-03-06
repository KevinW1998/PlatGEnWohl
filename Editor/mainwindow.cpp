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

#include "ui_mainwindow.h"
#include "mainwindow.h"

#include "npc_dialog/npcdialog.h"

MainWindow::MainWindow(QMdiArea *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    thread1 = new QThread;

    setDefaults(); // Apply default common settings

    QPixmap splashimg(":/splash.png");
    QSplashScreen splash(splashimg);
    splash.setCursor(Qt::ArrowCursor);
    splash.show();

    if(!configs.loadconfigs())
    {
        QMessageBox::critical(this, "Configuration error", "Configuration can't be load.\nSee in debug_log.txt for more information.", QMessageBox::Ok);
        splash.finish(this);
        WriteToLog(QtFatalMsg, "<Application emergency closed>");
        exit(EXIT_FAILURE);
        return;
    }

    splash.finish(this);

    WriteToLog(QtDebugMsg, QString("Set UI..."));
    ui->setupUi(this);

    WriteToLog(QtDebugMsg, QString("Setting Lang..."));
    setDefLang();

    setUiDefults(); //Apply default UI settings
}

//Scene Event Detector
void MainWindow::TickTack()
{
    if(TickTackLock) return;

    TickTackLock = true;

    try
    {
        if(activeChildWindow()==1)
        {
            if(activeLvlEditWin()->sceneCreated)
            {
                //Capturing flags from active Window
                /*if(activeLvlEditWin()->scene->wasPasted)
                {
                    activeLvlEditWin()->changeCursor(0);
                    activeLvlEditWin()->scene->wasPasted=false;
                    activeLvlEditWin()->scene->disableMoveItems=false;
                }
                else
                if(activeLvlEditWin()->scene->doCut)
                {
                    on_actionCut_triggered();
                    activeLvlEditWin()->scene->doCut=false;
                }
                else
                if(activeLvlEditWin()->scene->doCopy)
                {
                    on_actionCopy_triggered();
                    activeLvlEditWin()->scene->doCopy=false;
                }
                else*/
                if(activeLvlEditWin()->scene->historyChanged)
                {
                    ui->actionUndo->setEnabled( activeLvlEditWin()->scene->canUndo() );
                    ui->actionRedo->setEnabled( activeLvlEditWin()->scene->canRedo() );
                    activeLvlEditWin()->scene->historyChanged = false;
                }
                /*
                else
                if(activeLvlEditWin()->scene->resetPosition)
                {
                    on_actionReset_position_triggered();
                    activeLvlEditWin()->scene->resetPosition = false;
                }
                else
                if(activeLvlEditWin()->scene->SyncLayerList)
                {
                    setLayersBox();
                    activeLvlEditWin()->scene->SyncLayerList = false;
                }
                else
                if(activeLvlEditWin()->scene->resetResizingSection)
                {
                    ui->ResizeSection->setVisible(true);
                    ui->applyResize->setVisible(false);
                    ui->cancelResize->setVisible(false);
                    activeLvlEditWin()->scene->resetResizingSection = false;
                }*/
            }
        }
        /*
        else
        if(activeChildWindow()==2)
        {
            if(activeNpcEditWin()->NpcData.ReadFileValid);
        }*/
    }
    catch(int e)
    {
        WriteToLog(QtWarningMsg, QString("CLASS TYPE MISMATCH IN TIMER ON WINDOWS SWITCH: %1").arg(e));
    }

    TickTackLock = false;
}

MainWindow::~MainWindow()
{
    TickTackLock = false;
    delete ui;
    WriteToLog(QtDebugMsg, "--> Application closed <--");
}



//////////////////SLOTS///////////////////////////

//Exit from application
void MainWindow::on_Exit_triggered()
{
    MainWindow::close();
    exit(0);
}

//Open About box
void MainWindow::on_actionAbout_triggered()
{
    aboutDialog about;
    about.setWindowFlags (Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    about.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, about.size(), qApp->desktop()->availableGeometry()));
    about.exec();
}



////////////////////////New files templates///////////////////////////

void MainWindow::on_actionNewNPC_config_triggered()
{

    NpcDialog * npcList = new NpcDialog(&configs);
    npcList->setWindowFlags (Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    npcList->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, npcList->size(), qApp->desktop()->availableGeometry()));
    npcList->setState(0, 1);
    npcList->setWindowTitle(tr("Create new NPC.txt configuration file"));
    if(npcList->exec()==QDialog::Accepted)
    {
        npcedit *child = createNPCChild();
        child->newFile( npcList->selectedNPC);
        child->show();
    }

}


//Toolbar context menu
void MainWindow::on_MainWindow_customContextMenuRequested(const QPoint &pos)
{
    WriteToLog(QtDebugMsg, QString("Main Menu's context menu called! %1 %2").arg(pos.x()).arg(pos.y()));

    QMenu *cu = new QMenu(this);
    QAction *test= cu->addAction("Nothing");
    test->setEnabled(false);
    QAction *test2= cu->addAction("Nothing");
    test2->setEnabled(false);
    QAction *test3= cu->addAction("Nothing");
    test3->setEnabled(false);

    cu->exec(pos);

}

