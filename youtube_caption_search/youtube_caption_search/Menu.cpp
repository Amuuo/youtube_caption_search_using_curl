#include "Menu.h"
#include "usefulFunctions.h"



Menu::Menu() {
    
}
Menu::~Menu() {}




void Menu::displayMenu() {
  
  int i = 1;
  for (auto option : menuOptions) {
    printf("\n%d - ")
  }
    
}


void Menu::executeMenuSelection() {
  
  switch (getUserInput<int>("Selection")) { 
      

  }
      
}

