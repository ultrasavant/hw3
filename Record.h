#include "Person.h"
#include "GPS.h"
#include "TIME.h"

#include "ecs36b_Common.h"

#ifndef _RECORD_H_
#define _RECORD_H_

class Record {
 private:
  Person roles[4];
  GPS_DD eventLocation;
  TIME eventTime;
  std::string eventDescription;
  
public:
  explicit Record();

  void addRole(const Person& input_role);
  void addTime(int input_day, int input_hour);
  void addGPS(double input_LeagueX, double input_LeagueY);
  void addDescription(std::string input_description);
//   Print out record information in JSON
  virtual Json::Value dump2JSON();
  virtual bool Json2Object(Json::Value);

};

#endif