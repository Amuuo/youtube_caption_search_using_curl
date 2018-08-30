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
    Time   _time;
    
  };
  
  static struct CaptionWord {
    CaptionWord(string, CaptionLine*);
    vector<CaptionLine*> captionContext;
    string               word{};
    int                  wordCounter{};
  };


  /***********************************/
  /*    CONSTRUCTOR / DESTRUCTOR     */
  /***********************************/
  VideoCaptions();
  ~VideoCaptions();  
    



private:
 
  /****************************************/
  /*              VARIABLES               */
  /****************************************/  
  
  // simplify typenames for easy reading
  using _frequentWords     = vector<CaptionWord>; 
  using _captionWordsIndex = map<string, CaptionWord*>;
  using _captionLines      = vector<CaptionLine>;
  using lineCheck          = map<string, CaptionLine>;

  
  _frequentWords*       captionWordsSortedByFrequency;
  _captionWordsIndex    captionWordsIndex{};
  _captionLines         captionLines;
  string                videoTitle;  
  string                videoURL;
  string                captionText{};

  
  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  string  getCaptionClipURL(CaptionWord,string);  
  void    printCaptionsToConsole(VideoCaptions*, int);
  void    cleanupCaptionDownloadFile();
  void    createCaptionMap();
  void    deleteCommonWordsFromMap();
  int     displayPrintMenu();
  void    createMostFrequentWordsVector();
  void    printTopTenMentions() const;
  void    sendWebRequestForCaptions();
  void    getCaptions();

  inline void  buildAndStoreCaptionLine(lineCheck&,string,string,CaptionLine&);
  inline void  indexWord(string, CaptionLine*);
  inline void  setWordsToLowercase(string);
  inline bool  lineIsNotAlreadyIndexed(lineCheck&, string&);
  inline bool  lineContainsTimeInfo(string);
  inline bool  nextLineIsACopy(istringstream&, string&, string&);
  inline void  indexWordsInCurrentLine(CaptionLine&);
  
  bool  wordIsIndexed(string);
  void  printCaptionsToFile();
  void  searchForWord();
  void  printMaxMentions();
  

  inline bool           captionsContainWord(string);
  inline static size_t  writefunc(char*, size_t, size_t, string*);
};

