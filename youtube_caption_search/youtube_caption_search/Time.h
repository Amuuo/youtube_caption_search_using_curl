
#pragma once
#include<string>


/***********************************************************/
/*                          T I M E                        */
/***********************************************************/
struct Time { 
  

  /****************************************/
  /*      CONSTRUCTOR / DESTRUCTOR        */
  /****************************************/
  Time(){}
  Time(std::string h, std::string m, std::string s) : 
        hr{std::stoi(h)}, min{std::stoi(m)}, sec{std::stoi(s)} {}
  ~Time(){}
  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/
  int hr; 
  int min; 
  int sec;     
};