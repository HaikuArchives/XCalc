/**************************************************************************
 **
 ** XCalcTextView.cpp
 **
 ** The XCalcTextView for the display
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

#include <Beep.h>
#include <stdlib.h>
#include <Clipboard.h>
#include "XCalcWindow.h"
#include "XCalcTextView.h"
#include "Parser.h"
#include "Utility.h"
#include <string.h>
/* 
 * XCalcTextView :
 */

XCalcTextView :: XCalcTextView(BRect frame, const char *name, BRect textRec, uint32 resizingMode, uint32 flags) :
 BTextView(frame, name, textRec, resizingMode, flags)
{
	SetDoesUndo(true);
}

/* 
 * TextView KeyDown : catch keyboard
 */

void XCalcTextView :: KeyDown(const char *bytes, int32 numBytes)
{
	int pos;
	char *com;

	char *myLine;
	char *myTemp;
	int myEnd;
	
	myLine=(char *)malloc(1024*sizeof(char));
	myTemp=(char *)malloc(1024*sizeof(char));
	
		switch (bytes[0])
		{
			// ignore these keys
			case B_UP_ARROW:
			case B_DOWN_ARROW:
			case B_HOME:
			case B_END:
			case B_PAGE_UP:
			case B_PAGE_DOWN:
			case B_INSERT:
			case B_TAB:
			case B_FUNCTION_KEY:
			case B_ESCAPE:
				break;
	
			// get the result of the expression
			case B_ENTER:
			case '=':
				// expression is ok
			    strcpy(myLine,this->Text());
			    
			    if (evaluate(myTemp, myLine, &pos, &com)==TRUE)
			    {
			    	strcpy(myLine,myTemp);
			    	removeLastZeros(myLine);
					this->SetText(myLine);
					myEnd=strlen(myLine);
					Select(myEnd, myEnd);
				}
				// wrong expression : beep !
				else
				{
					Select(pos, pos);
					beep();
				}
				break;
				
			// type caracters on the display
			default:
				BTextView::KeyDown(bytes, numBytes);
				break;
		}

}

/* 
 * TextView Messages
 */

void XCalcTextView :: MessageReceived(BMessage* message)
{
	switch(message->what)
	{
		// Cut/Copy/Paste
		case MENU_EDIT_CUT:
			Cut(be_clipboard );
			break;
		case MENU_EDIT_COPY:
			Copy(be_clipboard );
			break;
		case MENU_EDIT_PASTE:
			Paste(be_clipboard );
			break;
		default:
			BTextView::MessageReceived(message);
			break;
	}
}

