/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                         connectDlg.cpp  -  description                              
                             -------------------                                         

    version              : $Id: connectDlg.cpp,v 1.10 2000/10/30 09:50:58 orzel Exp $
    begin                : Sat Nov 11 17:19:00 CET 1999
                                           
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

#include <stdlib.h>	// atoi
#include <netdb.h>	// gethostbyname()
#include <unistd.h>	// gethostname()

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

//#include <ksock.h>
//#include <kmessagebox.h>

#include "common/log.h"
#include "common/boconfig.h"
#include "common/bobuffer.h"
#include "common/msgData.h"

#include "boson.h"
#include "connectDlg.h"
#include "serverDlg.h"
#include "game.h"

connectDlg::connectDlg(BosonApp *p, char *servername , const char *name)
	:QDialog(0l, name,true) // parentless : application-wide dialog
	,_parent(p)
{
        QPushButton	*button;
	QLabel		*label;
	char		host[2000];

	/* layout */
	resize( 390, 340 );
	setCaption( "Choose game mode" );     
	
	/* buttons */
	b_ok = new QPushButton( "Ok", this );
	b_ok->setGeometry( 10,300, 100,30 );
	connect( b_ok, SIGNAL(clicked()), SLOT(tryServer()) );

	button = new QPushButton( "Launch Server", this );
	button->setGeometry( 120,300, 150,30 );
	connect( button, SIGNAL(clicked()), SLOT(launchServer()) );

	button = new QPushButton( "Cancel", this );
	button->setGeometry( 280,300, 100,30 );
	connect( button, SIGNAL(clicked()), SLOT(reject()) );

	/* server params */
	if (gethostname(host, 1999)) {
		logf(LOG_ERROR, "can't get hostname, using \"boson.eu.org\"");
		strcpy(host, "boson.eu.org");
	}

	label = new QLabel("Boson Server :", this);
	label->setGeometry( 10,200, 140,30 );
	label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	e_server = new QLineEdit(this);
	e_server->setText(servername?servername:host);
	e_server->setGeometry( 160,200, 220,30 );
	e_server->setMaxLength(50);

	label = new QLabel("Connecting Port :", this);
	label->setGeometry( 10,250, 140,30 );
	label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
	e_port = new QLineEdit(this);
	e_port->setText( BOSON_DEFAULT_PORT_CHAR );
	e_port->setGeometry( 160,250, 60,30 );
	e_port->setMaxLength(6);

	/* beautification */
	label = new QLabel(this);
	label->move( (390-352)/2, 10);		// biglogo is 352x160
	//label->setAutoResize(true);
	label->setPixmap ( *dataPath + "pics/biglogo.bmp"); 
	//label->setPixmap( QPixmap( *dataPath + "pics/biglogo.bmp" ));
	boAssert(!label->pixmap()->isNull());

}


void connectDlg::tryServer(void)
{
	int	sock;
	int	port;
	struct	hostent *hostinfo;
	sockaddr_in sin;
	
	/* create the socket */
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if ( sock<0 ) {
		logf(LOG_FATAL, "tryServer : unable to create socket.");
  		//KMessageBox::error(this, "Unable to create a socket", "connection error");
		return;
	}
	
	/* connect the socket to server */
	hostinfo = gethostbyname( e_server->text() );
	if ( !hostinfo ) {
		logf(LOG_FATAL,"tryServer : unknown host %s.", (const char*)e_server->text());
  		//KMessageBox::error(this, "Can't find the boson server on the net", "Unknown host");
		return;
	}

	port = atoi(e_port->text());

	if ( ! (port>1000) ) {
		logf(LOG_FATAL,"tryServer : unexpeted port %s.", (const char*) e_port->text());
  		//KMessageBox::error(this, "The port must be an integer bigger than 1000", "unexpected port");
		return;
	}
	sin.sin_addr = *(struct in_addr*) hostinfo->h_addr;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	
	if ( ::connect(sock, (struct sockaddr *)&sin, sizeof(sin))<0 ) {
		logf(LOG_FATAL, "tryServer : unable to connect socket to \"%s\" server", (const char*) e_server->text() );
  		//KMessageBox::error(this, "Unable to connect to the server", "Unreachable server");
		return ;
	}
	
//	/* create the KSocket */
//	/* we don't use KSocket() because of a bug in KDE 1.1.2 that prevent us to know if the connection has failed */
//	Socket = new KSocket(sock);
//
//	if ( Socket->socket() <= 0 )  {
//		logf(LOG_FATAL, "tryServer : unable to create KSocket()");
//		socketState = PSS_CONNECT_DOWN;
//		delete Socket;
//  		KMessageBox::error(this, "Internal error : KSocket() creation error", "Internal error");
//		return;
//	}
//
//	logf(LOG_COMM, "KSocket connect ok");
//	logf(LOG_COMM, "\tsocket = %d, addr = %lu",
//			Socket->socket(), Socket->ipv4_addr());
//
//
//	/* buffer creation */
//	buffer = new boBuffer(Socket->socket() );
//	socketState = PSS_INIT;
//
//	/* KSocket configuration */
//	connect ( Socket, SIGNAL(closeEvent(KSocket *)),
//		_parent, SLOT(connectionLost(KSocket*) ) );
//	connect ( Socket, SIGNAL(readEvent(KSocket *)),
//		_parent, SLOT(handleSocketMessage(KSocket*) ) );
//	Socket->enableRead(TRUE);
	
	/* beginning of the connection protocol */
	logf(LOG_LAYER1, "Sending MSG_HS_INIT...");
	sendMsg(buffer, MSG_HS_INIT, BOSON_NO_DATA );
	socketState = PSS_WAIT_CONFIRM_INIT ;

	//b_ok->setEnabled(false);
	
	accept();
	/*
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(timeOut()) );
	timer->start( 3000, TRUE );                 // 3 seconds single-shot
	
	
	puts("last news 1");
	*/

}



void connectDlg::launchServer(void)
{
	serverDlg *dlg = new serverDlg( "serverDlg_0");

	connect( dlg, SIGNAL(configure(const char *, const char *)), SLOT(configure(const char *, const char *)) );
	hide();
	if ( dlg->exec() == QDialog::Accepted ) {
		delete dlg;
		tryServer();
		return;
	}
	delete dlg;
	show();
}


/*
void connectDlg::timeOut(void)
{
	if (  State >= PS_WAIT_BEGIN  )  {
		accept();
		return;
	}

	// nothing has happened
	printf("! State(%d) >= %d\n", State, PS_WAIT_BEGIN);
	printf("socketState = %d\n", socketState);
	delete buffer;
	delete Socket;
	socketState	= PSS_INIT;
	State		= PS_INIT;
  	KMessageBox::message(this, "Server not fast enough", "The server hasn't answered fast enough.");
	b_ok->setEnabled(true);
	
	show();
	return;
}
*/


void connectDlg::configure(const char *servername, const char *port)
{
	e_server->setText(servername);
	e_port->setText( port );
}
