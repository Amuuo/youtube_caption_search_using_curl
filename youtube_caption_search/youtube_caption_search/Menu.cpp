#include "Menu.h"


Menu::
Menu() {}

Menu::
Menu(string menuTitle, vector<MenuOptionsData> menuOptions) :
  menuTitle{menuTitle}, menuOptions{menuOptions}{}

Menu::
~Menu() {}


void Menu::
displayMenu() {
  
  int i = 1;
  for (auto option : menuOptions) {
    printf("\n%d - ");
  }    
}


void Menu::
executeMenuSelection() {
  
  switch (getUserInput<int>("Selection")) { 
      

  }     
}



