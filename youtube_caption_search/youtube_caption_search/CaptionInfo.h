
#pragma once
#include<conio.h>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<regex>
#include<algorithm>
#include<functional>
#include<cstdio>
#include<string>
#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include"userIO.h"
#include"Menu.h"
using namespace std;

 
using captionLines  = vector<string>;
using lineCheck     = map<string, videoCaptionsList*>;
using capPair       = pair<string,set<videoCaptionsList*>>;



/***********************************************************/
/*             V I D E O  C A P T I O N  L I S T           */
/***********************************************************/
class videoCaptionsList{



public:

 
 
  /****************************************/
  /*      CONSTRUCTOR / DESTRUCTOR        */
  /****************************************/
  videoCaptionsList(){}
  ~videoCaptionsList(){}


  
  /****************************************/
  /*              VARIABLES               */
  /****************************************/


  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/


};



  /******************************************/
  /*        C A P T I O N   M E N U         */
  /******************************************/
  class _VideoCaptionsListMenu : public Menu {

  private:

  public:
    _VideoCaptionsListMenu();
    ~_VideoCaptionsListMenu();
    

    

  };








