/**************************************************************************
 **
 ** XCalcWindow.cpp
 **
 ** The XCalc window
 **
 **************************************************************************
 **
 ** First Author: Nicolas Mougel
 ** E-Mail: mougel@netcourrier.com
 **
 ** Second Author: Nikolaev Ruslan
 ** E-Mail: nruslan@hotbox.ru
 **
 ** If you update this program, please contact the author.
 **
 **************************************************************************/

#include <Application.h>
#include <MenuBar.h>
#include <Menu.h>
#include <Roster.h>
#include <stdio.h>

#include "XCalcWindow.h"
#include "Preferences.h"
#include "Defines.h"

extern Preferences Prefs;

/* 
 * Window constructor : add a view and menus
 */

XCalcWindow :: XCalcWindow(BRect frame) :
	BWindow(frame, "XCalc " XCALC_VERSION, B_TITLED_WINDOW_LOOK, B_NORMAL_WINDOW_FEEL, B_NOT_ZOOMABLE | B_NOT_RESIZABLE)
{
	// Load preferences
	if (Prefs.LoadPrefs()==false)
	{
		Prefs.SetDefaultPrefs();
	}

	// View
	myView = new XCalcView(Bounds());
	
	// Menu Bar
	BMenuBar *menubar = new BMenuBar(Bounds(),"Menu Bar");

	// File Menu	
	BMenu *menu = new BMenu(LANG_MENU_FILE);
	menu->AddItem(new BMenuItem(LANG_MENU_FILE_HELP,new BMessage(MENU_FILE_HELP), 'H'));
	menu->AddItem(new BMenuItem(LANG_ABOUT,new BMessage(MENU_FILE_ABOUT), 'A'));
	menu->AddSeparatorItem();
	menu->AddItem(new BMenuItem(LANG_MENU_FILE_QUIT,new BMessage(MENU_FILE_QUIT),'Q'));
	menubar->AddItem(menu);

	// Edit Menu
	menu = new BMenu(LANG_MENU_EDIT);
	menu->AddItem(new BMenuItem(LANG_MENU_EDIT_CUT,new BMessage(MENU_EDIT_CUT),'X'));
	menu->AddItem(new BMenuItem(LANG_MENU_EDIT_COPY,new BMessage(MENU_EDIT_COPY),'C'));
	menu->AddItem(new BMenuItem(LANG_MENU_EDIT_PASTE,new BMessage(MENU_EDIT_PASTE),'V'));
	menubar->AddItem(menu);

	// Tools Menu
	menu = new BMenu(LANG_MENU_VIEW);
	menu->AddItem(new BMenuItem(LANG_PREFS,new BMessage(MENU_VIEW_PREFS), 'P'));
	menu->AddSeparatorItem();
	if (Prefs.GetView()==X_LESS)
		MenuItemLessMore=new BMenuItem(LANG_MORE,new BMessage(MENU_VIEW_MORE),'S');
	else
		MenuItemLessMore=new BMenuItem(LANG_LESS,new BMessage(MENU_VIEW_MORE),'S');
	menu->AddItem(MenuItemLessMore);
	menubar->AddItem(menu);

	// Add
	AddChild(menubar);
	AddChild(myView);

	// View Less, More
	if (Prefs.GetView()==X_LESS)
		viewMore = false;
	else
	{
		ResizeTo(455,205);
		viewMore = true;
		myView->ViewMore();
	}
	
	MoveTo(Prefs.GetLeft(),Prefs.GetTop());

}

/* 
 * Window Messages : about and quit
 */

void XCalcWindow :: MessageReceived(BMessage* message)
{
	char *urld = "/boot/home/config/documentation/xcalc/index.html";

	switch(message->what)
	{
		// About
		case MENU_FILE_ABOUT:
		myAbout=new AboutWindow(BRect(150, 80, 407, 290));
		myAbout->Show();
		break;
		// Help
        case MENU_FILE_HELP:
		be_roster->Launch("text/html", 1, &urld);
        break;
		// Quit
		case MENU_FILE_QUIT:
		be_app->PostMessage(B_QUIT_REQUESTED);
		break;
		// View
		case MENU_VIEW_PREFS:
		myPrefs=new PrefsWindow(BRect(200,150,435,350));
		myPrefs->Show();
		break;
			
		case MENU_VIEW_MORE:
			if (viewMore==false)
		            {
				ResizeTo(455,205);
				viewMore=true;
				MenuItemLessMore->SetLabel(LANG_LESS);
				myView->ViewMore();
			}
			else
                                        {
				ResizeTo(177,205);
				viewMore=false;
				MenuItemLessMore->SetLabel(LANG_MORE);
				myView->ViewLess();
			}
			break;
		// Base
		case POPUP_BIN:
		case POPUP_TRI:
		case POPUP_BS4:
		case POPUP_BS5:
		case POPUP_BS6:
		case POPUP_BS7:
		case POPUP_OCT:
		case POPUP_BS9:
		case POPUP_DEC:
		case POPUP_BS11:
		case POPUP_DUO:
		case POPUP_BS13:
		case POPUP_BS14:
		case POPUP_BS15:
		case POPUP_HEX:
		case POPUP_BS17:
		case POPUP_BS18:
			myView->MessageReceived(message);
			break;
		// Cut, Copy, Paste
		case MENU_EDIT_CUT:
		case MENU_EDIT_COPY:
		case MENU_EDIT_PASTE:
			myView->MessageReceived(message);
			break;
		// Default
		default:
			BWindow::MessageReceived(message);
			break;

	}
}

/* 
 * Window Quit : quit application
 */

bool XCalcWindow :: QuitRequested()
{
	BRect rec = Frame();
	Prefs.SetTop(rec.top);
	Prefs.SetLeft(rec.left);

	// Save preferences
	Prefs.SavePrefs();
	
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}
