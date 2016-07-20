#include <estr.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char** argv) {
  struct estr_token_s tok;
  char* str;
  (void)argc;
  (void)argv;
  
  estr_split(&tok, 
    "Sic habere belli Nam omnia hoc ab nos intellego belli alia"\
    " suspicione hoc suspicione provinciis omni nobis perpetuae Patres quis.",
    " ");
  while(estr_token_has_more(&tok)) {
    str = estr_token_next(&tok);
    printf("Next token: '%s'\n", str);
    free(str);
  }
  return 0;
}
