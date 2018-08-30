
#pragma once
#include<string>


/*****************************************/
/*       GET USER INPUT (TEMPLATE)       */
/*****************************************/
template<typename type_>
type_ getUserInput(std::string prompt) {
  printf("\n\t%s: ", prompt.c_str());
  type_ tmp;
  cin >> tmp;
  return tmp;
}

