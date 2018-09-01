
//#ifndef VIDEOCAPTIONS_H
//#define VIDEOCAPTIONS_H

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
#include<memory>
#include"userIO.h"
#include"MenuOptionsData.h"

using std::map;
using std::vector;
using std::shared_ptr;
using std::string;
using std::ofstream;
using std::istringstream;
using std::ifstream;
using std::getline;
using std::cout;
using std::to_string;
using std::make_shared;
using std::smatch;
using std::regex;
using std::regex_match;
using std::back_inserter;
using std::function;

/**********************************************************/
/*                V I D E O  C A P T I O N                */
/**********************************************************/
class VideoCaptions {


public:
  
  VideoCaptions();
  VideoCaptions(string);
  ~VideoCaptions();  
  

  static struct CaptionLine {   
    
    static struct Time {   
      Time();
      Time(string,string,string);      
      int hr; 
      int min; 
      int sec;         
    };  
    CaptionLine();
    CaptionLine(string, Time);

    string line;
    string timedURL;
    Time   _time;
    
  };
  
  using linePtr = shared_ptr<CaptionLine>;

  struct CaptionWord {

    using ContextPtr = vector<linePtr>;
    
    CaptionWord();
    CaptionWord(string, linePtr);
    ContextPtr captionContext;
    string     word;

    void addContextLine(linePtr);
  };

  //using menuOptionPtr = shared_ptr<MenuOptionsData>;
  //using menuOptionFunc = vector<menuOptionPtr>;

  string  getCaptionClipURL(shared_ptr<CaptionLine>);  
  void    printCaptionsToConsole(shared_ptr<CaptionWord>, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  
  
  void printCaptionsToFile();
  void searchForWord();
  void printMaxMentions();
  shared_ptr<vector<MenuOptionsData>> getMenuOptions();


protected:


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
  static string  captionText;
  
  
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
  
  static size_t  writefunc(char*, size_t, size_t, string*);
};



//#endif // VIDEOCAPTIONS_H