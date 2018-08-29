
#pragma once
#include"Time.h"
using namespace std;



/***********************************************************/
/*                C A P T I O N S T R U C T                */
/***********************************************************/
struct CaptionStruct{

  using frequentWords = vector<pair<string,set<CaptionStruct*>>>;  
  using captionTable  = map<string,set<CaptionStruct*>>;
  using captionLines  = vector<string>;
  using lineCheck     = map<string, CaptionStruct*>;
  using capPair       = pair<string,set<CaptionStruct*>>;

  

  /****************************************/
  /*      CONSTRUCTOR / DESTRUCTOR        */
  /****************************************/
  CaptionStruct(){}
  CaptionStruct(const string*& s, string l, string u, Time t) : 
    videoTitle{s}, line {l}, time {t}, 
    captionURL {constructTimestampedURL(t, u)} {}
  ~CaptionStruct(){}

  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/
  const string*   videoTitle;
  static string   captionText;
  frequentWords*  maxMentionsVec{};
  captionTable*   captionMap{};
  string          line;
  string          captionURL;
  Time            time;



  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  static void  printCaptionsToFile();
  static void  printCaptionsToConsole(CaptionStruct*, int);
  string       constructTimestampedURL(Time,string);
  void         cleanupCaptionString();
  void         createCaptionMap(string*&);
  void         deleteCommonWordsFromMap();
  void         searchForWord(string);
};

