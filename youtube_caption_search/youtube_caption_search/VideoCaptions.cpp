#include "VideoCaptions.h"



VideoCaptions::VideoCaptions() {
}


VideoCaptions::~VideoCaptions() {
}

VideoCaptions::CaptionLine::Time::Time(string h, string m, string s): 
                                   hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} {}

VideoCaptions::CaptionLine::CaptionLine(const string* s, string l, string u, Time t) :
    videoTitle{s}, line {l}, time {t}, 
    videoURL {constructTimestampedURL(t, u)} {}


/*****************************************/
/*         PRINT CAPTIONS TO FILE        */
/*****************************************/
void VideoCaptions::printCaptionsToFile() {
  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << captionText;  
  outStream.close();
}




/*****************************************/
/*       PRINT CAPTIONS TO CONSOLE       */
/*****************************************/
void VideoCaptions::printCaptionsToConsole(VideoCaptions* c, int choice) {
  auto printStrings = [](vector<string*> tmp) {
    for (auto& t : tmp)
    printf("\n\t>> \"%s\"", t->c_str());
  };     

  switch (choice) {      
    case 1: printStrings({&c->captionURL});           break; //print url only
    case 2: printStrings({&c->line, &c->captionURL}); break; //print url+context
    case 3: printStrings({&c->line});                 break; //print context only
    default: break;
  }
}




/*****************************************/
/*          CLEANUP CAPTION TEXT         */
/*****************************************/
void VideoCaptions::cleanupCaptionDownloadFile(){

  printf("\n>> Parsing caption file...");

  string* caps = &captionText;
  string insert{};

  regex parser1{"<[^>]*>"};
  regex parser2{"-->.*%"};
  regex parser3{"\\.\\d{3}"};


  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser1, "");
  *caps = insert;
  insert.clear();
  
  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser2, "");
  *caps = insert;
  insert.clear();
  
  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser3, "");
  *caps = insert;
  insert.clear();
}




/*****************************************/
/*           CREATE CAPTION MAP          */
/*****************************************/
void VideoCaptions::createCaptionMap() {

  captionMap = new captionTable{};
  lineCheck*   lineMap{new lineCheck};
  string       tmpStr[2];


  printf("\n>> Generating caption hash table...");

  istringstream   fileStringStream{captionText};
  VideoCaptions*  tmpCap;

  while (fileStringStream) {
    
    getline(fileStringStream,tmpStr[0]);
    
    if (isdigit(tmpStr[0][0]) && tmpStr[0][2] == ':') {
      
      //string tmpS2{};
      getline(fileStringStream, tmpStr[1]);
      if (tmpStr[0] == tmpStr[1]) {
        continue;
      }
      if (lineMap->find(tmpStr[2]) == lineMap->end()) {
        
        tmpCap = new VideoCaptions{videoTitle, 
                                   tmpStr[1], 
                                   captionURL, 
                                   Time{tmpStr[0].substr(0,2), 
                                        tmpStr[0].substr(3,2), 
                                        tmpStr[0].substr(6.2)}};

        lineMap->insert(make_pair(tmpStr[2],tmpCap));
      }            

      istringstream lineStringStream(tmpStr[2]);
      while (lineStringStream) {
        lineStringStream >> tmpStr[0];
        transform(tmpStr[0].begin(), 
                  tmpStr[0].end(), 
                  tmpStr[0].begin(), 
                  ::tolower);
        (*captionMap)[tmpStr[0]].insert(tmpCap);
      }
    }
  }
}




/******************************************/
/*      DELETE COMMON WORDS FROM MAP      */
/******************************************/
void VideoCaptions::deleteCommonWordsFromMap() {
  
  printf("\n>> Deleting insignificant words from table...");

  string   commonWord;
  ifstream commonWordsStream{"commonWords.txt"};

  while (commonWordsStream) {    
    getline(commonWordsStream, commonWord);
    if (captionMap->find(commonWord) != captionMap->end()){
      captionMap->erase(commonWord);
    }
  }
}




/******************************************/
/*        CONSTRUCT TIMESTAMPED URL       */
/******************************************/
string VideoCaptions::constructTimestampedURL(CaptionWord word, string userEnteredURL) {
  return userEnteredURL + "&feature=youtu.be&t="  + 
         to_string(word.captionContext->time.hr)  + 'h' + 
         to_string(word.captionContext->time.min) + 'm' + 
         to_string(word.captionContext->time.sec) + 's';
}




/*****************************************/
/*         CAPTION CONTAINS WORD         */
/*****************************************/
inline bool VideoCaptions::captionsContainWord(string searchWord) { 
  return captionWordsIndex.find(searchWord) != captionWordsIndex.end();
  
}


