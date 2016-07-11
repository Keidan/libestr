/**
*******************************************************************************
* @file estrbuffer.c
* @brief Dynamic string buffer.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define SMAGIC 0x8001
#define EMAGIC 0x1337

struct estrbuffer_s {
    int smagic;
    char* str;
    unsigned int length;
    unsigned int alength;
    int emagic;
};

/**
 * @fn shell_term_t estrbuffer_new()
 * @brief New shell buffer.
 */
estrbuffer_t estrbuffer_new() {
  struct estrbuffer_s *b = malloc(sizeof(struct estrbuffer_s));
  if(!b) {
    fprintf(stderr, "%s: Not enough memory.\n", __func__);
    return NULL;
  }
  memset(b, 0, sizeof(struct estrbuffer_s));
  b->smagic = SMAGIC;
  b->emagic = EMAGIC;
  estrbuffer_set_capacity(b, 1);
  b->str[0] = 0;
  return b;
}

/**
 * @fn void estrbuffer_delete(estrbuffer_t buffer)
 * @brief Delete shell buffer.
 * @param buffer The buffer pointer.
 */
void estrbuffer_delete(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(b) {
    if(b->smagic != SMAGIC || b->emagic != EMAGIC) {
      fprintf(stderr, "%s: Currupted buffer detected.\n", __func__);
      return;
    }
    if(b->str) free(b->str), b->str = NULL;
    b->length = b->alength = 0;
    free(b);
  }
}

/**
 * @fn void estrbuffer_clear(estrbuffer_t buffer)
 * @brief Clear the buffer.
 * @param buffer The buffer pointer.
 */
void estrbuffer_clear(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b || !b->str) return;
  bzero(b->str, b->length);
  b->length = 0;
}

/**
 * @fn char* estrbuffer_to_str(estrbuffer_t buffer)
 * @brief Get the buffer to char* format.
 * @param buffer The buffer.
 * @return The char* (can be NULL)
 */
char* estrbuffer_to_str(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b) return NULL;
  return b->str;
}

/**
 * @fn unsigned int estrbuffer_length(estrbuffer_t buffer)
 * @brief Get the buffer length.
 * @param buffer The buffer.
 * @return The length
 */
unsigned int estrbuffer_length(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b) return 0;
  return b->length;
}

/**
 * @fn unsigned int estrbuffer_capacity(estrbuffer_t buffer)
 * @brief Get the buffer capacity.
 * @param buffer The buffer.
 * @return The capacity
 */
unsigned int estrbuffer_capacity(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b) return 0;
  return b->alength ? b->alength - 1 : 0;
}


/**
 * @fn int estrbuffer_set_capacity(estrbuffer_t buffer, unsigned int capacity)
 * @brief Change the buffer capacity.
 * @param buffer The buffer.
 * @param capacity The buffer capacity.
 * @return -1 on error else 0.
 */
int estrbuffer_set_capacity(estrbuffer_t buffer, unsigned int capacity) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  char* tmp;
  if(!b) return -1;
  if((b->alength - 1) == capacity) return 0;
  tmp = (char*)realloc(b->str, capacity + 1);
  if(!tmp) {
    fprintf(stderr, "%s: Not enough memory.\n", __func__);
    return -1;
  }

  b->alength = capacity + 1;
  b->str = tmp;
  b->str[capacity] = 0;
  return 0;
}

/**
 * @fn int estrbuffer_append_char(estrbuffer_t shell, const char c)
 * @brief Append a char into the buffer.
 * @param buffer The buffer.
 * @param c The char to append.
 * @return -1 on error else 0.
 */
int estrbuffer_append_char(estrbuffer_t buffer, const char c) {
  char cc[2];
  cc[0] = c;
  cc[1] = 0;
  return estrbuffer_append(buffer, cc);
}

/**
 * @fn int estrbuffer_append(estrbuffer_t shell, const char* str)
 * @brief Append a string into the buffer.
 * @param buffer The buffer.
 * @param str The string to append.
 * @return -1 on error else 0.
 */
