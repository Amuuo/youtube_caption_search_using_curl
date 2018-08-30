#pragma once
#include<conio.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<regex>
#include<algorithm>
#include<functional>
#include<cstdio>
#include<string>
#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include"userIO.h"

using namespace std;



/******************************************/
/*                 M E N U                */
/******************************************/
class Menu {

public:

  Menu();
  ~Menu();
  
  virtual void displayMenu();
  virtual void executeMenuSelection();

      

protected:  
  
  // holds menu option strings and corresponding functions  
  struct menuOptionsData {
    menuOptionsData(){}
    menuOptionsData(const char* str, function<void()>* func) :
      menuItemDescription{str}, menuItemFunction{func}{}
    
    string            menuItemDescription;    
    function<void()>* menuItemFunction; 
  };

  vector<menuOptionsData> menuOptions;



private:


};

