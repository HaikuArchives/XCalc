/**************************************************************************
 **
 ** XCalcPrefs.h
 **
 ** The Preferences window header
 **
 **************************************************************************/

#ifndef XCalcPrefs_h
#define XCalcPrefs_h

#include <Window.h>
#include <View.h>
#include <Slider.h>
#include <MenuField.h>
#include <PopUpMenu.h>
#include <MenuItem.h>
#include <TextControl.h>

#define POPUP_DEG	11
#define POPUP_RAD	12

#define POPUP_LESS 	21
#define POPUP_MORE	22

class PrefsView : public BView
{
	public:
		PrefsView(BRect rec);
		void MessageReceived(BMessage* );
		void AttachedToWindow();
	private:
		BButton *okButton,
				*cancelButton;
		BMenuField *MenuFieldDefaultView;
		BPopUpMenu *PopUpDefaultView;
		BSlider *precSlider;
		BMenuField *MenuFieldAngle;
		BPopUpMenu *PopUpAngle;
		BMenuItem *myMenuLessMore;
		BMenuItem *myMenuItem;
		BTextControl *TextControlEuro;
};

class PrefsWindow : public BWindow
{
	public:
		PrefsWindow(BRect frame);
	private:
		PrefsView *myView;
};

#endif /* XCalcPrefs_h */
