
#ifndef _THING_H_
#define _THING_H_

#include "ecs36b_Common.h"

class Thing {
 private:

  std::string item_name;
  std::string item_description;

 public:

  explicit Thing();

  void setItemName(std::string input_item);
  void setItemDescription(std::string input_description);

  std::string getItemName();
  std::string getItemDescription();

  virtual Json::Value dump2JSON();
  virtual bool Json2Object(Json::Value);

};

#endif