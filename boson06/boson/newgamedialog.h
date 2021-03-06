/*
    This file is part of the Boson game
    Copyright (C) 2001 The Boson Team (boson-devel@lists.sourceforge.net)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <kgame/kgamedialog.h>

/**
 * @author Andreas Beckermann <b_mann@gmx.de>
 **/
class NewGameDialog : public KGameDialog
{
	Q_OBJECT
public:
	NewGameDialog(KGame*, KPlayer* owner, QWidget* parent);
	virtual ~NewGameDialog();

public slots:
	virtual void slotOk();

signals:
	void signalStartGame();

private:
	KGame* mGame;
};

#endif
