#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <float.h>
#include "dataStructs.h"



bool takeUserInput(struct Shipment* package) {
	int inputWeight = 0;
	double inputSize = 0.0;
	char inputAddress[3 + 1] = "\0";

	int mapRow = 0;

	scanf("%d %lf %3s", &inputWeight, &inputSize, inputAddress);
	while (getchar() != '\n');
	if (inputWeight == 0 && inputSize == 0 && inputAddress[0] == 'x') {
		return false;
	}
	package->weight = inputWeight;
	package->size = inputSize;

	if (isdigit(inputAddress[0]) && isdigit(inputAddress[1])) {
		mapRow = ((inputAddress[0] - '0') * 10) + inputAddress[1] - '0';
		package->address.row = mapRow;
		package->address.col = toupper(inputAddress[2]);
	}
	else if (isdigit(inputAddress[0]) && isalpha(inputAddress[1])) { 
		mapRow = inputAddress[0] - '0';
		package->address.row = mapRow;
		package->address.col = toupper(inputAddress[1]);
	}

	return true;

}

bool checkSpace(struct Truck truck, struct Shipment shipment) {
	if ((truck.weight + shipment.weight) <= 5000 && (truck.volume + shipment.size) <= 250.0) {
		return true;
	}
	else {
		return false;
	}
}

bool validShip(struct Shipment shipment) {
	bool validity;

	if (shipment.weight <= 0 || shipment.weight > 5000) {//Set validity to false if incorrect weight
		validity = false;
	}
	else if (shipment.size != 0.5 && shipment.size != 2 && shipment.size != 5) {//Set validity to false if incorrect size
		validity = false;
	}
	else validity = true;

	return validity;
}

bool valid(struct Shipment shipment, struct Map map) {
	bool validity;
	int row, column;

	//convert char to int for map index
	switch (shipment.address.row) {
	case 0: row = 0; break;
	case 1: row = 1; break;
	case 2: row = 2; break;
	case 3: row = 3; break;
	case 4: row = 4; break;
	case 5: row = 5; break;
	case 6: row = 6; break;
	case 7: row = 7; break;
	case 8: row = 8; break;
	case 9: row = 9; break;
	case 10: row = 10; break;
	case 11: row = 11; break;
	case 12: row = 12; break;
	case 13: row = 13; break;
	case 14: row = 14; break;
	case 15: row = 15; break;
	case 16: row = 16; break;
	case 17: row = 17; break;
	case 18: row = 18; break;
	case 19: row = 19; break;
	case 20: row = 20; break;
	case 21: row = 21; break;
	case 22: row = 22; break;
	case 23: row = 23; break;
	case 24: row = 24; break;
	default: row = -1;
	}

	//convert char to int for map index
	switch (shipment.address.col) {
	case 'A': column = 0; break;
	case 'B': column = 1; break;
	case 'C': column = 2; break;
	case 'D': column = 3; break;
	case 'E': column = 4; break;
	case 'F': column = 5; break;
	case 'G': column = 6; break;
	case 'H': column = 7; break;
	case 'I': column = 8; break;
	case 'J': column = 9; break;
	case 'K': column = 10; break;
	case 'L': column = 11; break;
	case 'M': column = 12; break;
	case 'N': column = 13; break;
	case 'O': column = 14; break;
	case 'P': column = 15; break;
	case 'Q': column = 16; break;
	case 'R': column = 17; break;
	case 'S': column = 18; break;
	case 'T': column = 19; break;
	case 'U': column = 20; break;
	case 'V': column = 21; break;
	case 'W': column = 22; break;
	case 'X': column = 23; break;
	case 'Y': column = 24; break;
	default: column = -1;
	}

	 if (row == -1 || column == -1) {//Set validity to false if address is outside of map bounds
		validity = false;
	}
	else if (map.squares[row][column] != 1) {//Set validity to false if address on map is not a building
		validity = false;
		}
	else {
			validity = true;
			}
			return validity;
}

int assignPackage(const struct Map map, struct Truck trucks[], struct Shipment shipment) {

	//for the best truck to be assigned to, per the trucks array
	int index = -2;
	double minDistance = DBL_MAX;
	// If at least one truck has room and the shipment is valid, assign it

	if (!validShip(shipment)) {
		return -1;
	}

	int size = *(&trucks + 1) - trucks;
	//loop through all trucks to find the one with the closest distance to the package
	for (int i = 0; i < size; i++) {

		if (!checkSpace(trucks[i], shipment)) continue;

		int closestIndex = getClosestPoint((const struct Route*)&trucks[i].truckRoute, shipment.address);

		//get the distance between the closest point on the given truck route to the address
		double dist = distance((const struct Point*)&trucks[i].truckRoute.points[closestIndex],
			(const struct Point*)&shipment.address);

		//update per each iteration if the distance is smaller than our current minimum
		if (dist < minDistance) {
			minDistance = dist;
			index = i;
		}
	}

	if (index != -2) {
		// Add the shipment to the truck's packages
		int sz = findNextAvailableSlot(trucks[index].packages, 500);
		trucks[index].packages[sz] = shipment;

		// Update the truck's weight and volume
		trucks[index].weight += shipment.weight;
		trucks[index].volume += shipment.size;

		//blue, green, yellow 
		printf("Ship on %s LINE", (index == 0) ? "BLUE" : (index == 1) ? "GREEN" : "YELLOW");
	}
	//no truck was found as best or avaible
	else if (index == -2) {
		printf("Ships tomorrow \n");
		return -1;
	}

	//if the address is not directly across/on the line, divert
	if (minDistance > 1) {
		divert(map, trucks, shipment, index);

	}
	else {
		printf(", no diversion\n");
	}

	return index;
}




struct Route divert(struct Map map, struct Truck trucks[], struct Shipment shipment, int index) {

	struct Route route = { 0, -1, 0};
	if (!valid(shipment, map) || !validShip(shipment)) {
		printf("SHIPMENT NOT VALID!");
		return route;
	}
	int closestIndex = getClosestPoint((const struct Route*)&trucks[index].truckRoute, shipment.address);

	// get the closet point on the given truck route
	struct Point closestPoint = trucks[index].truckRoute.points[closestIndex];

	//stores a route to the shortest path in a route
	struct Route diversionPath = shortestPath(&map, closestPoint, shipment.address);
	if (diversionPath.numPoints == 0) {
		printf("DIVERSION PATH IS EMPTY");
		return route;
	}
	printf(", divert ");
	for (int i = 0; i < diversionPath.numPoints; i++) {
		printf("%d%c, ", diversionPath.points[i].row, diversionPath.points[i].col);
	}
	printf("\n");

	return diversionPath;
}



int findNextAvailableSlot(const struct Shipment packages[], int maxPackages) {
	for (int i = 0; i < maxPackages; i++) {
		if (packages[i].weight == 0 && packages[i].size == 0) {
			return i;
		}
	}
	return -1;
}