/**************************************************************************
 **
 ** XCalcView.cpp
 **
 ** The XCalc view
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

#include <MenuItem.h>

#include "XCalcWindow.h" 
#include "XCalcView.h"
#include "Preferences.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// The Preferences
extern Preferences Prefs;

/* 
 * View constructor : add the display and the keypad
 */

XCalcView :: XCalcView(BRect rec) :
	BView(rec, "XCalc View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	SetViewColor(216,216,216);
	BMenuItem *myMenuItem;

	// Show display	

	BFont *myFont= new BFont(be_plain_font); 
	myFont->SetSize(14.0); 

	myDisplay = new XCalcTextView(BRect(7, 30, 169, 46), "myDisplay", BRect(0, 0, 2048, 16), B_FOLLOW_ALL_SIDES, B_WILL_DRAW | B_NAVIGABLE);
	//140
	myDisplay->SetAlignment(B_ALIGN_RIGHT);
	myDisplay->SetFontAndColor(myFont);
	myScrollBar = new BScrollView("TextScroll", myDisplay, B_FOLLOW_ALL_SIDES, 0, false, false);
	AddChild(myScrollBar);

	// Keypad
	
	/* Bin, Tri, Bs4, Bs5, Bs6, Bs7, Oct, Bs9, Dec, Bs11, Duo, Bs13, Bs14, Bs15, Hex, Bs17, Bs18 */

	PopUpBase = new BPopUpMenu("Base");
	myMenuItem= new BMenuItem("Bin",new BMessage(POPUP_BIN));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Tri",new BMessage(POPUP_TRI));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs4",new BMessage(POPUP_BS4));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs5",new BMessage(POPUP_BS5));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs6",new BMessage(POPUP_BS6));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs7",new BMessage(POPUP_BS7));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Oct",new BMessage(POPUP_OCT));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs9",new BMessage(POPUP_BS9));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Dec",new BMessage(POPUP_DEC));
	myMenuItem->SetMarked(true);
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs11",new BMessage(POPUP_BS11));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Duo",new BMessage(POPUP_DUO));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs13",new BMessage(POPUP_BS13));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs14",new BMessage(POPUP_BS14));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs15",new BMessage(POPUP_BS15));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Hex",new BMessage(POPUP_HEX));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs17",new BMessage(POPUP_BS17));
	PopUpBase->AddItem(myMenuItem);
	myMenuItem= new BMenuItem("Bs18",new BMessage(POPUP_BS18));
	PopUpBase->AddItem(myMenuItem);
	
	/* Lg x, Ln x */
             ButtonLg = new BButton( BRect(123,142, 153,162), "ButtonLg", "lg x", new BMessage('blg'));
	ButtonLn = new BButton( BRect(91,142,121,162), "ButtonLn", "ln x", new BMessage('bln'));
	ButtonLb = new BButton( BRect(91,113,121,133), "ButtonLb", "lb x", new BMessage('blb'));
	ButtonLog = new BButton( BRect(123,113,153,133), "ButtonLog", "log", new BMessage('blo'));
	ButtonPow = new BButton( BRect(5,55,35,75), "ButtonPow", "x^y", new BMessage('bpow'));
	
	/* ^ functions and sqrt */
	ButtonRoot = new BButton( BRect(5,142,35,162), "ButtonRoot", "sqrt", new BMessage('brt'));
	AddChild(ButtonRoot);
	ButtonX1Y = new BButton( BRect(5,84,35,104), "ButtonX1Y", "^1/y", new BMessage('bx1y'));
	ButtonP2 = new BButton( BRect(5,171,35,191), "ButtonP2", "x^2", new BMessage('bp2'));
	AddChild(ButtonP2);
	// 123,84,153,104

	/* "PI" and "E" numbers */
	ButtonE1 = new BButton( BRect(123,171,153,191), "ButtonE1", "e", new BMessage('be1'));
	ButtonPi = new BButton( BRect(91,55,116,75), "ButtonPi", "pi", new BMessage('bpi'));
	AddChild(ButtonPi);
	ButtonExp = new BButton( BRect(91,171,121,191), "ButtonExp", "exp", new BMessage('bexp'));
	
	/* Hex buttons */	
	MenuFieldBase = new BMenuField( BRect(37,55,89,75), "Base menu", NULL, PopUpBase, true, B_FOLLOW_NONE);
	ButtonA = new BButton( BRect(37,171,62,191), "ButtonA", "A", new BMessage('ba'));	
	ButtonB = new BButton( BRect(64,171,89,191), "ButtonB", "B", new BMessage('bb'));
	ButtonC = new BButton( BRect(37,142,62,162), "ButtonC", "C", new BMessage('bc'));	
	ButtonD = new BButton( BRect(64,142,89,162), "ButtonD", "D", new BMessage('bd'));
	ButtonE = new BButton( BRect(37,113,62,133), "ButtonE", "E", new BMessage('be'));	
	ButtonF = new BButton( BRect(64,113,89,133), "ButtonF", "F", new BMessage('bf'));
	ButtonG = new BButton( BRect(37,84,62,104), "ButtonG", "G", new BMessage('bg'));
	ButtonH = new BButton( BRect(64,84,89,104), "ButtonH", "H", new BMessage('bh'));
	
	/* Standart buttons */
	Button0 = new BButton( BRect(37,171,89,191), "Button0", "0", new BMessage('b0'));	
	AddChild(Button0);
	Button1 = new BButton( BRect(37,142,62,162), "Button1", "1", new BMessage('b1'));	
	AddChild(Button1);
	Button2 = new BButton( BRect(64,142,89,162), "Button2", "2", new BMessage('b2'));	
	AddChild(Button2);
	Button3 = new BButton( BRect(91,142,116,162), "Button3", "3", new BMessage('b3'));	
	AddChild(Button3);
	Button4 = new BButton( BRect(37,113,62,133), "Button4", "4", new BMessage('b4'));	
	AddChild(Button4);
	Button5 = new BButton( BRect(64,113,89,133), "Button5", "5", new BMessage('b5'));	
	AddChild(Button5);
	Button6 = new BButton( BRect(91,113,116,133), "Button6", "6", new BMessage('b6'));	
	AddChild(Button6);
	Button7 = new BButton( BRect(37,84,62,104), "Button7", "7", new BMessage('b7'));	
	AddChild(Button7);
	Button8 = new BButton( BRect(64,84,89,104), "Button8", "8", new BMessage('b8'));	
	AddChild(Button8);
	Button9 = new BButton( BRect(91,84,116,104), "Button8", "9", new BMessage('b9'));	
	AddChild(Button9);
	ButtonAdd = new BButton( BRect(118,142,143,191), "ButtonAdd", "+", new BMessage('badd'));	
	AddChild(ButtonAdd);
	ButtonSub = new BButton( BRect(145,113,170,133), "ButtonSub", "-", new BMessage('bsub'));	
	AddChild(ButtonSub);
	ButtonDiv = new BButton( BRect(118,84,143,104), "ButtonDiv", "/", new BMessage('bdiv'));	
	AddChild(ButtonDiv);
	ButtonMult = new BButton( BRect(118,113,143,133), "ButtonMult", "*", new BMessage('bmul'));	
	AddChild(ButtonMult);
	ButtonRes = new BButton( BRect(145,142,170,191), "ButtonRes", "=", new BMessage('bres'));	
	AddChild(ButtonRes);
	ButtonDot = new BButton( BRect(91,171,116,191), "ButtonDot", ".", new BMessage('bdot'));	
	AddChild(ButtonDot);
	ButtonClear = new BButton( BRect(118,55,170,75), "ButtonClear", "CE", new BMessage('bcls'));	
	AddChild(ButtonClear);
	
	/* sin, cos, tan, arcsin, arccos, arctan */
	Button10X = new BButton( BRect(5,113,35,133), "Button10X", "10^", new BMessage('b10x'));
	ButtonCos = new BButton( BRect(155,113,185,133), "ButtonCos", "cos", new BMessage('bcos'));	
	ButtonCch = new BButton( BRect(91,84,121,104), "ButtonCch", "cch", new BMessage('bcch'));	
	ButtonAcos = new BButton( BRect(187,113,217,133), "ButtonAcos", "acos", new BMessage('baco'));		
	ButtonSin = new BButton( BRect(155,84,185,104), "ButtonSin", "sin", new BMessage('bsin'));
	ButtonAsin = new BButton( BRect(187,84,217,104), "ButtonAsin", "asin", new BMessage('basi'));
	ButtonSec = new BButton( BRect(155,55,185,75), "ButtonSec", "sec", new BMessage('bsec'));
	ButtonCsc = new BButton( BRect(91,55,121,75), "ButtonCsc", "csc", new BMessage('bcsc'));
	ButtonAcsc = new BButton( BRect(123,55,153,75), "ButtonAcsc", "acsc", new BMessage('bacs'));
	ButtonAcch = new BButton( BRect(123,84, 153,104), "ButtonAcch", "acch", new BMessage('bacc'));
	ButtonAsec = new BButton( BRect(187,55,217,75), "ButtonAsec", "asec", new BMessage('base'));
	ButtonSch = new BButton( BRect(219,55,249,75), "ButtonSch", "sch", new BMessage('bsch'));
	ButtonAsch = new BButton( BRect(251,55,281,75), "ButtonAsch", "asch", new BMessage('bah1'));
	ButtonAsnh = new BButton( BRect(251,84,281,104), "ButtonAsnh", "asnh", new BMessage('bah2'));
	ButtonAcsh = new BButton( BRect(251,113,281,133), "ButtonAcsh", "acsh", new BMessage('bah3'));
	ButtonAtgh = new BButton( BRect(251,142,281,162), "ButtonAtgh", "atgh", new BMessage('bah4'));
	ButtonAcgh = new BButton( BRect(251,171,281,191), "ButtonAcgh", "acgh", new BMessage('bah5'));
	ButtonSnh = new BButton( BRect(219,84,249,104), "ButtonSnh", "snh", new BMessage('bsnh'));
	ButtonCsh = new BButton( BRect(219,113,249,133), "ButtonCsh", "csh", new BMessage('bcsh'));
	ButtonTgh = new BButton( BRect(219,142,249,162), "ButtonTgh", "tgh", new BMessage('btgh'));
	ButtonTan = new BButton( BRect(155,142,185,162), "ButtonTan", "tan", new BMessage('btan'));	
	ButtonAtan = new BButton( BRect(187,142,217,162), "ButtonAtan", "atan", new BMessage('bata'));
	ButtonCtg = new BButton( BRect(155,171,185,191), "ButtonCtg", "ctg", new BMessage('bctg'));
	ButtonCgh = new BButton( BRect(219,171,249,191), "ButtonCgh", "cgh", new BMessage('bcgh'));
	ButtonActg = new BButton( BRect(187,171,217,191), "ButtonActg", "actg", new BMessage('bacg'));
	ButtonN = new BButton( BRect(5,171, 35,191), "ButtonN", "n!", new BMessage('bn'));
	Button10Y = new BButton( BRect(5,142, 35,162), "Button10Y", "/10^", new BMessage('b10y'));	
	
	/* Other buttons */
	ButtonLeftPar = new BButton( BRect(37,55,62,75), "ButtonLeftPar", "(", new BMessage('bltp'));	
	AddChild(ButtonLeftPar);
	ButtonRightPar = new BButton( BRect(64,55,89,75), "ButtonRightPar", ")", new BMessage('brtp'));	
	AddChild(ButtonRightPar);
	ButtonBack = new BButton( BRect(145,84,170,104), "ButtonBack", "<-", new BMessage('bbck'));	
	AddChild(ButtonBack);
	ButtonCurr = new BButton( BRect(5,84,35,104), "ButtonCurr", "curr", new BMessage('bcur'));	
	AddChild(ButtonCurr);
	ButtonEuro = new BButton( BRect(5,55,35,75), "ButtonEuro", "euro", new BMessage('beur'));	
	AddChild(ButtonEuro);	
	Button1X = new BButton( BRect(5,113,35,133), "Button1X", "1/x", new BMessage('b1x'));
	AddChild(Button1X);
	
	// Alloc memory for text manipulation
	myLine=(char *)malloc(1024*sizeof(char));

	ButtonA->SetEnabled(false);
	ButtonB->SetEnabled(false);
	ButtonC->SetEnabled(false);
	ButtonD->SetEnabled(false);
	ButtonE->SetEnabled(false);
	ButtonF->SetEnabled(false);
	ButtonG->SetEnabled(false);
	ButtonH->SetEnabled(false);
	
	myDisplay->MakeFocus();
}

