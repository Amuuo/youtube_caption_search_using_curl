#include "CaptionLine.h"



CaptionLine::CaptionLine() 
{
}


CaptionLine::
CaptionLine(string line, Time _time) : line{line}, contextTime{_time} 
{
}


CaptionLine::Time::Time(){}




CaptionLine::Time::
Time(string h, string m, string s): hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} {}




CaptionLine::CaptionWord::CaptionWord() {}




CaptionLine::CaptionWord::
CaptionWord(string word, linePtr context) : word{word} {
  captionContext.push_back(context);
}




void CaptionLine::CaptionWord::
addContextLine(linePtr contextLine) {
  captionContext.push_back(contextLine);
}