/*****************************************/
/*            SEARCH FOR WORD            */
/*****************************************/
void VideoCaptions::searchForWord() const {      

  string searchWord = getUserInput<string>("Enter word");

  
  if (captionsContainWord(searchWord)) {
    
    printf("\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
           captionMap->at(searchWord).size(),           
           "mentions): ",
           searchWord.c_str());
    
    int choice = displayPrintMenu();        
    for (auto& c : captionMap->at(searchWord)) {
      printCaptionsToConsole(c, choice);
    }
  } else {
    cout << "\n\nThat word was not found...";
  }
}






/****************************************/
/*          DISPLAY PRINT MENU          */
/****************************************/
int VideoCaptions::displayPrintMenu() {
    
  printf("\n\n\t1 - Print URL links"       );
  printf(  "\n\t2 - Print context and URLs");
  printf(  "\n\t3 - Print context"         );
  printf(  "\n\t4 - Print words only"      );
  printf(  "\n\t5 - Export URLs to file\n" );
  
  return getUserInput<int>("Selection");
}




/*****************************************/
/*   CREATE MOST FREQUENT WORDS VECTOR   */
/*****************************************/
void VideoCaptions::createMostFrequentWordsVector() {
    
  printf("\n>> Sorting words by number of mentions..."); 

  for(auto& m : *captionMap){      
    captionWordsSortedByFrequency->push_back({make_pair(m.first, m.second)});
  }
  sort(captionWordsSortedByFrequency->begin(), 
       captionWordsSortedByFrequency->end(), 
       [](pair<string, set<VideoCaptions*>> p1, 
          pair<string, set<VideoCaptions*>> p2) {
          return p1.second.size() > p2.second.size(); });

}




/*****************************************/
/*         PRINT TOP TEN MENTIONS        */
/*****************************************/
void VideoCaptions::printTopTenMentions() const {
  printf("\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  for (int i{1}; i<=10; ++i) {
    printf("%s(%d), ", captionWordsSortedByFrequency->at(i).first.c_str(), 
                       captionWordsSortedByFrequency->at(i).second.size());
    if(i % 2 == 0) 
      printf("\n\t\t");
  }
}




/******************************************/
/*               WRITEFUNC                */
/******************************************/
size_t VideoCaptions::writefunc(char* ptr, size_t size, size_t nmemb, string* s) {
  
  captionText += string{ptr + '\0'};
  //*s += string{ptr + '\0'};
  //captionText += *s;
  return size*nmemb;
}




/******************************************/
/*      SEND WEB-REQUEST FOR CAPTIONS     */
/******************************************/
void VideoCaptions::sendWebRequestForCaptions() {

  string new_url{"http://video.google.com/timedtext?type=track&lang=en&v="};
  regex rgx("v=(.{11})");
  smatch video_id_match;
  regex_search(captionURL, video_id_match, rgx);
  captionURL = new_url + string{video_id_match[1]};
  

  string r{"start: "};

  CURL* curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, captionURL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  regex rgx2("(<text.{3})*");
  smatch cap_match;

  regex_search(captionText.cbegin(), captionText.cend(), cap_match, rgx2);
}





/******************************************/
/*              GET CAPTIONS              */
/******************************************/
void VideoCaptions::getCaptions() {

  sendWebRequestForCaptions();  
  cleanupCaptionDownloadFile();  
  createCaptionMap();
  deleteCommonWordsFromMap();    
  createMostFrequentWordsVector();
}





/*****************************************/
/*          PRINT MAX MENTIONS           */
/*****************************************/
void VideoCaptions::printMaxMentions() const {

  int range = getUserInput<int>("Enter range");
  
  static const char* format = "\n\t(%d %-8s:  \"%s\"";
  int choice{displayPrintMenu()};

  if(choice != 4) printf("\n");

  if (r == 'r') {    
    for (auto i{captionWordsSortedByFrequency->rbegin()}; i!=captionWordsSortedByFrequency->rend(); ++i) {      
      printf(format, i->second.size(), "mentions)", i->first.c_str());                
      
      for (auto& c : i->second)
          VideoCaptions::printCaptionsToConsole(c, choice);
    } 
  } else {        
    for (int i = 0; i < range; ++i) {            
      printf(format, captionWordsSortedByFrequency->at(i).second.size(),           
                     "mentions)",
                     captionWordsSortedByFrequency->at(i).first.c_str());                
      
      for (auto& c : captionWordsSortedByFrequency->at(i).second)
          VideoCaptions::printCaptionsToConsole(c, choice);          
    }
  }
}