/* 
 * View Messages : mouse click on BButtons to put the corresponding
 *				caracters on the display.
 *
 */

void XCalcView :: MessageReceived(BMessage* message)
{
	char myString[2];
	
	int32 start_cursor, finish_cursor;
	myDisplay->GetSelection(&start_cursor, &finish_cursor);

	switch(message->what)
	{
		/* 0 */
		case 'b0':
			myDisplay->KeyDown("0", (int32) 1);
			break;
		/* 1 */
		case 'b1':
			myDisplay->KeyDown("1", (int32) 1);
			break;
		/* 2 */
		case 'b2':
			myDisplay->KeyDown("2", (int32) 1);
			break;
		/* 3 */
		case 'b3':
			myDisplay->KeyDown("3", (int32) 1);
			break;
		/* 4 */
		case 'b4':
			myDisplay->KeyDown("4", (int32) 1);
			break;
		/* 5 */
		case 'b5':
			myDisplay->KeyDown("5", (int32) 1);
			break;
		/* 6 */
		case 'b6':
			myDisplay->KeyDown("6", (int32) 1);
			break;
		/* e */
		case 'be1':
		             myDisplay->KeyDown("ne", (int32) 2);
		             break;
		/* 7 */
		case 'b7':
			myDisplay->KeyDown("7", (int32) 1);
			break;
		/* 8 */
		case 'b8':
			myDisplay->KeyDown("8", (int32) 1);
			break;
		/* 9 */
		case 'b9':
			myDisplay->KeyDown("9", (int32) 1);
			break;
		/* A */
		case 'ba':
			myDisplay->KeyDown("A", (int32) 1);
			break;
		/* B */
		case 'bb':
			myDisplay->KeyDown("B", (int32) 1);
			break;
		/* C */
		case 'bc':
			myDisplay->KeyDown("C", (int32) 1);
			break;
		/* D */
		case 'bd':
			myDisplay->KeyDown("D", (int32) 1);
			break;
		/* E */
		case 'be':
			myDisplay->KeyDown("E", (int32) 1);
			break;
		/* F */
		case 'bf':
			myDisplay->KeyDown("F", (int32) 1);
			break;
		/* G */
		case 'bg':
		              myDisplay->KeyDown("G", (int32) 1);
		              break;
		/* H */
		case 'bh':
		              myDisplay->KeyDown("H", (int32) 1);
		              break;
		/* + */
		case 'badd':
			myDisplay->KeyDown("+", (int32) 1);
			break;
		/* - */
		case 'bsub':
			myDisplay->KeyDown("-", (int32) 1);
			break;
		/* * */
		case 'bmul':
			myDisplay->KeyDown("*", (int32) 1);
			break;
		/* / */
		case 'bdiv':
			myDisplay->KeyDown("/", (int32) 1);
			break;
		/* . */
		case 'bdot':
			myDisplay->KeyDown(".", (int32) 1);
			break;
		/* 1/x */
		case 'b1x':
		              myDisplay->KeyDown("1/", (int32) 2);
		              break;
		/* ( */
		case 'bltp':
			myDisplay->KeyDown("(", (int32) 1);
			break;
		/* ) */
		case 'brtp':
			myDisplay->KeyDown(")", (int32) 1);
			break;
		/* n! */
		case 'bn':
		             myDisplay->KeyDown("!", (int32) 1);
		             break;
		/* /10^ */
		case 'b10y':
		             myDisplay->KeyDown("#", (int32) 1);
		             break;
		/* cos */
		case 'bcos':
			myDisplay->KeyDown("cos ", (int32) 4);			
			break;
		/* sec */
		case 'bsec':
		             myDisplay->KeyDown("sec ", (int32) 4);
		             break;
		/* sech */
		case 'bsch':
		             myDisplay->KeyDown("sch ", (int32) 4);
		             break;
		/* sinh */
		case 'bsnh':
		             myDisplay->KeyDown("snh ", (int32) 4);
		             break;
		/* cosh */
		case 'bcsh':
		             myDisplay->KeyDown("csh ", (int32) 4);
		             break;
		/* tanh */
		case 'btgh':
		             myDisplay->KeyDown("tgh ", (int32) 4);
		             break;
		/* ctgh */
		case 'bcgh':
		              myDisplay->KeyDown("cgh ", (int32) 4);
		              break; 
	             /* cosec */
		case 'bcsc':
		              myDisplay->KeyDown("csc ", (int32) 4);
		              break;
		/* cosech */
		case 'bcch':
		              myDisplay->KeyDown("cch ", (int32) 4);
		              break;
		/* sin */
		case 'bsin':
			myDisplay->KeyDown("sin ", (int32) 4);			
			break;
		/* tan */
		case 'btan':
			myDisplay->KeyDown("tan ", (int32) 4);			
			break;
		/* ctg */
		case 'bctg':
		             myDisplay->KeyDown("ctg ", (int32) 4);
		             break;
		/* acos */
		case 'baco':
			myDisplay->KeyDown("acos ", (int32) 5);			
			break;
		/* acosh */
		case 'bah3':
		              myDisplay->KeyDown("acsh ", (int32) 5);
		              break;
		/* acosec */
		case 'bacs':
		              myDisplay->KeyDown("acsc ", (int32) 5);
		              break;
		/* acosech */
		case 'bacc':
		               myDisplay->KeyDown("acch ", (int32) 5);
		               break;
		/* asin */
		case 'basi':
			myDisplay->KeyDown("asin ", (int32) 5);			
			break;
		/* asinh */
		case 'bah2':
		             myDisplay->KeyDown("asnh ", (int32) 5);
		             break;
		/* asec */
		case 'base':
		             myDisplay->KeyDown("asec ", (int32) 5);
		             break;
		/* asech */
		case 'bah1':
		             myDisplay->KeyDown("asch ", (int32) 5);
		             break;
		/* atan */
		case 'bata':
			myDisplay->KeyDown("atan ", (int32) 5);			
			break;
		/* atanh */
		case 'bah4':
		             myDisplay->KeyDown("atgh ", (int32) 5);
		             break;
		/* actgh */
		case 'bah5':
		              myDisplay->KeyDown("acgh ", (int32) 5);
		              break;
	             /* actg */
	             case 'bacg':
	                           myDisplay->KeyDown("actg ", (int32) 5);
	                           break;
		/* x^y */
		case 'bpow':
			myDisplay->KeyDown("^", (int32) 1);
			break;
		/* x^1/y */
		case 'bx1y':
		             myDisplay->KeyDown("@", (int32) 1);
		             break;
		/* x^2 */
		case 'bp2':
			myDisplay->KeyDown("^2", (int32) 2);
			break;
		/* 1/x */
		case 'blg':
		              myDisplay->KeyDown("lg ", (int32) 3);
		              break;
		/* 10^x */
		case 'b10x':
		              myDisplay->KeyDown("10^", (int32) 3);
		              break;
		/* sqrt */
		case 'brt':
			myDisplay->KeyDown("sqrt ", (int32) 5);			
			break;
		/* exp */
		case 'bexp':
			myDisplay->KeyDown("exp ", (int32) 4);			
			break;
		/* ln */
		case 'bln':
			myDisplay->KeyDown("ln ", (int32) 3);			
			break;
		/* lb */
		case 'blb':
		             myDisplay->KeyDown("lb ", (int32) 3);
		             break;
		/* log */
		case 'blo':
		             myDisplay->KeyDown(" log ", (int32) 5);
		             break;
		/* pi */
		case 'bpi':
			myDisplay->KeyDown("pi", (int32) 2);			
			break;
		/* clear */
		case 'bcls':
			strcpy(myLine,"");
			myDisplay->SetText("");
			break;
		/* <- */
		case 'bbck':
			myString[0]=B_BACKSPACE;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			break;
		/* = */
		case 'bres':
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			break;

		/* euro */
		case 'beur':
			Prefs.SetEuroMode(P_EUR);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);
			Prefs.SetEuroMode(P_NOT);
			break;

		/* currency */
		case 'bcur':
			Prefs.SetEuroMode(P_CUR);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);
			Prefs.SetEuroMode(P_NOT);
			break;

		/* bin */
		case POPUP_BIN:
			Prefs.SetBaseOutput(P_BIN);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BIN);
			Button2->SetEnabled(false);
			Button3->SetEnabled(false);
			Button4->SetEnabled(false);
			Button5->SetEnabled(false);
			Button6->SetEnabled(false);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* trinary */
		case POPUP_TRI:
		              Prefs.SetBaseOutput(P_TRI);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_TRI);
			Button2->SetEnabled(true);
			Button3->SetEnabled(false);
			Button4->SetEnabled(false);
			Button5->SetEnabled(false);
			Button6->SetEnabled(false);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 4 */
		              case POPUP_BS4:
		              Prefs.SetBaseOutput(P_BS4);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS4);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(false);
			Button5->SetEnabled(false);
			Button6->SetEnabled(false);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 5 */
		              case POPUP_BS5:
		              Prefs.SetBaseOutput(P_BS5);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS5);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(false);
			Button6->SetEnabled(false);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 6 */
		              case POPUP_BS6:
		              Prefs.SetBaseOutput(P_BS6);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS6);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(false);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 7 */
		              case POPUP_BS7:
		              Prefs.SetBaseOutput(P_BS7);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS7);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(false);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* oct */
		case POPUP_OCT:
			Prefs.SetBaseOutput(P_OCT);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_OCT);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(false);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 9 */
		case POPUP_BS9:
			Prefs.SetBaseOutput(P_BS9);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS9);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(false);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* dec */
		case POPUP_DEC:
			Prefs.SetBaseOutput(P_DEC);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_DEC);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(false);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 11 */
		case POPUP_BS11:
			Prefs.SetBaseOutput(P_BS11);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS11);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(false);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* duo */
		case POPUP_DUO:
			Prefs.SetBaseOutput(P_DUO);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_DUO);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(false);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 13 */
		case POPUP_BS13:
			Prefs.SetBaseOutput(P_BS13);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS13);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(false);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 14 */
		case POPUP_BS14:
			Prefs.SetBaseOutput(P_BS14);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS14);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(true);
			ButtonE->SetEnabled(false);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 15 */
		case POPUP_BS15:
			Prefs.SetBaseOutput(P_BS15);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS15);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(true);
			ButtonE->SetEnabled(true);
			ButtonF->SetEnabled(false);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* hex */
		case POPUP_HEX:
			Prefs.SetBaseOutput(P_HEX);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_HEX);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(true);
			ButtonE->SetEnabled(true);
			ButtonF->SetEnabled(true);
			ButtonG->SetEnabled(false);
			ButtonH->SetEnabled(false);
			break;
		/* base 17 */
		case POPUP_BS17:
			Prefs.SetBaseOutput(P_BS17);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS17);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(true);
			ButtonE->SetEnabled(true);
			ButtonF->SetEnabled(true);
			ButtonG->SetEnabled(true);
			ButtonH->SetEnabled(false);
			break;
		/* base 18 */
		case POPUP_BS18:
			Prefs.SetBaseOutput(P_BS18);
			myString[0]=B_ENTER;
			myString[1]='\0';
			myDisplay->KeyDown(myString, (int32) 1);			
			Prefs.SetBase(P_BS18);
			Button2->SetEnabled(true);
			Button3->SetEnabled(true);
			Button4->SetEnabled(true);
			Button5->SetEnabled(true);
			Button6->SetEnabled(true);
			Button7->SetEnabled(true);
			Button8->SetEnabled(true);
			Button9->SetEnabled(true);
			ButtonA->SetEnabled(true);
			ButtonB->SetEnabled(true);
			ButtonC->SetEnabled(true);
			ButtonD->SetEnabled(true);
			ButtonE->SetEnabled(true);
			ButtonF->SetEnabled(true);
			ButtonG->SetEnabled(true);
			ButtonH->SetEnabled(true);
			break;

		/* Cut/Copy/Paste */
		case MENU_EDIT_CUT:
		case MENU_EDIT_COPY:
		case MENU_EDIT_PASTE:
			myDisplay->MessageReceived(message);
			break;
	}

}

