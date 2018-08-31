
#include"VideoCaptionsListMenu.h"


VideoCaptionsListMenu::
VideoCaptionsListMenu(captionPtr caps) : Menu{}, captions{move(caps)} {}





VideoCaptionsListMenu::
~VideoCaptionsListMenu() {}





void VideoCaptionsListMenu::
addVideoCaptions() {

}




void VideoCaptionsListMenu::
setMenuOptions() {

}




function<void()> VideoCaptionsListMenu::
searchForWord() const {
  return function<void()>();
}




function<void()> VideoCaptionsListMenu::
printMaxMentions() const {
  return function<void()>();
}




function<void()> VideoCaptionsListMenu::
printCaptionsToFile() {
  return function<void()>();
}




void VideoCaptionsListMenu::VideoCaptionsListMenu::
loadVideoCaptionsList() {
}




void VideoCaptionsListMenu::
listAvailableVideoCaptions() {
}

