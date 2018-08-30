

#include "VideoCaptions.h"



VideoCaptions::VideoCaptions(){}
VideoCaptions::~VideoCaptions(){}


VideoCaptions::CaptionLine::Time::Time(string h, 
                                       string m, 
                                       string s): hr{stoi(h)}, 
                                                  min{stoi(m)}, 
                                                  sec{stoi(s)} {}

VideoCaptions::CaptionLine::CaptionLine(string l, 
                                        Time t) : line {l}, 
                                                  time {t} {}


bool VideoCaptions::wordIsIndexed(string _word) {
  return captionWordsIndex.find(_word) == captionWordsIndex.end();
}

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
    case 1: printStrings({&c->videoURL});           break; //print url only
    case 2: printStrings({&c->line, &c->videoURL}); break; //print url+context
    case 3: printStrings({&c->line});               break; //print context only
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

  lineCheck      lineMap;
  string         lineInfo; 
  string         capLine;
  istringstream  captionStream{captionText};
  CaptionLine    currentLine;


  printf("\n>> Generating caption hash table...");


  while (captionStream/*is not at the end*/) {    
    getline(captionStream,lineInfo);        
    if (lineContainsTimeInfo(lineInfo)) {      
      if(nextLineIsACopy(captionStream,lineInfo,capLine)) {
        continue;      
      } else {
        setWordsToLowercase(capLine);
        if (lineIsNotAlreadyIndexed(lineMap,capLine)) {        
          buildAndStoreCaptionLine(lineMap,lineInfo,capLine,currentLine);                    
        }    
      }

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
string VideoCaptions::getCaptionClipURL(CaptionWord word, string userEnteredURL) {
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

void VideoCaptions::indexWord(string capWord, CaptionLine* capLine) {
  
  if (wordIsIndexed(capWord)) {
    captionWordsIndex[capWord]->wordCounter++;
    captionWordsIndex[capWord]->captionContext.push_back(capLine);
  }
  else{
    captionWordsIndex[capWord] = new CaptionWord{capWord, capLine};
  }  
}

void VideoCaptions::buildAndStoreCaptionLine(lineCheck& lineMap, 
                                             string capLine, 
                                             string lineInfo,
                                             CaptionLine& lineStruct) {  

  /* parse first three values of timestamp, ex: "00:00:00" */
  lineStruct = CaptionLine{capLine, {lineInfo.substr(0,2),
                                     lineInfo.substr(3,2),
                                     lineInfo.substr(6,2)}}; 
  lineMap[capLine] = lineStruct;
  captionLines.push_back(lineStruct);
}

inline void VideoCaptions::setWordsToLowercase(string line) {
  transform(line.begin(), line.end(), line.begin(), ::tolower);
}

inline bool VideoCaptions::lineIsNotAlreadyIndexed(lineCheck& lineMap,
                                            string& capLine){
  return lineMap.find(capLine) == lineMap.end();      
}

inline bool VideoCaptions::lineContainsTimeInfo(string line) {
  /* check for format, ex: "00:00:00 -> 00:00:00" */
  return isdigit(line[0]) && line[2] == ':';
}

inline bool VideoCaptions::nextLineIsACopy(istringstream& sstream, 
                                           string& prevLine,
                                           string& line) {
  getline(sstream, line);
  return prevLine == line;
}

inline void VideoCaptions::storeCaptionLineStruct(lineCheck& lineMap, 
                                                  string line,
                                                  CaptionLine& lineStruct) {

}

inline void VideoCaptions::indexWordsInCurrentLine(CaptionLine& currentLine) {
  
  istringstream lineStream{currentLine._line};
  string wordInCaptionLine;
  while (lineStream) {
  lineStream >> wordInCaptionLine;
  indexWord(wordInCaptionLine, &currentLine);
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

VideoCaptions::CaptionWord::CaptionWord(
  string _word, 
  CaptionLine* context) : word{_word}, captionContext{context} {
  
  ++wordCounter;
}
