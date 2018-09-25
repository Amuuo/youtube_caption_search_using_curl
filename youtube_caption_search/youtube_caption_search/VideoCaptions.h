
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
#include"Menu.h"

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


  static struct CaptionLine{
    
    static struct Time 
    {   
      Time(string,string,string);      
      int hr; 
      int min; 
      int sec;         
    };  

    CaptionLine(string,Time);
    string line;
    string timedURL;
    Time   contextTime;         
  };

  static struct CaptionWord 
  {
    using ContextPtr    = shared_ptr<CaptionLine>;
    using ContextPtrVec = vector<shared_ptr<CaptionLine>>;
    
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






  using MenuOptions         = Menu::MenuFunction;
  using MenuOptionsVec      = vector<MenuOptions>;
  using MenuOptionsVecPtr   = unique_ptr<vector<MenuOptions>>;
  

  //string  getCaptionClipURL(shared_ptr<CaptionLines>);  
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
  
  
  /*MenuOptionsVecPtr menuOptionsVecPtr
  {   
   {"Print most frequent words", 
    make_shared<function<void()>>([this]()
    {      
      int range = getUserInput<int>("Enter range");  
      const char* wordContextFormat = "\n\t(%d %-8s:  \"%s\"";
      int choice{displayPrintMenu()};


      if(choice != 4) printf("\n");
      
      for (int i = 0; i < range; ++i) 
      {            
        printf(wordContextFormat, 
        captionWordsSortedByFrequency[i]->captionContext.size(),           
        "mentions)",
        captionWordsSortedByFrequency[i]->word.c_str()); 
      }
  })
  },
   {"Search word",               make_shared<function<void()>>(searchForWord)},
   {"Print entire table",        make_shared<function<void()>>(searchFor),
   {"Print table to file",       make_shared<function<void()>>(option3)}};
  }*/

MenuOptionsVec menuOptionsVec
{     
  {
    "Search for word",
    make_shared<function<void()>>([this]()
    {
      auto searchWord = getUserInput<string>("Enter word");
      if (captionsContainWord(searchWord)) 
      {    
        printf("\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
               captionWordsIndex[searchWord]->captionContextsList.size(),           
               "mentions): ",
               searchWord.c_str());        
        printCaptionsToConsole(captionWordsIndex[searchWord], displayPrintMenu());    
      } 
      else 
      { 
        cout << "\n\nThat word was not found..."; 
      }
    })
  },
  
  {
    "Print Captions to File",
    make_shared<function<void()>>([this]()
    {
      ofstream outStream{getUserInput<string>("Save as")};               
      outStream << captionText;  
      outStream.close();
    })
  },
  
  {
    "Print Max Mentions",
    make_shared<function<void()>>([this]()
    {
      int range = getUserInput<int>("Enter range");  
      const char* wordContextFormat = "\n\t(%d %-8s:  \"%s\"";
      int choice{displayPrintMenu()};
      if(choice != 4) printf("\n");      
      for (int i = 0; i < range; ++i) 
      {            
        printf(wordContextFormat, 
               captionWordsSortedByFrequency[i]->captionContextsList.size(),           
               "mentions)",
               captionWordsSortedByFrequency[i]->word.c_str()); 
      }
    })
  }
};



//#endif // VIDEOCAPTIONS_H