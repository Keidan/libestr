/**
*******************************************************************************
* @file estrbuffer.h
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
#ifndef __ESTRBUFFER_H__
#define __ESTRBUFFER_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

  #include <string.h>
  #include <stdint.h>
  #include <stdarg.h>

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

#endif /* __ESTRBUFFER_H__ */
