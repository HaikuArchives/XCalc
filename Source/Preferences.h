/**************************************************************************
 **
 ** Preferences.h
 **
 ** The Preferences header
 **
 **************************************************************************/

#ifndef Preferences_h
#define Preferences_h

/* Angle
 */

#define P_RAD	1
#define P_DEG	2

/* Base
 */

#define P_BIN	 2
#define P_TRI  3
#define P_BS4 4
#define P_BS5 5
#define P_BS6 6
#define P_BS7 7
#define P_OCT	8
#define P_BS9             9
#define P_DEC	10
#define P_BS11           11
#define P_DUO            12
#define P_BS13           13
#define P_BS14           14
#define P_BS15           15
#define P_HEX	16
#define P_BS17           17
#define P_BS18           18

/* Euro
 */
 
#define P_NOT	1
#define P_EUR	2
#define P_CUR	3

/* View Less / More
 */

#define X_LESS	1
#define X_MORE	2


/* 
 * The Preferences class
 */

class Preferences
{
	public:
		Preferences();
		void SetDefaultPrefs();
		bool LoadPrefs();
		void SavePrefs();
		
		void SetBase(int);
		int GetBase();
		void SetBaseOutput(int);
		int GetBaseOutput();
		void SetPrecision(int);
		int GetPrecision();
		void SetAngle(int);
		int GetAngle();
		
		void SetEuro(double);
		double GetEuro();
		void SetEuroMode(int);
		int GetEuroMode();

		void SetView(int);
		int GetView();		
		void SetTop(float);
		float GetTop();
		void SetLeft(float);
		float GetLeft();

	private:
		int parser_base;
		int parser_base_output;
		int parser_precision;
		int parser_angle;
		double parser_euro;
		int parser_euro_mode;
		int xcalc_view;
		float xcalc_top;
		float xcalc_left;
};

#endif /* Preferences_h */
