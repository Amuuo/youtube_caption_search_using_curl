
#pragma once
#include"Time.h"

using namespace std;



/***********************************************************/
/*                C A P T I O N S T R U C T                */
/***********************************************************/
struct CaptionStruct{


  using captionTable  = map<string,set<CaptionStruct*>>;
  using captionLines  = vector<string>;
  using lineCheck     = map<string, CaptionStruct*>;
  using frequentWords = vector<pair<string,set<CaptionStruct*>>>;  
  using capPair       = pair<string,set<CaptionStruct*>>;

  


  /****************************************/
  /*      CONSTRUCTOR / DESTRUCTOR        */
  /****************************************/
  CaptionStruct(){}
  CaptionStruct(const string*& s, string l, string u, Time t) : 
    videoTitle{s}, 
    line {l}, 
    time {t}, 
    captionURL {constructTimestampedURL(t, u)} {}
  ~CaptionStruct(){}

  

  /****************************************/
  /*              VARIABLES               */
  /****************************************/
  const string*   videoTitle;
  string          line;
  string          captionURL;
  Time            time;
  static string   captionText;
  captionTable*   captionMap{};
  frequentWords*  maxMentionsVec{};



  /****************************************/
  /*         FUNCTION DEFINITIONS         */
  /****************************************/
  static void printCaptionsToFile();
  static void printCaptionsToConsole(CaptionStruct*, int);
  void cleanupCaptionString();
  void createCaptionMap(string*&);
  void deleteCommonWordsFromMap();
  string constructTimestampedURL(Time,string);
};

