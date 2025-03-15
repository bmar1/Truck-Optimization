#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "dataStructs.h"



bool checkSpace(struct Truck truck, struct Shipment shipment) {
	if (truck.weight + shipment.weight <= 5000 && truck.volume + shipment.size <= 250.0) {
		return true;
	}
	else {
		return false;
	}
}

bool valid(struct Shipment shipment, struct Map map) {
	bool validity;
	int row, column;

	//convert char to int for map index
	switch (shipment.address.row) {
	case 'A': row = 0; break;
	case 'B': row = 1; break;
	case 'C': row = 2; break;
	case 'D': row = 3; break;
	case 'E': row = 4; break;
	case 'F': row = 5; break;
	case 'G': row = 6; break;
	case 'H': row = 7; break;
	case 'I': row = 8; break;
	case 'J': row = 9; break;
	case 'K': row = 10; break;
	case 'L': row = 11; break;
	case 'M': row = 12; break;
	case 'N': row = 13; break;
	case 'O': row = 14; break;
	case 'P': row = 15; break;
	case 'Q': row = 16; break;
	case 'R': row = 17; break;
	case 'S': row = 18; break;
	case 'T': row = 19; break;
	case 'U': row = 20; break;
	case 'V': row = 21; break;
	case 'W': row = 22; break;
	case 'X': row = 23; break;
	case 'Y': row = 24; break;
	default: row = -1;
	}
	
	//convert char to int for map index
	switch (shipment.address.col) {
	case '0': column = 0; break;
	case '1': column = 1; break;
	case '2': column = 2; break;
	case '3': column = 3; break;
	case '4': column = 4; break;
	case '5': column = 5; break;
	case '6': column = 6; break;
	case '7': column = 7; break;
	case '8': column = 8; break;
	case '9': column = 9; break; 
	case '10': column = 10; break;
	case '11': column = 11; break;
	case '12': column = 12; break;
	case '13': column = 13; break;
	case '14': column = 14; break;
	case '15': column = 15; break;
	case '16': column = 16; break;
	case '17': column = 17; break;
	case '18': column = 18; break;
	case '19': column = 19; break;
	case '20': column = 20; break;
	case '21': column = 21; break;
	case '22': column = 22; break;
	case '23': column = 23; break;
	case '24': column = 24; break;
	default: column = -1;
	}

	if (shipment.weight <= 0 || shipment.weight > 5000) {//Set validity to false if incorrect weight
		validity = false;
	}
	else if (shipment.size != 0.5 && shipment.size != 2 && shipment.size != 5) {//Set validity to false if incorrect size
		validity = false;
	}
	else if (row == -1 || column == -1) {//Set validity to false if address is outside of map bounds
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

