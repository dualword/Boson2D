/***************************************************************************
                         sprites.h  -  description                              
                             -------------------                                         

    version              : $Id: sprites.h,v 1.13 2000/10/30 09:51:23 orzel Exp $
    begin                : Sat Apr 24 20:42:00 CET 1999
                                           
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

#ifndef SPRITES_H 
#define SPRITES_H 

#define	S_BASE		1000
#define	S_PART		(S_BASE+	10)
#define	S_MOBILE	(S_PART+	200)
#define	S_FACILITY	(S_MOBILE+	100)
#define	S_SHOT		(S_FACILITY+	100)
#define	S_END		(S_SHOT+	100)

#define Z_MOBILE		(+400)
#define Z_FACILITY		(+300)
#define Z_DESTROYED_MOBILE	(+200)
#define Z_DESTROYED_FACILITY	(+100)
#define Z_INVISIBLE		(-10)


#define IS_MOBILE(rtti)		( ((rtti) >= S_MOBILE  )  && ((rtti) < S_FACILITY) )
#define IS_FACILITY(rtti)	( ((rtti) >= S_FACILITY)  && ((rtti) < S_SHOT    ) )
#define IS_UNIT(rtti)		( ((rtti) >= S_MOBILE  )  && ((rtti) < S_SHOT    ) )

#endif // SPRITES_H
