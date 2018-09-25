#pragma once
#include<string>
#include<iostream>

class DownloadCaptions {


public:

  DownloadCaptions();
  DownloadCaptions(std::string);
  ~DownloadCaptions();

private:

  std::string url;

};

