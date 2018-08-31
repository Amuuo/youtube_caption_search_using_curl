#pragma once
#ifndef MENU_H
#define MENU_H
#include<cstdio>
#include<functional>
#include<string>
#include<vector>
#include"userIO.h"
#include"MenuOptionsData.h"

using namespace std;


/******************************************/
/*                 M E N U                */
/******************************************/
class Menu {
     
public:      

  Menu();
  Menu(string, vector<MenuOptionsData>);
  ~Menu();
  
  void displayMenu();
  void executeMenuSelection();
      
protected:  
  
  string menuTitle;
  vector<MenuOptionsData> menuOptions;

private:


};

#endif //MENU_H