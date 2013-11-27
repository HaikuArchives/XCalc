/**************************************************************************
 **
 ** Parser.h
 **
 ** Parser header
 **
 **************************************************************************/

#ifndef Parser_h
#define Parser_h

int evaluate(char *, char *, int *, char **);

__extern_c_start
#if __INTEL__
double log2(double x);
#endif /* __INTEL__ */
__extern_c_end

#endif /* Parser_h */
