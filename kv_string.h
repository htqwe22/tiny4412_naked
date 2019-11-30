
/**********************************************************************************
 * FILE : kv_string.h
 * Description:
 * Author: Kevin He
 * Created On: 2018-12-01 , At 11:33:09
 * Modifiled On : 
 * Version : 0.0.1
 * Information :
 **********************************************************************************/

#ifndef KV_KV_STRING_H
#define KV_KV_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

void *kv_memove(void *dest, const void *src, unsigned int n);

void *kv_memcpy(void *dest, const void *src, unsigned int n);

int kv_memcmp(const void *s1, const void *s2, unsigned int n);

char *kv_strstr(const char *origin, int origin_len, const char *needle);

int kv_strcmp(const char *s1, const char *s2);

int kv_strcaecmp(const char *s1, const char *s2);

char *kv_strcpy(char *dest, const char *src);

void *kv_memset(void *s, int c, unsigned int n);

unsigned int kv_strlen(const char *s);
char *kv_strcat(char *dest, const char *src);

char *kv_strchr(const char *s, int c);

#ifdef __cplusplus
}
#endif

#endif

