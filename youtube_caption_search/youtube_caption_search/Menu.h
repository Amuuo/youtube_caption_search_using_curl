#pragma once
#include<string>
#include<vector>
#include<map>
#include<functional>
#include"userIO.h"
using namespace std;



/******************************************/
/*                 M E N U                */
/******************************************/
class Menu {

protected:  
  
  // holds menu option strings and corresponding functions  
  vector<function<void()>> menuOptions; 

public:

  Menu();
  ~Menu();
  
  virtual void displayMenu();
  virtual void executeMenuSelection();


};

