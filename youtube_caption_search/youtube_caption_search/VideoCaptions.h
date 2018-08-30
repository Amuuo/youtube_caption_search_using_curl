#pragma once
#include "CaptionInfo.h"
#include<unordered_map>


/***********************************************************/
/*           V I D E O  C A P T I O N  L I S T             */
/***********************************************************/
class VideoCaptions : public videoCaptionsList {


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
    CaptionLine(const string*, string, string, Time){}
    CaptionLine(){}

    vector<string> wordsInCaptionLine;
    string         line;
    Time           time;
    
  };
  
  static struct CaptionWord {
    CaptionLine* captionContext;
    string       word;
    int          wordCounter;
  };


private:

    
  /****************************************/
  /*              VARIABLES               */
  /****************************************/  
  
  // simplify typenames for easy reading
  using _frequentWords     = vector<CaptionWord>; 
  using _captionWordsIndex = unordered_map<string, CaptionWord*>;
  using _captionLines      = vector<CaptionLine>;

  
  _frequentWords*      captionWordsSortedByFrequency;
  _captionWordsIndex   captionWordsIndex;
  _captionLines        captionLines;
  string               videoTitle;  
  string               videoURL;
  string               captionText;

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  constructTimestampedURL(CaptionWord,string);  
  void    printCaptionsToFile();
  void    printCaptionsToConsole(videoCaptionsList*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  void    deleteCommonWordsFromMap();
  void    searchForWord() const;
  void    printMaxMentions() const;
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  
  
  inline bool           captionsContainWord(string);
  inline static size_t  writefunc(char*, size_t, size_t, string*);
};

