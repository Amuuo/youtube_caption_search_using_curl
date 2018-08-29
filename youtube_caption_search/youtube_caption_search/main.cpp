

#ifdef _WIN32

#define __USE_MINGW_ANSI_STDIO 0
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include<ws2tcpip.h>
#include<conio.h>
#pragma comment(lib, "Ws2_32.lib")

#endif


#ifdef __linux__

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netdb.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<arpa/inet.h>
#include<errno.h>

#endif


#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<regex>
#include<algorithm>
#include<functional>
#include<cstdio>
#include<string>
#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;





struct Time { 
  ~Time(){}
  Time(){}
  Time(string h, 
       string m, 
       string s) : hr{stoi(h)}, min{stoi(m)}, sec{stoi(s)} {}
  int hr; 
  int min; 
  int sec;     
};

struct CaptionInfo{
  ~CaptionInfo(){}
  CaptionInfo(){}
  CaptionInfo(const string*& s, string l, string u, Time t) : 
    title{s},
    line {l}, 
    time {t},
    url  {u + "&feature=youtu.be&t=" + to_string(t.hr) + 'h'
          + to_string(t.min) + 'm' + to_string(t.sec) + 's'} {}

  const string* title;
  string        line;
  string        url;
  Time          time;
};

using captionTable  = map<string,set<CaptionInfo*>>;
using captionLines  = vector<string>;
using lineCheck     = map<string, CaptionInfo*>;
using frequentWords = vector<pair<string,set<CaptionInfo*>>>;  
using capPair       = pair<string,set<CaptionInfo*>>;


#ifdef _WIN32
  WSADATA             winSock;
  SOCKET              connectSock;
  HOSTENT*            host;
#endif

#ifdef __linux__
  typedef int SOCKET;
  typedef struct hostent hostent;
  SOCKET connectSock;
  hostent* host;
  const int INVALID_SOCKET = -1;
#endif





struct sockaddr_in  svr;
frequentWords*  maxMentionsVec{};
const string*   title{};
captionTable*   captionMap{};
string          tmpS{};
string          insert{};  
string          testLines{};
string          filename{};
const char*     hostname{"www.google.com"};
int             requestMessageLength;
const int       LOCAL_PORT = 80;
const int       MSG_BUFF_LENGTH = 500000;
char            message[MSG_BUFF_LENGTH];



struct response_string {  
  
  char *ptr;
  size_t len;
};




string* getVideoUrl(bool, char**);
void downloadCaptions(string*&);
void importCaptionFile();
void cleanupCaptionString();
void createCaptionMap(string*&);
void printToFile();
void deleteCommonWordsFromMap();
void createMostFrequentWordsVector();
int  getMainMenuSelection();
int  askPrintOptions();
void printWords(CaptionInfo*,int);
void printMaxMentions(int, char='\0');
void searchWord(string);
int  streamSize(string);
bool userInteraction();
void printSnapShot();
#ifdef _WIN32
void initializeSocket();
#endif
void createSocket();
void setupProtocols();
void connectSocket();
void sendRequestForCaptions(string);
void getError(string);

template <typename type_>
type_ getUserInput(string="");








int main(int argc, char** argv){
    
#ifdef _WIN32
  //initializeSocket();
#endif
  
  //createSocket();
  //setupProtocols();
  //connectSocket();

  string* videoUrl{getVideoUrl(argc!=2, argv)};
  sendRequestForCaptions(*videoUrl);

  //downloadCaptions(videoUrl);  
  //importCaptionFile();  
  cleanupCaptionString();  
  createCaptionMap(videoUrl);
  deleteCommonWordsFromMap();  
  createMostFrequentWordsVector();
  while(userInteraction()); /* loop through user mode */
 
  return 0;
}







bool userInteraction() {
  printSnapShot();
  switch (getMainMenuSelection()) { 
    case 1: printMaxMentions(getUserInput<int>("Enter range")); break;      
    case 2: searchWord(getUserInput<string>("Enter word"));     break;      
    case 3: printMaxMentions(captionMap->size(),'r');           break;
    case 4: printToFile();                                      break;
    case 5: exit(1);                                            break;      
    default:                                                    break;
  } 
  return true;
}





