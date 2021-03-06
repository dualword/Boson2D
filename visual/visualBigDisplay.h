/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          visualBigDisplay.h  -  description                              
                             -------------------                                         

    version              : $Id: visualBigDisplay.h,v 1.16 2000/10/30 09:51:24 orzel Exp $
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

#ifndef VISUALBIGDISPLAY_H 
#define VISUALBIGDISPLAY_H 

#include <Q3Dict>
#include <QPainter>
#include <Q3CanvasView>

#include "common/groundType.h"
#include "common/unitType.h"
#include "common/unit.h"	// Facility

#include "speciesTheme.h"
//#include "visualTopLevel.h"

class Unit;
class QPixmap;
class visualTopLevel;
class orderWin;


/** 
  * This class handles all operations concerning the game Board/Map
  */
class visualBigDisplay : public Q3CanvasView
{
  Q_OBJECT

public:
  visualBigDisplay(/*orderWin *,*/ visualTopLevel *, QWidget *parent=0, const char *name=0L, Qt::WindowFlags f=0);
  ~visualBigDisplay();


	/* from display classes */
	virtual void actionClicked(int, int, int state)=0;	// selecting, moving...
	virtual QSize sizeHint() const { return QSize(100,100); } // minimum size

signals:
	void	relativeReCenterView (int x, int y);
	void	reSizeView (int l, int h);

protected:
	// display
	void drawRectSelect(int x1, int y1, int x2, int y2, QPainter &qp)
		{ qp.drawRect(x1, y1, x2-x1, y2-y1); }

/* events */
//  virtual void drawContents( QPainter*, int cx, int cy, int cw, int ch );

//  virtual void paintEvent(QPaintEvent *evt);
  virtual void viewportMousePressEvent(QMouseEvent *e);
  virtual void viewportMouseMoveEvent(QMouseEvent *e);
  virtual void viewportMouseReleaseEvent(QMouseEvent *e);
  virtual void resizeEvent(QResizeEvent *e); // do we receive this one ?

  visualTopLevel	*vtl;

  int selectX, selectY;
  int oldX, oldY;

};

#endif // VISUALBIGDISPLAY_H


