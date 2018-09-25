#pragma once

#include<memory>
#include<vector>
#include<functional>
#include<string>
#include<iostream>
#include<stack>
#include<fstream>
#include<algorithm>
#include"userIO.h"

using namespace std;





class Menu
{


  public:  
  

    static struct MenuFunction 
    {
      using functionPtr = shared_ptr<function<void()>>;
  
      MenuFunction(string,functionPtr);
      string       description;
      functionPtr  menuFunction;
    };
    
    using optionsVecPtr = unique_ptr<vector<MenuFunction>>;
  

    Menu();
    Menu(optionsVecPtr, string="", string="\n\n", string="\t");
    ~Menu();  
  

    inline bool getMenuSelection(int, int);
    bool        displayMenu(int=0);
    void        setTitle(string);




  private:
  

    optionsVecPtr  optionsPtr{};
    string         title;
    string         spaceBeforeMenu;
    string         spaceBeforeMenuOptions;

};