/* 
 * View Attached To Window : to catch the button clicks in the view
 */

void XCalcView :: AttachedToWindow()
{
	Button10X->SetTarget(this);
	ButtonP2->SetTarget(this);
	ButtonE1->SetTarget(this);
	ButtonN->SetTarget(this);
	Button10Y->SetTarget(this);
	ButtonLog->SetTarget(this);
	ButtonLg->SetTarget(this);
	ButtonX1Y->SetTarget(this);
	ButtonRoot->SetTarget(this);
	ButtonLeftPar->SetTarget(this);
	ButtonRightPar->SetTarget(this);
	ButtonDiv->SetTarget(this);
	ButtonMult->SetTarget(this);
	ButtonSub->SetTarget(this);
	ButtonExp->SetTarget(this);
	ButtonLn->SetTarget(this);
	ButtonLb->SetTarget(this);
	ButtonE->SetTarget(this);
	ButtonF->SetTarget(this);
	ButtonG->SetTarget(this);
	ButtonH->SetTarget(this);
	ButtonBack->SetTarget(this);
	Button7->SetTarget(this);
	Button8->SetTarget(this);
	Button9->SetTarget(this);
	Button1X->SetTarget(this);
	ButtonAdd->SetTarget(this);
	ButtonCos->SetTarget(this);
	ButtonCsh->SetTarget(this);
	ButtonCch->SetTarget(this);
	ButtonAcch->SetTarget(this);
	ButtonAcos->SetTarget(this);
	ButtonAsnh->SetTarget(this);
	ButtonAtgh->SetTarget(this);
	ButtonC->SetTarget(this);
	ButtonD->SetTarget(this);
	ButtonEuro->SetTarget(this);
	ButtonP2->SetTarget(this);
	Button4->SetTarget(this);
	Button5->SetTarget(this);
	Button6->SetTarget(this);
	ButtonSec->SetTarget(this);
	ButtonSch->SetTarget(this);
	ButtonSnh->SetTarget(this);
	ButtonCsc->SetTarget(this);
	ButtonAcsc->SetTarget(this);
	ButtonAsec->SetTarget(this);
	ButtonAsch->SetTarget(this);
	ButtonAcsh->SetTarget(this);
	ButtonSin->SetTarget(this);
	ButtonAsin->SetTarget(this);
	ButtonA->SetTarget(this);
	ButtonB->SetTarget(this);
	ButtonCurr->SetTarget(this);
	Button1->SetTarget(this);
	Button2->SetTarget(this);
	Button3->SetTarget(this);
	ButtonRes->SetTarget(this);
	ButtonTan->SetTarget(this);
	ButtonTgh->SetTarget(this);
	ButtonAtan->SetTarget(this);
	ButtonCtg->SetTarget(this);
	ButtonCgh->SetTarget(this);
	ButtonActg->SetTarget(this);
	ButtonAcgh->SetTarget(this);
	ButtonPi->SetTarget(this);
	ButtonPow->SetTarget(this);
	ButtonClear->SetTarget(this);
	Button0->SetTarget(this);
	ButtonDot->SetTarget(this);

	myDisplay->MakeFocus();
}

