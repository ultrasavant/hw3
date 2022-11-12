#include "Record.h"
#include "TIME.h"

#include "ecs36b_Common.h"

Record::Record() {
  this->eventDescription = "";
  this->eventTime.setDayAndHour(1, 0);
}

void Record::addGPS(double input_LeagueX, double input_LeagueY) {
  this->eventLocation.setLeagueXY(input_LeagueX, input_LeagueY);
}

void Record::addTime(int input_day, int input_hour) {
  this->eventTime.setDayAndHour(input_day, input_hour);
}

void Record::addRole(const Person& input_role) {
    for (int i = 0; i < 4; i += 1) {
        // Add role into empty roles[4] element
        if ((this->roles[i]).getRole() == "") {
            this->roles[i] = input_role;
            // std::cout << "input_role successfully added into roles[" << i << "]\n" << std::endl;
            break;
        }
    }

}

void Record::addDescription(std::string input_description) {
  this->eventDescription = input_description;
}

Json::Value Record::dump2JSON (void) {
  Json::Value result { };

  if (this->eventDescription != "") {
    result["event_description"] = this->eventDescription;
  }

  result["event_time"] = this->eventTime.dump2JSON();

  result["event_location"] = this->eventLocation.dump2JSON();

  Json::Value Person_result;

// Store individual Person_result into result
  std::string roleName = "";
  for (int i = 0; i < 4; i += 1) {
    roleName = this->roles[i].getRole();
    if (roleName == "") {
        continue;
    }
    Person_result = (this->roles[i].dump2JSON());

    result[roleName] = Person_result;
  }

  return result;
}

bool Record::Json2Object(Json::Value arg_jv) {
  // std::cout << "Record Json2Object" << std::endl;
  bool Json2ObjectSucceeded = true;

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)) {
    std::cout << "Not valid json value input" << std::endl;
    Json2ObjectSucceeded = false;
    return false;
  }

  if (arg_jv["event_description"].isNull() == true) {
    std::cout << "No event description" << std::endl;
    Json2ObjectSucceeded = false;
  }
  else {
    this->eventDescription = arg_jv["event_description"].asString();
  }

  if (this->eventTime.Json2Object(arg_jv) == false) {
    std::cout << "eventTime returned false" << std::endl;
    Json2ObjectSucceeded = false;
  }

  if (this->eventLocation.Json2Object(arg_jv) == false) {
    std::cout << "eventLocation returned false" << std::endl;
    Json2ObjectSucceeded = false;
  }

  // Hard code to check if role is in record
  // Call json2object if role exists in provided json::value parameter
  int i = 0;
  if (arg_jv["Little Red Riding Hood"].isNull() != true) {
    // Set role not equal to "" for dump2json()
    this->roles[i].setRole("Little Red Riding Hood");
    this->roles[i].Json2Object(arg_jv["Little Red Riding Hood"]);
    i += 1;
  }

  if (arg_jv["Grandmother"].isNull() != true) {
    this->roles[i].setRole("Grandmother");
    this->roles[i].Json2Object(arg_jv["Grandmother"]);
    i += 1;
  }

  if (arg_jv["Mother"].isNull() != true) {
    this->roles[i].setRole("Mother");
    this->roles[i].Json2Object(arg_jv["Mother"]);
    i += 1;
  }

  if (arg_jv["Wolf"].isNull() != true) {
    this->roles[i].setRole("Wolf");
    this->roles[i].Json2Object(arg_jv["Wolf"]);
    i += 1;
  }


  return Json2ObjectSucceeded;

}