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

#include "data_configs.h"

#include "../main_window/global_settings.h"

void dataconfigs::loadLevelBackgrounds()
{
    unsigned int i;
    obj_BG sbg;
    unsigned long bg_total=0;

    QString bg_ini = config_dir + "lvl_bkgrd.ini";

    if(!QFile::exists(bg_ini))
    {
        WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF lvl_bkgrd.ini: file not exist"));
          return;
    }

    QSettings bgset(bg_ini, QSettings::IniFormat);
    bgset.setIniCodec("UTF-8");

    main_bg.clear();   //Clear old

    bgset.beginGroup("background2-main");
        bg_total = bgset.value("total", "0").toInt();
        total_data +=bg_total;
    bgset.endGroup();

    ConfStatus::total_bg = bg_total;

    for(i=1; i<=bg_total; i++)
    {
        bgset.beginGroup( QString("background2-"+QString::number(i)) );
            sbg.name = bgset.value("name", "").toString();
            tmpstr = bgset.value("type", "single-row").toString();
                if(tmpstr=="single-row")
                   sbg.type = 0;
                else if(tmpstr=="double-row")
                   sbg.type = 1;
                else if(tmpstr=="tiled")
                   sbg.type = 2;
                else sbg.type = 0;

//                WriteToLog(QtDebugMsg, QString("Init BG image %1 with type %2 %3")
//                           .arg(i).arg(tmpstr).arg(sbg.type));

            sbg.repeat_h = bgset.value("repeat-h", "2").toInt();
            tmpstr = bgset.value("repeat-v", "NR").toString();
                if(tmpstr=="NR")
                    sbg.repead_v = 0;
                else if(tmpstr=="ZR")
                    sbg.repead_v = 1;
                else if(tmpstr=="RP")
                    sbg.repead_v = 2;
                else if(tmpstr=="RZ")
                    sbg.repead_v = 3;
                else sbg.repead_v = 0;

            imgFile = bgset.value("image", "").toString();
            sbg.image_n = imgFile;
            if( (imgFile!="") )
            {
                sbg.image = QPixmap(BGPath + imgFile);
            }
            else
            {
                sbg.image = QPixmap(QApplication::applicationDirPath() + "/" + "data/nobg.gif");
            }

            sbg.attached = (int)(bgset.value("attached", "bottom").toString()=="top");
            sbg.editing_tiled = (bgset.value("tiled-in-editor", "0").toString()=="1");

            sbg.magic = (bgset.value("magic", "0").toString()=="1");
            sbg.magic_strips = bgset.value("magic-strips", "1").toInt();
            sbg.magic_splits = bgset.value("magic-splits", "0").toString();
            sbg.magic_speeds = bgset.value("magic-speeds", "0").toString();

            sbg.animated = (bgset.value("animated", "0").toString()=="1");//animated
            sbg.frames = bgset.value("frames", "1").toInt();
            //frames

            if(sbg.type==1)
            {

                    imgFile = bgset.value("second-image", "").toString();
                    sbg.second_image_n = imgFile;
                    if( (imgFile!="") )
                    {
                        sbg.second_image = QPixmap(BGPath + imgFile);
                    }
                    else
                    {
                        sbg.second_image = QPixmap(QApplication::applicationDirPath() + "/" + "data/nobg.gif");
                    }
                    sbg.second_repeat_h = bgset.value("second-repeat-h", "2").toInt();
                    tmpstr = bgset.value("second-repeat-v", "NR").toString();
                        if(tmpstr=="NR")
                            sbg.second_repeat_v = 0;
                        else if(tmpstr=="ZR")
                            sbg.second_repeat_v = 1;
                        else if(tmpstr=="RP")
                            sbg.second_repeat_v = 2;
                        else if(tmpstr=="RZ")
                            sbg.second_repeat_v = 3;
                        else sbg.second_repeat_v = 0;
                    tmpstr = bgset.value("second-attached", "overfirst").toString();
                        if(tmpstr=="overfirst")
                            sbg.second_attached = 0;
                        else if(tmpstr=="bottom")
                            sbg.second_attached = 1;
                        else if(tmpstr=="top")
                            sbg.second_attached = 2;
                        else sbg.second_repeat_v = 0;
            }

            if(sbg.animated)
            {
                sbg.image=sbg.image.copy(0, 0, sbg.image.width(), (int)round(sbg.image.height()/sbg.frames));
            }
            sbg.id = i;
            main_bg.push_back(sbg);
        bgset.endGroup();


        if( bgset.status() != QSettings::NoError )
        {
            WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF lvl_bgrnd.ini N:%1 (background2-%2)").arg(bgset.status()).arg(i));
        }
    }

}
