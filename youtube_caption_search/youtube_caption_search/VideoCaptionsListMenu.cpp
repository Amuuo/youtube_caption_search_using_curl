#include "VideoCaptionsListMenu.h"



VideoCaptionsListMenu::VideoCaptionsListMenu() {
  
  menuOptions = {"Print most frequent words",
                 "Search word",
                 "Print entire table",
                 "Print table to file",
                 "Exit Program"};  

}

VideoCaptionsListMenu::~VideoCaptionsListMenu() {}

void VideoCaptionsListMenu::addVideoCaptions() {

}

void VideoCaptionsListMenu::setMenuOptions() {

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

