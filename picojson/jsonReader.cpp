#include "jsonReader.h"

  
//コンストラクタ
  jsonReader::jsonReader(){
  }

//デストラクタ
  jsonReader::~jsonReader(){
  }
//json文字列をstring型として読み出し
std::string jsonReader::readString(std::string str,std::string key){

  //std::string test("{Player:{\"Name\":\"Taro\"}}");
  std::string value;
  picojson::value val;

  std::string err = picojson::parse(val, str);
  if (! err.empty()) {
    printf("設定ファイルのパースに失敗しました。\n");
    return "error";
  }
  std::map<std::string, picojson::value> data = val.get<picojson::object>();
  value = data[key].get<std::string>();

  return value;
  
}
//json文字列をstring型として読み出し
double jsonReader::readDouble(std::string str,std::string key){

  //std::string test("{Player:{\"Name\":\"Taro\"}}");
  double value;
  picojson::value val;

  std::string err = picojson::parse(val, str);
  if (! err.empty()) {
    printf("設定ファイルのパースに失敗しました。\n");
    return -1.0;
  }
  std::map<std::string, picojson::value> data = val.get<picojson::object>();
  value = data[key].get<double>();

  return value;
  
}
