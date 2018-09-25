#include "Menu.h"



Menu::
Menu() 
{
}


Menu::
Menu(optionsVecPtr optionsPtr,           
     string        title,
     string        spaceBeforeMenu,
     string        spaceBeforeMenuOptions) :
  
                    optionsPtr{move(optionsPtr)}, 
                    title{title},
                    spaceBeforeMenu{spaceBeforeMenu},
                    spaceBeforeMenuOptions{spaceBeforeMenuOptions}
{
  transform(this->title.begin(), 
            this->title.end(), 
            this->title.begin(), 
            ::toupper);
}


Menu::
~Menu() 
{
}




Menu::MenuFunction::
MenuFunction(string description, functionPtr menuFunction) : 
  description{description}, menuFunction{menuFunction} 
{
}




bool Menu::
displayMenu(int functionNum) 
{
  cout << spaceBeforeMenu << "\t" << title << " MENU\n\n";      
  
  for (auto option : *optionsPtr) 
  {
    cout << spaceBeforeMenuOptions 
         << (functionNum++) + 1 << " - " 
         << option.description  << endl;
  } 
  int previousMenuOption = functionNum+1;
  int exitOption         = functionNum+2;


  cout << spaceBeforeMenuOptions << previousMenuOption 
       << " - Previous Menu" << endl
       << spaceBeforeMenuOptions << exitOption << " - Exit" << endl;
  
  
  return getMenuSelection(exitOption, previousMenuOption);  
}




void Menu::
setTitle(string title) 
{
  this->title = title;
}





bool Menu::
getMenuSelection(const int exitOption, const int previousMenuOption) 
{   
  int choice = getUserInput<int>("Selection");


  if      (choice > exitOption)  cout << "\n\nChoice is out of range";  
  else if (choice == exitOption) exit(1);
  else if (choice == previousMenuOption) return false;       
  else    (*optionsPtr.get()->at(choice-1).menuFunction.get())();

  
  return true;
}





