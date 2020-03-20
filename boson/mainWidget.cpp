/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                       mainWidget.cpp -  description 
                             -------------------                                         

    version              : $Id: mainWidget.cpp,v 1.6 2000/10/30 09:50:59 orzel Exp $
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

#include "bosonTopLevel.h"
#include "visualMiniDisplay.h"
#include "bosonBigDisplay.h"
#include "game.h"

#include "mainWidget.h"		// myself


#define VIEW_ONE	1
#define VIEW_MANY	2


mainWidget::mainWidget( bosonTopLevel *parent, const char *name)
	:Q3HBox(parent, name)
{ 
	btl = parent;

	Q3VBox *vb = new Q3VBox(this);
	big = new bosonBigDisplay( parent, this);
	mini = new visualMiniDisplay( parent, vb);
	mainFrame = new QFrame(vb);

	mini->setGeometry (   0,   0, 200,200);
	makeCommandGui();

	/* focus handling */
	//setFocusPolicy (StrongFocus);		// accept key event
	setFocus();

}

#define ARROW_KEY_STEP	2

void mainWidget::keyReleaseEvent ( QKeyEvent * e )
{
	switch (e->key()) {
		case Qt::Key_Left:
			btl->relativeMoveView(-ARROW_KEY_STEP,0);
			break;
		case Qt::Key_Right:
			btl->relativeMoveView(ARROW_KEY_STEP,0);
			break;
		case Qt::Key_Up:
			btl->relativeMoveView(0, -ARROW_KEY_STEP);
			break;
		case Qt::Key_Down:
			btl->relativeMoveView(0, ARROW_KEY_STEP);
			break;
	}
}


void mainWidget::makeCommandGui(void)
{

	mainFrame->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::MinimumExpanding ) );
	mainFrame->setMinimumSize (220, 200);

	mainFrame->setFrameStyle(QFrame::Sunken | QFrame::Panel);
	mainFrame->setLineWidth(5);
	
	/* stack */
	stack = new Q3WidgetStack(mainFrame, "qwidgetstack");
	stack->setFrameStyle(QFrame::Raised | QFrame::Panel);
	stack->setLineWidth(5);
	stack->setGeometry(10,23,180,110);

	/* stack/one */
	view_none = new QPixmap();

	view_one = new QLabel(stack,"preview");
	view_one->setPixmap(*view_none);
	stack->addWidget(view_one, VIEW_ONE);

	/* stack/many */
	view_many = new Q3ScrollView(stack,"scrollview");
	stack->addWidget(view_many, VIEW_MANY);

	stack->raiseWidget(VIEW_ONE);
}

