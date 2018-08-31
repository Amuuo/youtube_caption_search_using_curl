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

using namespace std;


/**********************************************************/
/*                V I D E O  C A P T I O N                */
/**********************************************************/
class VideoCaptions {


public:
  
  /***********************************/
  /*    CONSTRUCTOR / DESTRUCTOR     */
  /***********************************/
  VideoCaptions();
  ~VideoCaptions();  
  
  
  /****************************************/
  /*          CAPTION STRUCTURES          */
  /****************************************/
  static struct CaptionLine {   
    
    static struct Time {   
      Time(){}
      Time(string,string,string){}      
      int hr, min, sec;         
    };  
    CaptionLine(string, Time){}
    CaptionLine(){}

    string _line;
    string timedURL;
    Time   _time;
    
  };
  
  static struct CaptionWord {

    using ContextPtr = vector<shared_ptr<CaptionLine>>;
    
    CaptionWord(string, shared_ptr<CaptionLine>);
    ContextPtr captionContext;
    string     word{};

    void addContextLine(shared_ptr<CaptionLine>);
  };

protected:
    vector<menuOptionsData> menuOptions{
    {"Print most frequent words", &printMaxMentions()},
    {"Search word", searchForWord()},
    {"Print entire table", printMaxMentions()},
    {"Print table to file", printCaptionsToFile()}};

private:
  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/  

  vector<shared_ptr<CaptionWord>>      captionWordsSortedByFrequency{};
  map<string, shared_ptr<CaptionWord>> captionWordsIndex{};
  vector<unique_ptr<CaptionLine>>      captionLines{};
  
  string  videoTitle;  
  string  videoURL;
  string  videoID;
  string  captionText{};

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  getCaptionClipURL(CaptionLine*);  
  void    printCaptionsToConsole(CaptionWord*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  void    printCaptionsToFile();
  void    searchForWord();
  void    printMaxMentions();

  inline string  getWordURL(int); 
  inline void    deleteCommonWordsFromMap();
  inline void    buildAndStoreCaptionLine(map<string,CaptionLine*>&,string,string,CaptionLine&);
  inline void    indexWord(string, CaptionLine*);
  inline void    setWordsToLowercase(string);
  inline bool    lineIsNotAlreadyIndexed(map<string,CaptionLine*>&, string&);
  inline bool    lineContainsTimeInfo(string);
  inline void    indexWordsInCurrentLine(CaptionLine&);
  inline bool    nextLineIsACopy(istringstream&, string&, string&);  
  inline bool    wordIsIndexed(string);    
  inline bool    captionsContainWord(string);
  
  size_t  writefunc(char*, size_t, size_t, string*);
};



#endif // VIDEOCAPTIONS_H