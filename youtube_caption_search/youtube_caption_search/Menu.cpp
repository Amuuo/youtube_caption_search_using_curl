#include "Menu.h"


Menu::
Menu() {}

Menu::
Menu(string menuTitle, vector<MenuOptionsData> menuOptions) :
  menuTitle{menuTitle}, 
  menuOptions{make_shared<vector<MenuOptionsData>>(menuOptions)}{}

Menu::
~Menu() {}


void Menu::
launchMenu() {
    
  const char* itemFormat = "\n%d - %d";
  int itemNumber{0};
  
  for (auto option : *menuOptions) {
    printf(itemFormat, (itemNumber++)+1, option.menuItemDescription);    
  }    
    
  menuOptions->at(getUserInput<int>("Selection", "\n\n\t")).menuItemFunction();
}




