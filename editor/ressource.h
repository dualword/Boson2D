/***************************************************************************
                          ressource.h  -  description                              
                             -------------------                                         

    version              : $Id: ressource.h,v 1.5 2000/10/30 09:51:13 orzel Exp $
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

#ifndef EDITOR_RESSOURCE_H
#define EDITOR_RESSOURCE_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#define BOEDITOR_VERSION_TEXT 	"0.5.0"

///////////////////////////////////////////////////////////////////
// ressource.h  -- contains macros used for commands


///////////////////////////////////////////////////////////////////
// COMMAND VALUES FOR MENUBAR AND TOOLBAR ENTRIES


///////////////////////////////////////////////////////////////////
// File-menu entries
#define ID_FILE_NEW_WINDOW          10010
#define ID_FILE_NEW                 10020
#define ID_FILE_OPEN                10030
#define ID_FILE_RECENT              10040

#define ID_FILE_SAVE                10050
#define ID_FILE_SAVE_AS             10060
#define ID_FILE_CLOSE               10070

#define ID_FILE_PRINT               10080

#define ID_FILE_CLOSE_WINDOW        10090


///////////////////////////////////////////////////////////////////
// Edit-menu entries
#define ID_EDIT_UNDO                11010
#define ID_EDIT_REDO                11020
#define ID_EDIT_COPY                11030
#define ID_EDIT_CUT                 11040
#define ID_EDIT_DESTROY             11045
#define ID_EDIT_PASTE               11050
#define ID_EDIT_SELECT_ALL          11060


///////////////////////////////////////////////////////////////////
// View-menu entries                    
#define ID_VIEW_TOOLBAR_0           12010
#define ID_VIEW_STATUSBAR           12020
#define ID_VIEW_OPTIONS             12030



///////////////////////////////////////////////////////////////////
// General application values
#define ID_APP_EXIT                 1000      
#define ID_STATUS_MSG               1001
#define ID_HELP                     1002

#define IDS_DEFAULT                 "Ready."

#define IDS_APP_ABOUT		"BoEditor Version " BOEDITOR_VERSION_TEXT \
				"(c) 1999" \
				"\nThomas Capricelli" \
				" <orzel@yalbi.com>"


///////////////////////////////////////////////////////////////////
// MACROS FOR THE CONNECT OF YOUR SIGNALS TO CORRESPONDENT SLOTS 
// IN YOUR MAIN IMPLEMENTATION OF MENUBAR AND TOOLBAR


///////////////////////////////////////////////////////////////////
// MENU CONNECTS
#define CONNECT_CMD(submenu)           connect(submenu, SIGNAL(activated(int)), SLOT(commandCallback(int)));connect(submenu,SIGNAL(highlighted(int)), SLOT(statusCallback(int)))


///////////////////////////////////////////////////////////////////
// TOOLBAR CONNECT  
#define CONNECT_TOOLBAR(ToolBar)        connect(ToolBar, SIGNAL(clicked(int)), SLOT(commandCallback(int)));connect(ToolBar, SIGNAL(highlighted(int,bool)), SLOT(statusCallback(int)))


///////////////////////////////////////////////////////////////////
// MACROS FOR GENERATING THE SWITCH CONSTRUCTION OF THE commandCallback(int) METHOD
#define BEGIN_CMD(class)	void class::commandCallback(int id_){ switch (id_){
#define ON_CMD(id, cmd_class_function, message) \
				case id:slotStatusMsg(message);cmd_class_function; slotStatusMsg(IDS_DEFAULT);break;   
#define END_CMD()		}}


///////////////////////////////////////////////////////////////////
// MACROS FOR GENERATING THE SWITCH CONSTRUCTION OF THE statusCallback(int) METHOD
#define BEGIN_STATUS_MSG(class)		void class::statusCallback(int id_){ switch (id_){
#define ON_STATUS_MSG(id, message)	case id:  slotStatusHelpMsg(message);break;
#define END_STATUS_MSG()		default: slotStatusMsg(IDS_DEFAULT); }}

#endif // EDITOR_RESSOURCE_H

