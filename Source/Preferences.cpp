/**************************************************************************
 **
 ** Preferences.cpp
 **
 ** The Preferences
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

#include <stdio.h> 
#include "Preferences.h"

/* 
 * Preferences constructor
 */

Preferences :: Preferences()
{
	parser_base=P_DEC;
	parser_base_output=P_DEC;
	parser_euro_mode=P_NOT;
}

/* 
 * Set default value for Preferences
 */

void Preferences :: SetDefaultPrefs()
{
	parser_precision=14;
	parser_angle=P_DEG;
	parser_euro=6.5596;
	xcalc_view=X_MORE;
	xcalc_top=100.0;
	xcalc_left=100.0;
}

/* 
 * Load Preferences
 */

bool Preferences :: LoadPrefs()
{
	FILE *f;
	if ((f=fopen("/boot/home/config/settings/xcalc_prefs","r"))!=NULL)
	{
		fscanf(f,"%d %d %lf %d %f %f",&parser_precision,&parser_angle,&parser_euro, &xcalc_view, &xcalc_top, &xcalc_left);
		fclose(f);
		return true;
	}
	else
	{
	  return false;
	}
}

/* 
 * Save Preferences
 */

void Preferences :: SavePrefs()
{
	FILE *f;
	if ((f=fopen("/boot/home/config/settings/xcalc_prefs","w"))!=NULL)
	{
		fprintf(f,"%d %d %1f %d %f %f",parser_precision,parser_angle,parser_euro,xcalc_view, xcalc_top, xcalc_left);
		fclose(f);
	}
}

/* 
 * Set Base
 */

void Preferences :: SetBase(int mybase)
{
	parser_base=mybase;
}

/* 
 * Get Base
 */

int Preferences :: GetBase()
{
	return(parser_base);
}

/* 
 * Set Base Output
 */

void Preferences :: SetBaseOutput(int mybase)
{
	parser_base_output=mybase;
}

/* 
 * Get Base Output
 */

int Preferences :: GetBaseOutput()
{
	return(parser_base_output);
}

/* 
 * Set Precision
 */

void Preferences :: SetPrecision(int myprecision)
{
	parser_precision=myprecision;
}

/* 
 * Get Precision
 */

int Preferences :: GetPrecision()
{
	return(parser_precision);
}

/* 
 * Set Angle
 */

void Preferences :: SetAngle(int myangle)
{
	parser_angle=myangle;
}

/* 
 * Get Angle
 */

int Preferences :: GetAngle()
{
	return (parser_angle);
}

/* 
 * Set Euro Value
 */

void Preferences :: SetEuro(double myvalue)
{
	parser_euro=myvalue;
}

/* 
 * Get Euro Value
 */

double Preferences :: GetEuro()
{
	return(parser_euro);
}

/* 
 * Set Euro Mode
 */

void Preferences :: SetEuroMode(int mymode)
{
	parser_euro_mode=mymode;
}

/* 
 * Get Euro Mode
 */

int Preferences :: GetEuroMode()
{
	return (parser_euro_mode);
}

/* 
 * Set View Mode
 */

void Preferences :: SetView(int mymode)
{
	xcalc_view=mymode;
}

/* 
 * Get View Mode
 */

int Preferences :: GetView()
{
	return(xcalc_view);
}

/* 
 * Set Top
 */

void Preferences :: SetTop(float myvalue)
{
	xcalc_top=myvalue;
}

/* 
 * Get Top
 */

float Preferences :: GetTop()
{
	return(xcalc_top);
}

/* 
 * Set Left
 */

void Preferences :: SetLeft(float myvalue)
{
	xcalc_left=myvalue;
}

/* 
 * Get Left
 */

float Preferences :: GetLeft()
{
	return(xcalc_left);
}
