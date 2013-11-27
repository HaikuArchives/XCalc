/**************************************************************************
 **
 ** XCalcTextView.h
 **
 ** The XCalcTextView header
 **
 **************************************************************************/

#ifndef XCalcTextView_h
#define XCalcTextView_h

#include <TextView.h>

/* 
 * For the input of the user and the display of the result
 */

class XCalcTextView : public BTextView
{
	public:
		XCalcTextView(BRect , const char *, BRect , uint32, uint32);
		void KeyDown(const char *, int32);
		void MessageReceived(BMessage*);
	private:
};

#endif /* XCalcTextView_h */
