/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                       bosonBigDisplay.cpp  -  description                              
                             -------------------                                         

    version              : $Id: bosonBigDisplay.cpp,v 1.16 2000/10/30 09:50:58 orzel Exp $
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

#include "common/log.h"

#include "bosonTopLevel.h"
#include "bosonCanvas.h"
#include "playerUnit.h"
#include "bosonBigDisplay.h"
#include "game.h"


bosonBigDisplay::bosonBigDisplay(bosonTopLevel *btl, QWidget *parent, const char *name, Qt::WindowFlags f)
	:visualBigDisplay(btl,parent,name,f)
{
}


void bosonBigDisplay::actionClicked(int mx, int my, int /*state*/)
{
	Q3CanvasItem *sfg;

	/* is there any mobiles of my own selected ? */
	if (vtl->mobSelected.isEmpty()) return;	// nothing to do
	if ((int)who_am_i != vtl->selectionWho) return;	// nothing to do

	Q3IntDictIterator<visualMobUnit> mobIt(vtl->mobSelected);


	sfg = bocanvas->findUnitAt( mx, my);
	if (!sfg) {
		// nothing has been found : it's a ground-click
		// order all mobiles to go there
		for (mobIt.toFirst(); mobIt; ++mobIt) {
			boAssert(mobIt.current()->who == who_am_i);
			((playerMobUnit *)mobIt.current())->u_goto(QPoint(mx,my));
		}
		return;
	}
	

	if ( IS_MOBILE(sfg->rtti())) {
		playerMobUnit *m = (playerMobUnit *) sfg;

		for (mobIt.toFirst(); mobIt; ++mobIt) {
			boAssert(mobIt.current()->who == who_am_i);
			((playerMobUnit *)mobIt.current())->u_attack(m);
		}

		return;
	}

	/* do exactly the same, may change in the future */
	if ( IS_FACILITY(sfg->rtti())) {
		playerFacility *f = (playerFacility *) sfg;

		for (mobIt.toFirst(); mobIt; ++mobIt) {
			boAssert(mobIt.current()->who == who_am_i);
			((playerMobUnit *)mobIt.current())->u_attack(f);
		}

		return;
	}

	// should never be reached !
	logf(LOG_ERROR, "bosonBigDisplay.cpp, unexpected bocanvas->findUnitAt() result");
	

} 

