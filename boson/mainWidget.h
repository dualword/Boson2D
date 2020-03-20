/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                       mainWidget.h -  description 
                             -------------------                                         

    version              : $Id: mainWidget.h,v 1.5 2000/10/30 09:50:59 orzel Exp $
    begin                : Mon Apr 19 23:56:00 CET 1999
                                           
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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <Q3HBox>

#include "common/msgData.h"

class	bosonTopLevel;
class	visualMiniDisplay;
class	bosonBigDisplay;
class	Q3WidgetStack;
class	QLabel;
class	Q3ScrollView;
class	QPixmap;
class	QPushButton;
class	QFrame;

class mainWidget : public Q3HBox
{
	Q_OBJECT

	friend bosonTopLevel;
public:
	mainWidget( bosonTopLevel *parent=0, const char *name=0);

protected:
	virtual void keyReleaseEvent (QKeyEvent * e );

private:

	bosonTopLevel	*btl;
	/*
	 * GUI
	 */
	void	makeCommandGui(void);

	QFrame			*mainFrame;
	/* the map object we are playing in */
	visualMiniDisplay	*mini;
	bosonBigDisplay		*big;

	/* state view (for selected items) */
	Q3WidgetStack	*stack;
	QLabel		*view_one;
	Q3ScrollView	*view_many;
	QPixmap		*view_none;
};


#endif     // MAINWIDGET_H
