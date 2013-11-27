/**************************************************************************
 **
 ** XCalcPrefs.cpp
 **
 ** The Preferences window
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
#include <Button.h>

#include <stdio.h>
#include <stdlib.h>

#include "XCalcPrefs.h"
#include "Utility.h"
#include "Preferences.h"
#include "Defines.h"

extern Preferences Prefs;

/* 
 * Preferences window constructor : add a BView
 */

PrefsWindow :: PrefsWindow(BRect frame) :
	BWindow(frame, LANG_PREFS, B_FLOATING_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	myView = new PrefsView(Bounds());
	AddChild(myView);
}

/* 
 * Preferences view constructor
 */

PrefsView :: PrefsView(BRect rec) :
	BView(rec, "Preferences View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	SetViewColor(216,216,216);
	char sEuro[30], sPrecision[50];
	float position;
	
	// Default view
	PopUpDefaultView = new BPopUpMenu("View");
	myMenuLessMore= new BMenuItem(LANG_LESS,new BMessage(POPUP_LESS));
	if (Prefs.GetView()==X_LESS)
	myMenuLessMore->SetMarked(true);
	PopUpDefaultView->AddItem(myMenuLessMore);
	myMenuLessMore= new BMenuItem(LANG_MORE,new BMessage(POPUP_MORE));
	if (Prefs.GetView()==X_MORE)
	myMenuLessMore->SetMarked(true);
	PopUpDefaultView->AddItem(myMenuLessMore);
	
	MenuFieldDefaultView = new BMenuField( BRect(10,10,220,30), "Default view menu", LANG_DEFAULT_VIEW, PopUpDefaultView, true, B_FOLLOW_RIGHT | B_FOLLOW_TOP);
	AddChild(MenuFieldDefaultView);

	// Degree/Radian
	PopUpAngle = new BPopUpMenu("Angle");
	myMenuItem= new BMenuItem(LANG_DEG,new BMessage(POPUP_DEG));
	if (Prefs.GetAngle()==P_DEG)
		myMenuItem->SetMarked(true);
	PopUpAngle->AddItem(myMenuItem);
	myMenuItem= new BMenuItem(LANG_RAD,new BMessage(POPUP_RAD));
	if (Prefs.GetAngle()==P_RAD)
		myMenuItem->SetMarked(true);
	PopUpAngle->AddItem(myMenuItem);

	MenuFieldAngle = new BMenuField( BRect(10,40,220,60), "Angle menu", LANG_ANGLE_IN, PopUpAngle, true, B_FOLLOW_RIGHT | B_FOLLOW_TOP);
	AddChild(MenuFieldAngle);
	
	// Euro
	sprintf(sEuro,"%1f",Prefs.GetEuro());
	removeLastZeros(sEuro);
	TextControlEuro = new BTextControl(BRect(10,74,220,94), "Euro control", LANG_EURO, sEuro, new BMessage('eur'));
	AddChild(TextControlEuro);

	// Precision for the display
	sprintf(sPrecision,LANG_DEC_PREC_DISPLAY" %d", Prefs.GetPrecision());
	precSlider = new BSlider(BRect (10,105,220,125), "Precision Slider", sPrecision, new BMessage('psl'), (int32) 0, (int32) 16);
	precSlider->SetLimitLabels("0", "16");
	precSlider->SetHashMarks(B_HASH_MARKS_BOTTOM);
	precSlider->SetHashMarkCount(17);
	if (Prefs.GetPrecision()==0.0)
		position=0.0;
	else
		position=Prefs.GetPrecision()/16.0;
	precSlider->SetPosition(position);
	AddChild(precSlider);
	
	// Cancel button
	cancelButton=new BButton(BRect(35,170,105,190), "Unvalidate", LANG_CANCEL_BUTTON, new BMessage('pca'));
	AddChild(cancelButton);

	// Ok button
	okButton=new BButton(BRect(125,170,195,190), "Validate", LANG_OK_BUTTON, new BMessage('pok'));
	AddChild(okButton);

}

/* 
 * Preferences view : to catch the BButton click in this view
 */

void PrefsView :: AttachedToWindow()
{
	precSlider->SetTarget(this);
	okButton->SetTarget(this);
	cancelButton->SetTarget(this);
}

/* 
 * Preferences view : catch the BButtton message
 */

void PrefsView :: MessageReceived(BMessage* message)
{
	int precision;
	char sPrecision[50];

	switch(message->what)
	{
		/* Precision */
		case 'psl':
			precision=(int) ((precSlider->Position())*16);
			sprintf(sPrecision,LANG_DEC_PREC_DISPLAY" %d", precision);
			precSlider->SetLabel(sPrecision);
			break;
		/* The user wants to save the preferences */
		case 'pok':
			if (myMenuLessMore->IsMarked())
				Prefs.SetView(X_MORE);
			else
				Prefs.SetView(X_LESS);
			Prefs.SetPrecision((int) ((precSlider->Position())*16));
			if (myMenuItem->IsMarked())
				Prefs.SetAngle(P_RAD);
			else
				Prefs.SetAngle(P_DEG);
			Prefs.SetEuro(atof(TextControlEuro->Text()));
			(Window())->Quit();
			break;
		/* The user wants to ignore the changes */
		case 'pca':
			(Window())->Quit();
			break;
	}
}
