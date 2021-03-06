/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          visualCanvas.cpp  -  description                              
                             -------------------                                         

    version              : $Id: visualCanvas.cpp,v 1.9 2000/10/30 09:51:24 orzel Exp $
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

#include <assert.h>

//#include <kapp.h>

#include "common/log.h"
#include "common/boconfig.h"
#include "common/bomap.h"

#include "speciesTheme.h"
#include "visual.h"
#include "sprites.h"
  

visualCanvas::visualCanvas( QPixmap p, uint w, uint h)
	: Q3Canvas ( p, w, h, BO_TILE_SIZE, BO_TILE_SIZE)
{
	/* map geometry */
	maxX = w; maxY = h;
	_pm = p;

	initTheme();
}



visualCanvas::visualCanvas(void)
	: Q3Canvas ()
{
	/* map geometry */
	maxX = 0; maxY = 0;
}
	
	
	
void visualCanvas::initTheme(void)
{

species[1]	= new speciesTheme("human", qRgb(0, 0, 255) );
/*
	if (!species[1]->isOk()) KMsgBox::message(0l,
		i18n("Pixmap loading error"),
		i18n("Error while loading \"blue\" specie theme,\nsome images will show up awfully"),
		KMsgBox::EXCLAMATION);
*/

species[0]	= new speciesTheme("human", qRgb( 0, 255, 0) );
/*
	if (!species[0]->isOk()) KMsgBox::message(0l,
		i18n("Pixmap loading error"),
		i18n("Error while loading \"red\" specie theme,\nsome images will show up awfully"),
		KMsgBox::EXCLAMATION);
*/


}


void visualCanvas::resize (int w, int h)
{

	/* map geometry */
	maxX = w; maxY = h;
	Q3Canvas::resize(w * BO_TILE_SIZE ,h * BO_TILE_SIZE);
	Q3Canvas::setTiles( _pm, w, h, BO_TILE_SIZE, BO_TILE_SIZE);
	logf(LOG_INFO, "visualCanvas::resize to %d, %d", w, h);
}


void visualCanvas::setCell(int i, int j, cell_t c)
{
	boAssert(i>=0);
	boAssert(j>=0);
	boAssert(i< tilesHorizontally() );
	boAssert(j< tilesVertically() );

//	printf("setCell :  i,j,c = %d,%d,%d\n", i, j, c); fflush(stdout);

	setTile( i, j, c);

	///orzel : XXX this is the bottleneck in editor::New
	emit newCell(i,j, ground(c));
}



Q3CanvasItem * visualCanvas::findUnitAt(int x, int y)
{
	Q3CanvasItemList list = collisions( QPoint(x,y) );
	Q3CanvasItemList::Iterator it;

	for( it = list.begin(); it != list.end(); ++it )
		if ( IS_UNIT( (*it)->rtti() ) )
			return (*it);
	return NULL;
}

