#pragma once
#ifndef MENU_H
#define MENU_H


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



#endif //MENU_H