#include "Person.h"
#include "Thing.h"

#include "ecs36b_Common.h"

Person::Person() {
  this->role = "";
  this->description = "";
  this->location.setLeagueXY(0, 0);
}

// Better: Implement Thing objects to NULL instead of item_name to ""
// https://stackoverflow.com/questions/3030829/is-it-possible-to-set-an-object-to-null

void Person::changeLocation(double input_LeagueX, double input_LeagueY) {
  this->location.setLeagueXY(input_LeagueX, input_LeagueY);
}

GPS_DD Person::getLocation() {
  return this->location;
}

int inventoryCapacity = 3;

void Person::transferThing(Person* receiver, Thing item_to_transfer) {

  bool transferrable = false;
  int i = 0;
  for (i; i < inventoryCapacity; i += 1) {
    // Only take item from inventory index with corresponding name
    if (this->thingInventory[i].getItemName() == item_to_transfer.getItemName()) {
      this->thingInventory[i].setItemName("");
      transferrable = true;
      break;
    }
  }

  // Consider giver not having item to give away
  if (transferrable == false) {
    std::cout << "Giver does not have thing to give to receiver." << std::endl;
    exit(1);
  }

  int taken_i = i;
  i = 0;
  for (i; taken_i + i + 1 < inventoryCapacity; i += 1) {
    // Transfer elements above taken index one lower
    this->thingInventory[taken_i + i].setItemName(this->thingInventory[taken_i + i + 1].getItemName());
  }
  this->thingInventory[inventoryCapacity - 1].setItemName("");

  receiver->placeIntoInventory(item_to_transfer);

}

void Person::placeIntoInventory(Thing input_thing) {
  int i = 0;
  for (i; i < inventoryCapacity; i += 1) {
    // Only place item into empty inventory index
    if (this->thingInventory[i].getItemName() == "") {
      this->thingInventory[i] = input_thing;

      // Testing
      // std::cout << "Successfully placed '" << this->getInventoryName(i) 
      // << "' into inventory for " << this->role << "\n" << std::endl;
      break;
    }

  }

}

// Returns item name of an element in thingsInventory array
std::string Person::getInventoryName(int inventory_number) {
  return this->thingInventory[inventory_number].getItemName();
  // Printing object doesn't work (why?), use name instead
}

void Person::setRole(std::string input_role) {
  this->role = input_role;
}

void Person::setDescription(std::string input_description) {
  this->description = input_description;
}

std::string Person::getRole() {
  return this->role;
}

std::string Person::getDescription() {
  return this->description;
}

Json::Value Person::dump2JSON (void) {
  // std::cout << "called Person dump2json\n" << std::endl;

  Json::Value Person_result;
  Json::Value Thing_result;
  // Get item_name of things in role inventory
  for (int i = 0; i < 3; i += 1) {
    char identifier[8];
    sprintf(identifier, "Thing %d", i + 1);

    std::string itemName = this->thingInventory[i].getItemName();
    if (itemName != "") {
      Thing_result = this->thingInventory[i].dump2JSON();
    }
    else {
      Thing_result = "Empty";
    }
    
    Person_result[identifier] = Thing_result;
  }

  return Person_result;
  
}

bool Person::Json2Object(Json::Value person_jv) {

  bool Json2ObjectSucceeded = true;
  // std::cout << person_jv << std::endl;
  // std::cout << "Person Json2Object (calling Json2Object for things)\n" << std::endl;

  char identifier[8];
  for (int i = 0; i < 3; i += 1) {
    sprintf(identifier, "Thing %d", i + 1);

    if (person_jv[identifier] != "Empty") {
      // std::cout << person_jv[identifier] << std::endl;
      // std::cout << identifier << " not empty." << std::endl;
      if (!this->thingInventory[i].Json2Object(person_jv[identifier])) {
        Json2ObjectSucceeded = false;
      }

    }

  }

  return Json2ObjectSucceeded;
}
