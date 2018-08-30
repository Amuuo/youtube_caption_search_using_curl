#pragma once

#include"Menu.h"
#include"CaptionInfo.h"




/******************************************/
/*        C A P T I O N   M E N U         */
/******************************************/
class captionMenu : public Menu {

private:
  map<int, videoCaptionsList> captionMap

public:
  captionMenu();
  ~captionMenu();
  void addVideoCaptions();
  virtual void executeMenuSelection();
  virtual void displayMenu();
};

