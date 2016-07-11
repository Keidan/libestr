/**
*******************************************************************************
* @file estr.h
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
#ifndef __ESTR_H__
#define __ESTR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  #include <string.h>
  #include <stdbool.h>
  #include <stdarg.h>
 
 
  /*****************************************************
   *   _________ __         .__                
   *  /   _____//  |________|__| ____    ____  
   *  \_____  \\   __\_  __ \  |/    \  / ___\ 
   *  /        \|  |  |  | \/  |   |  \/ /_/  >
   * /_______  /|__|  |__|  |__|___|  /\___  / 
   *         \/                     \//_____/                        
   *****************************************************/ 
   
  /**
   * @fn char* estr_substring(const char* str, size_t begin, size_t len)
   * @brief Substract a string.
   * @param str Input string.
   * @param begin Begin index.
   * @param len Length.
   * @return substring (free required).
   */
  char* estr_substring(const char* str, size_t begin, size_t len);

  /**
   * @fn int estr_indexof(const char* source, const char* needed)
   * @brief Search the index of the needed string into the input string.
   * @param source Search string.
   * @param needed Needed string.
   * @return -1 if not found else 0.
   */
  int estr_indexof(const char* source, const char* needed);

  /**
   * @fn size_t estr_count(const char* source, const char needed)
   * @brief Count the number of occurences of the needed char.
   * @param source Search string.
   * @param needed The char.
   * @return Occurences number.
   */
  size_t estr_count(const char* source, const char needed);

  /**
   * @fn _Bool estr_isint(const char* source)
   * @brief Test if the string is a valid digit.
   * @param source The source string
   * @return 1 if the string is a valid int.
   */
  _Bool estr_isint(const char* source);


  /**
   * @fn void estr_tolower(const char* source, char* dest)
   * @brief Convert a string in lower case.
   * @param source Source string.
   * @param dest Destination string.
   */
  void estr_tolower(const char* source, char* dest);

  /**
   * @fn void estr_toupper(const char* source, char* dest)
   * @brief Convert a string in upper case.
   * @param source Source string.
   * @param dest Destination string.
   */
  void estr_toupper(const char* source, char* dest);

  /**
   * @fn int estr_parse_int(char* str, int def)
   * @brief Convert a string int to an int value.
   * @param str Src string.
   * @param def the default value on error
   * @return the int value.
   */
  int estr_parse_int(char* str, int def);

  /**
   * @fn unsigned long int estr_parse_long(char* str, unsigned long int def)
   * @brief Convert a string long to a long value.
   * @param str Src string.
   * @param def the default value on error
   * @return the long value.
   */
  unsigned long int estr_parse_long(char* str, unsigned long int def);

  /**
   * @fn _Bool estr_match(const char* str, const char* regex)
   * @brief Test if the regex match with the input string.
   * @param str The string to test.
   * @param regex The regex
   * @return 1 if the regex match else 0.
   */
  _Bool estr_match(const char* str, const char* regex);

  /**
   * @fn const char* estr_convert(unsigned long num, int base)
   * @brief Convert an unsigned int in string.
   * @param num The uint
   * @param base The desired base.
   * @return The string.
   */
  const char* estr_convert(unsigned long num, int base);

  /**
   * @fn const char* estr_hex2bin(const char* numstr)
   * @brief Convert and hexa string in binary value.
   * @param hexstr The hex string.
   * @return The binary representation.
   */
  const char* estr_hex2bin(const char* hexstr);

  /**
   * @fn _Bool estr_startswith(const char *str, const char *prefix)
   * @brief Test if the string starts with the prefix.
   * @param str The source string.
   * @param prefix The prefix string to find.
   * @return true/false
   */
  _Bool estr_startswith(const char *str, const char *prefix);

  /**
   * @fn _Bool estr_endswith(const char *str, const char *suffix)
   * @brief Test if the string ends with the suffix.
   * @param str The source string.
   * @param suffix The suffix string to find.
   * @return true/false
   */
  _Bool estr_endswith(const char *str, const char *suffix);
  
  
  /*****************************************************
   *   _________ __         .__             ___________     __                  
   *  /   _____//  |________|__| ____    ___\__    ___/___ |  | __ ____   ____  
   *  \_____  \\   __\_  __ \  |/    \  / ___\|    | /  _ \|  |/ // __ \ /    \ 
   *  /        \|  |  |  | \/  |   |  \/ /_/  >    |(  <_> )    <\  ___/|   |  \
   * /_______  /|__|  |__|  |__|___|  /\___  /|____| \____/|__|_ \\___  >___|  /
   *         \/                     \//_____/                   \/    \/     \/                        
   *****************************************************/ 
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
  
  
  /*****************************************************
   *   _________ __         .__              __________        _____  _____             
   *  /   _____//  |________|__| ____    ____\______   \__ ___/ ____\/ ____\___________ 
   *  \_____  \\   __\_  __ \  |/    \  / ___\|    |  _/  |  \   __\\   __\/ __ \_  __ \
   *  /        \|  |  |  | \/  |   |  \/ /_/  >    |   \  |  /|  |   |  | \  ___/|  | \/
   * /_______  /|__|  |__|  |__|___|  /\___  /|______  /____/ |__|   |__|  \___  >__|   
   *         \/                     \//_____/        \/                        \/      
   *****************************************************/

  typedef void* estrbuffer_t;

  /**
   * @fn shell_term_t estrbuffer_new()
   * @brief New shell buffer.
   */
  estrbuffer_t estrbuffer_new();

  /**
   * @fn void estrbuffer_delete(estrbuffer_t buffer)
   * @brief Delete shell buffer.
   * @param buffer The buffer pointer.
   */
  void estrbuffer_delete(estrbuffer_t buffer);

  /**
   * @fn void estrbuffer_clear(estrbuffer_t buffer)
   * @brief Clear the buffer.
   * @param buffer The buffer pointer.
   */
  void estrbuffer_clear(estrbuffer_t buffer);

  /**
   * @fn char* estrbuffer_to_str(estrbuffer_t buffer)
   * @brief Get the buffer to char* format.
   * @param buffer The buffer.
   * @return The char* (can be NULL)
   */
  char* estrbuffer_to_str(estrbuffer_t buffer);

  /**
   * @fn unsigned int estrbuffer_length(estrbuffer_t buffer)
   * @brief Get the buffer length.
   * @param buffer The buffer.
   * @return The length
   */
  unsigned int estrbuffer_length(estrbuffer_t buffer);

  /**
   * @fn unsigned int estrbuffer_capacity(estrbuffer_t buffer)
   * @brief Get the buffer capacity.
   * @param buffer The buffer.
   * @return The capacity
   */
  unsigned int estrbuffer_capacity(estrbuffer_t buffer);

  /**
   * @fn int estrbuffer_set_capacity(estrbuffer_t buffer, unsigned int capacity)
   * @brief Change the buffer capacity.
   * @param buffer The buffer.
   * @param capacity The buffer capacity.
   * @return -1 on error else 0.
   */
  int estrbuffer_set_capacity(estrbuffer_t buffer, unsigned int capacity);

  /**
   * @fn int estrbuffer_append(estrbuffer_t shell, const char* str)
   * @brief Append a string into the buffer.
   * @param buffer The buffer.
   * @param str The string to append.
   * @return -1 on error else 0.
   */
  int estrbuffer_append(estrbuffer_t buffer, const char* str);

  /**
   * @fn int estrbuffer_append_char(estrbuffer_t shell, const char c)
   * @brief Append a char into the buffer.
   * @param buffer The buffer.
   * @param c The char to append.
   * @return -1 on error else 0.
   */
  int estrbuffer_append_char(estrbuffer_t buffer, const char c);

  /**
   * @fn int estrbuffer_copy(estrbuffer_t shell, const char* str)
   * @brief Erase the buffer with the copy string.
   * @param buffer The buffer.
   * @param str The string to copy.
   * @return -1 on error else 0.
   */
  int estrbuffer_copy(estrbuffer_t buffer, const char* str);

  /**
   * @fn int estrbuffer_copy_char(estrbuffer_t shell, const char c)
   * @brief Erase the buffer with the copy char.
   * @param buffer The buffer.
   * @param c The char to copy.
   * @return -1 on error else 0.
   */
  int estrbuffer_copy_char(estrbuffer_t buffer, const char c);

  /**
   * @fn int estrbuffer_trim_to_size(estrbuffer_t buffer)
   * @brief Trim the buffer allocation size to the buffer size.
   * @param buffer The buffer.
   * @return -1 on error else 0.
   */
  int estrbuffer_trim_to_size(estrbuffer_t buffer);

  /**
   * @fn int estrbuffer_erase2(estrbuffer_t buffer, unsigned int index)
   * @brief Erase a string.
   * @param buffer The buffer.
   * @param index The index.
   * @return -1 on error else 0.
   */
  int estrbuffer_erase2(estrbuffer_t buffer, unsigned int index);

  /**
   * @fn int estrbuffer_insert(estrbuffer_t buffer, unsigned int index, char* str)
   * @brief Insert a string from a specific position.
   * @param buffer The buffer.
   * @param index The index.
   * @param str The str.
   * @return -1 on error else 0.
   */
  int estrbuffer_insert(estrbuffer_t buffer, unsigned int index, char* str);

  /**
   * @fn int estrbuffer_erase(estrbuffer_t buffer, unsigned int index, unsigned int length)
   * @brief Erase a string.
   * @param buffer The buffer.
   * @param index The start index.
   * @param length The length.
   * @return -1 on error else 0.
   */
  int estrbuffer_erase(estrbuffer_t buffer,unsigned int index, unsigned int length);

  /**
   * @fn int estrbuffer_printf(estrbuffer_t buffer, const char* fmt, ...)
   * @brief Simple printf into the estrbuffer.
   * @param buffer The buffer.
   * @param fmt The format.
   * @param ... The arguments.
   * @return -1 on error else 0.
   */
  int estrbuffer_printf(estrbuffer_t buffer, const char* fmt, ...);

  /**
   * @fn int estrbuffer_vprintf(estrbuffer_t buffer, const char* fmt, va_list pa)
   * @brief Simple printf into the estrbuffer.
   * @param buffer The buffer.
   * @param fmt The format.
   * @param pa The arguments.
   * @return -1 on error else 0.
   */
  int estrbuffer_vprintf(estrbuffer_t buffer, const char* fmt, va_list pa);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESTR_H__ */
