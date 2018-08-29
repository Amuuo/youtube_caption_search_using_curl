#pragma once
#include<iostream>
#include<string>

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