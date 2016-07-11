/**
*******************************************************************************
* @file estrtoken.c
* @brief String tokenizer.
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
#include <errno.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    char*    str;
    char*    sep;
    unsigned int len;
    unsigned int offset;
} estrtoken_handle_t;

/**
 * @fn estrtoken_t estrtoken_init(const char* str, const char* sep)
 * @brief Initialisation of the string token.
 * @param str String to use.
 * @param sep Delimiter.
 * @return Get a token pointer else NULL on error.
 */
estrtoken_t estrtoken_init(const char* str, const char* sep) {
  estrtoken_handle_t *tok = malloc(sizeof(estrtoken_handle_t));
  tok->str = (char*)str;
  tok->sep = (char*)sep;
  tok->len = strlen(str);
  tok->offset = 0;
  return tok;
}

/**
 * @fn unsigned int estrtoken_count(estrtoken_t tok)
 * @brief Count the number of tokens.
 * @param tok Token pointer.
 * @return The number of tokens.
 */
unsigned int estrtoken_count(estrtoken_t tok) {
  unsigned int offset, count = 0;
  estrtoken_handle_t *t = (estrtoken_handle_t *)tok;
  if(!t) return 0;
  offset = t->offset;
  t->offset = 0;
  while(estrtoken_has_more_tokens(t)) {
    estrtoken_next_token(t);
    count++;
  }
  t->offset = offset;
  return count;
}

/**
 * @fn void estrtoken_release(estrtoken_t tok)
 * @brief Release the token.
 * @param tok Token pointer.
 */
void estrtoken_release(estrtoken_t tok) {
  free(tok);
}


/**
 * @fn _Bool estrtoken_has_more_tokens(estrtoken_t tok)
 * @brief Test if the token contains more tokens.
 * @param tok Token pointer.
 * @return 1 if has more else 0.
 */
_Bool estrtoken_has_more_tokens(estrtoken_t tok) {
  estrtoken_handle_t *t = (estrtoken_handle_t *)tok;
  if(!t) return 0;
  return t->offset < t->len;
}

/**
 * @fn char* estrtoken_next_token(estrtoken_t tok)
 * @brief Get the next token.
 * @param tok Token pointer
 * @return New token else NULL (free is required for non NULL values)
 */
char* estrtoken_next_token(estrtoken_t tok) {
  char c;
  char* s;
  int i = 0;
  int end = 0;
  estrtoken_handle_t *t = (estrtoken_handle_t *)tok;
  if(!t) return NULL;
  /* search the next split */
  /* check immediate end of look */
  if (!estrtoken_has_more_tokens(tok))
    return NULL;
  while (!end) {
    /* check end of look */
    if (t->offset + i >= t->len)
      break;
    /* look next char */
    c = t->str[t->offset + i];
    if (estrtoken_split_condition(c, t->sep)) {
      /* split here */
      end = 1;
    }
    else i++;
  }
  s = estr_substring(t->str, t->offset, i);
  t->offset += i + 1; /* go just after the sep */
  if(!strlen(s)) {
    free(s);
    s = estrtoken_next_token(tok);
  }
  return s;
}


/**
 * @fn void estrtoken_set_separator(estrtoken_t tok, char* sep)
 * @brief update the delimiter.
 * @param tok Token pointer.
 * @param sep New delmiter.
 */
void estrtoken_set_separator(estrtoken_t tok, char* sep) {
  estrtoken_handle_t *t = (estrtoken_handle_t *)tok;
  t->sep = sep;
}

/**
 * @fn int estrtoken_split_condition(char c, char* sep)
 * @brief Test if the condition can be splited.
 * @param c Char to test.
 * @param sep Delimiter.
 */
int estrtoken_split_condition(char c, char* sep) {
  unsigned int i;
  for (i = 0; i< strlen(sep); i++)
    if (c== sep[i]) return 1;
  return 0; /* no matches*/
}

