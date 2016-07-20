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

#define SMAGIC 0x8001
#define EMAGIC 0x1337

#define valid_ret(e, ret) do {                              \
  errno = 0;                                                \
  if(!e || !e->buffer ||                                    \
      e->sm != SMAGIC || e->em != EMAGIC) {                 \
    errno = EINVAL;                                         \
    return ret;                                             \
  }                                                         \
}while(0)

#define valid_noret(e) do {                                 \
  errno = 0;                                                \
  if(!e || !e->buffer ||                                    \
      e->sm != SMAGIC || e->em != EMAGIC) {                 \
    errno = EINVAL;                                         \
    return;                                                 \
  }                                                         \
}while(0)

struct estr_s {
  int sm;
  char* buffer;
  size_t length;
  size_t capacity;
  int em;
};


/**
 * @fn estr_t estr_new_stringl(char* str, size_t str_len)
 * @brief New Easy string instance.
 * @param str The string to copy.
 * @param str_len The string length.
 * @return The instance else null
 */
estr_t estr_new_stringl(char* str, size_t str_len) {
  struct estr_s *e = malloc(sizeof(struct estr_s));
  if(!e) {
    errno = ENOMEM;
    return NULL;
  }
  memset(e, 0, sizeof(struct estr_s));
  e->sm = SMAGIC;
  e->em = EMAGIC;
  e->buffer = NULL;
  if(str)
    estr_appendl(e, str, str_len);
  else
    estr_set_capacity(e, 1);
  return e;
}

/**
 * @fn estr_t estr_new_string(char* str)
 * @brief New Easy string instance.
 * @param str The string to copy.
 * @return The instance else null
 */
estr_t estr_new_string(char* str) {
  return estr_new_stringl(str, str ? strlen(str) : 0);
}
  
/**
 * @fn estr_t estr_new(void)
 * @brief New Easy string instance.
 * @return The instance else null
 */
estr_t estr_new(void) {
  return estr_new_stringl(NULL, 0);
}

/**
 * @fn void estr_delete(estr_t buffer)
 * @brief Delete string buffer.
 * @param buffer The buffer pointer.
 */
void estr_delete(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  if(e) {
    valid_noret(e);
    if(e->buffer) free(e->buffer), e->buffer = NULL;
    e->length = e->capacity = 0;
    free(e);
  }
}

/**
 * @fn void estr_clear(estr_t buffer)
 * @brief Clear the buffer.
 * @param buffer The buffer pointer.
 */
void estr_clear(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_noret(e);
  bzero(e->buffer, e->length);
  e->length = 0;
}

/**
 * @fn char* estr_to_str(estr_t buffer)
 * @brief Get the buffer to char* format.
 * @param buffer The buffer.
 * @return The char* (can be NULL)
 */
char* estr_to_str(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, NULL);
  return e->buffer;
}

/**
 * @fn char estr_char_at(estr_t buffer, size_t index)
 * @brief Get a char 'at'.
 * @param buffer Search string.
 * @param index The index.
 * @return The char.
 */
char estr_char_at(estr_t buffer, size_t index) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  if(index > e->length) {
    errno = EINVAL;
    return 0;
  }
  return e->buffer[index];
}

/**
 * @fn size_t estr_length(estr_t buffer)
 * @brief Get the buffer length.
 * @param buffer The buffer.
 * @return The length
 */
size_t estr_length(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  return e->length ? e->length - 1 : 0;
}

/**
 * @fn size_t estr_capacity(estr_t buffer)
 * @brief Get the buffer capacity.
 * @param buffer The buffer.
 * @return The capacity
 */
size_t estr_capacity(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  return e->capacity ? e->capacity - 1 : 0;
}

/**
 * @fn int estr_set_capacity(estr_t buffer, size_t capacity)
 * @brief Change the buffer capacity.
 * @param buffer The buffer.
 * @param capacity The buffer capacity.
 * @return 0 on success, -1 else (see errno)
 */
int estr_set_capacity(estr_t buffer, size_t capacity) {
  struct estr_s *e = (struct estr_s*) buffer;
  char* tmp;
  valid_ret(e, -1);
  if(estr_capacity(e) == capacity) return 0;
  capacity++;
  tmp = (char*)realloc(e->buffer, capacity);
  if(!tmp) {
    errno = ENOMEM;
    return -1;
  }
  e->capacity = capacity;
  if(e->capacity > e->length) e->length = e->capacity;
  e->buffer = tmp;
  e->buffer[e->capacity - 1] = 0;
  return 0;
}

