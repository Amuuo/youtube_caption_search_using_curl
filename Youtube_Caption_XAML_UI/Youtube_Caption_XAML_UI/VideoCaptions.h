
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
class VideoCaptions 
{


public:

  static struct Time 
  {   
    Time();
    Time(string,string,string);      
    int hr; 
    int min; 
    int sec;         
  }; 


  static struct CaptionLine
  {
    CaptionLine();
    CaptionLine(string,Time);
    string line;
    string timedURL;
    Time   contextTime;         
  };


  static struct CaptionWord 
  {
    using ContextPtr    = shared_ptr<CaptionLine>;
    using ContextPtrVec = vector<shared_ptr<CaptionLine>>;
    
    CaptionWord();
    CaptionWord(string, ContextPtr);
    ContextPtrVec captionContextsList;
    string        word;

    void addContextLine(ContextPtr);
  };





  /****************************************/
  /*              VARIABLES               */
  /****************************************/  
  
  
  using mostMentionVec    = vector<shared_ptr<CaptionWord>>;
  using captionMap        = map<string,shared_ptr<CaptionWord>>;
  using captionLineMap    = map<string,shared_ptr<CaptionLine>>;
  using ContextPtr        = shared_ptr<CaptionLine>;


  VideoCaptions();
  VideoCaptions(string);
  ~VideoCaptions();  


  mostMentionVec  captionWordsSortedByFrequency;
  captionMap      captionWordsIndex;  
  vector<string>  captionLines;
  string          videoTitle;  
  string          videoURL;
  string          videoID;
  string          captionText;



  

  string  getCaptionClipURL(ContextPtr);  
  void    printCaptionsToConsole(shared_ptr<CaptionWord>, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  
  
  //void printCaptionsToFile();
  //void searchForWord();
  //void printMaxMentions();



  
  



  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/


  inline void    buildCaptionLineAndWords(captionLineMap,string,string);
  inline string  getWordURL(int); 
  inline void    deleteCommonWordsFromMap();
  inline void    indexWord(string&, ContextPtr);
  inline void    setWordsToLowercase(string);
  inline bool    lineIsNotAlreadyIndexed(string&);
  inline bool    lineContainsTimeInfo(string&);
  inline void    indexWordsInCurrentLine(ContextPtr);
  inline bool    nextLineIsADuplicate(istringstream&,string&, captionLineMap&);  
  inline bool    wordIsIndexed(string);    
  inline bool    captionsContainWord(string);
  
  static size_t  writefunc(char*, size_t, size_t, string*);
  