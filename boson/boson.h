/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          boson.h  -  description                              
                             -------------------                                         

    version              : $Id: boson.h,v 1.22 2000/10/30 09:50:58 orzel Exp $
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

#ifndef BOSON_H 
#define BOSON_H 
 
// include files for QT
#include <QApplication>
#include <QList>
// include files for KDE 
//#include <kapp.h>
// application specific includes
#include "common/msgData.h"


//class KSocket;
class KProcess;
class bosonTopLevel;


/*
 * The boson Application : handle the different communication layers
 *
 */
class BosonApp : public QApplication
{
	Q_OBJECT

public:
	/** construtor */
	BosonApp(int &argc, char **argv);
	/** destructor */
	~BosonApp();

protected slots:
//	/** first communication layer : socket */
//	void handleSocketMessage(KSocket *);
//
//	/** slots used when the connection is lost, whoever detected this */
//	void connectionLost(KSocket *s);
//
//	/** called whenever the server launched by serverDlg died */
//	void serverDied(KProcess *);

private:
	/** socket initialisation : try to connect to the BosonServer */
	//void initSocket(char *servername=0l);
	/** second communication layer : client/server */
	void handleDialogMessage(bosonMsgTag, int, bosonMsgData *);

	/** initialisation functions */
	void init(void); // internal
	void initCanvas(int, int);
	/** called when the server told us the game has finished */
	void gameEnd( endMsg_t::endReasonType reason );
};

///orzel : ugly global variable, only used once in connect.cpp by bosonCanvas
/* the different topLevel Window */
extern QList<bosonTopLevel>	topLevels;

#endif // BOSON_H
 
