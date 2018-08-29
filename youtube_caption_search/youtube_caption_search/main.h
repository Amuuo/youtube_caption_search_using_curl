

#define __USE_MINGW_ANSI_STDIO 0
#define _CRT_SECURE_NO_WARNINGS

#include"AdamFunctions.h"
#include"CaptionInfo.h"
#include"Time.h"
using namespace std;


/****************************************/
/* struct to hand each caption download */
/****************************************/
CaptionStruct* Captions;



void  getVideoUrl(bool, char**);
bool  userInteraction();
void  sendRequestForCaptions(string);
int   getMainMenuSelection();

