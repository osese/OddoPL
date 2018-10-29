#include "ochar.h"

int main(){

  ochar_t a = ochar_create_m("\xc3\xb6", 2);
  ochar_display(a);
  return 0;
}