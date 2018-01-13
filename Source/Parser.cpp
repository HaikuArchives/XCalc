/**************************************************************************
 **
 ** Parser.cpp
 **
 ** A grammar for arithmetic expressions
 **
 ** +, -, *, /, cos, sin, tan, ^y, ^2, sqrt, (), -, integer, real
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
 **************************************************************************
 **
 ** The grammar used in the parser : 
 **
 ** 	TC  -> H S2 S
 **		S	-> +H S2 S | -H S2 S | #
 **		S2	-> *H S2 | / H S2 | #
 **		
 **		H	-> +H | -H | I
 **		I	-> cos H | sin H | tan H | acos H | asin H | atan H |
 **				sqrt H | exp H | ln H | lg H | J P
 **		J	-> ( TC ) | L
 **		P	-> ^H | #
 **		L	-> dM | d.C | bB | oO | xX | pi | e | M | .C | B | O | X 
 **
 **		M	-> D D1 N
 **		D	-> 0|1|2|3|4|5|6|7|8|9
 **		D1	-> D D1 | #
 **		N	-> .D1 | #
 **		C	-> DD1
 **
 **		B	-> B1 B2
 **		B1	-> 0|1
 **		B2	-> B1 B2 | #
 **
 **		0	-> O1 O2
 **		O1	-> 0|1|2|3|4|5|6|7
 **		O2	-> O1 O2 | #
 **
 **		X	-> X1 X2
 **		X1	-> 0|1|2|3|4|5|6|7|8|9|A|B|C|D|E|F
 **		X2	-> X1 X2 | #
 **
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Parser.h"
#include "Preferences.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* Error
 */

#define N       7
#define OK      0
#define SYNTAX  1
#define DIV_Z   2
#define ROOT_N  3
#define LN_N	4
#define RANGE	5
#define X1_ER     6
#define PI M_PI
/* The Preferences
 */

Preferences Prefs;

/* Fonctions' declarations
 */

int evaluate(char *result, char *string, int *pos, char **com);
int is_a_TC(double *x, char **p);
int is_a_S(double *x, char **p);
int is_a_S2(double *x, char **p);

int is_a_H(double *x, char **p);
int is_a_I(double *x, char **p);
int is_a_J(double *x, char **p);
int is_a_P(double *x, char **p);
int is_a_L(double *x, char **p);

int is_a_M(double *x, char **p);
int is_a_D(double *x, char **p);
int is_a_D1(double *x, char **p);
int is_a_N(double *x, char **p);
int is_a_C(double *x, char **p);

int is_a_B(double *x, char **p);
int is_a_B1(double *x, char **p);
int is_a_B2(double *x, char **p);

int is_a_Z(double *x, char **p);
int is_a_Z1(double *x, char **p);
int is_a_Z2(double *x, char **p);

int is_a_W(double *x, char **p);
int is_a_W1(double *x, char **p);
int is_a_W2(double *x, char **p);

int is_a_Y(double *x, char **p);
int is_a_Y1(double *x, char **p);
int is_a_Y2(double *x, char **p);

int is_a_V(double *x, char **p);
int is_a_V1(double *x, char **p);
int is_a_V2(double *x, char **p);

int is_a_U(double *x, char **p);
int is_a_U1(double *x, char **p);
int is_a_U2(double *x, char **p);

int is_a_O(double *x, char **p);
int is_a_O1(double *x, char **p);
int is_a_O2(double *x, char **p);

int is_a_T(double *x, char **p);
int is_a_T1(double *x, char **p);
int is_a_T2(double *x, char **p);

int is_a_R(double *x, char **p);
int is_a_R1(double *x, char **p);
int is_a_R2(double *x, char **p);

int is_a_Q(double *x, char **p);
int is_a_Q1(double *x, char **p);
int is_a_Q2(double *x, char **p);

int is_a_K(double *x, char **p);
int is_a_K1(double *x, char **p);
int is_a_K2(double *x, char **p);

int is_a_G(double *x, char **p);
int is_a_G1(double *x, char **p);
int is_a_G2(double *x, char **p);

