
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
  void setMenuOptions();
  function<void()> searchForWord()    const;
  function<void()> printMaxMentions() const;
  function<void()> printCaptionsToFile();

private:

  captionPtr captions;
  
};

