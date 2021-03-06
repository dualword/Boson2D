/***************************************************************************
                          serverCell.h  -  description                              
                             -------------------                                         

    version              : $Id: serverCell.h,v 1.10 2000/10/30 09:51:19 orzel Exp $
    begin                : Sat Jan  9 19:35:36 CET 1999
                                           
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

#ifndef SERVERCELL_H 
#define SERVERCELL_H 

#include "common/groundType.h"
#include "knownBy.h"

class BosonServer;

/** 
  * This is a cell in the server point of view
  */
class serverCell : public knownBy
{
	friend	BosonServer; /* to write in _cell */

public:
	serverCell() { _cell = makeCell(GROUND_UNKNOWN); }

	groundType	ground(void) { return ::ground(_cell); }
//	byte		version(void) { return version(_cell); }
//	void		operator= (cell_t c) { _cell = c; }
private:
	cell_t	_cell;
};

#endif // SERVERCELL_H
