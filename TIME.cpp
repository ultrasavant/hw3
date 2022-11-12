#include "TIME.h"

#include "ecs36b_Common.h"

TIME::TIME() {
    this->day = 0;
    this->hour = 0;
}

TIME::TIME(int arg_day, int arg_hour){
    this->day = arg_day;
    this->hour = arg_hour;
}

int
TIME::getDay()
{
  return this->day;
}

int 
TIME::getHour()
{
  return this->hour;
}
void
TIME::setDayAndHour(int arg_day, int arg_hour)
{
  this->day = arg_day;
  this->hour = arg_hour;
}

Json::Value TIME::dump2JSON()
{
  Json::Value TIME_result;

  TIME_result["Day"] = this->day;
  TIME_result["Hour"] = this->hour;

  return TIME_result;
}

bool TIME::Json2Object(Json::Value arg_jv) {

  if (arg_jv["event_time"]["Day"].isNull() == true || arg_jv["event_time"]["Hour"].isNull() == true) {
    return false;
  }

  this->day = arg_jv["event_time"]["Day"].asInt();
  this->hour = arg_jv["event_time"]["Hour"].asInt();

  return true;
}