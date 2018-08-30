#pragma once
#include "CaptionInfo.h"



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

  /****************************/
  /*           TIME           */
  /****************************/
  struct Time {     
    
    Time(){}
    Time(string,string,string){}  
    
    int hr, min, sec;         
  };
  /****************************/
  /*       CAPTION LINE       */
  /****************************/
  struct CaptionLine {
  
    CaptionLine(){}
    CaptionLine(const string* s, string l, string u, Time t) : 
    videoTitle{s}, line {l}, time {t}, 
    captionURL {constructTimestampedURL(t, u)} {}
  };

private:

    
  /****************************************/
  /*              VARIABLES               */
  /****************************************/
  frequentWords*  maxMentionsVec {};
  captionTable*   captionMap     {};
  const string*   videoTitle     {};
  static string   captionURL     {};
  static string   captionText    {};
  string          line           {};
  Time            time           {};


};

