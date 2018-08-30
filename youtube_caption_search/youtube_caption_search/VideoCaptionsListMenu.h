
#include"Menu.h"


class VideoCaptionsListMenu : protected Menu {

public:
  VideoCaptionsListMenu();
  ~VideoCaptionsListMenu();

  //add function to pull binary from file later
  virtual void  executeMenuSelection();
  virtual void  displayMenu();
  
  void loadVideoCaptionsList(); 
  void listAvailableVideoCaptions();
  void addVideoCaptions();
  void setMenuOptions();
  function<void()> searchForWord()    const;
  function<void()> printMaxMentions() const;
  function<void()> printCaptionsToFile();

private:
  

};

