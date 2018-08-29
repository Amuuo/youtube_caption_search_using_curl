
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
#include"CaptionInfo.h"
#include"Time.h"
using namespace std;


/****************************************/
/* struct to hand each caption download */
/****************************************/
CaptionStruct* Captions;




string* getVideoUrl(bool, char**);
void    createMostFrequentWordsVector();
int     getMainMenuSelection();

void    printMaxMentions(int, char='\0');
bool    userInteraction();
void    printTopTenMentions();
void    sendRequestForCaptions(string);

