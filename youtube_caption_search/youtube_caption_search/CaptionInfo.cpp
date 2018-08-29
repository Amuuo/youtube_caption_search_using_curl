

#include "CaptionInfo.h"
#include "main.h"


void CaptionStruct::printCaptionsToFile() {
  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << captionText;  
  outStream.close();
}




void CaptionStruct::printCaptionsToConsole(CaptionStruct* c, int choice) {
  auto printStrings = [](vector<string*> tmp) {
    for (auto& t : tmp)
    printf("\n\t>> \"%s\"", t->c_str());
  };     

  switch (choice) {      
    case 1: printStrings({&c->captionURL});           break; //print url only
    case 2: printStrings({&c->line, &c->captionURL}); break; //print url+context
    case 3: printStrings({&c->line});          break; //print context only
    default: break;
  }
}




void CaptionStruct::cleanupCaptionString(){

  printf("\n>> Parsing caption file...");

  string* caps = Captions->captionText;
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




void CaptionStruct::createCaptionMap(string*& url) {

  captionMap = new captionTable{};
  lineCheck*  lineMap{new lineCheck};
  string      tmpS;


  printf("\n>> Generating caption hash table...");

  istringstream   fileStringStream{Captions->captionText};
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
