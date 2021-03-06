/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          bosonCanvas.cpp  -  description                              
                             -------------------                                         

    version              : $Id: bosonCanvas.cpp,v 1.31 2000/10/30 09:50:58 orzel Exp $
    begin                : Thu Sep  9 01:27:00 CET 1999
                                           
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

#include <stdlib.h>	// rand

#include <assert.h>

#include "common/log.h"
#include "common/boconfig.h" // MAX_PLAYERS

#include "bosonCanvas.h"
#include "boshot.h"
#include "game.h" 	// who_am_i
  

#undef DEBUG_REQUEST_F

/*
 *  BOSON CANVAS
 */
bosonCanvas::bosonCanvas( QPixmap p, uint w, uint h)
	: visualCanvas(p,w,h)
{
	mobile.resize(149);
	facility.resize(149);

	my_fix = my_mobiles = 0;

	// ping initialisation, not relevant
	last_sync = time(NULL);

	cells = new Cell[w*h];
}


bosonCanvas::~bosonCanvas()
{
	delete [] cells;
}

void bosonCanvas::setCellFlag(QRect r, Cell::cell_flags flag)
{
	int i,j;
	for(i=r.left(); i<=r.right(); i++)
		for(j=r.top(); j<=r.bottom(); j++) {
			cell(i,j).setFlag( flag);
#ifdef DEBUG_REQUEST_F
			// does _not_ affect cells[]
			//  -> so it's only 'visual'
			//  -> algorithms not modified by this
			if (flag==Cell::request_f || flag==Cell::request_flying_f)
				setTile( i, j, makeCell(GROUND_WATER_OIL) );
#endif // DEBUG_REQUEST_F
		}
}

void bosonCanvas::unsetCellFlag(QRect r, Cell::cell_flags flag)
{
	int i,j;
	for(i=r.left(); i<=r.right(); i++)
		for(j=r.top(); j<=r.bottom(); j++) {
			cell(i,j).unsetFlag( flag);
#ifdef DEBUG_REQUEST_F
			if (flag==Cell::request_f || flag==Cell::request_flying_f)
				setTile( i, j, makeCell(GROUND_GRASS) ); 
#endif // DEBUG_REQUEST_F
			 }
}


bool bosonCanvas::checkMove(QRect r, uint goFlag )
	
{
	int	i,j;

	if ( r.left()<0 || r.top()<0) return false;
	if ( r.right()>=maxX || r.right()>=maxY ) return false;

	for(i=r.left(); i<=r.right(); i++)
		for(j=r.top(); j<=r.bottom(); j++)
			if (!cell(i, j).canGo( goFlag, ground( tile(i,j)))) return false;
	return true;
}

void bosonCanvas::hideMob(destroyedMsg_t &m)
{
	playerMobUnit *u;

	//u = mobile.find(m.key);
	if (u) u->doHide();
	else logf(LOG_ERROR, "bosonCanvas::unHideMob : can't find m.key");

	// XXX emit something for the minimap
}


void bosonCanvas::unHideMob(mobileMsg_t &m)
{
	playerMobUnit *u;

	assert( m.who < nb_player);
	//u = mobile.find(m.key);
	if (u) u->doShow();
	else logf(LOG_ERROR, "bosonCanvas::unHideMob : can't find m.key");

	// XXX emit something for the minimap
}



void bosonCanvas::createMob(mobileMsg_t &m)
{
	playerMobUnit *u;

	assert( m.who < nb_player);

	switch (m.type) {
		default:
			u = new playerMobUnit(&m);
			break;
		case MOB_MINERAL_HARVESTER:
		case MOB_OIL_HARVESTER:
			u = new harvesterUnit(&m);
			break;
	};

	//mobile.insert(m.key, u);

	emit updateMobile(u);

	if (m.who == who_am_i)
		emit mobileNbUpdated(++my_mobiles);
}


void bosonCanvas::destroyMob(destroyedMsg_t &m)
{
	playerMobUnit *mob ;
	
	//mob = mobile.find(m.key);
	if (!mob) {
		logf(LOG_ERROR, "bosonCanvas::destroyMob : can't find m.key");
		return;
	}

	if ( QPoint(m.x, m.y) != mob->gridRect().topLeft() )
		logf(LOG_WARNING, "Assertion failed file %s, line %d", __FILE__, __LINE__);

	QPoint p  = mob->center();
	new boShot ( p.x(), p.y(), mob->z(), boShot::SHOT_UNIT);

	if (mob->who == who_am_i)
		emit mobileNbUpdated(--my_mobiles);

	mob->destroy();
	//boAssert( mobile.remove(m.key) == true );

}


