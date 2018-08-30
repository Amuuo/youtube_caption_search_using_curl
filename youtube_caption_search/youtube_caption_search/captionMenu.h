#pragma once

#include"Menu.h"
#include"CaptionInfo.h"




/******************************************/
/*        C A P T I O N   M E N U         */
/******************************************/
class captionMenu : public Menu {

private:
  map<int, CaptionStruct> captionMap

public:
  captionMenu();
  ~captionMenu();
  virtual void executeMenuSelection();
  virtual void displayMenu();
};

