/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                         boshot.h  -  description                              
                             -------------------                                         

    version              : $Id: boshot.h,v 1.7 2000/10/30 16:21:10 orzel Exp $
    begin                : Thu Dec 16 14:35:00 CET 1999
                                           
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

#ifndef BOSHOT_H 
#define BOSHOT_H 

#include <QObject>		// timer
#include <QBitArray>
#include <QBitmap>
#include <Q3Canvas>		// graphism
#include "sprites.h"		// rtti S_SHOT

#define SHOT_FRAMES		5

#define UNITS_SHOT_FRAMES	16
#define FIX_SHOT_FRAMES		16

#define UNITS_SHOTS_NB		4
#define FIX_SHOTS_NB		4



class boShot : public QObject,  public Q3CanvasSprite
{
	Q_OBJECT
public:
	enum shot_style { SHOT_SHOT, SHOT_UNIT, SHOT_FACILITY };

	boShot(int _x, int _y, int _z, shot_style s);
	/* QCanvas stuff */
	virtual int	rtti() const { return S_SHOT; }

protected:
	void	timerEvent( QTimerEvent * );

private:
	static	QBitArray		qba_units;			// which unit explosions are already loaded
	static	Q3CanvasPixmapArray	*unitSequ[UNITS_SHOTS_NB];	// explosions sequences for units
	static	QBitArray		qba_fix;			// which facilities explosions are already loaded
	static	Q3CanvasPixmapArray	*fixSequ[FIX_SHOTS_NB];		// explosions sequences for facilities
	static	Q3CanvasPixmapArray	*shotSequ;			// explosions sequence for small shots

	static	bool loadBig(shot_style style, int version);		// load one unit/facilitye pixmaps set
	static	bool loadSmall();

	int	counter;
	int	maxCounter;
	
};

#endif // BOSHOT_H 

