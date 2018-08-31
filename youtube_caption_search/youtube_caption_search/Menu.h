
//#ifndef MENU_H
//#define MENU_H
#pragma once

#include<cstdio>
#include<functional>
#include<string>
#include<vector>
#include<memory>
#include"userIO.h"
#include"MenuOptionsData.h"


using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


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

//#endif //MENU_H