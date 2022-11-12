#ifndef _GPS_H_
#define _GPS_H_

// GPS.h

#include "ecs36b_Common.h"

class GPS_DD
{
 private:
  double LeagueX;
  double LeagueY;

 public:
  explicit GPS_DD();
  explicit GPS_DD(double, double);
  double getLeagueX();
  double getLeagueY();

  void setLeagueXY(double input_LeagueX, double input_LeagueY); 

  virtual Json::Value dump2JSON();
  virtual bool Json2Object(Json::Value);

};

#endif /* _GPS_H_ */