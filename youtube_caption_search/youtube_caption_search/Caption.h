#pragma once
#include"VideoCaptions.h"


class Caption : public VideoCaptions 
{


  public:

    Caption();
    Caption(shared_ptr<CaptionWord> caption);
    ~Caption();
  
    function<void(vector<string>)> printStrings{[](vector<string> itemsToPrint) -> void {
      for (auto& capLine : itemsToPrint)
      printf("\n\t>> \"%s\"", capLine.c_str());
    }};
  
    MenuOptionsVecPtr captionPrintMenuOptionsVecPtr
    {
      {"1 - Print URL links",
       make_shared<function<void()>>([this]() 
       {
            

      }),
    "2 - Print context and URLs",
    "3 - Print context",
    "4 - Print words only",
    "5 - Export URLs to file",
    }
    };

    shared_ptr<CaptionWord> caption;
};

