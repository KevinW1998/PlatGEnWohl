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

void dataconfigs::loadMusic()
{
    unsigned int i;

    obj_music smusic_lvl;
    obj_music smusic_wld;
    obj_music smusic_spc;

    unsigned long music_lvl_total=0;
    unsigned long music_wld_total=0;
    unsigned long music_spc_total=0;

    QString music_ini = config_dir + "music.ini";

    if(!QFile::exists(music_ini))
    {
        WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF music.ini: file not exist"));
          return;
    }

    QSettings musicset(music_ini, QSettings::IniFormat);
    musicset.setIniCodec("UTF-8");

    main_music_lvl.clear();   //Clear old
    main_music_wld.clear();   //Clear old
    main_music_spc.clear();   //Clear old

    musicset.beginGroup("music-main");
        music_lvl_total = musicset.value("total-level", "0").toInt();
        music_wld_total = musicset.value("total-world", "0").toInt();
        music_spc_total = musicset.value("total-special", "0").toInt();

        music_custom_id = musicset.value("level-custom-music-id", "24").toInt();
        total_data +=music_lvl_total;
        total_data +=music_wld_total;
        total_data +=music_spc_total;
    musicset.endGroup();

    ConfStatus::total_music_lvl = music_lvl_total;
    ConfStatus::total_music_wld = music_wld_total;
    ConfStatus::total_music_spc = music_spc_total;


    //////////////////////////////

    //World music
    for(i=1; i<=music_wld_total; i++)
    {
        musicset.beginGroup( QString("world-music-"+QString::number(i)) );
            smusic_wld.name = musicset.value("name", "").toString();
            smusic_wld.file = musicset.value("file", "").toString();
            smusic_wld.id = i;
            main_music_wld.push_back(smusic_wld);
        musicset.endGroup();

        if( musicset.status() != QSettings::NoError )
        {
            WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF music.ini N:%1 (world music %2)").arg(musicset.status()).arg(i));
            break;
        }
    }

    //Special music
    for(i=1; i<=music_spc_total; i++)
    {
        musicset.beginGroup( QString("special-music-"+QString::number(i)) );
            smusic_spc.name = musicset.value("name", "").toString();
            smusic_spc.file = musicset.value("file", "").toString();
            smusic_spc.id = i;
            main_music_spc.push_back(smusic_spc);
        musicset.endGroup();

        if( musicset.status() != QSettings::NoError )
        {
            WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF music.ini N:%1 (special music %2)").arg(musicset.status()).arg(i));
            break;
        }
    }

    //Level music
    for(i=1; i<=music_lvl_total; i++)
    {
        musicset.beginGroup( QString("level-music-"+QString::number(i)) );
            smusic_lvl.name = musicset.value("name", "").toString();
            smusic_lvl.file = musicset.value("file", "").toString();
            smusic_lvl.id = i;
            main_music_lvl.push_back(smusic_lvl);
        musicset.endGroup();

        if( musicset.status() != QSettings::NoError )
        {
            WriteToLog(QtCriticalMsg, QString("ERROR LOADING OF music.ini N:%1 (level-music %2)").arg(musicset.status()).arg(i));
            break;
        }
    }


}
