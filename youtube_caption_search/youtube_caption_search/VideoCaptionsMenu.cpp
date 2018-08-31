
#include"VideoCaptionsMenu.h"


VideoCaptionsMenu::
VideoCaptionsMenu(captionPtr caps) : Menu{}, captions{move(caps)} {}





VideoCaptionsMenu::
~VideoCaptionsMenu() {}





void VideoCaptionsMenu::
addVideoCaptions() {

}




void VideoCaptionsMenu::
setMenuOptions() {

}




function<void()> VideoCaptionsMenu::
searchForWord() const {
  return function<void()>();
}




function<void()> VideoCaptionsMenu::
printMaxMentions() const {
  return function<void()>();
}




function<void()> VideoCaptionsMenu::
printCaptionsToFile() {
  return function<void()>();
}




void VideoCaptionsMenu::VideoCaptionsMenu::
loadVideoCaptionsList() {
}




void VideoCaptionsMenu::
listAvailableVideoCaptions() {
}