int estrbuffer_append(estrbuffer_t buffer, const char* str) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  unsigned int slen = 0, diff;
  char* tmp;
  if(!b) return -1;
  if(!str) return -1;
  slen = strlen(str);
  if(!b->alength) {
    b->alength = slen + 1;
    b->length = b->alength - 1;
    b->str = (char*)malloc(b->alength);
    if(!b->str) {
      fprintf(stderr, "%s: Not enough memory.\n", __func__);
      b->length = b->alength = 0;
      return -1;
    }
    bzero(b->str, b->alength);
    strncpy(b->str, str, b->length);
  } else if((strlen(b->str) + slen) <= b->alength) {
    b->length += slen;
    strncat(b->str, str, b->length);
  } else {
    diff = abs(b->alength - (b->length + slen)) + 1;
    b->alength += diff;
    b->length = b->alength;/*strlen(b->str) + slen;*/
    tmp = (char*)realloc(b->str, b->alength);
    if(!tmp) {
      fprintf(stderr, "%s: Not enough memory.\n", __func__);
      b->alength -= diff;
      b->length = b->alength - 1;
      return -1;
    }
    b->str = tmp;
    strncat(b->str, str, b->length);
  }
  return 0;
}

/**
 * @fn int estrbuffer_copy_char(estrbuffer_t shell, const char c)
 * @brief Erase the buffer with the copy char.
 * @param buffer The buffer.
 * @param c The char to copy.
 * @return -1 on error else 0.
 */
int estrbuffer_copy_char(estrbuffer_t buffer, const char c) {
  char cc[2];
  cc[0] = c;
  cc[1] = 0;
  return estrbuffer_copy(buffer, cc);
}

/**
 * @fn int estrbuffer_copy(estrbuffer_t shell, const char* str)
 * @brief Erase the buffer with the copy string.
 * @param buffer The buffer.
 * @param str The string to copy.
 * @return -1 on error else 0.
 */
int estrbuffer_copy(estrbuffer_t buffer, const char* str) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b) return -1;
  estrbuffer_clear(b);
  return estrbuffer_append(b, str);
}

/**
 * @fn int estrbuffer_trim_to_size(estrbuffer_t buffer)
 * @brief Trim the buffer allocation size to the buffer size.
 * @param buffer The buffer.
 * @return -1 on error else 0.
 */
int estrbuffer_trim_to_size(estrbuffer_t buffer) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b || !b->str) return -1;
  if(!b->alength) return 0;
  if((b->alength - 1) == b->length) return 0;
  b->length = strlen(b->str);
  return estrbuffer_set_capacity(b, b->length);
}

/**
 * @fn int estrbuffer_erase2(estrbuffer_t buffer, unsigned int index)
 * @brief Erase a string.
 * @param buffer The buffer.
 * @param index The index.
 * @return -1 on error else 0.
 */
int estrbuffer_erase2(estrbuffer_t buffer, unsigned int index) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b || index > b->length || !b->length)
    return -1;
  bzero(b->str + index, b->length - index);
  b->length = strlen(b->str);
  return 0;
}

/**
 * @fn int estrbuffer_erase(estrbuffer_t buffer, unsigned int index, unsigned int length)
 * @brief Erase a string.
 * @param buffer The buffer.
 * @param index The start index.
 * @param length The length.
 * @return -1 on error else 0.
 */
int estrbuffer_erase(estrbuffer_t buffer,unsigned int index, unsigned int length) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  if(!b || (index+length) > b->length || !b->length)
    return -1;
  memcpy(b->str+index, b->str + index + length, b->length - (index + length));
  bzero(b->str + b->length - length, length);
  b->length = strlen(b->str);
  return 0;
}

/**
 * @fn int estrbuffer_insert(estrbuffer_t buffer, unsigned int index, char* str)
 * @brief Insert a string from a specific position.
 * @param buffer The buffer.
 * @param index The index.
 * @param str The str.
 * @return -1 on error else 0.
 */