/**
 * @fn int estr_append_char(estr_t buffer, const char c)
 * @brief Append a char into the buffer.
 * @param buffer The buffer.
 * @param c The char to append.
 * @return 0 on success, -1 else (see errno).
 */
int estr_append_char(estr_t buffer, const char c) {
  char cc[2];
  cc[0] = c;
  cc[1] = 0;
  return estr_appendl(buffer, cc, 2);
}

/**
 * @fn int estr_append(estr_t buffer, const char* str)
 * @brief Append a string into the buffer.
 * @param buffer The buffer.
 * @param str The string to append.
 * @return 0 on success, -1 else (see errno).
 */
int estr_append(estr_t buffer, const char* str) {
  return estr_appendl(buffer, str, strlen(str) + 1);
}

/**
 * @fn int estr_appends(estr_t buffer, estr_t str)
 * @brief Append a string into the buffer.
 * @param buffer The buffer.
 * @param str The string to append.
 * @return 0 on success, -1 else (see errno).
 */
int estr_appends(estr_t buffer, estr_t str) {
  struct estr_s *s = (struct estr_s*) str;
  valid_ret(s, -1);
  return estr_appendl(buffer, s->buffer, s->length);
}

/**
 * @fn int estr_appendl(estr_t buffer, const char* str, size_t str_len)
 * @brief Append a string into the buffer.
 * @param buffer The buffer.
 * @param str The string to append.
 * @param str_len The string length.
 * @return 0 on success, -1 else (see errno).
 */
int estr_appendl(estr_t buffer, const char* str, size_t str_len) {
  struct estr_s *e = (struct estr_s*) buffer;
  char* tmp = NULL;
  if(!e || e->sm != SMAGIC || e->em != EMAGIC) {
    errno = EINVAL;
    return -1;
  }
  if(strlen(str) == str_len) str_len++;
  
  if(!e->capacity) {
    e->capacity = str_len + 1;
    e->length = e->capacity;
    e->buffer = (char*)malloc(e->capacity);
    if(!e->capacity) {
      errno = ENOMEM;
      e->length = e->capacity = 0;
      return -1;
    }
    strcpy(e->buffer, str);
  } else if((e->length + str_len) < e->capacity) {
    e->length += str_len;
    strcat(e->buffer, str);
  } else {
    e->capacity += str_len;
    tmp = (char*)realloc(e->buffer, e->capacity);
    if(!tmp) {
      errno = ENOMEM;
      e->capacity -= str_len;
      return -1;
    }
    e->length += str_len;
    e->buffer = tmp;
    strcat(e->buffer, str);
  }
  return 0;
}

/**
 * @fn int estr_copy_char(estr_t buffer, const char c)
 * @brief Erase the buffer and copy the char.
 * @param buffer The buffer.
 * @param c The char to copy.
 * @return 0 on success, -1 else (see errno).
 */
int estr_copy_char(estr_t buffer, const char c) {
  char cc[2];
  cc[0] = c;
  cc[1] = 0;
  return estr_copyl(buffer, cc, 2);
}

/**
 * @fn int estr_copy(estr_t buffer, const char* str)
 * @brief Erase the buffer with the copy string.
 * @param buffer The buffer.
 * @param str The string to copy.
 * @return 0 on success, -1 else (see errno).
 */
int estr_copy(estr_t buffer, const char* str) {
  return estr_copyl(buffer, str, strlen(str) + 1);
}

/**
 * @fn int estr_copyl(estr_t buffer, const char* str, size_t str_eln)
 * @brief Erase the buffer with the copy string.
 * @param buffer The buffer.
 * @param str The string to copy.
 * @return 0 on success, -1 else (see errno).
 */
int estr_copyl(estr_t buffer, const char* str, size_t str_len) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  estr_clear(e);
  return estr_appendl(e, str, str_len);
}

/**
 * @fn int estr_trim_to_size(estr_t buffer)
 * @brief Trim the buffer capacity to the real buffer size.
 * @param buffer The buffer.
 * @return 0 on success, -1 else (see errno).
 */
int estr_trim_to_size(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  if(!e->capacity) return 0;
  if(estr_capacity(e) == estr_length(e)) return 0;
  return estr_set_capacity(e, e->length);
}

/**
 * @fn int estr_erase2(estr_t buffer, size_t index)
 * @brief Erase a string.
 * @param buffer The buffer.
 * @param index The index.
 * @return 0 on success, -1 else (see errno).
 */
