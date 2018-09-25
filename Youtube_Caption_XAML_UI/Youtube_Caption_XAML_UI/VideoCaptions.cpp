

#include"pch.h"
#include "VideoCaptions.h"

template<typename type_>
type_ getUserInput(wstring prompt, wstring leadingSpace=L"\n\t") {
  wprintf(L"%s%s: ", leadingSpace, prompt);
  type_ tmp;
  std::wcin >> tmp;
  return tmp;
}

VideoCaptions::
VideoCaptions()
{  
}



VideoCaptions::VideoCaptions(wstring url) : videoURL{url} 
{    
  getCaptions();
}



VideoCaptions::
~VideoCaptions()
{
  ofstream saveCaptionStruct{videoTitle, ofstream::binary};
  saveCaptionStruct.write((char*)this, sizeof(VideoCaptions));
}


VideoCaptions::Time::Time() 
{
}

VideoCaptions::Time::
Time(wstring h, wstring m, wstring s): hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} 
{
}


VideoCaptions::CaptionLine::CaptionLine() 
{
}

VideoCaptions::CaptionLine::
CaptionLine(wstring line, Time time) : line{line}, contextTime{time} 
{
}


VideoCaptions::CaptionWord::CaptionWord() 
{
}

VideoCaptions::CaptionWord::
CaptionWord(wstring word, ContextPtr context) : word{word} {
  captionContextsList.push_back(context);
}




void VideoCaptions::CaptionWord::
addContextLine(ContextPtr contextLine) {
  captionContextsList.push_back(contextLine);
}




bool VideoCaptions::
wordIsIndexed(wstring word) 
{
  return captionWordsIndex.find(word) == captionWordsIndex.end();
}




/*****************************************/
/*         PRINT CAPTIONS TO FILE        */
/*****************************************
void VideoCaptions::
printCaptionsToFile() 
{
  ofstream outStream{getUserInput<wstring>("Save as")};               
  outStream << captionText;  
  outStream.close();
}
*/




/****************************************/
/*          DISPLAY PRINT MENU          */
/****************************************/
int VideoCaptions::
displayPrintMenu() 
{
  return getUserInput<int>(L"Selection");
}





