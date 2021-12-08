
/**********************************************************************************
 * FILE : util_string.h
 * Description:
 * Author: Kevin He
 * Created On: 2018-03-19 , At 11:21:19
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

//#define USE_BIGENDIAN
#ifndef NULL
#define NULL ((void*)0)
#endif


int util_atoi(const char *s);

int hex_string_to_bin(const char *hexstr, int hexstr_len, unsigned char *binbuf, int binbuff_size);

/**/
int bin_to_hex_string(const unsigned char *binbuf, int binbuff_len, char *hexstr, int hexstr_size);


void *memove2(void *dest, const void *src, unsigned int n);

void *memcpy2(void *dest, const void *src, unsigned int n);

int memcmp2(const void *s1, const void *s2, unsigned int n);

char *strstr2(const char *origin, int origin_len, const char *needle);

unsigned int strlen2(const char *s);


void swap_byte_arr(unsigned char arr[], int arr_size);

void swap_short_arr(unsigned     short arr[], int arr_size);

void swap_int_arr(unsigned    int arr[], int arr_size);

void swap_u64_arr(unsigned long long arr[], int arr_size);

#ifdef __cplusplus
}
#endif
#endif

