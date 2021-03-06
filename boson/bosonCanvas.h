/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          bosonCanvas.h  -  description                              
                             -------------------                                         

    version              : $Id: bosonCanvas.h,v 1.14 2000/10/30 09:50:58 orzel Exp $
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

#ifndef BOSONFIELD_H 
#define BOSONFIELD_H 

#include <time.h>

#include <Q3Dict>

#include "common/msgData.h"
#include "common/unit.h"	// Facility
#include "common/cell.h"

#include "playerUnit.h"		// playerMobUnit
#include "visualCanvas.h"

class QRect;
class QPainter;
class Unit;


/** 
  * This class encapsulate the "physical" idea of the map : size, contents..
  */
class bosonCanvas : public visualCanvas
{
	Q_OBJECT

public:
	bosonCanvas( QPixmap, uint w, uint h);
	~bosonCanvas();

  void createMob(mobileMsg_t &);
  void unHideMob(mobileMsg_t &);
  void destroyMob(destroyedMsg_t &);
  void hideMob(destroyedMsg_t &);

  void createFix(facilityMsg_t &);
  void unHideFix(facilityMsg_t &);
  void destroyFix(destroyedMsg_t &);
  void hideFix(destroyedMsg_t &);

  void move(moveMsg_t &);
  void shooted(powerMsg_t &);
  void shoot(shootMsg_t &);
  void requestAction(void);
  void updateRess(unitRessMsg_t &);


	/** third (and last) communication layer : game */
	void handleGameMessage(bosonMsgTag, int, bosonMsgData *);

	/** configure the cell at the given point (i,j) */
  	void	setCell(int i, int j, cell_t c);	// not virtual !
	/** return the cell at (x,y) */
	Cell	&cell(int x, int y)
			{return cells[ x + y * maxX ]; }
	/** convenient function */
	Cell	&cell(QPoint p ) { return cell(p.x(), p.y()); }
	void 	setCellFlag(QRect r, Cell::cell_flags flag);
	void 	unsetCellFlag(QRect r, Cell::cell_flags flag);

	/* concerning contents */
	//playerFacility *getFacility(long key) { return facility.find(key); }
	bool		checkMove(QRect r, uint goFlag );

	//private :
	 Q3Dict<playerMobUnit>	mobile;
	 Q3Dict<playerFacility> facility;

signals:
	void	oilUpdated(int);
	void	mineralUpdated(int);
	void	mobileNbUpdated(int);
	void	facilityNbUpdated(int);
	void	pingUpdated(int);

private:
	Cell	*cells;
	time_t	ping;
	time_t	last_sync;
	int	my_fix;
	int	my_mobiles;
};

#endif // BOSONFIELD_H