int is_a_F(double *x, char **p);
int is_a_F1(double *x, char **p);
int is_a_F2(double *x, char **p);

int is_a_X(double *x, char **p);
int is_a_X1(double *x, char **p);
int is_a_X2(double *x, char **p);

int is_a_E(double *x, char **p);
int is_a_E1(double *x, char **p);
int is_a_E2(double *x, char **p);

int is_a_A(double *x, char **p);
int is_a_A1(double *x, char **p);
int is_a_A2(double *x, char **p);

/* Utility 
 */

void deg_to_rad(double *angle);
void rad_to_deg(double *angle);
void dec_to_base(unsigned long a, int b, char chaine[]);
void reverse(char s[]);

int digit_number, err;

/**
 ** evaluate() :
 **
 **   Return the value of the arithmetic expression gived in the string
 **   Put the result in result
 **   Put the current character position in pos
 **	  The com variable is used to give the error message
 **
 **/

int evaluate(char *result, char *string, int *pos, char **com)
{
  double x;
  long int n;
  char *p;              /* pointer on the current character */
  char format[20], precision[20];

  char *lib[N]={"Good expression", 
                "Syntax Error", 
                "Division by zero",
                "Negative number in root",
                "Negative number in log",
                "Out of range"
                "You number = 0"};
  p=string;

  err=SYNTAX;
  *com=lib[err];

  /* precision of the parser
   */
  strcpy(format,"%.");
  sprintf(precision,"%d", Prefs.GetPrecision());
  strcat(format, precision);
  strcat(format, "lf");

  /* return true if string is null
   */
  if (string[0]=='\0')
  {
    return TRUE;
  }

  /* evaluate the expression
   */
  if (is_a_TC(&x,&p)==TRUE)
  {
  	if (Prefs.GetEuroMode()==P_EUR)
  		x=x*Prefs.GetEuro();
  	else if (Prefs.GetEuroMode()==P_CUR)
  		x=x/Prefs.GetEuro();
 
    sprintf(result,format,x);
  	if (Prefs.GetBaseOutput() != P_DEC)
  	{
      n=(long int) x;
      dec_to_base(n, Prefs.GetBaseOutput(), result);
	}
    if (*p=='\0')
    {
      return TRUE;
    }
    else
    {
      *pos=p-string;
      *com=lib[err];
      return FALSE;
    }
  }
  else
  {
    sprintf(result,format,x);
    *pos=p-string;
    *com=lib[err];
    return FALSE;
  }

}

/* deg_to_rad() :
 */

void deg_to_rad(double *angle)
{
	*angle=*angle*PI/180;
}

/* rad_to_def() :
 */

void rad_to_deg(double *angle)
{
	*angle=*angle*180/PI;
}

/* dec_to_base :
 *   convert a number a from base 10 to base b
 *   put the result in string
 */

void dec_to_base(unsigned long a, int b, char string[])
{
    int i = 0;
    char charmap[17] = "0123456789ABCDEF";

    do
    {
        string[i] = charmap[(a - (a/b) * b)];
        a = a / b;
        i++;
    }
    while (a != 0);
    string[i]='\0';

    reverse(string);
}

/* reverse a string
 */

void reverse(char s[])
{
    int i, j;
    char tmp;
    i = j = 0;
    while (s[j] != '\0')
        j++;
    j--;

    while(i < j)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

/* is_a_TC() :
 */

int is_a_TC(double *x, char **p)
{
  if ( is_a_H(x,p)==TRUE && is_a_S2(x,p)==TRUE && is_a_S(x,p)==TRUE)
  {
    return TRUE;
  }
  return FALSE;
}

/* is_a_S() :
 */

int is_a_S(double *x, char **p)
{
  double y=0,z=0;
  while (**p==' ')
    *p=*p+1;
  if (**p=='+')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE && is_a_S2(&y,p)==TRUE && is_a_S(&z,p))
    {
      /* Add terms
       */
      *x=*x+y+z;
      return TRUE;
    }
    else
      return FALSE;
  }
  else if (**p=='-')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE && is_a_S2(&y,p)==TRUE && is_a_S(&z,p))
    {
      /* Substract terms
       */
      *x=*x-y+z;
      return TRUE;
    }
    else
      return FALSE;
  }

  return TRUE;
}

