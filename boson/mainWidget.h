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

#include <qhbox.h>

#include "common/msgData.h"

class	bosonTopLevel;
class	visualMiniDisplay;
class	bosonBigDisplay;
class	QWidgetStack;
class	QLabel;
class	QScrollView;
class	QPixmap;
class	QPushButton;
class	QFrame;

class mainWidget : public QHBox 
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
	QWidgetStack	*stack;
	QLabel		*view_one;
	QScrollView	*view_many;
	QPixmap		*view_none;
};


#endif     // MAINWIDGET_H