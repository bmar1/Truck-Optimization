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

#endif