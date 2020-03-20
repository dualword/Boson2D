/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                         selectPart.h  -  description                              
                             -------------------                                         

    version              : $Id: selectPart.h,v 1.9 2000/10/30 09:51:23 orzel Exp $
    begin                : Sat Jun 26 16:23:00 CET 1999
                                           
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

#ifndef SELECTPART_H 
#define SELECTPART_H 


#include <Q3Canvas>
#include "sprites.h"		// S_PART
#include "common/unit.h"	// POWER_LEVELS


#define PART_NB		(POWER_LEVELS)

class selectPart : public Q3CanvasSprite
{
public:
	enum sp_type { PART_UP, PART_DOWN};

	selectPart(int frame, int z, sp_type type);
	
	virtual int rtti() const { return S_PART; } /* Qcanvas stuff */
private:
	static Q3CanvasPixmapArray	*qsps_up;
	static Q3CanvasPixmapArray	*qsps_down;
	
};

#endif // SELECTPART_H 
