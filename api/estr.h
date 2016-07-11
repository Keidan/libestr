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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ESTR_H__ */
