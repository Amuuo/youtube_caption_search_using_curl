#pragma once
#include "Menu.h"
#include "CaptionInfo.h"


class VideoCaptionsListMenu : public Menu {

public:
  VideoCaptionsListMenu();
  ~VideoCaptionsListMenu();

  //add function to pull binary from file later
  virtual void  executeMenuSelection();
  virtual void  displayMenu();
  void loadVideoCaptionsList(); 
  void listAvailableVideoCaptions();
  void addVideoCaptions();
  void setMenuOptions();
private:
  

};

