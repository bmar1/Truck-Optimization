#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "mapping.h"
#include "dataStructs.h"

int main(void)
{
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();

	struct Truck trucks[3] = {  
		{0, 0.0, blueRoute, {0} }, 
		{0, 0.0, greenRoute, {0} }, 
		{0, 0.0, yellowRoute, {0} }
	};
	struct Shipment package = { 0, 0.0, {0,0} };
	bool flag;
	do {
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		flag = takeUserInput(&package); 

		assignPackage(baseMap, trucks, package);

	} while (flag);
	printf("Thanks for shipping with Seneca Polytechnic!\n");



	//struct Map routeMap = addRoute(&baseMap, &blueRoute);

	

	return 0;
}