/* is_a_S2() :
 */

int is_a_S2(double *x, char **p)
{
  double y=1,z=1;
  while (**p==' ')
    *p=*p+1;
  if (**p=='*')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE && is_a_S2(&y,p)==TRUE)
    {
      /* Multiply terms
       */
      *x=*x*y;
      return TRUE;
    }
    else
      return FALSE;
  }
  else if (**p=='/')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE && is_a_S2(&z,p)==TRUE)
    {
      if (y==0 || z==0)
      {
        err=DIV_Z;
        return FALSE;
      }
      else
      {
        /* Divide terms
         */
        *x=(*x/y)*z;
        return TRUE;
      }
    }
    else
      return FALSE;
  }

  return TRUE;
}


/* is_a_H() :
 */

int is_a_H(double *x, char **p)
{
  while (**p==' ')
    *p=*p+1;
  if (**p=='+')
  {
    *p=*p+1;
    if ( is_a_H(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else if (**p=='-')
  {
    *p=*p+1;
    if ( is_a_H(x,p)==TRUE )
    {
      *x=-*x;
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( is_a_I(x,p)==TRUE )
  {
  	return TRUE;
  }
  else
    return FALSE;
}

/* is_a_I() :
 */

int is_a_I(double *x, char **p)
{
  double y=0;

  while (**p==' ')
    *p=*p+1;
  if ( **p=='c' && *(*p+1)=='o' && *(*p+2)=='s' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=cos(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='c' && *(*p+1)=='s' && *(*p+2)=='h')
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=cosh(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='s' && *(*p+1)=='n' && *(*p+2)=='h')
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=sinh(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='c' && *(*p+1)=='s' && *(*p+2)=='c' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(cos(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='c' && *(*p+1)=='c' && *(*p+2)=='h' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(cosh(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='s' && *(*p+1)=='i' && *(*p+2)=='n' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=sin(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='s' && *(*p+1)=='e' && *(*p+2)=='c' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(sin(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='s' && *(*p+1)=='c' && *(*p+2)=='h' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(sinh(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='t' && *(*p+1)=='a' && *(*p+2)=='n' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
          if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
     *x=tan(y);
      return TRUE;
    }
    else
      return FALSE;
  }
   else if ( **p=='t' && *(*p+1)=='g' && *(*p+2)=='h' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=tanh(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='c' && *(*p+1)=='t' && *(*p+2)=='g' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(tan(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='c' && *(*p+1)=='g' && *(*p+2)=='h' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (Prefs.GetAngle()==P_DEG)
      	deg_to_rad(&y);
      *x=1/(tanh(y));
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='o' && *(*p+3)=='s')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y <-1.0 || y > 1.0)
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=acos(y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='c' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y<=0 || y>1.0 )
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=acosh(1/y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='s' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
     if ( y<1)
      {
        err=RANGE;
        return FALSE;
      } 
      else
      {
        *x=acosh(y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='s' && *(*p+2)=='c' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y==0 )
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=asinh(1/y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='s' && *(*p+3)=='c')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
     if ( y > -1.0 && y < 1.0)
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=acos(1/y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
     }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='s' && *(*p+2)=='i' && *(*p+3)=='n')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y <-1.0 || y > 1.0)
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=asin(y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='t' && *(*p+2)=='g' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y<= -1.0 || y>= 1.0 )
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=atanh(y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='g' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
     if ( y>= -1.0 && y<=1)
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=atanh(1/y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='s' && *(*p+2)=='n' && *(*p+3)=='h')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
        *x=asinh(y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='s' && *(*p+2)=='e' && *(*p+3)=='c')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if ( y > -1.0 && y < 1.0)
      {
        err=RANGE;
        return FALSE;
      }
      else
      {
        *x=asin(1/y);
        if (Prefs.GetAngle()==P_DEG)
      	  rad_to_deg(x);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='a' && *(*p+1)=='t' && *(*p+2)=='a' && *(*p+3)=='n')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=atan(y);
      if (Prefs.GetAngle()==P_DEG)
      	rad_to_deg(x);
      return TRUE;
    }
    else
      return FALSE;
  }
    else if ( **p=='a' && *(*p+1)=='c' && *(*p+2)=='t' && *(*p+3)=='g')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=atan(1/y);
      if (Prefs.GetAngle()==P_DEG)
      	rad_to_deg(x);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( **p=='s' && *(*p+1)=='q' && *(*p+2)=='r' && *(*p+3)=='t')
  {
    *p=*p+4;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (y<0)
      {
        err=ROOT_N;
        return FALSE;
      }
      else
      {
        *x=sqrt(y);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='l' && *(*p+1)=='n')
  {
    *p=*p+2;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (y<=0)
      {
        err=LN_N;
        return FALSE;
      }
      else
      { 
        *x=log(y);
        return TRUE;
      }
      }
    else
      return FALSE;
  }
  else if ( **p=='!')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE )
    {
    int i;
   if (y > 1000) y = 1000;
			else if (y < -1000) y = -1000;

			if (y >= 0)
			{
				i = (int)(y + 0.0000000001);
				y = 1.0;
			}
			else
			{
				i = (int)(-y + 0.0000000001);
				y = -1.0;
			}
			while (i > 0)
			{
				y *= i;
				i--;
			}
        *x=y;
        return TRUE;
      }
    else
      return FALSE;
  }
  else if ( **p=='l' && *(*p+1)=='g')
  {
    *p=*p+2;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (y<=0)
      {
        err=LN_N;
        return FALSE;
      }
      else
      {
        *x=log10(y);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='l' && *(*p+1)=='b')
  {
    *p=*p+2;
    if ( is_a_H(&y,p)==TRUE )
    {
      if (y<=0)
      {
        err=LN_N;
        return FALSE;
      }
      else
      {
        *x=log2(y);
        return TRUE;
      }
    }
    else
      return FALSE;
  }
  else if ( **p=='e' && *(*p+1)=='x' && *(*p+2)=='p')
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=exp(y);
      return TRUE;
    }
    else
      return FALSE;
  }
  else if ( is_a_J(x,p)==TRUE && is_a_P(x,p)==TRUE )
  {
    return TRUE;
  }
  else
    return FALSE;
}

/* is_a_J() :
 */

int is_a_J(double *x, char **p)
{
  while (**p==' ')
    *p=*p+1;
  if (**p=='(')
  {
    *p=*p+1;
    if ( is_a_TC(x,p)==TRUE )
    {
      if (**p==')')
      {
        *p=*p+1;
        return TRUE;
      }
      else
        return FALSE;
    }
    else
      return FALSE;
  }
  else if ( is_a_L(x,p)==TRUE )
  {
    return TRUE;
  }
  else
    return FALSE;
}

/* is_a_P() :
 */

int is_a_P(double *x, char **p)
{
  double y=1;
  while (**p==' ')
    *p=*p+1;
  if (**p=='^')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=pow(*x,y);
      return TRUE;
    }
    else
      return FALSE;
  }
else if (**p=='@')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=pow(*x,(1/y));
      return TRUE;
    }
    else
      return FALSE;
  }
  
else if (**p=='#')
  {
    *p=*p+1;
    if ( is_a_H(&y,p)==TRUE )
    {
      *x=*x/(pow(10,(y)));
      return TRUE;
    }
    else
      return FALSE;
  }
  
else if (**p=='l' && *(*p+1)=='o' && *(*p+2)=='g' )
  {
    *p=*p+3;
    if ( is_a_H(&y,p)==TRUE )
    {
    if (y <=0 || *x==1.0 || *x<=0)
    {
     err=LN_N;
    return FALSE;
    }
    else
    {
      *x=(log10(y))/(log10(*x));
      return TRUE;
    }
    }
    else
      return FALSE;
  }
  return TRUE;
}

/* is_a_L() :
 */

int is_a_L(double *x, char **p)
{
  if (**p=='k')
  {
    *p=*p+1;
    if ( is_a_B(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else if (**p=='t')
  {
    *p=*p+1;
    if ( is_a_Z(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else if (**p=='o')
  {
    *p=*p+1;
    if ( is_a_O(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else if (**p=='j')
  {
    *p=*p+1;
    if ( is_a_M(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else if (**p=='.')
    {
      /* Compute decimal number
       */
      digit_number=0;
      *p=*p+1;
      if ( is_a_C(x,p)==TRUE )
      {
        while (digit_number>0)
        {
          *x=*x/10;
          digit_number--;
        }
	    return TRUE;    
      }
      else
        return FALSE;
    }
    else
      return FALSE;
  }
  else if (**p=='i')
  {
    *p=*p+1;
    if ( is_a_Q(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else if (**p=='x')
  {
    *p=*p+1;
    if ( is_a_X(x,p)==TRUE )
    {
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else if ( **p=='p' && *(*p+1)=='i' )
  {
  	*p=*p+2;
  	*x=PI;
  	return TRUE;
  }
  else if ( **p=='n' && *(*p+1)=='e' )
  {
  	*p=*p+2;
  	*x=M_E;
  	return TRUE;
  }
  else if ( **p=='N' && *(*p+1)=='E' )
  {
  	*p=*p+2;
  	*x=M_E;
  	return TRUE;
  }
  else if ( **p=='P' && *(*p+1)=='I' )
  {
  	*p=*p+2;
  	*x=PI;
  	return TRUE;
  }

  /* Use the defined base :
   * 	Not a "pure" grammar, so the code should be at the end
   * 	of the function
   */
  else if (Prefs.GetBase()==P_DEC)
  {
    if ( is_a_M(x,p)==TRUE )
    {
        return TRUE;
    }
    else if (**p=='.')
    {
      /* Compute decimal number
       */
      digit_number=0;
      *p=*p+1;
      if ( is_a_C(x,p)==TRUE )
      {
        while (digit_number>0)
        {
          *x=*x/10;
          digit_number--;
        }
	    return TRUE;    
      }
      else
      	return FALSE;
    }
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BIN)
  {
    if ( is_a_B(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_TRI)
  {
    if ( is_a_Z(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS4)
  {
    if ( is_a_W(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS5)
  {
    if ( is_a_Y(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS6)
  {
    if ( is_a_V(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS7)
  {
    if ( is_a_U(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_OCT)
  {
    if ( is_a_O(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS9)
  {
    if ( is_a_T(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS11)
  {
    if ( is_a_R(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_DUO)
  {
    if ( is_a_Q(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS13)
  {
    if ( is_a_K(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS14)
  {
    if ( is_a_G(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_BS15)
  {
    if ( is_a_F(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else if (Prefs.GetBase()==P_HEX)
  {
    if ( is_a_X(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
else if (Prefs.GetBase()==P_BS17)
  {
    if ( is_a_E(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
else if (Prefs.GetBase()==P_BS18)
  {
    if ( is_a_A(x,p)==TRUE )
        return TRUE;
    else
    	return FALSE;
  }
  else
    return FALSE;
}
/* is_a_M() :
 */

int is_a_M(double *x, char **p)
{
  if ( is_a_D(x,p)==TRUE && is_a_D1(x,p)==TRUE && is_a_N(x,p)==TRUE )
  {
    return TRUE;
  }
  else
    return FALSE;
}

/* is_a_D() :
 */

int is_a_D(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      digit_number++;
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_D1() :
 */

int is_a_D1(double *x, char **p)
{
  double y=0;
  if ( is_a_D(&y,p)==TRUE )
  {
    /* Compute decimal number
     */
    *x=(*x*10)+y;
    if ( is_a_D1(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_N() :
 */

int is_a_N(double *x, char **p)
{
  double y;
  y=0.0;
  if (**p=='.')
  {
    /* Compute decimal number
     */
    digit_number=0;
    *p=*p+1;
    if ( is_a_D1(&y,p)==TRUE )
    {
      while (digit_number>0)
      {
        y=y/10;
        digit_number--;
      }
      *x=*x+y;
	  return TRUE;    
    }
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_C() :
 */

int is_a_C(double *x, char **p)
{
  if ( is_a_D(x,p)==TRUE && is_a_D1(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_B() :
 */

int is_a_B(double *x, char **p)
{
  if ( is_a_B1(x,p)==TRUE && is_a_B2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_B1() :
 */

int is_a_B1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_B2() :
 */

int is_a_B2(double *x, char **p)
{
  double y=0;
  if ( is_a_B1(&y,p)==TRUE )
  {
    /* Compute binary number
     */
    *x=(*x*2)+y;
    if ( is_a_B2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}
/* is_a_Z() :
 */

int is_a_Z(double *x, char **p)
{
  if ( is_a_Z1(x,p)==TRUE && is_a_Z2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_Z1() :
 */

int is_a_Z1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_Z2() :
 */

int is_a_Z2(double *x, char **p)
{
  double y=0;
  if ( is_a_Z1(&y,p)==TRUE )
  {
    /* Compute trinary number
     */
    *x=(*x*3)+y;
    if ( is_a_Z2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_W() :
 */

int is_a_W(double *x, char **p)
{
  if ( is_a_W1(x,p)==TRUE && is_a_W2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_W1() :
 */

int is_a_W1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_W2() :
 */

int is_a_W2(double *x, char **p)
{
  double y=0;
  if ( is_a_W1(&y,p)==TRUE )
  {
    /* Compute base 4 number
     */
    *x=(*x*4)+y;
    if ( is_a_W2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_Y() :
 */

int is_a_Y(double *x, char **p)
{
  if ( is_a_Y1(x,p)==TRUE && is_a_Y2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_Y1() :
 */

int is_a_Y1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_Y2() :
 */

int is_a_Y2(double *x, char **p)
{
  double y=0;
  if ( is_a_Y1(&y,p)==TRUE )
  {
    /* Compute base 5 number
     */
    *x=(*x*5)+y;
    if ( is_a_Y2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_V() :
 */

int is_a_V(double *x, char **p)
{
  if ( is_a_V1(x,p)==TRUE && is_a_V2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_V1() :
 */

int is_a_V1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_V2() :
 */

int is_a_V2(double *x, char **p)
{
  double y=0;
  if ( is_a_V1(&y,p)==TRUE )
  {
    /* Compute base 6 number
     */
    *x=(*x*6)+y;
    if ( is_a_V2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_U() :
 */

int is_a_U(double *x, char **p)
{
  if ( is_a_U1(x,p)==TRUE && is_a_U2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_U1() :
 */

int is_a_U1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_U2() :
 */

int is_a_U2(double *x, char **p)
{
  double y=0;
  if ( is_a_U1(&y,p)==TRUE )
  {
    /* Compute base 7 number
     */
    *x=(*x*7)+y;
    if ( is_a_U2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}


/* is_a_O() :
 */

int is_a_O(double *x, char **p)
{
  if ( is_a_O1(x,p)==TRUE && is_a_O2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_O1() :
 */

int is_a_O1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_O2() :
 */

int is_a_O2(double *x, char **p)
{
  double y=0;
  if ( is_a_O1(&y,p)==TRUE )
  {
    /* Compute octal number
     */
    *x=(*x*8)+y;
    if ( is_a_O2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_T() :
 */

int is_a_T(double *x, char **p)
{
  if ( is_a_T1(x,p)==TRUE && is_a_T2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_T1() :
 */

int is_a_T1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_T2() :
 */

int is_a_T2(double *x, char **p)
{
  double y=0;
  if ( is_a_T1(&y,p)==TRUE )
  {
    /* Compute base 9 number
     */
    *x=(*x*9)+y;
    if ( is_a_T2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_R() :
 */

int is_a_R(double *x, char **p)
{
  if ( is_a_R1(x,p)==TRUE && is_a_R2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_R1() :
 */

int is_a_R1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_R2() :
 */

int is_a_R2(double *x, char **p)
{
  double y=0;
  if ( is_a_R1(&y,p)==TRUE )
  {
    /* Compute base 11 number
     */
    *x=(*x*11)+y;
    if ( is_a_R2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_Q() :
 */

int is_a_Q(double *x, char **p)
{
  if ( is_a_Q1(x,p)==TRUE && is_a_Q2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_Q1() :
 */

int is_a_Q1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_Q2() :
 */

int is_a_Q2(double *x, char **p)
{
  double y=0;
  if ( is_a_Q1(&y,p)==TRUE )
  {
    /* Compute duodecimal number
     */
    *x=(*x*12)+y;
    if ( is_a_Q2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_K() :
 */

int is_a_K(double *x, char **p)
{
  if ( is_a_K1(x,p)==TRUE && is_a_K2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_K1() :
 */

int is_a_K1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_K2() :
 */

int is_a_K2(double *x, char **p)
{
  double y=0;
  if ( is_a_K1(&y,p)==TRUE )
  {
    /* Compute base 13 number
     */
    *x=(*x*13)+y;
    if ( is_a_K2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_G() :
 */

int is_a_G(double *x, char **p)
{
  if ( is_a_G1(x,p)==TRUE && is_a_G2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_G1() :
 */

int is_a_G1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_G2() :
 */

int is_a_G2(double *x, char **p)
{
  double y=0;
  if ( is_a_G1(&y,p)==TRUE )
  {
    /* Compute base 14 number
     */
    *x=(*x*14)+y;
    if ( is_a_G2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_F() :
 */

int is_a_F(double *x, char **p)
{
  if ( is_a_F1(x,p)==TRUE && is_a_F2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_F1() :
 */

int is_a_F1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_F2() :
 */

int is_a_F2(double *x, char **p)
{
  double y=0;
  if ( is_a_F1(&y,p)==TRUE )
  {
    /* Compute base 15 number
     */
    *x=(*x*15)+y;
    if ( is_a_F2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_X() :
 */

int is_a_X(double *x, char **p)
{
  if ( is_a_X1(x,p)==TRUE && is_a_X2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_X1() :
 */

int is_a_X1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_X2() :
 */

int is_a_X2(double *x, char **p)
{
  double y=0;
  if ( is_a_X1(&y,p)==TRUE )
  {
    /* Compute hexadecimal number
     */
    *x=(*x*16)+y;
    if ( is_a_X2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_E() :
 */

int is_a_E(double *x, char **p)
{
  if ( is_a_E1(x,p)==TRUE && is_a_E2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_E1() :
 */

int is_a_E1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_E2() :
 */

int is_a_E2(double *x, char **p)
{
  double y=0;
  if ( is_a_E1(&y,p)==TRUE )
  {
    /* Compute base 17 number
     */
    *x=(*x*17)+y;
    if ( is_a_E2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}

/* is_a_A() :
 */

int is_a_A(double *x, char **p)
{
  if ( is_a_A1(x,p)==TRUE && is_a_A2(x,p)==TRUE )
    return TRUE;
  return FALSE;
}

/* is_a_A1() :
 */

int is_a_A1(double *x, char **p)
{
  switch (**p)
  {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      *x=*(*p)-'0';
      *p=*p+1;
      return TRUE;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
      *x=10+*(*p)-'A';
      *p=*p+1;
      return TRUE;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
      *x=10+*(*p)-'a';
      *p=*p+1;
      return TRUE;
    default:
     return FALSE;
  }
}

/* is_a_A2() :
 */

int is_a_A2(double *x, char **p)
{
  double y=0;
  if ( is_a_A1(&y,p)==TRUE )
  {
    /* Compute base 18 number
     */
    *x=(*x*18)+y;
    if ( is_a_A2(x,p)==TRUE )
      return TRUE;
    else
      return FALSE;
  }
  else
    return TRUE;
}
