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
  Menu(string,vector<MenuOptionsData>);
  ~Menu();
  
  void launchMenu();

      
protected:  
  
  string menuTitle;
  shared_ptr<vector<MenuOptionsData>> menuOptions;

private:


};

#endif //MENU_H