/* 
 * View More
 */

void XCalcView :: ViewMore()
{
	// Add buttons
	AddChild(ButtonLg);
	AddChild(ButtonLog);
	AddChild(ButtonX1Y);
	AddChild(ButtonE1);
	AddChild(ButtonN);
	AddChild(Button10Y);
	AddChild(ButtonExp);
	AddChild(ButtonLn);
	AddChild(ButtonLb);
	AddChild(ButtonCos);
	AddChild(ButtonCsh);
	AddChild(ButtonCch);
	AddChild(ButtonAcos);
	AddChild(ButtonSec);
	AddChild(ButtonSch);
	AddChild(ButtonSnh);
	AddChild(ButtonCsc);
	AddChild(ButtonAcsc);
	AddChild(ButtonAsec);
	AddChild(ButtonAsch);
	AddChild(ButtonAsnh);
	AddChild(ButtonAcsh);
	AddChild(ButtonAcch);
	AddChild(ButtonAtgh);
	AddChild(ButtonAcgh);
	AddChild(ButtonSin);
	AddChild(ButtonAsin);
	AddChild(ButtonTan);
	AddChild(ButtonTgh);
	AddChild(ButtonAtan);
	AddChild(ButtonCtg);
	AddChild(ButtonCgh);
	AddChild(ButtonActg);
	AddChild(ButtonA);
	AddChild(ButtonB);
	AddChild(ButtonC);
	AddChild(ButtonD);
	AddChild(ButtonE);
	AddChild(ButtonF);
	AddChild(ButtonG);
	AddChild(ButtonH);
	AddChild(Button10X);
	AddChild(ButtonPow);
	AddChild(MenuFieldBase);

	// Move others
	ButtonP2->MoveBy(278,0);
	ButtonRoot->MoveBy(278,0);
	ButtonPi->MoveBy(278,0);
	ButtonLeftPar->MoveBy(278,0);
	ButtonRightPar->MoveBy(278,0);
	ButtonDiv->MoveBy(278,0);
	ButtonMult->MoveBy(278,0);
	ButtonSub->MoveBy(278,0);

	ButtonBack->MoveBy(278,0);
	Button7->MoveBy(278,0);
	Button8->MoveBy(278,0);
	Button9->MoveBy(278,0);

	ButtonEuro->MoveBy(278,0);
	Button4->MoveBy(278,0);
	Button5->MoveBy(278,0);
	Button6->MoveBy(278,0);
	ButtonAdd->MoveBy(278,0);
	Button1X->MoveBy(278,0);

	ButtonCurr->MoveBy(278,0);
	Button1->MoveBy(278,0);
	Button2->MoveBy(278,0);
	Button3->MoveBy(278,0);
	ButtonRes->MoveBy(278,0);

	ButtonClear->MoveBy(278,0);
	Button0->MoveBy(278,0);
	ButtonDot->MoveBy(278,0);
}

