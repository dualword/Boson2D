/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                         game.h  -  description                              
                             -------------------                                         

    version              : $Id: game.h,v 1.13 2000/10/30 09:50:58 orzel Exp $
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

#ifndef BOSON_GAME_H 
#define BOSON_GAME_H 

#include "visual.h"
#include "connect.h"

class bosonCanvas;
//class KSocket;
class boBuffer;

#ifndef uint
typedef unsigned int uint;
#endif

	extern speciesTheme		*myspecy;
	extern uint			who_am_i;
/* The map which handle grouds and units*/
	extern bosonCanvas		*bocanvas;
/* synchronization */
	extern uint			jiffies;
/* deal with the communication layer */
	//extern KSocket			*Socket;
	extern playerSocketState	socketState;
	extern playerState		State;
	extern boBuffer			*buffer;
	
/* possesions */
	extern uint			oil;
	extern uint			mineral;

#endif // BOSON_GAME_H 
