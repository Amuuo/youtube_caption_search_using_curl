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
  vector<string> menuOptions;
  map<int,
  

public:

  Menu();
  ~Menu();
  
  virtual void displayMenu();
  virtual void executeMenuSelection();


};

