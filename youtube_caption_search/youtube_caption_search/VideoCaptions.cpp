

#include "VideoCaptions.h"



VideoCaptions::
VideoCaptions()
{  
}



VideoCaptions::VideoCaptions(string url) : videoURL{url} 
{    
  getCaptions();
}



VideoCaptions::
~VideoCaptions()
{
  ofstream saveCaptionStruct{videoTitle, ofstream::binary};
  saveCaptionStruct.write((char*)this, sizeof(VideoCaptions));
}



VideoCaptions::CaptionLine::Time::
Time(string h, string m, string s): hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} 
{
}



VideoCaptions::CaptionLine::
CaptionLine(string line, Time time) : line{line}, contextTime{time} 
{
}



VideoCaptions::CaptionWord::
CaptionWord(string word, ContextPtr context) : word{word} {
  captionContexts.push_back(context);
}




void VideoCaptions::CaptionWord::
addContextLine(ContextPtr contextLine) {
  captionContexts.push_back(contextLine);
}




bool VideoCaptions::
wordIsIndexed(string word) 
{
  return captionWordsIndex.find(word) == captionWordsIndex.end();
}




/*****************************************/
/*         PRINT CAPTIONS TO FILE        */
/*****************************************/
void VideoCaptions::
printCaptionsToFile() 
{
  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << captionText;  
  outStream.close();
}




/****************************************/
/*          DISPLAY PRINT MENU          */
/****************************************/
int VideoCaptions::
displayPrintMenu() 
{
  return getUserInput<int>("Selection");
}





