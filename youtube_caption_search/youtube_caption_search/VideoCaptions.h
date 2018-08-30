#pragma once
#include"VideoCaptionsList.h"
#include<functional>
#include<vector>
#include<unordered_map>


/***********************************************************/
/*           V I D E O  C A P T I O N  L I S T             */
/***********************************************************/
class VideoCaptions : public VideoCaptionsList {


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

    string line;
    Time   time;
    
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

  
  _frequentWords*       captionWordsSortedByFrequency;
  _captionWordsIndex*   captionWordsIndex;
  _captionLines         captionLines;
  string                videoTitle;  
  string                videoURL;
  string                captionText{};

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  constructTimestampedURL(CaptionWord,string);  
  void    printCaptionsToConsole(VideoCaptions*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  void    deleteCommonWordsFromMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();
  
  
  void  printCaptionsToFile();
  void  searchForWord();
  void  printMaxMentions();
  

  inline bool           captionsContainWord(string);
  inline static size_t  writefunc(char*, size_t, size_t, string*);
};

