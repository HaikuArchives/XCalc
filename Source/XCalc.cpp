/**************************************************************************
 **
 ** XCalc.cpp
 **
 ** A GUI Calculator
 **
 ** Copyright © 1999 Nicolas Mougel (mougel@netcourrier.com)
 ** Copyright © 2001 - 2002 Nikolaev Ruslan (nruslan@hotbox.ru)
 **
 ** Under GPL License
 **
 **************************************************************************
 **
 ** History :
 **
 ** 1995 : First Release (Windows, Unix)
 ** 1998 : Let's go to the BeOS World!
 ** 1999 :  - GUI Version of XCalc
 **			- Base conversion added
 **			- Euro conversion
 **			- Cut/Copy/Paste Menu
 **			- Preferences Menu
 **			- View Less/More
 **			- More math functions
 **			- Use of BTextView instead of BTextControl
 **			- When an error occurs put the cursor on the wrong character
 **			- Corrected bugs of the parser (expressions like -2-2-2 or 3/3/3 now work)
 ** 2001 :  - First release of XCalc for BeOS R5.
 **			- Added lg x, ^1/y, number "e" functions, interface's changes.
 **			- Fixed some bugs
 **			- Added "Contents" menu
 **	2002 :  - More optimazation
 **			- Updated About dialog
 **			- Removed QuickHelp and "Contents" now is "Help"
 **			- Some other changes
 **************************************************************************/

#include <Application.h>

#include "XCalcWindow.h"
#include "XCalc.h"

// Create a window for the Calculator
XCalcApp :: XCalcApp() : BApplication("application/x-vnd.nruslan.xcalc")
{
	myWindow = new XCalcWindow(BRect(100, 100, 277, 305));
	myWindow->Show();
}

// Main Program
int main()
{ 
	XCalcApp myApp;
	myApp.Run();
	return(B_NO_ERROR);
}
