                      


/*============================================================================
|                                                                            |
|                                                                            |
|                                                                            |     
|                        ___         ___         ___   ___                   |
|                  \ /  |   | |   |   |   |   |   | | |                      |
|                   +   |   | |   |   +   |   |   +-  |-+-                   | 
|                   |   |   | |   |   |   |   |   | | |                      |
|                        ---   ---         ---   ---   ---                   |
|                  ___   ___   ___   ___   ___   ___                         |
|                 |     |   | |   |   |     |   |   | |\  |                  |
|                 |     |-+-| |-+-    +     +   |   | | + |                  |
|                 |     |   | |       |     |   |   | |  \|                  |
|                  ---                     ---   ---                         |
|                     ___   ___   ___   ___   ___                            |                                                                                                                 
|                    |     |     |   | |   | |     |   |                     |
|                     -+-  |-+-  |-+-| |-+-  |     |-+-|                     |
|                        | |     |   | |  \  |     |   |                     |
|                     ---   ---               ---                            |
|                                                                            |
|                                                                            |
|                                                                            |
|                                                                            |
|                                                                            |
|                Copyright (C) 2017 - 2018, Adam Williams,                   |
|                                                                            |
|                   <adamthewilliams@gmail.com>, et al.                      |
|                                                                            |
|                                                                            |                                                                            |
|    You may opt to use, copy, modify, merge, publish, distribute and/or     |
|    sell copies of the Software, and permit persons to whom the Software    |
|    is furnished to do so, under the terms of the COPYING file.             |
|                                                                            |
|    This software is distributed on an "AS IS" basis, WITHOUT WARRANTY      |
|    OF ANY KIND, either express or implied.                                 |
|                                                                            |
|                                                                            |
=============================================================================*/

                                                                           


#include"main.h"


int main(int argc, char** argv){

  Captions = new CaptionStruct;
  string* videoUrl{getVideoUrl(argc!=2, argv)};
  
  sendRequestForCaptions(*videoUrl);
  
  Captions->cleanupCaptionDownloadFile();  
  Captions->createCaptionMap(videoUrl);
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
  printTopTenMentions();
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
string* getVideoUrl(bool commandLineUrl, char** args) {
  if (commandLineUrl)
    return new string{getUserInput<string>("Enter URL")}; 
  else
    return new string{args[1]};
}




/*****************************************/
/*         PRINT TOP TEN MENTIONS        */
/*****************************************/
void printTopTenMentions() {
  printf("\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  for (int i{1}; i<=10; ++i) {
    printf("%s(%d), ", Captions->maxMentionsVec->at(i).first.c_str(), 
                       Captions->maxMentionsVec->at(i).second.size());
    if(i % 2 == 0) 
      printf("\n\t\t");
  }
}




/*****************************************/
/*               WRITEFUNC               */
/*****************************************/
size_t writefunc(char *ptr, size_t size, size_t nmemb, string* s) {  

  *s += string{ptr + '\0'};
  Captions->captionText += *s;
  return size*nmemb;
}




/*****************************************/
/*       SEND REQUEST FOR CAPTIONS       */
/*****************************************/
void sendRequestForCaptions(string url) {
  
  string new_url{"http://video.google.com/timedtext?type=track&lang=en&v="};
  regex rgx("v=(.{11})");
  smatch video_id_match;
  regex_search(url, video_id_match, rgx);
  url = new_url + string{video_id_match[1]};
  

  string r{"start: "};

  CURL* curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  regex rgx2("(<text.{3})*");
  smatch cap_match;

  regex_search(Captions->captionText.cbegin(), Captions->captionText.cend(), cap_match, rgx2);
                            
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























