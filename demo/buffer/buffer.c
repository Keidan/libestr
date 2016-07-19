#include <estr.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv) {
  estr_t b;
  
  (void)argc;
  (void)argv;
  
  b = estr_new();
  estr_append(b, "azerty");
  printf("Buffer after append: '%s'\n", estr_to_str(b));
  estr_append(b, "1234567890");
  printf("Buffer after append: '%s'\n", estr_to_str(b));
  estr_copy(b, "12");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_copy(b, "34567");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_erase(b, 2, 2);
  printf("Buffer after erase at 2 with len 2: '%s'\n", estr_to_str(b));
  estr_erase(b, 0, 1);
  printf("Buffer after erase at 0 with len 1: '%s'\n", estr_to_str(b));
  estr_copy(b, "AZERTYUIOPQSDFGHJKLMWXCVBN");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_erase2(b, 5);
  printf("Buffer after erase2 from 5: '%s'\n", estr_to_str(b));
  estr_insert(b, 2, "blabla");
  printf("Buffer after insert at 2: '%s'\n", estr_to_str(b));
  estr_copy(b, "AZERTYUIOPQSDFGHJKLMWXCVBN3");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_copy(b, "AZERTYUIOPQSDFGHJKLMWXCVBN1234567890987654321");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_clear(b);
  printf("Buffer after clear: '%s'\n", estr_to_str(b));
  estr_copy(b, "AZ12345");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_insert(b, 2, "ERTY");
  printf("Buffer after insert at 2: '%s'\n", estr_to_str(b));
  estr_trim_to_size(b);
  printf("Buffer after trim: '%s'\n", estr_to_str(b));
  estr_copy(b, "123");
  printf("Buffer after copy: '%s'\n", estr_to_str(b));
  estr_insert(b, 0, "0ab");
  printf("Buffer after insert at 0: '%s'\n", estr_to_str(b));

  estr_printf(b, "Hellow \"%s\" %d %d %d %d \"%c\" %x %X %#X %p", "from:klhjkhjkhjkhjk", 10,11,12,13, 'A', 255,255,255, b);
  printf("Buffer after printf: '%s'\n", estr_to_str(b));

  estr_delete(b);
  return 0;
}
