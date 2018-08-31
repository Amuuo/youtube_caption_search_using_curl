
//#ifndef MENU_OPTIONS_DATA_H
//#define MENU_OPTIONS_DATA_H

#pragma once
#include<string>
#include<functional>


using std::string;
using std::function;
using std::shared_ptr;


/*******************************************/
/*     M E N U  O P T I O N S  D A T A     */
/*******************************************/
class MenuOptionsData {
  

public:      

  MenuOptionsData();
  MenuOptionsData(const char*, shared_ptr<function<void()>>);
  ~MenuOptionsData();    
    
  string           menuItemDescription;    
  shared_ptr<function<void()>> menuItemFunction; 
  
};

//#endif //MENU_OPTIONS_DATA_H