int estr_erase2(estr_t buffer, size_t index) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  if(index >= estr_length(e) || !e->length) {
    errno = EINVAL;
    return -1;
  }
  bzero(e->buffer + index, e->length - index);
  e->length = strlen(e->buffer) + 1;
  return 0;
}

/**
 * @fn int estr_erase(estr_t buffer, size_t index, size_t length)
 * @brief Erase a string.
 * @param buffer The buffer.
 * @param index The start index.
 * @param length The length.
 * @return 0 on success, -1 else (see errno).
 */
int estr_erase(estr_t buffer,size_t index, size_t length) {
  struct estr_s *e = (struct estr_s*) buffer;
  if((index+length) >= estr_length(e) || !e->length) {
    errno = EINVAL;
    return -1;
  }
  memcpy(e->buffer + index, e->buffer + index + length, e->length - (index + length));
  bzero(e->buffer + e->length - length, length);
  e->length = strlen(e->buffer) + 1;
  return 0;
}

/**
 * @fn int estr_insert(estr_t buffer, size_t index, char* str)
 * @brief Insert a string at a specific position.
 * @param buffer The buffer.
 * @param index The index.
 * @param str The str.
 * @return 0 on success, -1 else (see errno).
 */
int estr_insert(estr_t buffer, size_t index, char* str) {
  struct estr_s *e = (struct estr_s*) buffer;
  char *tmp;
  valid_ret(e, -1);
  if(index >= estr_length(e) || !e->length) {
    errno = EINVAL;
    return -1;
  }
  if(index == estr_length(e))
    return estr_append(buffer, str);
  tmp = malloc((e->length - index) + 1);
  memcpy(tmp, e->buffer + index, e->length - index);
  tmp[e->length - index] = 0;
  bzero(e->buffer + index, e->length - index);
  e->length = strlen(e->buffer) + 1;
  estr_append(e, str);
  estr_append(e, tmp);
  free(tmp);
  return 0;
}

/**
 * @fn int estr_printf(estr_t buffer, const char* fmt, ...)
 * @brief Simple printf into the estr.
 * @param buffer The buffer.
 * @param fmt The format.
 * @param ... The arguments.
 * @return 0 on success, -1 else (see errno).
 */
int estr_printf(estr_t buffer, const char* fmt, ...) {
  int ret;
  va_list pa;
  va_start(pa, fmt);
  ret = estr_vprintf(buffer, fmt, pa);
  va_end(pa);
  return ret;
}

/**
 * @fn int estr_vprintf(estr_t buffer, const char* fmt, va_list pa)
 * @brief Simple printf into the estr.
 * @param buffer The buffer.
 * @param fmt The format.
 * @param pa The arguments.
 * @return 0 on success, -1 else (see errno).
 */
int estr_vprintf(estr_t buffer, const char* fmt, va_list pa) {
  struct estr_s *e = (struct estr_s*) buffer;
  estr_t tmp= NULL;
  char *p, c;
  int i, count, idx;
  valid_ret(e, -1);
  tmp = estr_new();
  p = (char*)fmt;
  estr_clear(e);
  while(*p != '\0') {
    if(*p == '%') {
      p++;
      if((*p) == '#') { /* %#x */
        estr_append(e, "0x");
        p++;
      }
      /* %02x */
      if((isdigit(*p) || *p == ' ') && isdigit(*p+1)) {
        c = *p;
        count = (*p+1) - '0';
        for(idx = 0; idx < count; idx++)
          estr_append_char(e, c);
        p+=2;
      }
      switch (*p) {
        case '%' :
          estr_append_char(e, *p);
          break;
        case 'c' :
          estr_append_char(e, (char)va_arg(pa, int));/* !!!!! */
          break;
        case 'd' :
        case 'i' :
          i = va_arg(pa, int);
          if(i<0){
            i=-i;
            estr_append_char(e, '-');
          }
          estr_append_int(e, i, 10);
          break;
        case 'u' :
          estr_append_uint(e, va_arg(pa, unsigned int), 10);
          break;
        case 'o' :
          estr_append_uint(e, va_arg(pa, unsigned int), 8);
          break;
        case 'p' :
        case 'x' :
          estr_append_uint(e, va_arg(pa, unsigned int), 16);
          break;
        case 'X' :
          estr_clear(tmp);
          estr_append_int(tmp, va_arg(pa, int), 16);
          estr_toupper(tmp);
          estr_appends(e, tmp);
          break;
        case 'f' :
          estr_append_float(e, va_arg(pa, double));
          break;
        case 's' :
          estr_append(e, va_arg(pa, char*));
          break;
        default:
          estr_append_char(e, *p); 
      } /* end switch */
    }
    else {
      estr_append_char(e, *p);
    }
    p++;
  }
  estr_delete(tmp);
  return 0;
}

