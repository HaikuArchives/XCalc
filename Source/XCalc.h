/**************************************************************************
 **
 ** XCalc.h
 **
 ** The application header
 **
 **************************************************************************/

#ifndef XCalc_h
#define XCalc_h

#include <Window.h>

/* 
 * The Application contains a Window
 */

class XCalcApp : public BApplication
{
	public:
		XCalcApp();
	private:
		BWindow *myWindow;
};

#endif /* XCalc_h */
