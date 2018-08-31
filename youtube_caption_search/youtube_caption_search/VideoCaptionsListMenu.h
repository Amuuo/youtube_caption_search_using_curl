
#include"Menu.h"
#include"VideoCaptions.h"
#include<map>
#include<vector>


class VideoCaptionsListMenu : public Menu {

  using captionPtr = unique_ptr<VideoCaptions>;

public:

  VideoCaptionsListMenu(captionPtr);
  ~VideoCaptionsListMenu();


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

