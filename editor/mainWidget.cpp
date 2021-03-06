/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                       mainWidget.cpp -  description 
                             -------------------                                         

    version              : $Id: mainWidget.cpp,v 1.6 2000/10/30 09:51:13 orzel Exp $
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

//#include <qkeycode.h>
#include <Q3WidgetStack>
#include <QFrame>
#include <Q3ScrollView>
#include <QPixmap>
#include <QLabel>
#include <Q3VBox>
#include <QKeyEvent>

#include "common/log.h"

#include "editorTopLevel.h"
#include "visualMiniDisplay.h"
#include "editorBigDisplay.h"
#include "mainWidget.h"		// myself


mainWidget::mainWidget( editorTopLevel *parent, const char *name)
	:Q3HBox(parent, name)
{ 
	etl = parent;

	Q3VBox  *vb = new Q3VBox (this);
	big = new editorBigDisplay( parent, this);
	mini = new visualMiniDisplay( parent, vb);
	mainFrame = new QFrame(vb);

	connect (etl, SIGNAL(setSelectedObject(object_type, int)), big, SLOT(setSelectedObject(object_type, int)));
	connect (etl, SIGNAL(setWho(uint)), big, SLOT(setWho(uint)));

	/* focus handling */
	setFocusPolicy (Qt::StrongFocus);		// accept key event
	setFocus();


}

#define ARROW_KEY_STEP	2

void mainWidget::keyReleaseEvent ( QKeyEvent * e )
{
	switch (e->key()) {
		case Qt::Key_Left:
			etl->relativeMoveView(-ARROW_KEY_STEP,0);
			break;
		case Qt::Key_Right:
			etl->relativeMoveView(ARROW_KEY_STEP,0);
			break;
		case Qt::Key_Up:
			etl->relativeMoveView(0, -ARROW_KEY_STEP);
			break;
		case Qt::Key_Down:
			etl->relativeMoveView(0, ARROW_KEY_STEP);
			break;
	}
}

