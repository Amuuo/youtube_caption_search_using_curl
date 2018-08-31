#pragma once
#ifndef MENU_OPTIONS_DATA_H
#define MENU_OPTIONS_DATA_H
#include<string>
#include<functional>

using namespace std;



class MenuOptionsData {

public:      

  MenuOptionsData();
  MenuOptionsData(string, function<void()>);
  ~MenuOptionsData();    
    
  string           menuItemDescription;    
  function<void()> menuItemFunction; 
  
};

#endif //MENU_OPTIONS_DATA_H