void bosonCanvas::hideFix(destroyedMsg_t &m)
{
	playerFacility *f;

	//f = facility.find(m.key);
	if (f) f->doHide();
	else logf(LOG_ERROR, "bosonCanvas::unHideFix : can't find m.key");

	// XXX emit something for the minimap
}

void bosonCanvas::unHideFix(facilityMsg_t &m)
{
	playerFacility *f;

	assert( m.who < nb_player);
	//f = facility.find(m.key);
	if (f) f->doShow();
	else logf(LOG_ERROR, "bosonCanvas::unHideFix : can't find m.key");

	// XXX emit something for the minimap
}


void bosonCanvas::createFix(facilityMsg_t &m)
{
	playerFacility *f;

	assert(m.who < (uint) nb_player);

	f = new playerFacility(&m);
	//facility.insert(m.key, f);

	emit updateFix(f);

	if (m.who == who_am_i)
		emit facilityNbUpdated(++my_fix);
}


void bosonCanvas::destroyFix(destroyedMsg_t &msg)
{
	playerFacility * f;
	
	//f = facility.find(msg.key);
	if (!f) {
		logf(LOG_ERROR, "bosonCanvas::destroyFix : can't find msg.key");
		return;
	}

	if ( QPoint(msg.x, msg.y) != f->gridRect().topLeft() )
		logf(LOG_WARNING, "Assertion failed file %s, line %d", __FILE__, __LINE__);

	QPoint p = f->center();
	new boShot ( p.x(), p.y(), f->z(), boShot::SHOT_FACILITY);

	if (f->who == who_am_i)
		emit facilityNbUpdated(--my_fix);

	f->destroy();
	//boAssert( facility.remove(msg.key) == true);
}


void bosonCanvas::move(moveMsg_t &msg)
{
	playerMobUnit * m;
	
	//m = mobile.find(msg.key);
	if (!m) {
		logf(LOG_ERROR, "bosonCanvas::move : can't find msg.key");
		return;
	}

	m->s_moveTo(QPoint(msg.newx, msg.newy));
}

void bosonCanvas::requestAction(void)
{
	Q3DictIterator<playerMobUnit> mobIt(mobile);
	Q3DictIterator<playerFacility> fixIt(facility);

	for (mobIt.toFirst(); mobIt; ++mobIt)
		mobIt.current()->getWantedAction();
	for (fixIt.toFirst(); fixIt; ++fixIt)
		fixIt.current()->getWantedAction();
}

void bosonCanvas::shooted(powerMsg_t &m)
{
	playerMobUnit	* mob;
	playerFacility	* fix;

//	mob = mobile.find(m.key);
//	fix = facility.find(m.key);

	if (mob) {
		/* shooting a mobile */
		mob->shooted(m.power);
	} else if (fix) {
		/* shooting a facility */
		fix->shooted(m.power);
	} else	logf(LOG_ERROR, "bosonCanvas::shooted : unexpected key in powerMsg_t : %d", m.key);

}


void bosonCanvas::updateRess(unitRessMsg_t &m)
{
	playerMobUnit	* mob = 0;  //mobile.find(m.key);
	
	if (mob) {
		mob->updateContain(m.contain);
	} else logf(LOG_ERROR, "bosonCanvas::updateRess : unexpected key in unitRessMsg_t : %d", m.key);
}


void bosonCanvas::shoot(shootMsg_t &m)
{
	playerMobUnit	* mob;
	playerFacility	* fix;
	QRect		r;
	double		_z;

//	mob = mobile.find(m.target_key);
//	fix = facility.find(m.target_key);
	if (!mob && !fix) {
		logf(LOG_ERROR, "bosonCanvas::shoot : unexpected target_key in shootMsg_t : %d", m.target_key);
		return;
	}
	
	if (!mob) {
		r  = fix->rect();
		_z = fix->z();

	} else {
		r  = mob->rect();
		_z = mob->z();
	}

	r.setSize( r.size()/2 );
	r.moveBy ( r.size().width()>>1, r.size().height()>>1 );

	new boShot(
			r.x() + rand()%r.width(),
			r.y() + rand()%r.height(),
			_z , 
			boShot::SHOT_SHOT);
}

void bosonCanvas::setCell(int i, int j, cell_t c)
{
	visualCanvas::setCell(i,j,c);
}