/**
 * @fn void estr_tolower(estr_t buffer)
 * @brief Convert a string in lower case.
 * @param buffer The buffer to convert.
 */
void estr_tolower(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  size_t i = 0;
  char c = 0;
  valid_noret(e);
  for(i = 0; i < e->length; i++) {
    c = e->buffer[i];
    if(c >= 65 && c <= 90) c += 32;
    e->buffer[i] = c;
  }
}

/**
 * @fn void estr_toupper(estr_t buffer)
 * @brief Convert a string in upper case.
 * @param buffer The buffer to convert.
 */
void estr_toupper(estr_t buffer) {
  struct estr_s *e = (struct estr_s*) buffer;
  size_t i = 0;
  char c = 0;
  valid_noret(e);
  for(i = 0; i < e->length; i++) {
    c = e->buffer[i];
    if(c >= 97 && c <= 122) c -= 32;
    e->buffer[i] = c;
  }
}

/**
 * @fn char* estr_substring_c(const char* buffer, size_t begin, size_t len)
 * @brief Substract a string.
 * @param buffer Input string.
 * @param begin Begin index.
 * @param len Length.
 * @return substring (free required).
 */
char* estr_substring_c(const char* buffer, size_t begin, size_t len) {
  size_t l = buffer ? strlen(buffer) : 0; 
  if (!l || l < begin || l < (begin+len)) 
    return NULL; 
  return strndup(buffer + begin, len); 
}

/**
 * @fn char* estr_substring(const char* str, size_t begin, size_t len)
 * @brief Substract a string.
 * @param str Input string.
 * @param begin Begin index.
 * @param len Length.
 * @return substring (free required).
 */
char* estr_substring(estr_t buffer, size_t begin, size_t len)  { 
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, NULL);
  if (estr_length(e) < begin || estr_length(e) < (begin+len)) 
    return NULL; 
  return strndup(e->buffer + begin, len); 
}


/**
 * @fn estr_t estr_substr(const char* str, size_t begin, size_t len)
 * @brief Substract a string.
 * @param str Input string.
 * @param begin Begin index.
 * @param len Length.
 * @return estr_delete required.
 */
estr_t estr_substr(estr_t buffer, size_t begin, size_t len)  { 
  char* tmp;
  struct estr_s *t = NULL, *e = (struct estr_s*) buffer;
  valid_ret(e, NULL);
  tmp = estr_substring(buffer, begin, len);
  if(tmp) {
    t = estr_new_string(tmp);
    free(tmp);
  }
  return t; 
}


/**
 * @fn int estr_indexof(estr_t buffer, const char* needed)
 * @brief Search the index of the needed string into the input string.
 * @param buffer Search string.
 * @param needed Needed string.
 * @return -1 if not found else 0.
 */
int estr_indexof(estr_t buffer, const char* needed) {
  char* found;
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  if(!needed) return -1;
  found = strstr(e->buffer, needed);
  if(found != NULL)  return found - e->buffer;
  return -1;
}

/**
 * @fn size_t estr_count(estr_t buffer, const char needed)
 * @brief Count the number of occurences of the needed char.
 * @param buffer Search string.
 * @param needed The char.
 * @return Occurences number.
 */
size_t estr_count(estr_t buffer, const char needed) {
  size_t i, count = 0;
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  for(i = 0; i < e->length; i++)
    if(e->buffer[i] == needed) count++;
  return count;
}


/**
 * @fn _Bool estr_isint(const char* source)
 * @brief Test if the string is a valid digit.
 * @param source The source string
 * @return 1 if the string is a valid int.
 */
_Bool estr_isint(estr_t buffer) {
  size_t i, off = 0;
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  if(e->buffer[0] == '-') off = 1;
  for(i = off; i < e->length; i++)
    if(!isdigit(e->buffer[i]))
      return 0;
  return 1;
}

/**
 * @fn int estr_append_float(estr_t buffer, double value)
 * @brief Append a float to the buffer.
 * @param buffer The buffer.
 * @param value The value to append.
 * @return 0 on success, -1 else (see errno).
 */