void searchWord(string searchWord) {      

  if (captionMap->find(searchWord) != captionMap->end()) {
    
    printf("\n\n\tFOUND!\n\n\t(%d %-12s\"%s\"", 
           captionMap->at(searchWord).size(),           
           "mentions): ",
           searchWord.c_str());
    
    int choice = askPrintOptions();        
    for (auto& c : captionMap->at(searchWord)) {
      printWords(c, choice);
    }
  } else {
    cout << "\n\nThat word was not found...";
  }
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



#ifdef _WIN32
void initializeSocket() {
	printf("\n>> Initializing winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &winSock) < 0) {
		printf("\nFailed to initialize");
		exit(1);
	} printf("\n>> Initialized...");
}
#endif




void createSocket() {
	if ((connectSock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		getError("\nCould not create socket: ");
    
		exit(1);
	} printf("\n>> Socket created.");
}




void setupProtocols() {
	memset(&svr, 0, sizeof(struct sockaddr_in));
  //svr.sin_addr.S_un.S_addr = inet_addr("192.168.1.4");
  svr.sin_family = AF_INET;
	svr.sin_port = htons(LOCAL_PORT);
  host = gethostbyname("localhost");  	  
	memcpy(&svr.sin_addr, host->h_addr_list[0], host->h_length);
}




void connectSocket() {
	if ((connect(connectSock, (struct sockaddr*)&svr, sizeof(svr))) < 0) {
		getError("\nConnect failed.. Error: ");
		exit(1);
	} printf("\n>> Connected\n\n");
}



/*void init_response(response_string *s) {
  s->len = 0;
  s->ptr = (char*)malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
} */




size_t writefunc(char *ptr, size_t size, size_t nmemb, string* s) {  

  *s += string{ptr + '\0'};
  testLines += *s;
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
  //response_string r;
  //char* r = (char*)malloc(1);
  //r[0] = '\0';
  string r{"start: "};
  //init_response(r);
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);
  
  response = curl_easy_perform(curl);
  //testLines = r;
  curl_easy_cleanup(curl);

  regex rgx2("(<text.{3})*");
  smatch cap_match;

  regex_search(testLines.cbegin(), testLines.cend(), cap_match, rgx2);
                            
}





void getError(string message) {

  #ifdef _WIN32
  printf("%s %d", message.c_str(), WSAGetLastError());
  #endif

  #ifdef __linux__
  printf("%s %d", message.c_str(), errno);
  #endif
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
          printWords(c, choice);
    } 
  } else {        
    for (int i = 0; i < range; ++i) {            
      printf(format, maxMentionsVec->at(i).second.size(),           
                     "mentions)",
                     maxMentionsVec->at(i).first.c_str());                
      
      for (auto& c : maxMentionsVec->at(i).second)
          printWords(c, choice);            
    }
  }
}




void printWords(CaptionInfo* c, int choice){
  
  auto printStrings = [](vector<string*> tmp) {
    for (auto& t : tmp)
      printf("\n\t>> \"%s\"", t->c_str());
  };
  /*auto lineString = [](string s) { 
    return string{"\n\t>> \"" + s + "\""}; 
  };
  auto urlString = [](string u, string x="") { 
    return string{"\n\t"+x+">> " + u}; 
  };*/      

  switch (choice) {      
    case 1: printStrings({&c->url});           break; //print url only
    case 2: printStrings({&c->line, &c->url}); break; //print url+context
    case 3: printStrings({&c->line});          break; //print context only
    default: break;
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
       [](pair<string, set<CaptionInfo*>> p1, 
          pair<string, set<CaptionInfo*>> p2) {
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




void printToFile() {

  ofstream outStream{getUserInput<string>("Save as")};               
  outStream << testLines;  
  outStream.close();
}




void deleteCommonWordsFromMap() {
  
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




void downloadCaptions(string*& arg) {

  printf("\n>> Downloading video file...");

  string cmd{"youtube-dl --skip-download --write-sub --write-auto-sub " + 
             string{*arg} + 
             " | gawk 'match($0, /.*subtitles to: (.*)/, a) {print a[1];}' " +
             " > filename.txt"};
  system(cmd.c_str());

  string videoTitle{};
  ifstream filenameStream{"filename.txt"};
  getline(filenameStream, filename);
  filenameStream.close();
  regex titleTrim{"\\(.en.vtt\\)|\\(.vtt\\)"};
  regex_replace(back_inserter(videoTitle), 
                filename.begin(), 
                filename.end(), 
                titleTrim, "");
  title = new string{videoTitle};
}




void createCaptionMap(string*& url) {

  captionMap = new captionTable{};
  lineCheck* lineMap{new lineCheck};

  printf("\n>> Generating caption hash table...");

  istringstream fileStringStream{testLines};
  CaptionInfo*  tmpCap;

  while (fileStringStream) {
    
    getline(fileStringStream,tmpS);
    
    if (isdigit(tmpS[0]) && tmpS[2] == ':') {
      
      string tmpS2{};
      getline(fileStringStream, tmpS2);
      if (tmpS == tmpS2) {
        continue;
      }
      if (lineMap->find(tmpS2) == lineMap->end()) {
        
        tmpCap = new CaptionInfo{title, 
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




void cleanupCaptionString() {

  printf("\n>> Parsing caption file...");

  regex parser1{"<[^>]*>"};
  regex parser2{"-->.*%"};
  regex parser3{"\\.\\d{3}"};


  regex_replace(back_inserter(insert),
                testLines.begin(),
                testLines.end(),
                parser1, "");
  testLines = insert;
  insert.clear();
  regex_replace(back_inserter(insert),
                testLines.begin(),
                testLines.end(),
                parser2, "");
  testLines = insert;
  insert.clear();
  regex_replace(back_inserter(insert),
                testLines.begin(),
                testLines.end(),
                parser3, "");
  testLines = insert;
  insert.clear();
}




void importCaptionFile() {

  printf("\n>> Importing caption file...");

  ifstream testStream{filename};

  while(testStream){    
    getline(testStream, tmpS);
    if(tmpS != " \n" && 
       tmpS != ""    && 
       tmpS != "\n"  && 
       tmpS != " ") {
      testLines += string{"\n" + tmpS};
    }
  }
  testStream.close();
}