/* 
 * View Less
 */

void XCalcView :: ViewLess()
{
	// Remove buttons
	RemoveChild(ButtonLg);
	RemoveChild(ButtonLog);
	RemoveChild(ButtonX1Y);
	RemoveChild(ButtonE1);
	RemoveChild(ButtonN);
	RemoveChild(Button10Y);
	RemoveChild(ButtonExp);
	RemoveChild(ButtonLn);
	RemoveChild(ButtonLb);
	RemoveChild(ButtonCos);
	RemoveChild(ButtonCsh);
	RemoveChild(ButtonCch);
	RemoveChild(ButtonAcos);
	RemoveChild(ButtonSec);
	RemoveChild(ButtonSch);
	RemoveChild(ButtonSnh);
	RemoveChild(ButtonCsc);
	RemoveChild(ButtonAcsc);
	RemoveChild(ButtonAsec);
	RemoveChild(ButtonAsch);
	RemoveChild(ButtonAcch);
	RemoveChild(ButtonAcsh);
	RemoveChild(ButtonAsnh);
	RemoveChild(ButtonAtgh);
	RemoveChild(ButtonAcgh);
	RemoveChild(ButtonSin);
	RemoveChild(ButtonAsin);
	RemoveChild(ButtonTan);
	RemoveChild(ButtonTgh);
	RemoveChild(ButtonAtan);
	RemoveChild(ButtonCtg);
	RemoveChild(ButtonCgh);
	RemoveChild(ButtonActg);
	RemoveChild(ButtonA);
	RemoveChild(ButtonB);
	RemoveChild(ButtonC);
	RemoveChild(ButtonD);
	RemoveChild(ButtonE);
	RemoveChild(ButtonF);
	RemoveChild(ButtonG);
	RemoveChild(ButtonH);
	RemoveChild(Button10X);
	RemoveChild(ButtonPow);
	RemoveChild(MenuFieldBase);

	// Move others
	ButtonLeftPar->MoveBy(-278,0);
	ButtonRightPar->MoveBy(-278,0);
	ButtonDiv->MoveBy(-278,0);
	ButtonMult->MoveBy(-278,0);
             ButtonP2->MoveBy(-278,0);
             ButtonRoot->MoveBy(-278,0);
             ButtonPi->MoveBy(-278,0);
             ButtonSub->MoveBy(-278,0);

	ButtonBack->MoveBy(-278,0);
	Button7->MoveBy(-278,0);
	Button8->MoveBy(-278,0);
	Button9->MoveBy(-278,0);

	ButtonEuro->MoveBy(-278,0);
	Button4->MoveBy(-278,0);
	Button5->MoveBy(-278,0);
	Button6->MoveBy(-278,0);
	ButtonAdd->MoveBy(-278,0);
	Button1X->MoveBy(-278,0);

	ButtonCurr->MoveBy(-278,0);
	Button1->MoveBy(-278,0);
	Button2->MoveBy(-278,0);
	Button3->MoveBy(-278,0);
	ButtonRes->MoveBy(-278,0);

	ButtonClear->MoveBy(-278,0);
	Button0->MoveBy(-278,0);
	ButtonDot->MoveBy(-278,0);
}
