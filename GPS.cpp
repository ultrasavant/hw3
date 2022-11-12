#include "GPS.h"

#include "ecs36b_Common.h"

GPS_DD::GPS_DD(){
    this->LeagueX = 0.0;
    this->LeagueY = 0.0;
}

GPS_DD::GPS_DD(double arg_LeagueX, double arg_LeagueY)
{
  this->LeagueX = arg_LeagueX;
  this->LeagueY = arg_LeagueY;
}

void GPS_DD::setLeagueXY(double input_LeagueX, double input_LeagueY) {
  this->LeagueX = input_LeagueX;
  this->LeagueY = input_LeagueY;
}

double 
GPS_DD::getLeagueX()
{
  return this->LeagueX;
}
 
double
GPS_DD::getLeagueY()
{
  return this->LeagueY;
}

Json::Value GPS_DD::dump2JSON()
{
  Json::Value result;

  result["LeagueX"] = this->LeagueX;
  result["LeagueY"] = this->LeagueY;

  return result;
}

bool GPS_DD::Json2Object(Json::Value arg_jv) {

  if (arg_jv["event_location"]["LeagueX"].isNull() == true || arg_jv["event_location"]["LeagueY"].isNull() == true) {
    return false;
  }

  this->LeagueX = arg_jv["event_location"]["LeagueX"].asDouble();
  this->LeagueY = arg_jv["event_location"]["LeagueY"].asDouble();

  return true;
}
