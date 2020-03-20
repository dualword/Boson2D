/***************************************************************************
                          miniDisplay.cpp  -  description                              
                             -------------------                                         

    version              : $Id: miniDisplay.cpp,v 1.9 2000/10/30 09:51:13 orzel Exp $
    begin                : Sat Feb 17, 1999
                                           
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

#include <qpainter.h>
#include <qpixmap.h>

#include "common/bomap.h"

#include "visualMiniDisplay.h"
#include "visualUnit.h"


void visualMiniDisplay::drawMobile(visualMobUnit *unit)
{
	QPainter p;
	p.begin(_ground);
	setPoint(unit->x()/BO_TILE_SIZE, unit->y()/BO_TILE_SIZE, (unit->who==1/*orzelhack gpp.who_am_i*/)?magenta:darkMagenta, &p);
	p.end();
	repaint(FALSE);
}


void visualMiniDisplay::drawFix(visualFacility *fix)
{
	QPainter p;
	p.begin(_ground);
	setPoint(fix->x(), fix->y(), (fix->who==1/*orzelhack gpp.who_am_i*/)?magenta:darkMagenta, &p);
	p.end();
	repaint(FALSE);
}

