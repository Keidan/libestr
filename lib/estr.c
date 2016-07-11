/**
*******************************************************************************
* @file estr.c
* @brief Basic string manipulations.
* @author Keidan
* @par Project estr
* @copyright Copyright 2016 Keidan, all right reserved.
* @par License:
* This software is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY.
*
* Licence summary : 
*    You can modify and redistribute the sources code and binaries.
*    You can send me the bug-fix
*
* Term of the licence in in the file licence.txt.
*
* .____    ._____.                             
* |    |   |__\_ |__                           
* |    |   |  || __ \
* |    |___|  || \_\ \
* |_______ \__||___  /                         
*         \/       \/                          
* ___________                                  
* \_   _____/____    _________.__.             
*  |    __)_\__  \  /  ___<   |  |             
*  |        \/ __ \_\___ \ \___  |             
* /_______  (____  /____  >/ ____|             
*         \/     \/     \/ \/                  
*   _________ __         .__                
*  /   _____//  |________|__| ____    ____  
*  \_____  \\   __\_  __ \  |/    \  / ___\ 
*  /        \|  |  |  | \/  |   |  \/ /_/  >
* /_______  /|__|  |__|  |__|___|  /\___  / 
*         \/                     \//_____/
*******************************************************************************
*/
#include <estr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <errno.h>

/**
 * @fn void estr_tolower(const char* source, char* dest)
 * @brief Convert a string in lower case.
 * @param source Source string.
 * @param dest Destination string.
 */
void estr_tolower(const char* source, char* dest) {
  size_t i;
  if(!source || !dest) return;
  for(i = 0; i < strlen(source); i++)
    dest[i] = tolower(source[i]);
}

/**
 * @fn void estr_toupper(const char* source, char* dest)
 * @brief Convert a string in upper case.
 * @param source Source string.
 * @param dest Destination string.
 */
void estr_toupper(const char* source, char* dest) {
  size_t i;
  if(!source || !dest) return;
  for(i = 0; i < strlen(source); i++)
    dest[i] = toupper(source[i]);
}

/**
 * @fn char* estr_substring(const char* str, size_t begin, size_t len)
 * @brief Substract a string.
 * @param str Input string.
 * @param begin Begin index.
 * @param len Length.
 * @return substring (free required).
 */
char* estr_substring(const char* str, size_t begin, size_t len)  { 
  if (!str || !strlen(str) || strlen(str) < begin || strlen(str) < (begin+len)) 
    return 0; 
  return strndup(str + begin, len); 
} 

/**
 * @fn int estr_indexof(const char* source, const char* needed)
 * @brief Search the index of the needed string into the input string.
 * @param source Search string.
 * @param needed Needed string.
 * @return -1 if not found else 0.
 */
int estr_indexof(const char* source, const char* needed) {
  char* found;
  if(!source || !needed) return -1;
  found = strstr(source, needed);
  if(found != NULL)  return found - source;
  return -1;
}

/**
 * @fn size_t estr_count(const char* source, const char needed)
 * @brief Count the number of occurences of the needed char.
 * @param source Search string.
 * @param needed The char.
 * @return Occurences number.
 */
size_t estr_count(const char* source, const char needed) {
  size_t i, len, count = 0;
  if(!source) return 0;
  len = strlen(source);
  for(i = 0; i < len; i++)
    if(source[i] == needed) count++;
  return count;
}


/**
 * @fn _Bool estr_isint(const char* source)
 * @brief Test if the string is a valid digit.
 * @param source The source string
 * @return 1 if the string is a valid int.
 */
_Bool estr_isint(const char* source) {
  size_t i, off = 0;
  if(!source) return 0;
  if(source[0] == '-') off = 1;
  for(i = off; i < strlen(source); i++)
    if(!isdigit(source[i]))
      return 0;
  return 1;
}

/**
 * @fn int estr_parse_int(char* str, int def)
 * @brief Convert a string int to an int value.
 * @param str Src string.
 * @param def the default value on error
 * @return the int value.
 */
