#include "VideoCaptions.h"



VideoCaptions::VideoCaptions() {
}


VideoCaptions::~VideoCaptions() {
}

VideoCaptions::Time::Time(string h, string m, string s): hr{stoi(h)}, 
                                                         min{stoi(m)}, 
                                                         sec{stoi(s)} {}

VideoCaptions::CaptionLine::CaptionLine(const string* s, string l, string u, Time t) :
    videoTitle{s}, line {l}, time {t}, 
    captionURL {constructTimestampedURL(t, u)} {}
