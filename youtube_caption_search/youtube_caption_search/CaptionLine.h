#pragma once
#include<iostream>
#include<string>
#include<memory>
#include<vector>

using namespace std;


class CaptionLine {


public:

    static struct Time 
    {   
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
    Time   contextTime;
    
    
    using linePtr = shared_ptr<CaptionLine>;                                                 

    class CaptionWord 
    {
      using ContextPtr = vector<linePtr>;
    
      CaptionWord();
      CaptionWord(string, linePtr);
      ContextPtr captionContext;
      string     word;

      void addContextLine(linePtr);
    };
};

