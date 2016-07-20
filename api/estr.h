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

  /**
   * @typedef estr_t
   * @brief Easy string buffer context.
   */
  typedef void* estr_t;
 
  /**
   * @fn estr_t estr_new_stringl(char* str, size_t str_len)
   * @brief New Easy string instance.
   * @param str The string to copy.
   * @param str_len The string length.
   * @return The instance else null
   */
  estr_t estr_new_stringl(char* str, size_t str_len);

  /**
   * @fn estr_t estr_new_string(c!!har* str)
   * @brief New Easy string instance.
   * @param str The string to copy.
   * @return The instance else null
   */
  estr_t estr_new_string(char* str);
    
  /**
   * @fn estr_t estr_new(void)
   * @brief New Easy string instance.
   * @return The instance else null
   */
  estr_t estr_new(void);

  /**
   * @fn void estr_delete(estr_t buffer)
   * @brief Delete string buffer.
   * @param buffer The buffer pointer.
   */
  void estr_delete(estr_t buffer);

  /**
   * @fn void estr_clear(estr_t buffer)
   * @brief Clear the buffer.
   * @param buffer The buffer pointer.
   */
  void estr_clear(estr_t buffer);

  /**
   * @fn char* estr_to_str(estr_t buffer)
   * @brief Get the buffer to char* format.
   * @param buffer The buffer.
   * @return The char* (can be NULL)
   */
  char* estr_to_str(estr_t buffer);

  /**
   * @fn char estr_char_at(estr_t buffer, size_t index)
   * @brief Get a char 'at'.
   * @param buffer Search string.
   * @param index The index.
   * @return The char.
   */
  char estr_char_at(estr_t buffer, size_t index);
  
  /**
   * @fn size_t estr_length(estr_t buffer)
   * @brief Get the buffer length.
   * @param buffer The buffer.
   * @return The length
   */
  size_t estr_length(estr_t buffer);

  /**
   * @fn size_t estr_capacity(estr_t buffer)
   * @brief Get the buffer capacity.
   * @param buffer The buffer.
   * @return The capacity
   */
  size_t estr_capacity(estr_t buffer);

  /**
   * @fn int estr_set_capacity(estr_t buffer, size_t capacity)
   * @brief Change the buffer capacity.
   * @param buffer The buffer.
   * @param capacity The buffer capacity.
   * @return 0 on success, -1 else (see errno)
   */
  int estr_set_capacity(estr_t buffer, size_t capacity);
  
  /**
   * @fn int estr_append_char(estr_t buffer, const char c)
   * @brief Append a char into the buffer.
   * @param buffer The buffer.
   * @param c The char to append.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_append_char(estr_t buffer, const char c);

  /**
   * @fn int estr_append(estr_t buffer, const char* str)
   * @brief Append a string into the buffer.
   * @param buffer The buffer.
   * @param str The string to append.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_append(estr_t buffer, const char* str);

  /**
   * @fn int estr_appends(estr_t buffer, estr_t str)
   * @brief Append a string into the buffer.
   * @param buffer The buffer.
   * @param str The string to append.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_appends(estr_t buffer, estr_t str);

  /**
   * @fn int estr_appendl(estr_t buffer, const char* str, size_t str_len)
   * @brief Append a string into the buffer.
   * @param buffer The buffer.
   * @param str The string to append.
   * @param str_len The string length.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_appendl(estr_t buffer, const char* str, size_t str_len);

  /**
   * @fn int estr_copy_char(estr_t buffer, const char c)
   * @brief Erase the buffer and copy the char.
   * @param buffer The buffer.
   * @param c The char to copy.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_copy_char(estr_t buffer, const char c);

  /**
   * @fn int estr_copy(estr_t buffer, const char* str)
   * @brief Erase the buffer with the copy string.
   * @param buffer The buffer.
   * @param str The string to copy.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_copy(estr_t buffer, const char* str);

  /**
   * @fn int estr_copyl(estr_t buffer, const char* str, size_t str_eln)
   * @brief Erase the buffer with the copy string.
   * @param buffer The buffer.
   * @param str The string to copy.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_copyl(estr_t buffer, const char* str, size_t str_len);

  /**
   * @fn int estr_trim_to_size(estr_t buffer)
   * @brief Trim the buffer capacity to the real buffer size.
   * @param buffer The buffer.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_trim_to_size(estr_t buffer);

  /**
   * @fn int estr_erase2(estr_t buffer, size_t index)
   * @brief Erase a string.
   * @param buffer The buffer.
   * @param index The index.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_erase2(estr_t buffer, size_t index);

  /**
   * @fn int estr_erase(estr_t buffer, size_t index, size_t length)
   * @brief Erase a string.
   * @param buffer The buffer.
   * @param index The start index.
   * @param length The length.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_erase(estr_t buffer,size_t index, size_t length);

  /**
   * @fn int estr_insert(estr_t buffer, size_t index, char* str)
   * @brief Insert a string at a specific position.
   * @param buffer The buffer.
   * @param index The index.
   * @param str The str.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_insert(estr_t buffer, size_t index, char* str);

  /**
   * @fn int estr_printf(estr_t buffer, const char* fmt, ...)
   * @brief Simple printf into the estr.
   * @param buffer The buffer.
   * @param fmt The format.
   * @param ... The arguments.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_printf(estr_t buffer, const char* fmt, ...);

  /**
   * @fn int estr_vprintf(estr_t buffer, const char* fmt, va_list pa)
   * @brief Simple printf into the estr.
   * @param buffer The buffer.
   * @param fmt The format.
   * @param pa The arguments.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_vprintf(estr_t buffer, const char* fmt, va_list pa);

  /**
   * @fn void estr_tolower(estr_t buffer)
   * @brief Convert a string in lower case.
   * @param buffer The buffer to convert.
   */
  void estr_tolower(estr_t buffer);

  /**
   * @fn void estr_toupper(estr_t buffer)
   * @brief Convert a string in upper case.
   * @param buffer The buffer to convert.
   */
  void estr_toupper(estr_t buffer);

  /**
   * @fn char* estr_substring(const char* str, size_t begin, size_t len)
   * @brief Substract a string.
   * @param str Input string.
   * @param begin Begin index.
   * @param len Length.
   * @return substring (free required).
   */
  char* estr_substring(estr_t buffer, size_t begin, size_t len);

  /**
   * @fn estr_t estr_substr(const char* str, size_t begin, size_t len)
   * @brief Substract a string.
   * @param str Input string.
   * @param begin Begin index.
   * @param len Length.
   * @return estr_delete required.
   */
  estr_t estr_substr(estr_t buffer, size_t begin, size_t len);

  /**
   * @fn int estr_indexof(estr_t buffer, const char* needed)
   * @brief Search the index of the needed string into the input string.
   * @param buffer Search string.
   * @param needed Needed string.
   * @return -1 if not found else 0.
   */
  int estr_indexof(estr_t buffer, const char* needed);

  /**
   * @fn size_t estr_count(estr_t buffer, const char needed)
   * @brief Count the number of occurences of the needed char.
   * @param buffer Search string.
   * @param needed The char.
   * @return Occurences number.
   */
  size_t estr_count(estr_t buffer, const char needed);

  /**
   * @fn _Bool estr_isint(const char* source)
   * @brief Test if the string is a valid digit.
   * @param source The source string
   * @return 1 if the string is a valid int.
   */
  _Bool estr_isint(estr_t buffer);

  /**
   * @fn int estr_append_float(estr_t buffer, double value)
   * @brief Append a float to the buffer.
   * @param buffer The buffer.
   * @param value The value to append.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_append_float(estr_t buffer, double value);

  /**
   * @fn int estr_append_uint(estr_t buffer, unsigned int value, int base)
   * @brief Append an unsigned int to the buffer.
   * @param buffer The buffer.
   * @param value The value to append.
   * @param base The int base.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_append_uint(estr_t buffer, unsigned int value, int base);

  /**
   * @fn int estr_append_int(estr_t buffer, unsigned int value, int base)
   * @brief Append an int to the buffer.
   * @param buffer The buffer.
   * @param value The value to append.
   * @param base The int base.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_append_int(estr_t buffer, int value, int base);

  /**
   * @fn int estr_to_int(estr_t buffer, int def)
   * @brief Convert a string int to an int value.
   * @param buffer Src string.
   * @param def the default value on error
   * @return the int value.
   */
  int estr_to_int(estr_t buffer, int def);

  /**
   * @fn unsigned long int estr_to_long(estr_t buffer, unsigned long int def)
   * @brief Convert a string int to an int value.
   * @param buffer Src string.
   * @param def the default value on error
   * @return the int value.
   */
  unsigned long int estr_to_long(estr_t buffer, unsigned long int def);

  /**
   * @fn _Bool estr_match(const char* str, const char* regex)
   * @brief Test if the regex match with the input string.
   * @param buffer The string to test.
   * @param regex The regex
   * @return 1 if the regex match else 0.
   */
  _Bool estr_match(estr_t buffer, const char* regex);

  /**
   * @fn const char* estr_convert(unsigned long num, int base)
   * @brief Convert an size_t in string.
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
   * @fn _Bool estr_startswith(estr_t buffer, const char *prefix)
   * @brief Test if the string starts with the prefix.
   * @param str The source string.
   * @param prefix The prefix string to find.
   * @return true/false
   */
  _Bool estr_startswith(estr_t buffer, const char *prefix);

  /**
   * @fn _Bool estr_endswith(estr_t buffer, const char *suffix)
   * @brief Test if the string ends with the suffix.
   * @param str The source string.
   * @param suffix The suffix string to find.
   * @return true/false
   */
  _Bool estr_endswith(estr_t buffer, const char *suffix);
  
  /**
   * @fn _Bool estr_startswith_c(const char* buffer, size_t length, const char *prefix)
   * @brief Test if the string starts with the prefix.
   * @param str The source string.
   * @param length The buffer length.
   * @param prefix The prefix string to find.
   * @return true/false
   */
  _Bool estr_startswith_c(const char* buffer, size_t length, const char *prefix);

  /**
   * @fn _Bool estr_endswith_c(const char* buffer, size_t length, const char *suffix)
   * @brief Test if the string ends with the suffix.
   * @param str The source string.
   * @param length The buffer length.
   * @param suffix The suffix string to find.
   * @return true/false
   */
  _Bool estr_endswith_c(const char* buffer, size_t length, const char *suffix);
  
  /**
   * @fn char* estr_substring_c(const char* buffer, size_t begin, size_t len)
   * @brief Substract a string.
   * @param buffer Input string.
   * @param begin Begin index.
   * @param len Length.
   * @return substring (free required).
   */
  char* estr_substring_c(const char* buffer, size_t begin, size_t len);


  /*******************************************************************************
   * ___________     __                  
   * \__    ___/___ |  | __ ____   ____  
   *   |    | /  _ \|  |/ // __ \ /    \ 
   *   |    |(  <_> )    <\  ___/|   |  \
   *   |____| \____/|__|_ \\___  >___|  /
   *                     \/    \/     \/ 
   ********************************************************************************/
   
  /**
   * @struct estr_token_s
   * @brief String token context.
   */
  struct estr_token_s {
    char   *buffer;  /**< Token buffer. */
    char   *sep;     /**< Separator. */
    size_t len;      /**< Buffer length. */
    size_t offset;   /**< Current buffer offset. */
  };

  /**
   * @typedef estr_token_t
   * @brief String token pointer.
   */
  typedef struct estr_token_s *estr_token_t; 

  /**
   * @fn int estr_split_with_buffer(estr_token_t token, estr_t buffer, const char* sep)
   * @brief Split a str buffer to a token instance.
   * @param token The token instance.
   * @param buffer The string buffer.
   * @param sep The split separator.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_split_with_buffer(estr_token_t token, estr_t buffer, const char* sep);

  /**
   * @fn int estr_split(estr_token_t token, const char* buffer, const char* sep)
   * @brief Split a str to a token instance.
   * @param token The token instance.
   * @param buffer The string to split.
   * @param sep The split separator.
   * @return 0 on success, -1 else (see errno).
   */
  int estr_split(estr_token_t token, const char* buffer, const char* sep);

  /**
   * @fn size_t estr_token_count(estrtoken_t tok)
   * @brief Count the number of tokens.
   * @param tok Token pointer.
   * @return The number of tokens.
   */
  size_t estr_token_count(estr_token_t tok);

  /**
   * @fn _Bool estr_token_has_more(estr_token_t tok)
   * @brief Test if the token contains more tokens.
   * @param tok Token pointer.
   * @return 1 if has more else 0.
   */
  _Bool estr_token_has_more(estr_token_t tok);

  /**
   * @fn char* estr_token_next(estr_token_t tok)
   * @brief Get the next token.
   * @param tok Token pointer
   * @return New token else NULL (free is required for non NULL values)
   */
  char* estr_token_next(estr_token_t tok);
      
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESTR_H__ */
