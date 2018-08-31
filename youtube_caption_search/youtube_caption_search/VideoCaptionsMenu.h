
#pragma once

#ifndef VIDEO_CAPTION_MENU_H
#define VIDEO_CAPTION_MENU_H

#include"Menu.h"
#include"VideoCaptions.h"
#include<map>
#include<vector>


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

#endif //VIDEO_CAPTION_MENU_H

