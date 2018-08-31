#pragma once

#ifndef VIDEOCAPTIONS_H
#define VIDEOCAPTIONS_H

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
#include<memory>
#include"userIO.h"
#include"MenuOptionsData.h"

using namespace std;


/**********************************************************/
/*                V I D E O  C A P T I O N                */
/**********************************************************/
class VideoCaptions {


public:
  
  VideoCaptions();
  ~VideoCaptions();  
  

  struct CaptionLine {   
    
    struct Time {   
      Time(){}
      Time(string,string,string){}      
      int hr, min, sec;         
    };  
    CaptionLine(string, Time){}
    CaptionLine(){}

    string line;
    string timedURL;
    Time   time;
    
  };
  
  using linePtr = shared_ptr<CaptionLine>;

  struct CaptionWord {

    using ContextPtr = vector<linePtr>;
    
    CaptionWord(string, linePtr);
    ContextPtr captionContext;
    string     word;

    void addContextLine(linePtr);
  };




  string  getCaptionClipURL(shared_ptr<CaptionLine>);  
  void    printCaptionsToConsole(shared_ptr<CaptionWord>, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  
  function<void()> printCaptionsToFile();
  function<void()> searchForWord();
  function<void()> printMaxMentions();


protected:

  vector<MenuOptionsData> menuOptions = {
    
    {"Print most frequent words", printMaxMentions()},
    {"Search word",               searchForWord()},
    {"Print entire table",        printMaxMentions()},
    {"Print table to file",       printCaptionsToFile()}
  };

private:
  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/  

  
  using wordPtr = shared_ptr<CaptionWord>;

  vector<wordPtr>      captionWordsSortedByFrequency{};
  map<string, wordPtr> captionWordsIndex{};
  
  string  videoTitle;  
  string  videoURL;
  string  videoID;
  string  captionText{};

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/


  inline string  getWordURL(int); 
  inline void    deleteCommonWordsFromMap();
  inline void    buildAndStoreCaptionLine(map<string,CaptionLine>,string,string,CaptionLine&);
  inline void    indexWord(string, linePtr);
  inline void    setWordsToLowercase(string);
  inline bool    lineIsNotAlreadyIndexed(map<string,CaptionLine>, string&);
  inline bool    lineContainsTimeInfo(string);
  inline void    indexWordsInCurrentLine(CaptionLine&);
  inline bool    nextLineIsACopy(istringstream&, string&, string&);  
  inline bool    wordIsIndexed(string);    
  inline bool    captionsContainWord(string);
  
  size_t  writefunc(char*, size_t, size_t, string*);
};



#endif // VIDEOCAPTIONS_H