/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                         game.cpp  -  description                              
                             -------------------                                         

    version              : $Id: game.cpp,v 1.16 2000/10/30 09:50:58 orzel Exp $
    begin                : Wen Apr 14 20:22:00 CET 1999
                                           
    copyright            : (C) 1999-2000 by Thomas Capricelli                         
    email                : orzel@yalbi.com                                     
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   * 
 *                                                                         *
 ***************************************************************************/


#include "game.h"

/*
 * visual/visual.h
 */
visualCanvas		*vcanvas=0;
speciesTheme		*species[BOSON_MAX_PLAYERS] = {0l, 0l};
uint			nb_player;
QString			*dataPath;

/*
 * boson/game.h
 */
speciesTheme		*myspecy	= 0l;
uint			who_am_i	= 0u;
/* The map which handle grouds and units*/
bosonCanvas		*bocanvas	= 0l;
/* synchronization */
uint			jiffies		= 0u;
/* deal with the communication layer */
//KSocket			*Socket		= 0l;
playerSocketState	socketState	= PSS_INIT;
playerState		State		= PS_INIT;
boBuffer		*buffer		= 0l;

/* possesions */
uint			oil		= 0u;
uint			mineral		= 0u;