int estr_append_float(estr_t buffer, double value) {
  char tmp[40];
  bzero(tmp, 40);
  snprintf(tmp, 40, "%f", value);
  return estr_append(buffer, tmp);
}

/**
 * @fn int estr_append_uint(estr_t buffer, unsigned int value, int base)
 * @brief Append an unsigned int to the buffer.
 * @param buffer The buffer.
 * @param value The value to append.
 * @param base The int base.
 * @return 0 on success, -1 else (see errno).
 */
int estr_append_uint(estr_t buffer, unsigned int value, int base) {
  const char* tmp = estr_convert(value, base);
  if(tmp != NULL)
    return estr_append(buffer, tmp);
  return -1;
}

/**
 * @fn int estr_append_int(estr_t buffer, unsigned int value, int base)
 * @brief Append an int to the buffer.
 * @param buffer The buffer.
 * @param value The value to append.
 * @param base The int base.
 * @return 0 on success, -1 else (see errno).
 */
int estr_append_int(estr_t buffer, int value, int base) {
  const char* tmp = estr_convert(value, base);
  if(tmp != NULL)
    return estr_append(buffer, tmp);
  return -1;
}

/**
 * @fn int estr_to_int(estr_t buffer, int def)
 * @brief Convert a string int to an int value.
 * @param buffer Src string.
 * @param def the default value on error
 * @return the int value.
 */
int estr_to_int(estr_t buffer, int def) {
  int n;
  struct estr_s *e = (struct estr_s*) buffer;
  errno = 0;
  valid_ret(e, def);
  n = strtol(e->buffer, NULL, 10);
  if((errno == ERANGE) || (errno == EINVAL))
    return def;
  return n;
}

/**
 * @fn unsigned long int estr_to_long(estr_t buffer, unsigned long int def)
 * @brief Convert a string int to an int value.
 * @param buffer Src string.
 * @param def the default value on error
 * @return the int value.
 */
unsigned long int estr_to_long(estr_t buffer, unsigned long int def) {
  unsigned long int n;
  struct estr_s *e = (struct estr_s*) buffer;
  errno = 0;
  valid_ret(e, def);
  n = strtoll(e->buffer, NULL, 10);
  if((errno == ERANGE) || (errno == EINVAL))
    return def;
  return n;
}

/**
 * @fn _Bool estr_match(const char* str, const char* regex)
 * @brief Test if the regex match with the input string.
 * @param buffer The string to test.
 * @param regex The regex
 * @return 1 if the regex match else 0.
 */
_Bool estr_match(estr_t buffer, const char* regex) {
  regex_t preg;
  char *text;
  size_t size;
  int err, match;
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  err = regcomp(&preg, regex, REG_NOSUB|REG_EXTENDED);
  if(!err) {
    match = regexec(&preg, e->buffer, 0, NULL, 0);
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
 * @brief Convert an size_t in string.
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
 * @fn _Bool estr_startswith(estr_t buffer, const char *prefix)
 * @brief Test if the string starts with the prefix.
 * @param str The source string.
 * @param prefix The prefix string to find.
 * @return true/false
 */
_Bool estr_startswith(estr_t buffer, const char *prefix) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  return estr_startswith_c(e->buffer, e->length, prefix);
}

/**
 * @fn _Bool estr_endswith(estr_t buffer, const char *suffix)
 * @brief Test if the string ends with the suffix.
 * @param str The source string.
 * @param suffix The suffix string to find.
 * @return true/false
 */
_Bool estr_endswith(estr_t buffer, const char *suffix) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, 0);
  return estr_endswith_c(e->buffer, e->length, suffix);
}

/**
 * @fn _Bool estr_startswith_c(const char* buffer, size_t length, const char *prefix)
 * @brief Test if the string starts with the prefix.
 * @param str The source string.
 * @param length The buffer length.
 * @param prefix The prefix string to find.
 * @return true/false
 */
_Bool estr_startswith_c(const char* buffer, size_t length, const char *prefix) {
  size_t prefix_l;
  if(!prefix) return 0;
  prefix_l = strlen(prefix);
  return length < prefix_l ? 0 : strncmp(prefix, buffer, prefix_l) == 0;
}

/**
 * @fn _Bool estr_endswith_c(const char* buffer, size_t length, const char *suffix)
 * @brief Test if the string ends with the suffix.
 * @param str The source string.
 * @param length The buffer length.
 * @param suffix The suffix string to find.
 * @return true/false
 */
