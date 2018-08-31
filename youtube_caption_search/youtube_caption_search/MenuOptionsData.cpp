#include "MenuOptionsData.h"



MenuOptionsData::
MenuOptionsData() {}


MenuOptionsData::
~MenuOptionsData() {}

MenuOptionsData::
MenuOptionsData(const char* menuItemDescription, shared_ptr<function<void()>> menuItemFunction) :  
  menuItemDescription{menuItemDescription}, menuItemFunction{menuItemFunction} {}

