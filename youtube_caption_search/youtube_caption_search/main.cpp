
/*============================================================================
==============================================================================
||                                                                           ||
||                                                                           ||
||                                                                           ||     
||                        ___         ___         ___   ___                  ||
||                  \ /  |   | |   |   |   |   |   | | |                     ||
||                   +   |   | |   |   +   |   |   +-  |-+-                  || 
||                   |   |   | |   |   |   |   |   | | |                     ||
||                        ---   ---         ---   ---   ---                  ||
||                  ___   ___   ___   ___   ___   ___                        ||
||                 |     |   | |   |   |     |   |   | |\  |                 ||
||                 |     |-+-| |-+-    +     +   |   | | + |                 ||
||                 |     |   | |       |     |   |   | |  \|                 ||
||                  ---                     ---   ---                        ||
||                    ___   ___   ___   ___   ___                            ||                                                                                                                 
||                    |     |     |   | |   | |     |   |                    ||
||                     -+-  |-+-  |-+-| |-+-  |     |-+-|                    ||
||                        | |     |   | |  \  |     |   |                    ||
||                     ---   ---               ---                           ||
||                                                                           ||
||                                                                           ||
||                                                                           ||
||                                                                           ||
||                                                                           ||
||                Copyright (C) 2017 - 2018, Adam Williams,                  ||
||                                                                           ||
||                   <adamthewilliams@gmail.com>, et al.                     ||
||                                                                           ||
||                                                                           ||                                                                            |
||    You may opt to use, copy, modify, merge, publish, distribute and/or    ||
||    sell copies of the Software, and permit persons to whom the Software   ||
||    is furnished to do so, under the terms of the COPYING file.            ||
||                                                                           ||
||    This software is distributed on an "AS IS" basis, WITHOUT WARRANTY     ||
||    OF ANY KIND, either express or implied.                                ||
||                                                                           ||
||                                                                           ||
==============================================================================
=============================================================================*/

                      
//#define __USE_MINGW_ANSI_STDIO 0
#define _CRT_SECURE_NO_WARNINGS
#include"userIO.h"
#include"Menu.h"
#include"MenuOptionsData.h"
#include"VideoCaptions.h"
#include"VideoCaptionsMenu.h"


using namespace std;


inline void checkForValidCommandLine(int,char**);
void  getVideoUrl(bool, char**);
void  sendRequestForCaptions(string);
bool  userInteraction();
int   getMainMenuSelection();


shared_ptr<VideoCaptions> Captions;







/*****************************************/
/*                M A I N                */
/*****************************************/
int main(int argc, char** argv){

  checkForValidCommandLine(argc,argv);
  
  Captions = make_shared<VideoCaptions>(new VideoCaptions);
  
  getVideoUrl(argc==2, argv);
  Captions->getCaptions();
  
  
  /**************************/
  /* loop through user mode */
  /**************************/
  while(userInteraction()); 
 
  return 0;
}







/*****************************************/
/*             GET VIDEO URL             */
/*****************************************/
void getVideoUrl(bool cmdLineUrlPresent, char** args) {
  
  if (cmdLineUrlPresent)
    Captions->captionURL = string{args[1]};    
  else
    Captions->captionURL = getUserInput<string>("Enter URL");    
}




/*****************************************/
/*            USER INTERACTION           */
/*****************************************/
bool userInteraction() {
  Captions->printTopTenMentions();

  return true;
}




/******************************************/
/*         GET MAIN MENU SELECTION        */
/******************************************/
int getMainMenuSelection() {
  
  printf("\n\n\t1 - Print most frequent words");
  printf(  "\n\t2 - Search word"              );
  printf(  "\n\t3 - Print entire table"       );
  printf(  "\n\t4 - Print table to file"      );
  printf(  "\n\t5 - Exit Program\n"           );
    
  return getUserInput<int>("Selection");
}

inline void checkForValidCommandLine(int argNum, char** args) {
   
  if (argNum > 2) {
    printf("\n\nUsage: ./<PROGRAM> <URL>"
           "\n       ./<PROGRAM>");
    exit(1);
  }
}

