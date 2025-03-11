#pragma once
#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H
#include "mapping.h"


//weight : The current weight the Truck is carrying
//volume : The space currently taken up within the truck
//truckId: A string to uniquely identify a Truck
struct Truck {
	int weight;
	float volume;
	char truckId[10];
};

//weight : The weight of the package
//size   : The size of the package in cubic meters
//truckId: A string corresponding to a trucks unique identifier for assignment
//address: A point on the map representing the address to be deliverd to
struct Shipment {
	int weight;
	float size;
	char truckId[10];
	Point address;
};


/*
* Calculates the distance from point a, to point b in double format
* @param Point 1, Point2 - The two points which store their locations in them to compare
* @returns The distance in double format
*/
double checkDistance(Point point1, Point point2);

/*
* Calculates if given a shipment, a truck can accept it or not
* @param Shipment to be delivered, Truck to be checked
* @returns true or false if acceptable
*/
bool checkSpace(Truck truck, Shipment shipment);


/*
* Calculates if given a shipment is valid
* @param Shipment to be delivered
* @returns true or false if acceptable
*/
bool valid(Shipment shipment);

/*
* Calculates which truck a shipment should follow, and if a diversion should be made or if a package cannot be shipped
* @param Map, Array of trucks, the given shipment
* @returns true or false if acceptable
*/
int assignPackage(Map map, Truck trucks[], Shipment shipment);


/*
* Calculates the least distance to divert from a given package and prints the diversion
* @param Map, Array of trucks, the given shipment
* @returns nothing, only prints a diversion
*/
void divert(Map map, Truck trucks[], Shipment shipment);
#endif