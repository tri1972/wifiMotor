#ifndef JSON_READER
#define JSON_READER

#include <string.h>
#include "picojson.h"

class jsonReader
{
 public:
  jsonReader();
  std::string readString(std::string str,std::string key);
  double readDouble(std::string str,std::string key);
  ~jsonReader();
};

#endif
