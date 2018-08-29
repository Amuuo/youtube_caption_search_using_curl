
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
#include"AdamFunctions.h"
#include"Time.h"
using namespace std;



/***********************************************************/
/*                C A P T I O N S T R U C T                */
/***********************************************************/
struct CaptionStruct{


  using frequentWords = vector<pair<string,set<CaptionStruct*>>>;  
  using captionTable  = map<string,set<CaptionStruct*>>;
  using captionLines  = vector<string>;
  using lineCheck     = map<string, CaptionStruct*>;
  using capPair       = pair<string,set<CaptionStruct*>>;
  
  

  
  /****************************************/
  /*      CONSTRUCTOR / DESTRUCTOR        */
  /****************************************/
  CaptionStruct(){}
  CaptionStruct(const string* s, string l, string u, Time t) : 
    videoTitle{s}, line {l}, time {t}, 
    captionURL {constructTimestampedURL(t, u)} {}
  ~CaptionStruct(){}


  
  /****************************************/
  /*              VARIABLES               */
  /****************************************/
  frequentWords*  maxMentionsVec {};
  captionTable*   captionMap     {};
  const string*   videoTitle     {};
  string          line           {};
  string          captionURL     {};
  Time            time           {};
  inline static string   captionText{};



  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  constructTimestampedURL(Time,string);
  
  void    printCaptionsToFile();
  void    printCaptionsToConsole(CaptionStruct*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  void    deleteCommonWordsFromMap();
  void    searchForWord(string);
  void    printMaxMentions(char='\0');
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions();
  void    sendWebRequestForCaptions();
  inline static size_t  writefunc(char*, size_t, size_t, string*);
};

