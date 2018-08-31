

#include "VideoCaptions.h"



VideoCaptions::
VideoCaptions(){
  
}




VideoCaptions::
~VideoCaptions(){
  ofstream saveCaptionStruct{videoTitle, ofstream::binary};
  saveCaptionStruct.write((char*)this, sizeof(VideoCaptions));
}




VideoCaptions::CaptionLine::Time::
Time(string h, string m, string s): hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} {}




VideoCaptions::CaptionLine::
CaptionLine(string line, Time time) : line{line}, time{time} {}




VideoCaptions::CaptionWord::
CaptionWord(string word, linePtr captionLine) : word{ word } {
  captionContext.push_back(captionLine);
}




bool VideoCaptions::
wordIsIndexed(string word) {
  return captionWordsIndex.find(word) == captionWordsIndex.end();
}




/*****************************************/
/*         PRINT CAPTIONS TO FILE        */
/*****************************************/
function<void()> VideoCaptions::
printCaptionsToFile() {
  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << captionText;  
  outStream.close();
}




/*****************************************/
/*       PRINT CAPTIONS TO CONSOLE       */
/*****************************************/
void VideoCaptions::
printCaptionsToConsole(shared_ptr<CaptionWord> wordToPrint, int menuChoice) {
  
  auto printStrings = [](vector<string> itemsToPrint) {
    for (auto& capLine : itemsToPrint)
    printf("\n\t>> \"%s\"", capLine.c_str());
  };     

  switch (menuChoice) {      
    
    //print url only
    case 1: 
      printStrings({wordToPrint->captionContext[menuChoice]->timedURL});           
      break; 
    
    //print url+context
    case 2: 
      printStrings({wordToPrint->captionContext[menuChoice]->timedURL, 
                   getCaptionClipURL(wordToPrint->captionContext[menuChoice])}); 
      break; 
    
    //print context only
    case 3: 
      printStrings({wordToPrint->captionContext[menuChoice]->timedURL});               
      break; 
    
    default: 
      break;
  }
}