int estrbuffer_insert(estrbuffer_t buffer, unsigned int index, char* str) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  char *tmp;
  if(!b || index > b->length || !b->length)
    return -1;
  if(index == b->length)
    return estrbuffer_append(buffer, str);
  tmp = malloc(b->length - index);
  memcpy(tmp, b->str + index, b->length - index);
  tmp[b->length - index] = 0;
  bzero(b->str + index, b->length - index);
  b->length = strlen(b->str);
  estrbuffer_append(b, str);
  estrbuffer_append(b, tmp);
  free(tmp);
  return 0;
}

/**
 * @fn int estrbuffer_printf(estrbuffer_t buffer, const char* fmt, ...)
 * @brief Simple printf into the estrbuffer.
 * @param buffer The buffer.
 * @param fmt The format.
 * @param ... The arguments.
 * @return -1 on error else 0.
 */
int estrbuffer_printf(estrbuffer_t buffer, const char* fmt, ...) {
  int ret;
  va_list pa;
  va_start(pa, fmt);
  ret = estrbuffer_vprintf(buffer, fmt, pa);
  va_end(pa);
  return ret;
}

/**
 * @fn int estrbuffer_vprintf(estrbuffer_t buffer, const char* fmt, va_list pa)
 * @brief Simple printf into the estrbuffer.
 * @param buffer The buffer.
 * @param fmt The format.
 * @param pa The arguments.
 * @return -1 on error else 0.
 */
int estrbuffer_vprintf(estrbuffer_t buffer, const char* fmt, va_list pa) {
  struct estrbuffer_s *b = (struct estrbuffer_s*) buffer;
  unsigned int ltmp = 40;
  char *p, c, tmp[40];
  int i, count, idx;
  if(!b) return -1;
  /*estrbuffer_clear(b);*/
  p = (char*)fmt;
  while(*p != '\0') {
    if(*p == '%') {
      p++;
      if((*p) == '#') { /* %#x */
        estrbuffer_append(b, "0x");
        p++;
      }
      /* %02x */
      if((isdigit(*p) || *p == ' ') && isdigit(*p+1)) {
        c = *p;
        count = (*p+1) - '0';
        for(idx = 0; idx < count; idx++)
          estrbuffer_append_char(b, c);
        p+=2;
      }
      switch (*p) {
        case '%' :
          estrbuffer_append_char(b, *p);
          break;
        case 'c' :
          estrbuffer_append_char(b, (char)va_arg(pa, int));/* !!!!! */
          break;
        case 'd' :
        case 'i' :
          i = va_arg(pa, int);
          if(i<0){
            i=-i;
            estrbuffer_append_char(b, '-');
          }
          estrbuffer_append(b, estr_convert(i, 10));
          break;
        case 'u' :
          estrbuffer_append(b, estr_convert(va_arg(pa, unsigned int), 10));
          break;
        case 'o' :
          estrbuffer_append(b, estr_convert(va_arg(pa, unsigned int), 8));
          break;
        case 'p' :
        case 'x' :
          estrbuffer_append(b, estr_convert(va_arg(pa, unsigned int), 16));
          break;
        case 'X' :
          bzero(tmp, ltmp);
          estr_toupper(estr_convert(va_arg(pa, int), 16), tmp);
          estrbuffer_append(b, tmp);
          break;
        case 'f' :
          bzero(tmp, ltmp);
          snprintf(tmp, ltmp, "%f", va_arg(pa, double));/* !!!!! */
          estrbuffer_append(b, tmp);
          break;
        case 's' :
          estrbuffer_append(b, va_arg(pa, char *)); 
          break;
        default:
          estrbuffer_append_char(b, *p); 
      } /* end switch */
    }
    else {
      estrbuffer_append_char(b, *p);
    }
    p++;
  }
  return 0;
}
