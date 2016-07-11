/**
*******************************************************************************
* @file estrtoken.h
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
#ifndef __ESTRTOKEN_H__
#define __ESTRTOKEN_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  #include <string.h>
  #include <stdbool.h>
  
  typedef void* estrtoken_t;

  /**
   * @fn estrtoken_t estrtoken_init(const char* str, const char* sep)
   * @brief Initialisation of the string token.
   * @param str String to use.
   * @param sep Delimiter.
   * @return Get a token pointer else NULL on error.
   */
  estrtoken_t estrtoken_init(const char* str, const char* sep);

  /**
   * @fn void estrtoken_release(estrtoken_t tok)
   * @brief Release the token.
   * @param tok Token pointer.
   */
  void estrtoken_release(estrtoken_t tok);

  /**
   * @fn _Bool estrtoken_has_more_tokens(estrtoken_t tok)
   * @brief Test if the token contains more tokens.
   * @param tok Token pointer.
   * @return 1 if has more else 0.
   */
  _Bool estrtoken_has_more_tokens(estrtoken_t tok);

  /**
   * @fn unsigned int estrtoken_count(estrtoken_t tok)
   * @brief Count the number of tokens.
   * @param tok Token pointer.
   * @return The number of tokens.
   */
  unsigned int estrtoken_count(estrtoken_t tok);

  /**
   * @fn char* estrtoken_next_token(estrtoken_t tok)
   * @brief Get the next token.
   * @param tok Token pointer
   * @return New token else NULL (free is required for non NULL values)
   */
  char* estrtoken_next_token(estrtoken_t tok);

  /**
   * @fn void estrtoken_set_separator(estrtoken_t tok, char* sep)
   * @brief update the delimiter.
   * @param tok Token pointer.
   * @param sep New delmiter.
   */
  void estrtoken_set_separator(estrtoken_t tok, char* sep);

  /**
   * @fn int estrtoken_split_condition(char c, char* sep)
   * @brief Test if the condition can be splited.
   * @param c Char to test.
   * @param sep Delimiter.
   */
  int estrtoken_split_condition(char c, char* sep);
  
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESTRTOKEN_H__ */
