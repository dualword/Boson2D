/***************************************************************************
                       mainWidget.h -  description 
                             -------------------                                         

    version              : $Id: mainWidget.h,v 1.3 2000/10/30 09:51:13 orzel Exp $
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


class editorTopLevel;
class visualMiniDisplay;
class editorBigDisplay;
class QFrame;


class mainWidget : public QHBox
{
	Q_OBJECT

	friend editorTopLevel;
public:
	mainWidget( editorTopLevel *parent=0, const char *name=0);

	void	ressourcesUpdated(void);
protected:
	virtual void keyReleaseEvent (QKeyEvent * e );

private:
	QFrame			*mainFrame;
	editorTopLevel		*etl;
	visualMiniDisplay	*mini;
	editorBigDisplay	*big;

};


#endif     // MAINWIDGET_H