#include"AdamFunctions.h"



/*****************************************/
/*       GET USER INPUT (TEMPLATE)       */
/*****************************************/
template<typename type_>
type_ getUserInput(string prompt) {
  printf("\n\t%s: ", prompt.c_str());
  type_ tmp;
  cin >> tmp;
  return tmp;
}
