/* Boson2D (2020) http://github.com/dualword/Boson2D License:GNU GPL */
/***************************************************************************
                          boeditor.h  -  description                              
                             -------------------                                         

    version              : $Id: boeditor.h,v 1.20 2000/10/30 09:51:13 orzel Exp $
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

#ifndef BOEDITOR_H 
#define BOEDITOR_H 
 
// include files for Qt
#include <QApplication>
#include <QList>
// include files for KDE 
//#include <kapp.h>
//#include <kaction.h>

//class KActionCollection;
class editorTopLevel;


/*
 * The boson Application : handle the different communication layers
 *
 */
class BoEditorApp : public QApplication
{
	Q_OBJECT

public:
	/** construtor */
	BoEditorApp(int &argc, char **argv);
	/** destructor */
	~BoEditorApp();

	//KActionCollection &actions(void) { return m_actions; }

	// should be private, but needed in main.cpp
	/** actually open the file / set filename */
	void do_open(QString name);
public slots:

	/*
	 *  GUI stuff : Action slots
	 */
	/** open a new application window by creating a new instance of BoEditorApp */
	void slot_newWindow();

	/** clears the document in the actual view to reuse it as the new document */
	void slot_openNew();

	/** open a file and load it into the document*/
	void slot_open();

	/** close the current document
	 * return false when the document can't be closed */
	bool slot_close();

	/** open a recent file */
	void slot_openRecent();

	/** save a document */
	bool slot_save();

	/** save a document by a new filename*/
	bool slot_saveAs();

	/** quit the application  */
	void slot_quit();

private:
	void init(void); // internal

	//KActionCollection m_actions;
	QString		filename;

	QList<editorTopLevel>	topLevels;
};

#endif // BOEDITOR_H
 
