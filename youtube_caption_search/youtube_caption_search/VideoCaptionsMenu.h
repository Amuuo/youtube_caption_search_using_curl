

//#ifndef VIDEO_CAPTION_MENU_H
//#define VIDEO_CAPTION_MENU_H

#pragma once
#include<map>
#include<vector>
#include<memory>
#include"Menu.h"
#include"VideoCaptions.h"


using std::unique_ptr;


class VideoCaptionsMenu : public Menu {

  using captionPtr = unique_ptr<VideoCaptions>;

public:

  VideoCaptionsMenu(captionPtr);
  ~VideoCaptionsMenu();


  void loadVideoCaptionsList(); 
  void listAvailableVideoCaptions();
  void addVideoCaptions();


private:

  captionPtr captions;
  
};

//#endif //VIDEO_CAPTION_MENU_H

