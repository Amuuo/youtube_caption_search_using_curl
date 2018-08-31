
#pragma once
#include<string>
#include<iostream>

//using namespace std;

using std::string;
using std::cin;


/*****************************************/
/*       GET USER INPUT (TEMPLATE)       */
/*****************************************/
template<typename type_>
type_ getUserInput(string prompt, string leadingSpace="\n\t") {
  printf("%s%s: ", leadingSpace.c_str(), prompt.c_str());
  type_ tmp;
  cin >> tmp;
  return tmp;
}

