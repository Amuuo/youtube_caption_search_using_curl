#include"VideoCaptionsListMenu.h"
#include"VideoCaptions.h"


VideoCaptionsListMenu::VideoCaptionsListMenu(): Menu{} {
  
  menuOptions.push_back(menuOptionsData{"Print most frequent words", &printMaxMentions()});
  menuOptions.push_back(menuOptionsData{"Search word", searchForWord()});
  menuOptions.push_back(menuOptionsData{"Print entire table", printMaxMentions()});      
  menuOptions.push_back(menuOptionsData{"Print table to file", printCaptionsToFile()});    
}

VideoCaptionsListMenu::~VideoCaptionsListMenu() {}

void VideoCaptionsListMenu::addVideoCaptions() {

}

void VideoCaptionsListMenu::setMenuOptions() {

}

function<void()> VideoCaptionsListMenu::searchForWord() const {
  return function<void()>();
}

function<void()> VideoCaptionsListMenu::printMaxMentions() const {
  return function<void()>();
}

function<void()> VideoCaptionsListMenu::printCaptionsToFile() {
  return function<void()>();
}


void VideoCaptionsListMenu::executeMenuSelection() {
    
  switch(getUserInput<int>("Selection")){

    case 1: printMaxMentions();    break;      
    case 2: searchForWord();       break;      
    case 3: printMaxMentions('r'); break;
    case 4: printCaptionsToFile(); break;
    case 5: exit(1);               break;      
      
    default: break;
  }
}

void VideoCaptionsListMenu::displayMenu() {
  
  for (auto option : *menuOptions) {

  }
}

void VideoCaptionsListMenu::VideoCaptionsListMenu::loadVideoCaptionsList() {
}

void VideoCaptionsListMenu::listAvailableVideoCaptions() {
}

