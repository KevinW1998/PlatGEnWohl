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

#ifndef NPC_FILEDATA_H
#define NPC_FILEDATA_H

struct NPCConfigFile
{
    bool ReadFileValid;

    /* Using options flags BEGIN */
    bool en_gfxoffsetx;
    bool en_gfxoffsety;
    bool en_width;
    bool en_height;
    bool en_gfxwidth;
    bool en_gfxheight;
    bool en_score;
    bool en_playerblock;
    bool en_playerblocktop;
    bool en_npcblock;
    bool en_npcblocktop;
    bool en_grabside;
    bool en_grabtop;
    bool en_jumphurt;
    bool en_nohurt;
    bool en_noblockcollision;
    bool en_cliffturn;
    bool en_noyoshi;
    bool en_foreground;
    bool en_speed;
    bool en_nofireball;
    bool en_nogravity;
    bool en_frames;
    bool en_framespeed;
    bool en_framestyle;
    bool en_noiceball;
    bool en_nohammer;
    bool en_noshell;
    /* Using options flags END */

    int gfxoffsetx;
    int gfxoffsety;
    unsigned int width;
    unsigned int height;
    unsigned int gfxwidth;
    unsigned int gfxheight;
    unsigned int score;
    bool playerblock;
    bool playerblocktop;
    bool npcblock;
    bool npcblocktop;
    bool grabside;
    bool grabtop;
    bool jumphurt;
    bool nohurt;
    bool noblockcollision;
    bool cliffturn;
    bool noyoshi;
    bool foreground;
    float speed;
    bool nofireball;
    bool nogravity;
    unsigned int frames;
    unsigned int framespeed;
    unsigned int framestyle;
    bool noiceball;

    bool nohammer;
    bool noshell;
};

#endif // NPC_FILEDATA_H
