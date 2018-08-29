

#include "CaptionInfo.h"




/*****************************************/
/*         PRINT CAPTIONS TO FILE        */
/*****************************************/
void CaptionStruct::printCaptionsToFile() {
  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << captionText;  
  outStream.close();
}




/*****************************************/
/*       PRINT CAPTIONS TO CONSOLE       */
/*****************************************/
void CaptionStruct::printCaptionsToConsole(CaptionStruct* c, int choice) {
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
void CaptionStruct::cleanupCaptionDownloadFile(){

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
void CaptionStruct::createCaptionMap(string*& url) {

  captionMap = new captionTable{};
  lineCheck*  lineMap{new lineCheck};
  string      tmpS;


  printf("\n>> Generating caption hash table...");

  istringstream   fileStringStream{captionText};
  CaptionStruct*  tmpCap;

  while (fileStringStream) {
    
    getline(fileStringStream,tmpS);
    
    if (isdigit(tmpS[0]) && tmpS[2] == ':') {
      
      string tmpS2{};
      getline(fileStringStream, tmpS2);
      if (tmpS == tmpS2) {
        continue;
      }
      if (lineMap->find(tmpS2) == lineMap->end()) {
        
        tmpCap = new CaptionStruct{videoTitle, 
                                 tmpS2, 
                                 *url, 
                                 Time{tmpS.substr(0,2), 
                                      tmpS.substr(3,2), 
                                      tmpS.substr(6.2)}};

        lineMap->insert(make_pair(tmpS2,tmpCap));
      }            

      istringstream lineStringStream(tmpS2);
      while (lineStringStream) {
        lineStringStream >> tmpS;
        transform(tmpS.begin(), 
                  tmpS.end(), 
                  tmpS.begin(), 
                  ::tolower);
        (*captionMap)[tmpS].insert(tmpCap);
      }
    }
  }
  delete url;
}




/******************************************/
/*      DELETE COMMON WORDS FROM MAP      */
/******************************************/
void CaptionStruct::deleteCommonWordsFromMap() {
  
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

string CaptionStruct::constructTimestampedURL(Time time, string userEnteredURL) {
  return userEnteredURL + "&feature=youtu.be&t=" + to_string(time.hr) + 'h'
      + to_string(time.min) + 'm' + to_string(time.sec) + 's';
}




/*****************************************/
/*            SEARCH FOR WORD            */
/*****************************************/
void CaptionStruct::searchForWord(string searchWord) {      


  if (captionMap->find(searchWord) != captionMap->end()) {
    
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




/*****************************************/
/*           DISPLAY PRINT MENU          */
/*****************************************/
int CaptionStruct::displayPrintMenu() {
    
  printf("\n\n\t1 - Print URL links"       );
  printf(  "\n\t2 - Print context and URLs");
  printf(  "\n\t3 - Print context"         );
  printf(  "\n\t4 - Print words only"      );
  printf(  "\n\t5 - Export URLs to file\n" );
  
  return getUserInput<int>("Selection");
}




/*****************************************/
/*          PRINT MAX MENTIONS           */
/*****************************************/
void CaptionStruct::printMaxMentions(char r) {
  int range = captionMap->size();
  static const char* format = "\n\t(%d %-8s:  \"%s\"";
  int choice{displayPrintMenu()};

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