/*****************************************/
/*          CLEANUP CAPTION TEXT         */
/*****************************************/
void VideoCaptions::
cleanupCaptionDownloadFile(){

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
void VideoCaptions::
createCaptionMap() {

  map<string, CaptionLine> lineMap;
  
  string         lineInfo; 
  string         capLine;
  CaptionLine    currentLine;
  istringstream  captionStream{captionText};


  printf("\n>> Generating caption index...");



  while (captionStream) {    
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




/****************/
/*  INDEX WORD  */
/****************/
void VideoCaptions::
indexWord(string capWord, linePtr capLine) {
  
  if (wordIsIndexed(capWord)) {
    captionWordsIndex[capWord]->captionContext.push_back(capLine);
  }
  else{        
    captionWordsIndex[capWord] = wordPtr{new CaptionWord{capWord, capLine}};
  }  
}




/**********************************/
/*  BUILD AND STORE CAPTION LINE  */
/**********************************/
void VideoCaptions::
buildAndStoreCaptionLine(map<string,CaptionLine> lineMap, 
                         string capLine, 
                         string lineInfo,
                         CaptionLine& lineStruct) {  

  /* parse first three values of timestamp, ex: "00:00:00" */
  lineStruct = CaptionLine{capLine, {lineInfo.substr(0,2),
                                     lineInfo.substr(3,2),
                                     lineInfo.substr(6,2)}}; 
  
  lineMap[capLine] = lineStruct;
}




/**********************************/
/*     SET WORDS TO LOWERCASE     */
/**********************************/
inline void VideoCaptions::
setWordsToLowercase(string line) {
  transform(line.begin(), line.end(), line.begin(), ::tolower);
}




/*********************************/
/*  LINE IS NOT ALREADY INDEXED  */
/*********************************/
inline bool VideoCaptions::
lineIsNotAlreadyIndexed(map<string,CaptionLine> lineMap, string& capLine){
  return lineMap.find(capLine) == lineMap.end();      
}




/**********************************/
/*    LINE CONTAINS TIME INFO     */
/**********************************/
inline bool VideoCaptions::
lineContainsTimeInfo(string line) {
  /* check for format, ex: "00:00:00 -> 00:00:00" */
  return isdigit(line[0]) && line[2] == ':';
}




/*********************************/
/*      NEXT LINE IS A COPY      */
/*********************************/
inline bool VideoCaptions::
nextLineIsACopy(istringstream& sstream, string& prevLine, string& line) {
  getline(sstream, line);
  return prevLine == line;
}




/***********************************/
/*   INDEX WORDS IN CURRENT LINE   */
/***********************************/
inline void VideoCaptions::
indexWordsInCurrentLine(CaptionLine& currentLine) {
  
  istringstream lineStream{currentLine.line};
  string wordInCaptionLine;
  while (lineStream) {
    lineStream >> wordInCaptionLine;
    indexWord(wordInCaptionLine, &currentLine);
  }
}






inline string VideoCaptions::
getWordURL(int) {

  return ;
}

/******************************************/
/*      DELETE COMMON WORDS FROM MAP      */
/******************************************/
void VideoCaptions::
deleteCommonWordsFromMap() {
  
  printf("\n>> Deleting all common words from table...");

  string   commonWord;
  ifstream commonWordsStream{"commonWords.txt"};

  while (commonWordsStream) {    
    getline(commonWordsStream, commonWord);
    if (captionWordsIndex.find(commonWord) != captionWordsIndex.end()){
      captionWordsIndex.erase(commonWord);
    }
  }
}




/******************************************/
/*        CONSTRUCT TIMESTAMPED URL       */
/******************************************/
string VideoCaptions::
getCaptionClipURL(shared_ptr<CaptionLine> line) {
  
  return "www.youtube.com/watch&feature=youtu.be&t="  + 
         to_string(line->time.hr)  + 'h' + 
         to_string(line->time.min) + 'm' + 
         to_string(line->time.sec) + 's' + videoID;
}




/*****************************************/
/*         CAPTION CONTAINS WORD         */
/*****************************************/
inline bool VideoCaptions::
captionsContainWord(string searchWord) { 
  return captionWordsIndex.find(searchWord) != captionWordsIndex.end();
  
}


/*****************************************/
/*            SEARCH FOR WORD            */
/*****************************************/
function<void()> VideoCaptions::
searchForWord() {      

  string searchWord = getUserInput<string>("Enter word");
  
  if (captionsContainWord(searchWord)) {
    
    printf("\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
           captionWordsIndex[searchWord]->captionContext.size(),           
           "mentions): ",
           searchWord.c_str());
        
    printCaptionsToConsole(captionWordsIndex[searchWord], displayPrintMenu());
    
  } else { cout << "\n\nThat word was not found..."; }
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

  for(auto currentWord : captionWordsIndex){      
    captionWordsSortedByFrequency.push_back(currentWord.second);
  }  
  sort(captionWordsSortedByFrequency.begin(), 
       captionWordsSortedByFrequency.end(), 
       [](wordPtr p1, wordPtr p2) {
          return p1->captionContext.size() > p2->captionContext.size();});

}




/*****************************************/
/*         PRINT TOP TEN MENTIONS        */
/*****************************************/
/* 
 * prints 10 most used words
 * format: "word(10)" 
 */
void VideoCaptions::printTopTenMentions() const {
  
  printf("\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  
  for (int i=0; i<10; ++i) {
    printf("%s(%d), ", captionWordsSortedByFrequency[i]->word.c_str(), 
                       captionWordsSortedByFrequency[i]->captionContext.size());
    if(i % 2 == 0) 
      printf("\n\t\t");
  }
}




/******************************************/
/*               WRITEFUNC                */
/******************************************/
size_t VideoCaptions::writefunc(char* ptr, size_t size, size_t nmemb, string* s) {
  
  captionText += string{ptr + '\0'};
  return size*nmemb;
}




/******************************************/
/*      SEND WEB-REQUEST FOR CAPTIONS     */
/******************************************/
void VideoCaptions::sendWebRequestForCaptions() {

  string new_url{"http://video.google.com/timedtext?type=track&lang=en&v="};
  regex rgx("v=(.{11})");
  smatch video_id_match;
  regex_search(videoURL, video_id_match, rgx);
  videoID = video_id_match[1];
  videoURL = new_url + string{video_id_match[1]};
  

  string r{"start: "};

  CURL* curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, videoURL.c_str());
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

shared_ptr<vector<MenuOptionsData>> VideoCaptions::getMenuOptions() {
  return make_shared<vector<MenuOptionsData>>(menuOptions);
}





/*****************************************/
/*          PRINT MAX MENTIONS           */
/*****************************************/
function<void()> VideoCaptions::printMaxMentions() {

  int range = getUserInput<int>("Enter range");  
  const char* wordContextFormat = "\n\t(%d %-8s:  \"%s\"";
  int choice{displayPrintMenu()};


  if(choice != 4) printf("\n");
      
  for (int i = 0; i < range; ++i) {            
    printf(wordContextFormat, 
           captionWordsSortedByFrequency[i]->captionContext.size(),           
           "mentions)",
           captionWordsSortedByFrequency[i]->word.c_str());                          
  }  
}





VideoCaptions::CaptionWord::
CaptionWord(string word, shared_ptr<CaptionLine> context) : word{word} {
  captionContext.push_back(context);
}





void VideoCaptions::CaptionWord::
addContextLine(linePtr contextLine) {
  captionContext.push_back(contextLine);
}
