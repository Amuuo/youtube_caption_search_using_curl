
#include"VideoCaptionsMenu.h"


VideoCaptionsMenu::
VideoCaptionsMenu(captionPtr captions) : Menu{}, captions{move(captions)} {
  menuOptions = captions->getMenuOptions(); 
}



VideoCaptionsMenu::
~VideoCaptionsMenu() {}



void VideoCaptionsMenu::
addVideoCaptions() {}



void VideoCaptionsMenu::VideoCaptionsMenu::
loadVideoCaptionsList() {}



void VideoCaptionsMenu::
listAvailableVideoCaptions() {}

