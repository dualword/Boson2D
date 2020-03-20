/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          speciesTheme.h  -  description                              
                             -------------------                                         

    version              : $Id: speciesTheme.h,v 1.12 2000/10/30 15:51:03 orzel Exp $
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

#ifndef SPECIESTHEME_H 
#define SPECIESTHEME_H 

#include <QString>
#include <QRgb>

#include "common/unitType.h"
#include "common/unit.h"

class QString;
class QBitArray;
class QPixmap;
class Q3CanvasPixmapArray;

/** 
  * This class handles the drawing of the different units for a given specy(ie?)
  */
class speciesTheme
{
public:
	speciesTheme(char *themeName, QRgb c);
	~speciesTheme();

	Q3CanvasPixmapArray *getPixmap(mobType unit);
	Q3CanvasPixmapArray *getPixmap(facilityType unit);

	QPixmap		*getBigOverview(mobType unit);
	QPixmap		*getBigOverview(facilityType unit);

	QPixmap		*getBigOverview(mobUnit *u) { return getBigOverview(u->getType()); }
	QPixmap		*getBigOverview(Facility *u) { return getBigOverview(u->getType()); }


	QPixmap		*getSmallOverview(mobType unit);
	QPixmap		*getSmallOverview(facilityType unit);

	QPixmap		*getSmallOverview(mobUnit *u) { return getSmallOverview(u->getType()); }
	QPixmap		*getSmallOverview(Facility *u) { return getSmallOverview(u->getType()); }

protected:
	bool 		loadMob(int index);
	bool		loadFix(int index);
	bool		loadPixmap(const QString &path, QPixmap **p, bool withMask = true, bool with_team_color=true);

private:
	QString		themePath;
	QRgb		team_color;

	QBitArray	*mobiles, *facilities;

	QPixmap		**mobBigOverview;	// pixmaps for the control panel
	QPixmap		**fixBigOverview;	// pixmaps for the control panel
	QPixmap		**mobSmallOverview;	// pixmaps for the control panel
	QPixmap		**fixSmallOverview;	// pixmaps for the control panel

	Q3CanvasPixmapArray
			**mobSprite,		// all sprites for a given mobile
			**fixSprite;		// all sprites for a giver facility

};

#endif // SPECIESTHEME_H


