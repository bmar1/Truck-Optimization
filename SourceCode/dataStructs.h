#pragma once
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include "mapping.h"


/*
* weight: The weight of the package
* size   : The size of the package in cubic meters
* address: A point on the map representing the address to be deliverd to
*/
struct Shipment {
	int weight;
	float size;
	struct Point address;
};

/*
* weight    : The current weight the Truck is carrying
* volume    : The space currently taken up within the truck
* truckRoute: The set route the truck follows 
* packages[]: The max amount of Shipments a Truck can hold (assuming weight is not the limiting factor)
*/
struct Truck {
	int weight;
	float volume;
	struct Route truckRoute;
	struct Shipment packages[500];
};

/*
* Calculates if given a shipment, a truck can accept it or not
* @param Shipment to be delivered, Truck to be checked
* @returns true or false if acceptable
*/
bool checkSpace(struct Truck truck, struct Shipment shipment); 

/*
* Calculates if given a shipment is valid
* @param Shipment to be delivered
* @returns true or false if acceptable
*/
bool valid(struct Shipment shipment, struct Map map);

/*
* Calculates which truck a shipment should follow, and if a diversion should be made or if a package cannot be shipped
* @param Map, Array of trucks, the given shipment
* @returns true or false if acceptable
*/
int assignPackage(struct Map map, struct Truck trucks[], struct Shipment shipment);


/*
* Calculates the least distance to divert from a given package and prints the diversion
* @param Map, Array of trucks, the given shipment
* @returns nothing, only prints a diversion
*/
void divert(struct Map map, struct Truck trucks[], struct Shipment shipment);
#endif