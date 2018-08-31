#pragma once
#ifndef MENU_OPTIONS_DATA_H
#define MENU_OPTIONS_DATA_H
#include<string>
#include<functional>

using namespace std;


/*******************************************/
/*     M E N U  O P T I O N S  D A T A     */
/*******************************************/
class MenuOptionsData {

public:      

  MenuOptionsData();
  MenuOptionsData(string, function<void()>);
  ~MenuOptionsData();    
    
  string           menuItemDescription;    
  function<void()> menuItemFunction; 
  
};

#endif //MENU_OPTIONS_DATA_H