_Bool estr_endswith_c(const char* buffer, size_t length, const char *suffix) {
  size_t suffix_l;
  suffix_l = strlen(suffix);
  if(suffix_l > length) return 0;
  return strncmp(buffer + length - suffix_l, suffix, suffix_l) == 0;
}

/*******************************************************************************
 * ___________     __                  
 * \__    ___/___ |  | __ ____   ____  
 *   |    | /  _ \|  |/ // __ \ /    \ 
 *   |    |(  <_> )    <\  ___/|   |  \
 *   |____| \____/|__|_ \\___  >___|  /
 *                     \/    \/     \/ 
 ********************************************************************************/

/**
 * @fn int estr_split_with_buffer(estr_token_t token, estr_t buffer, const char* sep)
 * @brief Split a str buffer to a token instance.
 * @param token The token instance.
 * @param buffer The string buffer.
 * @param sep The split separator.
 * @return 0 on success, -1 else (see errno).
 */
int estr_split_with_buffer(estr_token_t token, estr_t buffer, const char* sep) {
  struct estr_s *e = (struct estr_s*) buffer;
  valid_ret(e, -1);
  return estr_split(token, e->buffer, sep);
}

/**
 * @fn int estr_split(estr_token_t token, const char* buffer, const char* sep)
 * @brief Split a str to a token instance.
 * @param token The token instance.
 * @param buffer The string to split.
 * @param sep The split separator.
 * @return 0 on success, -1 else (see errno).
 */
int estr_split(estr_token_t token, const char* buffer, const char* sep) {
  struct estr_token_s *tok = (struct estr_token_s*) token;
  errno = 0; /* reset errno */
  if(!token || !buffer || !sep) {
    errno = EINVAL;
    return -1;
  }
  tok->buffer = (char*)buffer;
  tok->sep = (char*)sep;
  tok->len = strlen(buffer);
  tok->offset = 0;
  return 0;
}

/**
 * @fn size_t estr_token_count(estrtoken_t tok)
 * @brief Count the number of tokens.
 * @param tok Token pointer.
 * @return The number of tokens.
 */
size_t estr_token_count(estr_token_t tok) {
  size_t offset, count = 0;
  struct estr_token_s *t = (struct estr_token_s *)tok;
  errno = 0; /* reset errno */
  if(!t) {
    errno = EINVAL;
    return 0;
  }
  offset = t->offset;
  t->offset = 0;
  while(estr_token_has_more(t)) {
    estr_token_next(t);
    count++;
  }
  t->offset = offset;
  return count;
}


/**
 * @fn _Bool estr_token_has_more(estr_token_t tok)
 * @brief Test if the token contains more tokens.
 * @param tok Token pointer.
 * @return 1 if has more else 0.
 */
_Bool estr_token_has_more(estr_token_t tok) {
  struct estr_token_s *t = (struct estr_token_s *)tok;
  errno = 0; /* reset errno */
  if(!t) {
    errno = EINVAL;
    return 0;
  }
  return t->offset < t->len;
}

/**
 * @fn static int estr_token_split_condition(char c, char* sep)
 * @brief Test if the condition can be splited.
 * @param c Char to test.
 * @param sep Delimiter.
 */
static int estr_token_split_condition(char c, char* sep) {
  unsigned int i;
  for (i = 0; i< strlen(sep); i++)
    if (c == sep[i]) return 1;
  return 0; /* no matches*/
}

/**
 * @fn char* estr_token_next(estr_token_t tok)
 * @brief Get the next token.
 * @param tok Token pointer
 * @return New token else NULL (free is required for non NULL values)
 */
char* estr_token_next(estr_token_t tok) {
  char c, *s;
  int i = 0, end = 0;
  struct estr_token_s *t = (struct estr_token_s *)tok;
  errno = 0; /* reset errno */
  if(!t) {
    errno = EINVAL;
    return 0;
  }
  /* search the next split */
  /* check immediate end of look */
  if (!estr_token_has_more(tok))
    return NULL;
  while (!end) {
    /* check end of look */
    if (t->offset + i >= t->len)
      break;
    /* look next char */
    c = t->buffer[t->offset + i];
    if (estr_token_split_condition(c, t->sep)) {
      /* split here */
      end = 1;
    }
    else i++;
  }
  s = estr_substring_c(t->buffer, t->offset, i);
  t->offset += i + 1; /* go just after the sep */
  if(!strlen(s)) {
    free(s);
    s = estr_token_next(tok);
  }
  return s;
}


