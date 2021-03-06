/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          visualMiniDisplay.h  -  description                              
                             -------------------                                         

    version              : $Id: visualMiniDisplay.h,v 1.10 2000/10/30 09:51:24 orzel Exp $
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

#ifndef VISUALMINIDISPLAY_H 
#define VISUALMINIDISPLAY_H 

#include "common/groundType.h"

#include <QWidget>
//#include <qframe.h> ///orzel qwidget.h XXXX

class Unit;
class QPixmap;
class visualTopLevel;
class visualMobUnit;
class visualFacility;

/** 
  * This is the little map, which "zoom" the battle field
  */
class visualMiniDisplay : public QWidget
{

	Q_OBJECT

public:
	visualMiniDisplay(visualTopLevel *, QWidget *parent=0, const char *name=0L);

	virtual QSize sizeHint() const { return QSize(_w+5, _h+5); }

signals:
  void	reCenterView(int x, int y);
//  void  reSizeView(int l, int h);

public slots:
  void newCell(int,int, groundType);
  void drawMobile(visualMobUnit *mob);
  void drawFix(visualFacility *fix);
  /** synchronize with the bocanvas (both ground and units) */
  void	sync(void);

protected:
	void setPoint(int x, int y, const QColor &color, QPainter *p=0L);
	void createData();

/* events */
  virtual void paintEvent(QPaintEvent *evt);
  virtual void mousePressEvent(QMouseEvent *e);

private:

  int			_w, _h;
  visualTopLevel	*vtl;
  QPixmap		*_ground;

};

#endif // VISUALMINIDISPLAY_H

