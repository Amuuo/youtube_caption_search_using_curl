
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
#include<unordered_set>
#include<regex>
#include<algorithm>
#include<functional>
#include<cstdio>
#include<future>
#include<wchar.h>


//#include<wwstring>
//#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include<memory>
#include<thread>


using std::map;
using std::vector;
using std::shared_ptr;
using std::wstring;
using std::ofstream;
using std::istringstream;
using std::wstringstream;
using std::ifstream;
using std::getline;
using std::cout;
using std::to_wstring;
using std::make_shared;
using std::smatch;
using std::regex;
using std::regex_match;
using std::back_inserter;
using std::function;
using std::wstring;
using std::wregex;



using namespace winrt;
using namespace Windows::Web::Http;


/**********************************************************/
/*                V I D E O  C A P T I O N                */
/**********************************************************/
class VideoCaptions 
{


public:

  static struct Time 
  {   
    Time();
    Time(const Time&);
    Time(Time&&);
    Time(wstring,wstring,wstring); 
    Time(int,int,int);
    int hr; 
    int min; 
    int sec;         
  }; 


  static struct CaptionLine
  {
    CaptionLine();
    CaptionLine(wstring,Time);
    wstring line;
    wstring timedURL;
    Time    time;         
  };


  static struct CaptionWord 
  {
    using ContextPtr    = shared_ptr<CaptionLine>;
    using ContextPtrSet = vector<shared_ptr<CaptionLine>>;
    
    CaptionWord();
    CaptionWord(wstring, ContextPtr);
    wstring       word;
    ContextPtrSet captionContextsList;

    void addContextLine(ContextPtr);
  };





  /****************************************/
  /*              VARIABLES               */
  /****************************************/  
  
  
  using mostMentionVec    = vector<shared_ptr<CaptionWord>>;
  using captionMap        = map<wstring,shared_ptr<CaptionWord>>;
  using captionLineMap    = map<wstring,shared_ptr<CaptionLine>>;
  using ContextPtr        = shared_ptr<CaptionLine>;


  VideoCaptions();
  VideoCaptions(wstring);
  ~VideoCaptions();  


  vector<shared_ptr<CaptionLine>> captionLines;
  mostMentionVec  captionWordsSortedByFrequency;
  captionMap      captionWordsIndex;  
  wstring         videoTitle;  
  wstring         videoURL;
  wstring         videoID;
  wstring         captionText;



  

  wstring  getCaptionClipURL(ContextPtr);  
  void     printCaptionsToConsole(shared_ptr<CaptionWord>, int);
  void     cleanupCaptionDownloadFile();
  void     createCaptionMap();
  int      displayPrintMenu();
  void     createMostFrequentWordsVector();
  void     printTopTenMentions() const;
  void     sendWebRequestForCaptions();
  void     getCaptions();
  
  
  //void printCaptionsToFile();
  void searchForWord();
  wstring printMaxMentions(int=10);



  
  



  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/


  inline void    buildCaptionLineAndWords(captionLineMap,wstring&);
  inline wstring  getWordURL(int); 
  inline void    deleteCommonWordsFromMap();
  inline void    indexWord(wstring&, ContextPtr);
  inline void    setWordsToLowercase(wstring&);
  inline bool    lineIsNotAlreadyIndexed(wstring&);
  inline bool    lineContainsTimeInfo(wstring&);
  inline void    indexWordsInCurrentLine(ContextPtr);
  inline bool    nextLineIsADuplicate(wstringstream&,wstring&, captionLineMap);  
  inline bool    wordIsIndexed(wstring);    
  inline bool    captionsContainWord(wstring);
  
  //static size_t  writefunc(char*, size_t, size_t, wstring*);
 
  
};