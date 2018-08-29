
#include"main.h"


int main(int argc, char** argv){

  Captions = new CaptionStruct;
  string* videoUrl{getVideoUrl(argc!=2, argv)};
  
  sendRequestForCaptions(*videoUrl);
  
  Captions->cleanupCaptionString();  
  Captions->createCaptionMap(videoUrl);
  Captions->deleteCommonWordsFromMap();  
  
  createMostFrequentWordsVector();
  
  
  /**************************/
  /* loop through user mode */
  /**************************/
  while(userInteraction()); 
 
  return 0;
}




bool userInteraction() {
  printSnapShot();
  switch (getMainMenuSelection()) { 
    case 1: printMaxMentions(getUserInput<int>("Enter range")); break;      
    case 2: searchWord(getUserInput<string>("Enter word"));     break;      
    case 3: printMaxMentions(Captions->captionMap->size(),'r'); break;
    case 4: CaptionStruct::printCaptionsToFile();               break;
    case 5: exit(1);                                            break;      
    default:                                                    break;
  } 
  return true;
}










string* getVideoUrl(bool commandLineUrl, char** args) {
  if (commandLineUrl)
    return new string{getUserInput<string>("Enter URL")}; 
  else
    return new string{args[1]};
}





void printSnapShot() {
  printf("\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  for (int i{1}; i<=10; ++i) {
    printf("%s(%d), ", maxMentionsVec->at(i).first.c_str(), 
                       maxMentionsVec->at(i).second.size());
    if(i % 2 == 0) 
      printf("\n\t\t");
  }
}




size_t writefunc(char *ptr, size_t size, size_t nmemb, string* s) {  

  *s += string{ptr + '\0'};
  Captions.captionText += *s;
  return size*nmemb;
}




void sendRequestForCaptions(string url) {
  
  string new_url{"http://video.google.com/timedtext?type=track&lang=en&v="};
  regex rgx("v=(.{11})");
  smatch video_id_match;
  regex_search(url, video_id_match, rgx);
  url = new_url + string{video_id_match[1]};
  

  CURL* curl;
  CURLcode response;

  string r{"start: "};

  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  regex rgx2("(<text.{3})*");
  smatch cap_match;

  regex_search(Captions.captionText.cbegin(), Captions.captionText.cend(), cap_match, rgx2);
                            
}




template<typename type_>
type_ getUserInput(string prompt) {
  printf("\n\t%s: ", prompt.c_str());
  type_ tmp;
  cin >> tmp;
  return tmp;
}




void printMaxMentions(int range, char r) {
  
  static const char* format = "\n\t(%d %-8s:  \"%s\"";
  int choice{askPrintOptions()};

  if(choice != 4) printf("\n");

  if (r == 'r') {    
    for (auto i{maxMentionsVec->rbegin()}; i!=maxMentionsVec->rend(); ++i) {      
      printf(format, i->second.size(), "mentions)", i->first.c_str());                
      
      for (auto& c : i->second)
          CaptionStruct::printCaptionsToConsole(c, choice);
    } 
  } else {        
    for (int i = 0; i < range; ++i) {            
      printf(format, maxMentionsVec->at(i).second.size(),           
                     "mentions)",
                     maxMentionsVec->at(i).first.c_str());                
      
      for (auto& c : maxMentionsVec->at(i).second)
          CaptionStruct::printCaptionsToConsole(c, choice);          
    }
  }
}




int askPrintOptions() {
    
  printf("\n\n\t1 - Print URL links"       );
  printf(  "\n\t2 - Print context and URLs");
  printf(  "\n\t3 - Print context"         );
  printf(  "\n\t4 - Print words only"      );
  printf(  "\n\t5 - Export URLs to file\n" );
  
  return getUserInput<int>("Selection");
}




void createMostFrequentWordsVector() {
  
  maxMentionsVec = new frequentWords{};
  
  printf("\n>> Sorting words by number of mentions..."); 

  for(auto& m : *captionMap){      
    maxMentionsVec->push_back({make_pair(m.first, m.second)});
  }
  sort(maxMentionsVec->begin(), 
       maxMentionsVec->end(), 
       [](pair<string, set<CaptionStruct*>> p1, 
          pair<string, set<CaptionStruct*>> p2) {
          return p1.second.size() > p2.second.size(); });
}




int getMainMenuSelection() {
  
  printf("\n\n\t1 - Print most frequent words");
  printf(  "\n\t2 - Search word"              );
  printf(  "\n\t3 - Print entire table"       );
  printf(  "\n\t4 - Print table to file"      );
  printf(  "\n\t5 - Exit Program\n"           );
    
  return getUserInput<int>("Selection");
}























