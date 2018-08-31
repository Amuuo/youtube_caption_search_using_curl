#include "MenuOptionsData.h"



MenuOptionsData::
MenuOptionsData() {}


MenuOptionsData::
~MenuOptionsData() {}

MenuOptionsData::
MenuOptionsData(string menuItemDescription, function<void()> menuItemFunction) :  
  menuItemDescription{menuItemDescription}, menuItemFunction{menuItemFunction} {}

