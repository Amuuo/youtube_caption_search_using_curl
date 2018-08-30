#pragma once
#include<string>
#include<vector>
#include<map>
#include<functional>
#include"usefulFunctions.h"
using namespace std;



/******************************************/
/*                 M E N U                */
/******************************************/
class Menu {

protected:  
  
  // holds menu option strings and corresponding functions  
  vector<pair<string,function<void()>>> menuOptions; 

public:

  Menu();
  ~Menu();
  
  virtual void displayMenu();
  virtual void executeMenuSelection();


};