/*****************************************/
/*       PRINT CAPTIONS TO CONSOLE       */
/*****************************************/
void VideoCaptions::
printCaptionsToConsole(shared_ptr<CaptionWord> wordToPrint, int menuChoice) 
{
  auto printStrings = [](vector<wstring> itemsToPrint) 
  {
    for (auto& capLine : itemsToPrint)
    {
      wprintf(L"\n\t>> \"%s\"", capLine.c_str());
    }
  }; 

  switch (menuChoice) 
  {        
    //print url only
    case 1: 
      printStrings({wordToPrint->captionContextsList[menuChoice]->timedURL});           
      break; 
    
    //print url+context
    case 2: 
      printStrings({wordToPrint->captionContextsList[menuChoice]->timedURL, 
                   getCaptionClipURL(wordToPrint->captionContextsList[menuChoice])}); 
      break; 
    
    //print context only
    case 3: 
      printStrings({wordToPrint->captionContextsList[menuChoice]->timedURL});               
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
  wprintf(L"\n>> Parsing caption file...");

  wstring* caps = &captionText;
  wstring insert{};

  wregex parser1{L"<[^>]*>"};
  wregex parser2{L"-->.*%"};
  wregex parser3{L"\\.\\d{3}"};


  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser1, L"");
  *caps = insert;
  insert.clear();
  
  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser2, L"");
  *caps = insert;
  insert.clear();
  
  regex_replace(back_inserter(insert), caps->begin(), caps->end(), parser3, L"");
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
  wstring                 currentLine; 
  wstring                 nextLine; 
  Time                    time;
  wstringstream           captionStream{captionText};
  shared_ptr<CaptionLine> currentLinePtr{};

  wprintf(L"\n>> Generating caption index...");



  while (captionStream) 
  {        
    getline(captionStream,currentLine);        
    
    if(lineContainsTimeInfo(currentLine)) 
    {      
      if(nextLineIsADuplicate(captionStream,currentLine,tmpLineMap)) 
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
indexWord(wstring& capWord, ContextPtr capLinePtr) 
{
  if (wordIsIndexed(capWord)) 
  {
    captionWordsIndex[capWord]->captionContextsList.push_back(capLinePtr);
  }
  else
  {        
    captionWordsIndex[capWord] = make_shared<CaptionWord>(capWord, capLinePtr);
  }  
}




/**********************************/
/*  BUILD AND STORE CAPTION LINE  */
/**********************************/
void VideoCaptions::
buildCaptionLineAndWords(captionLineMap lineMap, 
                         wstring         capLine, 
                         wstring         lineInfo) 
{  
  
  /* parse first three values of timestamp, ex: "00:00:00" */
  lineMap[capLine] = make_shared<CaptionLine>( capLine, 
                                               Time{lineInfo.substr(0,2),
                                                    lineInfo.substr(3,2),
                                                    lineInfo.substr(6,2)} ); 


  indexWordsInCurrentLine(lineMap[capLine]);
}




/**********************************/
/*     SET WORDS TO LOWERCASE     */
/**********************************/
inline void VideoCaptions::
setWordsToLowercase(wstring line) 
{
  transform(line.begin(), line.end(), line.begin(), ::tolower);
}




/*********************************/
/*  LINE IS NOT ALREADY INDEXED  */
/*********************************/
inline bool VideoCaptions::
lineIsNotAlreadyIndexed(wstring& capLine)
{
  return captionWordsIndex.find(capLine) == captionWordsIndex.end();      
}




/**********************************/
/*    LINE CONTAINS TIME INFO     */
/**********************************/
inline bool VideoCaptions::
lineContainsTimeInfo(wstring& line) 
{
  /* check for format, ex: "00:00:00 -> 00:00:00" */
  return isdigit(line[0]) && line[2] == ':';
}

                      


/*********************************/
/*      NEXT LINE IS A COPY      */
/*********************************/
inline bool VideoCaptions::
nextLineIsADuplicate(wstringstream& sstream, 
                     wstring&       nextLine, 
                     captionLineMap tmpLineMap) 
{    
  getline(sstream, nextLine);
  //wcin.getline(sstream, nextLine);
  
  // if the temporary map find the line just taken
  return tmpLineMap.find(nextLine) != tmpLineMap.end();
}




/***********************************/
/*   INDEX WORDS IN CURRENT LINE   */
/***********************************/
inline void VideoCaptions::
indexWordsInCurrentLine(ContextPtr currentLine) 
{ 
  wstringstream lineStream{currentLine->line};
  wstring wordInCaptionLine;
  
  while (lineStream) 
  {
    lineStream >> wordInCaptionLine;
    indexWord(wordInCaptionLine, currentLine);
  }
}



inline wstring VideoCaptions::
getWordURL(int) 
{
}




/******************************************/
/*      DELETE COMMON WORDS FROM MAP      */
/******************************************/
void VideoCaptions::
deleteCommonWordsFromMap() 
{ 
  wprintf(L"\n>> Deleting all common words from table...");

  wstring   commonWord;
  std::wfstream commonWordsStream{L"commonWords.txt"};

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
wstring VideoCaptions::
getCaptionClipURL(ContextPtr line) 
{  
  return L"www.youtube.com/watch&feature=youtu.be&t="  + 
         to_wstring(line->contextTime.hr)  + L'h' + 
         to_wstring(line->contextTime.min) + L'm' + 
         to_wstring(line->contextTime.sec) + L's' + videoID;
}




/*****************************************/
/*         CAPTION CONTAINS WORD         */
/*****************************************/
inline bool VideoCaptions::
captionsContainWord(wstring searchWord) 
{ 
  return captionWordsIndex.find(searchWord) != captionWordsIndex.end();  
}


/*****************************************/
/*            SEARCH FOR WORD            */
/*****************************************/
void VideoCaptions::
searchForWord() 
{      
  auto searchWord = getUserInput<wstring>(L"Enter word");
  
  if (captionsContainWord(searchWord)) 
  {    
    wprintf(L"\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
           captionWordsIndex[searchWord]->captionContextsList.size(),           
           "mentions): ",
           searchWord.c_str());
        
    printCaptionsToConsole(captionWordsIndex[searchWord], displayPrintMenu());  
  } 
  else 
  { 
    std::wcout << L"\n\nThat word was not found..."; 
  }
}





/*****************************************/
/*   CREATE MOST FREQUENT WORDS VECTOR   */
/*****************************************/
void VideoCaptions::
createMostFrequentWordsVector() 
{    
  wprintf(L"\n>> Sorting words by number of mentions..."); 

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
  wprintf(L"\n\n\n\tTOP 10 MENTIONS:\n\n\t\t");
  
  for (int i=0; i<10; ++i) 
  {
    wprintf(L"%s(%d), ", captionWordsSortedByFrequency[i]->word.c_str(), 
                       captionWordsSortedByFrequency[i]->captionContextsList.size());
    
    if(i % 2 == 0) 
    {
      wprintf(L"\n\t\t");
    }
  }
}




/******************************************/
/*               WRITEFUNC                */
/******************************************
size_t VideoCaptions::
writefunc(char* ptr, size_t size, size_t nmemb, wstring* s) 
{  
  captionText += wstring{ptr + '\0'};
  return size*nmemb;
}*/




/******************************************/
/*      SEND WEB-REQUEST FOR CAPTIONS     */
/******************************************/
void VideoCaptions::
sendWebRequestForCaptions() 
{
  using std::wstring;
  wstring new_url{L"http://video.google.com/timedtext?type=track&lang=en&v="};
  std::wregex rgx(L"v=(.{11})");
  std::wsmatch video_id_match;
  regex_search(videoURL, video_id_match, rgx);
  videoID = video_id_match[1];
  videoURL = new_url.c_str() + wstring{video_id_match[1]};
  wstring testURL = new_url + wstring(video_id_match[1]);

  //wstring r{"start: "};

  HttpRequestMessage urlRequest{HttpMethod::Get(), Windows::Foundation::Uri(testURL)};

  /*
  CURL* curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, videoURL.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  regex rgx2("(<text.{3})*");
  smatch cap_match;

  regex_search(captionText.cbegin(), captionText.cend(), cap_match, rgx2);
  */
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





/*void VideoCaptions::
displayMenu() 
{
  wprintf("\n\n\t1 - Print URL links"       );
  wprintf(  "\n\t2 - Print context and URLs");
  wprintf(  "\n\t3 - Print context"         );
  wprintf(  "\n\t4 - Print words only"      );
  wprintf(  "\n\t5 - Export URLs to file\n" );
} 






 
    

//return make_shared<vector<MenuOptionsData>>(menuOps);


shared_ptr<vector<MenuOptionsData>> VideoCaptions::
selectedCaptionMenuOptions() 
{  
  auto printStrings = [](vector<wstring> itemsToPrint) 
  {
    for (auto& capLine : itemsToPrint)
    {
      wprintf("\n\t>> \"%s\"", capLine.c_str());
    }
  };  
  
  auto printURL = [&]()
  {
    printStrings({itemsToPrint->captionContext[menuChoice]->timeURL});
  };

  vector<MenuOptionsData> menuOps = 
  {
    {"\n\n\t1 - Print URL links"       ;
  wprintf(  "\n\t2 - Print context and URLs");
  wprintf(  "\n\t3 - Print context"         );
  wprintf(  "\n\t4 - Print words only"      );
  wprintf(  "\n\t5 - Export URLs to file\n" );
  
  return shared_ptr<vector<MenuOptionsData>>();
}





/*****************************************/
/*          PRINT MAX MENTIONS           */
/*****************************************
void VideoCaptions::
printMaxMentions() 
{
  int range = getUserInput<int>("Enter range");  
  const char* wordContextFormat = "\n\t(%d %-8s:  \"%s\"";
  int choice{displayPrintMenu()};


  if(choice != 4) wprintf("\n");
      
  for (int i = 0; i < range; ++i) 
  {            
    wprintf(wordContextFormat, 
           captionWordsSortedByFrequency[i]->captionContext.size(),           
           "mentions)",
           captionWordsSortedByFrequency[i]->word.c_str());                          
  }  
}*/





