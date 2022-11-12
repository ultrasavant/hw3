#ifndef _TIME_H_
#define _TIME_H_

// TIME.h
#include "ecs36b_Common.h"

class TIME
{
 private:
  int day;
  int hour;

 public:
  
  explicit TIME();
  explicit TIME(int arg_day, int arg_hour);
  int getDay();
  int getHour();
  void setDayAndHour(int arg_day, int arg_hour);

  virtual Json::Value dump2JSON();
  virtual bool Json2Object(Json::Value);

};

#endif /* _TIME_H_ */
