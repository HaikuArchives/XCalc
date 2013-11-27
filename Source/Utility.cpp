/**************************************************************************
 **
 ** Utility.cpp
 **
 ** Utility fonctions
 **
 **************************************************************************/

/* Remove unwanted zero in a decimal number string
 */

void removeLastZeros(char *s)
{
	int length,dot,i;
	for (length=0; s[length]!='\0'; length++)
	  ;
	for (dot=0; s[dot]!='.' && s[dot]!='\0'; dot++)
	  ;
	if (length>0)
	  for (i=length-1; i>=dot && ( s[i]=='0' || s[i]=='.' ); i--)
 	    s[i]='\0';
}

/* Remove the last character in a string
 */

void removeLastChar(char *s)
{
	int length;
	for (length=0; s[length]!='\0'; length++)
	  ;
	if (length>0)
	  s[length-1]='\0';
}
