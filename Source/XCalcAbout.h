/**************************************************************************
 **
 ** XCalcAbout.h
 **
 ** The About window header
 **
 **************************************************************************/

#ifndef XCalcAbout_h
#define XCalcAbout_h

#include <View.h>
#include <Window.h>

class AboutView : public BView
{
	public:
		AboutView(BRect rec);
		void MessageReceived(BMessage* );
		void AttachedToWindow();
		void Draw(BRect);
	private:
		BButton *okButton;
		BButton *webButton;
		BButton *bwButton;
};

class AboutWindow : public BWindow
{
	public:
		AboutWindow(BRect frame);
	private:
};

#endif /* XCalcAbout_h */
