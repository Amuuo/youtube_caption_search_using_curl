                      
#include"main.h"

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







/*****************************************/
/*                M A I N                */
/*****************************************/
int main(int argc, char** argv){

  Captions = new CaptionStruct;
  
  getVideoUrl(argc!=2, argv);
  Captions->sendWebRequestForCaptions();  
  Captions->cleanupCaptionDownloadFile();  
  Captions->createCaptionMap();
  Captions->deleteCommonWordsFromMap();    
  Captions->createMostFrequentWordsVector();
  
  
  /**************************/
  /* loop through user mode */
  /**************************/
  while(userInteraction()); 
 
  return 0;
}










/*****************************************/
/*            USER INTERACTION           */
/*****************************************/
bool userInteraction() {
  Captions->printTopTenMentions();
  switch (getMainMenuSelection()) { 
    case 1: Captions->printMaxMentions(getUserInput<int>("Enter range")); break;      
    case 2: Captions->searchForWord(getUserInput<string>("Enter word"));  break;      
    case 3: Captions->printMaxMentions('r');                              break;
    case 4: Captions->printCaptionsToFile();                              break;
    case 5: exit(1);                                                      break;      
    default:                                                              break;
  } 
  return true;
}




/*****************************************/
/*             GET VIDEO URL             */
/*****************************************/
void getVideoUrl(bool commandLineUrl, char** args) {
  if (commandLineUrl)
    Captions->captionURL = getUserInput<string>("Enter URL");    
  else
    Captions->captionURL = string{args[1]};    
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

