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
    CaptionWord(string, CaptionLine*);
    vector<CaptionLine*> captionContext;
    string               word{};
    int                  wordCounter{};
  };



private:
  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/  
  
  // simplify typenames for easy reading
  using _frequentWords     = vector<CaptionWord*>; 
  using _captionWordsIndex = map<string, CaptionWord*>;
  using _captionLines      = vector<CaptionLine*>;
  using lineCheck          = map<string, CaptionLine*>;

  
  _frequentWords      captionWordsSortedByFrequency;
  _captionWordsIndex  captionWordsIndex{};
  _captionLines       captionLines;
  string              videoTitle;  
  string              videoURL;
  string              videoID;
  string              captionText{};

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  getCaptionClipURL(CaptionLine*);  
  void    printCaptionsToConsole(CaptionWord*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  void    deleteCommonWordsFromMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  void    printCaptionsToFile();
  void    searchForWord();
  void    printMaxMentions();

  inline void  buildAndStoreCaptionLine(lineCheck&,string,string,CaptionLine&);
  inline void  indexWord(string, CaptionLine*);
  inline void  setWordsToLowercase(string);
  inline bool  lineIsNotAlreadyIndexed(lineCheck&, string&);
  inline bool  lineContainsTimeInfo(string);
  inline void  indexWordsInCurrentLine(CaptionLine&);
  inline bool  nextLineIsACopy(istringstream&, string&, string&);  
  inline bool  wordIsIndexed(string);    
  inline bool  captionsContainWord(string);
  
  size_t  writefunc(char*, size_t, size_t, string*);
};

#endif // VIDEOCAPTIONS_H