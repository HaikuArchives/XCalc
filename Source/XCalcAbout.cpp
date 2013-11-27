/**************************************************************************
 **
 ** XCalcAbout.cpp
 **
 ** The About window with the application's icon
 **
 **************************************************************************
 **
 ** XCalc About was rewritten by Nikolaev Ruslan (nruslan@hotbox.ru)
 **
 **************************************************************************/

#include <Application.h>
#include <Button.h>
#include <File.h>
#include <AppFileInfo.h>
#include <Bitmap.h>
#include <Roster.h>
#include "XCalcAbout.h"
#include "Defines.h"

// About Window constructor

AboutWindow :: AboutWindow(BRect frame) :
	BWindow(frame, "About...", B_MODAL_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL, B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	AboutView *myView = new AboutView(Bounds());
	AddChild(myView);
}

AboutView :: AboutView(BRect rect) :
	BView(rect, "About View", B_FOLLOW_ALL_SIDES, B_WILL_DRAW)
{
	SetViewColor(216, 216, 216);

	webButton = new BButton(BRect(40, 175, 100, 110), "Web", LANG_ABOUT_WEB, new BMessage('wbs'));
	AddChild(webButton);
	bwButton = new BButton(BRect(110, 175, 170, 110), "OtherWeb", LANG_ABOUT_BEBITS, new BMessage('bbw'));
	AddChild(bwButton);
	okButton = new BButton(BRect(180, 175, 250, 110), "Validate", LANG_ABOUT_OK, new BMessage('vld'));
	AddChild(okButton);
	okButton->MakeDefault(true);
}

// okButton, webButton

void AboutView :: AttachedToWindow()
{
	okButton->SetTarget(this);
	webButton->SetTarget(this);
	bwButton->SetTarget(this);
}

void AboutView :: MessageReceived(BMessage *message)
{
	char *urlw = "http://nruslan.hotbox.ru/projects/xcalc/index.html";
	char *urlb = "http://www.bebits.com/app/2760";
	
	switch(message->what)
	{
		// BeBits Button
		case 'bbw':
        be_roster->Launch("text/html", 1, &urlb);
		break;
		// All Right Button
		case 'vld':
		(Window())->Quit();
		break;
		// Website Button
		case 'wbs':
		be_roster->Launch("text/html", 1, &urlw);
		break;
	}
}

// About Icon
void AboutView :: Draw(BRect frame)
{
	DrawString("XCalc " XCALC_VERSION " " LANG_FOR " BeOS", BPoint(50,20));
	DrawString("Copyright © 1999 Nikolas Mougel", BPoint(50,50));
	DrawString("E-mail: mougel@netcourrier.com", BPoint(50,65));
	DrawString("Copyright © 2001-2002 Nikolaev Ruslan", BPoint(50,95));
	DrawString("E-mail: nruslan@hotbox.ru", BPoint(50,110));
	DrawString(LANG_ABOUT_A, BPoint(50,140));
	DrawString(LANG_ABOUT_B, BPoint(50,155));
	
	BFile file;
	BAppFileInfo fileinfo;
	app_info info;

	SetHighColor(152,152,152);
	FillRect(BRect(0,0,30,320));
	
	BBitmap icon(BRect(0,0,31,31 ), B_CMAP8);
	be_app->GetAppInfo(&info);
	file.SetTo(&(info.ref), B_READ_ONLY);
	fileinfo.SetTo(&file);
	fileinfo.GetIcon(&icon, B_LARGE_ICON);
	SetLowColor(ViewColor());
	SetDrawingMode(B_OP_OVER);
	DrawBitmap(&icon, BPoint(5,10));
}
