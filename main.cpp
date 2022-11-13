#include "Person.h"
#include "Thing.h"
#include "GPS.h"
#include "TIME.h"
#include "Record.h"

#include "ecs36b_Common.h"
#include "ecs36b_JSON.h"

int main() {
    
    // Initialize roles, GPS default of (0, 0)
    Person ridingHood;
    ridingHood.setRole("Little Red Riding Hood");
    ridingHood.setDescription("A dear little girl");

    Person grandmother;
    grandmother.setRole("Grandmother");
    grandmother.changeLocation(0, 0.5);

    Person mother;
    mother.setRole("Mother");
    mother.changeLocation(0, 0);

    Person wolf;
    wolf.setRole("Wolf");
    wolf.changeLocation(0, 0.6);
   
    // Intialize things
    Thing cap;
    cap.setItemName("Cap");
    cap.setItemDescription("A little cap of red velvet");

    Thing cake;
    cake.setItemName("cake");
    
    Thing wine;
    wine.setItemName("wine");

    // Record 1: Riding hood wearing cap
    grandmother.placeIntoInventory(cap);
    grandmother.transferThing(&ridingHood, cap);

    Record ridingHoodWearCap;
    ridingHoodWearCap.addRole(ridingHood);
    ridingHoodWearCap.addRole(grandmother);
    ridingHoodWearCap.addDescription("Grandmother gives riding hood the cap long before she sets out.");


    // Record 2: Mother gives riding hood cake and wine in village
    mother.placeIntoInventory(cake);
    mother.placeIntoInventory(wine);

    mother.transferThing(&ridingHood, cake);
    mother.transferThing(&ridingHood, wine);

    Record ridingHoodGetsFood;
    ridingHoodGetsFood.addRole(ridingHood);
    ridingHoodGetsFood.addRole(mother);
    ridingHoodGetsFood.addTime(100, 12);
    ridingHoodGetsFood.addDescription("Mother gives riding hood cake and wine in village");


    // Record 3: Riding Hood meets wolf in woods
    Record ridingHoodEncountersWolf;
    ridingHoodEncountersWolf.addRole(ridingHood);
    ridingHoodEncountersWolf.addRole(wolf);
    ridingHoodEncountersWolf.addTime(100, 20);
    ridingHoodEncountersWolf.addGPS(0, 0.25);
    ridingHoodEncountersWolf.addDescription("Riding Hood meets wolf in woods");


    // Record 4: Grandmother at home right outside woods with three oak trees nearby
    GPS_DD threeOakTrees(0, 0.5);
    
    Record grandmotherAtHome;
    grandmotherAtHome.addRole(grandmother);
    grandmotherAtHome.addTime(100, 20);
    grandmotherAtHome.addGPS(0, 0.5);
    grandmotherAtHome.addDescription("Grandmother at home right outside woods with three oak trees nearby");

    // Combine records in testingJV, write to file "jsonFile.txt"
    // Read json values from "jsonFile.txt" to readJsonFile
    // Use readJsonFile sections to call Json2Object()
    // Verify record using dump2Json() for original and new record
    Json::Value testingJV;
    Json::Value readJsonFile;
    testingJV["Record 1"] = ridingHoodWearCap.dump2JSON();
    testingJV["Record 2"] = ridingHoodGetsFood.dump2JSON();
    testingJV["Record 3"] = ridingHoodEncountersWolf.dump2JSON();
    testingJV["Record 4"] = grandmotherAtHome.dump2JSON();
    char jsonFile[] = "jsonFile.txt";

    myJSON2File(jsonFile, &testingJV);
    myFile2JSON (jsonFile, &readJsonFile);

    // dump2json and json2object (print and compare records)
    Record ridingHoodWearCap_Json2Object;
    Record ridingHoodGetsFood_Json2Object;
    Record ridingHoodEncountersWolf_Json2Object;
    Record grandmotherAtHome_Json2Object;

    if (ridingHoodWearCap_Json2Object.Json2Object(readJsonFile["Record 1"])) {
        std::cout << "Riding Hood Wears Cap (Json2Object):\n" << ridingHoodWearCap_Json2Object.dump2JSON()  << "\n" << std::endl;
    }
    std::cout << "Riding Hood Wears Cap (dump2json):\n" << ridingHoodWearCap.dump2JSON()  << "\n" << std::endl;
    
    if (ridingHoodGetsFood_Json2Object.Json2Object(readJsonFile["Record 2"])) {
        std::cout << "Riding Hood Gets Food (Json2Object):\n" << ridingHoodGetsFood_Json2Object.dump2JSON()  << "\n" << std::endl;
    }
    std::cout << "Riding Hood Gets Food (dump2json):\n" << ridingHoodGetsFood.dump2JSON()  << "\n" << std::endl;
    
    if (ridingHoodEncountersWolf_Json2Object.Json2Object(readJsonFile["Record 3"])) {
        std::cout << "Riding Hood Encounters Wolf (Json2Object):\n" << ridingHoodEncountersWolf_Json2Object.dump2JSON()  << "\n" << std::endl;
    }
    std::cout << "Riding Hood Encounters Wolf (dump2json):\n" << ridingHoodEncountersWolf.dump2JSON()  << "\n" << std::endl;
    
    if (grandmotherAtHome_Json2Object.Json2Object(readJsonFile["Record 4"])) {
        std::cout << "Grandmother At Home (Json2Object):\n" << grandmotherAtHome_Json2Object.dump2JSON()  << "\n" << std::endl;
    }
    std::cout << "Grandmother At Home (dump2json):\n" << grandmotherAtHome.dump2JSON()  << "\n" << std::endl;
 
    return 0;
}