int estr_parse_int(char* str, int def) {
  int n;
  errno = 0;
  if(!str) return def;
  n = strtol(str, NULL, 10);
  if((errno == ERANGE) || (errno == EINVAL))
    return def;
  return n;
}

/**
 * @fn unsigned long int estr_parse_long(char* str, unsigned long int def)
 * @brief Convert a string long to a long value.
 * @param str Src string.
 * @param def the default value on error
 * @return the long value.
 */
unsigned long int estr_parse_long(char* str, unsigned long int def) {
  unsigned long int n;
  errno = 0;
  if(!str) return def;
  n = strtoll(str, NULL, 10);
  if((errno == ERANGE) || (errno == EINVAL))
    return def;
  return n;
}

/**
 * @fn _Bool estr_match(const char* str, const char* regex)
 * @brief Test if the regex match with the input string.
 * @param str The string to test.
 * @param regex The regex
 * @return 1 if the regex match else 0.
 */
_Bool estr_match(const char* str, const char* regex) {
  regex_t preg;
  char *text;
  size_t size;
  int err, match;
  if(!str) return 0;
  err = regcomp(&preg, regex, REG_NOSUB|REG_EXTENDED);
  if(!err) {
    match = regexec(&preg, str, 0, NULL, 0);
    regfree(&preg);
    if(!match) return 1;
    else if(match == REG_NOMATCH) return 0;
    else {
      size = regerror(err, &preg, NULL, 0);
      text = malloc(sizeof (*text) * size);
      if(text) {
        regerror (err, &preg, text, size);
        fprintf(stderr, "Regex failed with error: %s\n", text);
        free(text);
      }
      else {
        errno = ENOMEM;
        return -1;
      }
    }
  }
  return 0;
}

/**
 * @fn const char* estr_convert(unsigned long num, int base)
 * @brief Convert an unsigned int in string.
 * @param num The uint
 * @param base The desired base.
 * @return The string.
 */
const char* estr_convert(unsigned long num, int base) {
  static char buf[33];
  char *ptr;
  ptr=&buf[sizeof(buf)-1];
  *ptr='\0';
  do {
    *--ptr="0123456789abcdef"[num%base];
    num /= base;
  } while(num != 0);
  return (const char*)ptr;
}

/**
 * @fn const char* estr_hex2bin(const char* numstr)
 * @brief Convert and hexa string in binary value.
 * @param hexstr The hex string.
 * @return The binary representation.
 */
const char* estr_hex2bin(const char* hexstr) {
  int i = 0;
  static char str[132];
  static char hex[] = "0123456789ABCDEF";
  static char *quad [] = { "0000", "0001", "0010", "0011", "0100", "0101",
                            "0110", "0111", "1000", "1001", "1010", "1011",
                            "1100", "1101", "1110", "1111" };
  bzero(str, 132);
  if(!hexstr) return str;
  if(hexstr[0] == '0' && hexstr[1] == 'x')
    hexstr+=2;
  while(*hexstr) {
    strcpy(str+i, quad[strchr(hex, *hexstr)-hex]);
    i+=4;
    hexstr++;
  }
  return str;
}


/**
 * @fn _Bool estr_startswith(const char *str, const char *prefix)
 * @brief Test if the string starts with the prefix.
 * @param str The source string.
 * @param prefix The prefix string to find.
 * @return true/false
 */
_Bool estr_startswith(const char *str, const char *prefix) {
  size_t prefix_l, str_l;
  if(!str || !prefix) return 0;
  prefix_l = strlen(prefix);
  str_l = strlen(str);
  return str_l < prefix_l ? 0 : strncmp(prefix, str, prefix_l) == 0;
}

/**
 * @fn _Bool estr_endswith(const char *str, const char *suffix)
 * @brief Test if the string ends with the suffix.
 * @param str The source string.
 * @param suffix The suffix string to find.
 * @return true/false
 */
_Bool estr_endswith(const char *str, const char *suffix) {
  size_t suffix_l, str_l;
  if(!str || !suffix) return 0;
  suffix_l = strlen(suffix);
  str_l = strlen(str);
  if(suffix_l > str_l) return 0;
  return strncmp(str + str_l - suffix_l, suffix, suffix_l) == 0;
}