/*****************************************/
/*       PRINT CAPTIONS TO CONSOLE       */
/*****************************************/
void VideoCaptions::
printCaptionsToConsole(shared_ptr<CaptionWord> wordToPrint, int menuChoice) 
{
  switch (menuChoice) 
  {        
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
cleanupCaptionDownloadFile()
{
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
createCaptionMap() 
{
  captionLineMap          tmpLineMap;
  string                  currentLine; 
  string                  nextLine; 
  CaptionLine::Time       time;
  istringstream           captionStream{captionText};
  shared_ptr<CaptionLine> currentLinePtr{};

  printf("\n>> Generating caption index...");



  while (captionStream) 
  {        
    getline(captionStream,currentLine);        
    
    if(lineContainsTimeInfo(currentLine)) 
    {      
      if(nextLineIsADuplicate(captionStream,currentLine, tmpLineMap)) 
      {
        continue;      
      } 
      else
      {
        setWordsToLowercase(nextLine);
        
        if(lineIsNotAlreadyIndexed(nextLine)) 
        {        
          buildCaptionLineAndWords(tmpLineMap,currentLine,nextLine);                            
        }   
      }
    }
  }
}




/****************/
/*  INDEX WORD  */
/****************/
void VideoCaptions::
indexWord(string& capWord, ContextPtr capLinePtr) 
{
  if (wordIsIndexed(capWord)) 
  {
    captionWordsIndex[capWord]->captionContextsList.push_back(capLinePtr);
  }
  else
  {        
    captionWordsIndex[capWord] = make_shared<shared_ptr<CaptionWord>>(capWord, capLinePtr);
  }  
}




/**********************************/
/*  BUILD AND STORE CAPTION LINE  */
/**********************************/
void VideoCaptions::
buildCaptionLineAndWords(captionLineMap lineMap, 
                         string      capLine, 
                         string      lineInfo) 
{  
  using CaptionLine = VideoCaptions::CaptionLine;
  using Time        = CaptionLine::Time;
  
  /* parse first three values of timestamp, ex: "00:00:00" */
  lineMap[capLine] = make_shared<CaptionLine>(
                                capLine, Time{lineInfo.substr(0,2),
                                              lineInfo.substr(3,2),
                                              lineInfo.substr(6,2)}
                        ); 


  indexWordsInCurrentLine(lineMap[capLine]);
}




/**********************************/
/*     SET WORDS TO LOWERCASE     */
/**********************************/
inline void VideoCaptions::
setWordsToLowercase(string line) 
{
  transform(line.begin(), line.end(), line.begin(), ::tolower);
}




/*********************************/
/*  LINE IS NOT ALREADY INDEXED  */
/*********************************/
inline bool VideoCaptions::
lineIsNotAlreadyIndexed(string& capLine)
{
  return captionWordsIndex.find(capLine) == captionWordsIndex.end();      
}




/**********************************/
/*    LINE CONTAINS TIME INFO     */
/**********************************/
inline bool VideoCaptions::
lineContainsTimeInfo(string line) 
{
  /* check for format, ex: "00:00:00 -> 00:00:00" */
  return isdigit(line[0]) && line[2] == ':';
}

                      


/*********************************/
/*      NEXT LINE IS A COPY      */
/*********************************/
inline bool VideoCaptions::
nextLineIsADuplicate(istringstream& sstream, 
                     string& nextLine, 
                     map<string,CaptionLine>& tmpLineMap) 
{
  getline(sstream, nextLine);
  
  // if the temporary map find the line just taken
  return tmpLineMap.find(nextLine) != tmpLineMap.end();
}




/***********************************/
/*   INDEX WORDS IN CURRENT LINE   */
/***********************************/
inline void VideoCaptions::
indexWordsInCurrentLine(ContextPtr currentLine) 
{ 
  istringstream lineStream{currentLine->line};
  string wordInCaptionLine;
  
  while (lineStream) 
  {
    lineStream >> wordInCaptionLine;
    indexWord(wordInCaptionLine, currentLine);
  }
}



inline string VideoCaptions::
getWordURL(int) 
{
}




/******************************************/
/*      DELETE COMMON WORDS FROM MAP      */
/******************************************/
void VideoCaptions::
deleteCommonWordsFromMap() 
{ 
  printf("\n>> Deleting all common words from table...");

  string   commonWord;
  ifstream commonWordsStream{"commonWords.txt"};

  while (commonWordsStream) 
  {    
    getline(commonWordsStream, commonWord);
    
    if (captionWordsIndex.find(commonWord) != captionWordsIndex.end())
    {
      captionWordsIndex.erase(commonWord);
    }
  }
}




/******************************************/
/*        CONSTRUCT TIMESTAMPED URL       */
/******************************************/
string VideoCaptions::
getCaptionClipURL(shared_ptr<CaptionLine> line) 
{  
  return "www.youtube.com/watch&feature=youtu.be&t="  + 
         to_string(line->_time.hr)  + 'h' + 
         to_string(line->_time.min) + 'm' + 
         to_string(line->_time.sec) + 's' + videoID;
}




/*****************************************/
/*         CAPTION CONTAINS WORD         */
/*****************************************/
inline bool VideoCaptions::
captionsContainWord(string searchWord) 
{ 
  return captionWordsIndex.find(searchWord) != captionWordsIndex.end();  
}


/*****************************************/
/*            SEARCH FOR WORD            */
/*****************************************/
void VideoCaptions::
searchForWord() 
{      
  auto searchWord = getUserInput<string>("Enter word");
  
  if (captionsContainWord(searchWord)) 
  {    
    printf("\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
           captionWordsIndex[searchWord]->captionContextsList.size(),           
           "mentions): ",
           searchWord.c_str());
        
    printCaptionsToConsole(captionWordsIndex[searchWord], displayPrintMenu());  
  } 
  else 
  { 
    cout << "\n\nThat word was not found..."; 
  }
}





/*****************************************/
/*   CREATE MOST FREQUENT WORDS VECTOR   */
/*****************************************/
void VideoCaptions::
createMostFrequentWordsVector() 
{    
  printf("\n>> Sorting words by number of mentions..."); 

  for(auto currentWord : captionWordsIndex)
  {      
    captionWordsSortedByFrequency.push_back(currentWord.second);
  }  
  sort(captionWordsSortedByFrequency.begin(), 
       captionWordsSortedByFrequency.end(), 
       [](shared_ptr<CaptionWord> p1, shared_ptr<CaptionWord> p2) 
       {
          return p1->captionContextsList.size() > p2->captionContextsList.size();
       });
}




/*****************************************/
/*         PRINT TOP TEN MENTIONS        */
/*****************************************/
/* 
 * prints 10 most used words
 * format: "word(10)" 
 */
void VideoCaptions::
printTopTenMentions() const 
{  
  printf("\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  
  for (int i=0; i<10; ++i) 
  {
    printf("%s(%d), ", captionWordsSortedByFrequency[i]->word.c_str(), 
                       captionWordsSortedByFrequency[i]->captionContextsList.size());
    
    if(i % 2 == 0) 
    {
      printf("\n\t\t");
    }
  }
}




/******************************************/
/*               WRITEFUNC                */
/******************************************/
size_t VideoCaptions::
writefunc(char* ptr, size_t size, size_t nmemb, string* s) 
{  
  captionText += string{ptr + '\0'};
  return size*nmemb;
}




/******************************************/
/*      SEND WEB-REQUEST FOR CAPTIONS     */
/******************************************/
void VideoCaptions::
sendWebRequestForCaptions() 
{
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
void VideoCaptions::getCaptions() 
{
  sendWebRequestForCaptions();  
  cleanupCaptionDownloadFile();  
  createCaptionMap();
  deleteCommonWordsFromMap();    
  createMostFrequentWordsVector();
}





void VideoCaptions::
displayMenu() 
{
  printf("\n\n\t1 - Print URL links"       );
  printf(  "\n\t2 - Print context and URLs");
  printf(  "\n\t3 - Print context"         );
  printf(  "\n\t4 - Print words only"      );
  printf(  "\n\t5 - Export URLs to file\n" );
}






 
    

//return make_shared<vector<MenuOptionsData>>(menuOps);


shared_ptr<vector<MenuOptionsData>> VideoCaptions::
selectedCaptionMenuOptions() 
{  
  auto printStrings = [](vector<string> itemsToPrint) 
  {
    for (auto& capLine : itemsToPrint)
    {
      printf("\n\t>> \"%s\"", capLine.c_str());
    }
  };  
  
  auto printURL = [&]()
  {
    printStrings({itemsToPrint->captionContext[menuChoice]->timeURL});
  };

  vector<MenuOptionsData> menuOps = 
  {
    {"\n\n\t1 - Print URL links"       ;
  printf(  "\n\t2 - Print context and URLs");
  printf(  "\n\t3 - Print context"         );
  printf(  "\n\t4 - Print words only"      );
  printf(  "\n\t5 - Export URLs to file\n" );
  
  return shared_ptr<vector<MenuOptionsData>>();
}





/*****************************************/
/*          PRINT MAX MENTIONS           */
/*****************************************/
void VideoCaptions::
printMaxMentions() 
{
  int range = getUserInput<int>("Enter range");  
  const char* wordContextFormat = "\n\t(%d %-8s:  \"%s\"";
  int choice{displayPrintMenu()};


  if(choice != 4) printf("\n");
      
  for (int i = 0; i < range; ++i) 
  {            
    printf(wordContextFormat, 
           captionWordsSortedByFrequency[i]->captionContext.size(),           
           "mentions)",
           captionWordsSortedByFrequency[i]->word.c_str());                          
  }  
}





