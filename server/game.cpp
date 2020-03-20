/***************************************************************************
                         game.cpp  -  description                              
                             -------------------                                         

    version              : $Id: game.cpp,v 1.7 2000/10/30 09:51:19 orzel Exp $
    begin                : Sat Jun 19 01:53:00 CET 1999
                                           
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

QString	*worldName;
Player	player[BOSON_MAX_CONNECTION];
uint	jiffies = 0;
uint	nbConnected = 0;
BosonServer	*server = 0;

