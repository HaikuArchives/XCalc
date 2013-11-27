/**************************************************************************
 **
 ** XCalcView.h
 **
 ** The XCalc view header
 **
 **************************************************************************/

#ifndef XCalcView_h
#define XCalcView_h

#include <View.h>
#include <Button.h>
#include <TextView.h>
#include <ScrollView.h>
#include <MenuField.h>
#include <PopUpMenu.h>
#include "XCalcTextView.h"

#define POPUP_BIN	91
#define POPUP_TRI	95
#define POPUP_BS4	96
#define POPUP_BS5	97
#define POPUP_BS6	98
#define POPUP_BS7	99
#define POPUP_OCT	92
#define POPUP_BS9	100
#define POPUP_DEC	93
#define POPUP_BS11	101
#define POPUP_DUO	102
#define POPUP_BS13	103
#define POPUP_BS14	104
#define POPUP_BS15	105
#define POPUP_HEX	94
#define POPUP_BS17	106
#define POPUP_BS18	107

/* 
 * The View contains a BTextView and a lot of BButtons !
 */

class XCalcView : public BView
{
	public:
		XCalcView(BRect rec);
		void MessageReceived(BMessage*);
		void AttachedToWindow();
		void ViewMore();
		void ViewLess();
		
	private:
		// Display for the calculator
		XCalcTextView *myDisplay;
		BScrollView *myScrollBar;

		// The buttons of the keypad
		BButton *Button7, *Button8, *Button9,
				*Button4, *Button5, *Button6,
				*Button1, *Button2, *Button3,
				*Button0;
					
		BButton *ButtonEuro, *ButtonCurr;

		BButton *ButtonAdd, *Button1X, *ButtonSub, *ButtonDiv,
				*ButtonMult, *ButtonLeftPar, *ButtonRightPar;

		BButton *ButtonP2, *ButtonLg, *ButtonX1Y, *ButtonE1, *ButtonRoot, *ButtonPow,
				*ButtonLn, *ButtonLb, *ButtonLog, *ButtonExp, *ButtonPi, *ButtonN, *Button10Y;

		// Trigonometry
		BButton *ButtonCos, *ButtonSin, *ButtonTan, *ButtonCtg, *ButtonSec, *ButtonCsc,
		*ButtonAcos, *ButtonAsin, *ButtonAtan, *ButtonActg, *ButtonAsec, *ButtonAcsc,
		*ButtonCsh, *ButtonSnh, *ButtonTgh, *ButtonCgh, *ButtonSch, *ButtonCch,
		*ButtonAcsh, *ButtonAsnh, *ButtonAtgh, *ButtonAcgh, *ButtonAsch, *ButtonAcch;
		
		BButton *ButtonA, *ButtonB, *ButtonC, *ButtonD,
				*ButtonE, *Button10X, *ButtonF, *ButtonG, *ButtonH;
		
		BButton *ButtonClear, *ButtonBack, *ButtonDot,
				*ButtonRes;

		BMenuField *MenuFieldBase;
		BPopUpMenu *PopUpBase;

		// For string manipulation		
		char *myLine;
		
};

#endif /* XCalcView_h */
