/**************************************************************************
 **
 ** XCalcView.h
 **
 ** The XCalc window header
 **
 **************************************************************************/

#ifndef XCalcWindow_h
#define XCalcWindow_h

#include <Window.h>
#include <MenuItem.h>
#include <Dragger.h>

#include "XCalcAbout.h"
#include "XCalcPrefs.h"
#include "XCalcView.h"

#define MENU_FILE_HELP		11
#define MENU_FILE_ABOUT		12
#define MENU_FILE_QUIT		13

#define MENU_EDIT_CUT		21
#define MENU_EDIT_COPY		22
#define MENU_EDIT_PASTE		23

#define MENU_VIEW_PREFS		31
#define MENU_VIEW_MORE		32


/* 
 * The Window contains a View and an About window
 */

class XCalcWindow : public BWindow
{
	public:
		XCalcWindow(BRect frame);
		void MessageReceived(BMessage*);
		bool QuitRequested();
	private:
		AboutWindow *myAbout;
		PrefsWindow *myPrefs;
		XCalcView *myView;
		BDragger *myDragger;
		
		BMenuItem *MenuItemLessMore;
		bool viewMore;
};

#endif /* XCalcWindow_h */
