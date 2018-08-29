

#define __USE_MINGW_ANSI_STDIO 0
#define _CRT_SECURE_NO_WARNINGS

#include<conio.h>
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
#include"AdamFunctions.h"
#include"CaptionInfo.h"
#include"Time.h"
using namespace std;


/****************************************/
/* struct to hand each caption download */
/****************************************/
CaptionStruct* Captions;



string* getVideoUrl(bool, char**);
bool    userInteraction();
void    printTopTenMentions();
void    sendRequestForCaptions(string);
int     getMainMenuSelection();

