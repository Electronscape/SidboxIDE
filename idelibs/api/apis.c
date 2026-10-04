#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include "apis.h"
/*

  #####################################################################################################
//#                                                                                                   #//
//#   SIDBOX SYSTEMS API V0.525                                                                       #//
//#   Written Wayne H (2026)                                                                          #//
//#   sorry its taken so long everyone                                                                #//
//#                                                                                                   #//
//#   systems:                                                                                        #//
//#                                                                                                   #//
  #####################################################################################################
*/

// Random Generator (crude but works)
long _Randseed = 402;		// random seed

int16_t randomi(unsigned short range){
    _Randseed = _Randseed * 11 + 125;
    return ((signed short)(_Randseed >> 16) % range);
}

uint16_t urandomi(unsigned short range){
    _Randseed = _Randseed * 11 + 125;
    return ((uint16_t)(_Randseed >> 16) % range);
}

void urandomseed(long newseed){
    _Randseed = newseed;
}

// Case-insensitive string compare up to 'n' characters
int stringcmp(const char *s1, const char *s2, size_t n) {
    while (n--) {
        char c1 = ((unsigned char)*s1++);
        char c2 = ((unsigned char)*s2++);
        if (c1 != c2) return (unsigned char)c1 - (unsigned char)c2;
        if (c1 == '\0') break;
    }
    return 0;
}


