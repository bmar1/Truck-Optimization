#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackBoxTests
{
    //Test Series 1
    const struct Map map = populateMap();

    const struct Route blueRoute = getBlueRoute();
    const struct Route yellow = getYellowRoute();
    const struct Route green = getGreenRoute();

    const struct Map map1 = addRoute(&map, &blueRoute);
    const struct Map map2 = addRoute(&map1, &green);
    const struct Map finalMap = addRoute(&map2, &yellow);


    TEST_CLASS(BlackBoxTests) {
    public:

        TEST_METHOD(test_distance_case1)
        {

            const struct Point p1 = { 3, 4 };
            const struct Point p2 = { 3, 4 };

            double result = distance(&p1, &p2);
            Assert::AreEqual(result, 0.0, 0.0001);
        }
        TEST_METHOD(test_distance_case2)
        {

            struct Point p1 = { 1, 2 };
            struct Point p2 = { 1, 12 };

            double result = distance(&p1, &p2);
            Assert::AreEqual(result, 10.0, 0.0001);
        }
        TEST_METHOD(test_distance_case3)
        {
            struct Point p1 = { 1, 1 };
            struct Point p2 = { 4, 5 };

            double result = distance(&p1, &p2);
            Assert::AreEqual(result, 5.0, 0.0001);
        }
        TEST_METHOD(test_distance_case4)
        {
            struct Point p1 = { 1, 4 };
            struct Point p2 = { 1, 10 };

            double result = distance(&p1, &p2);
            Assert::AreEqual(result, 6.0, 0.0001);
        };

        //Series 2 - AssignPackage/checkValid/checkSpace
        TEST_METHOD(test_assign_case1)
        {

            struct Truck trucks[] = {
                {1000, 50.0, green, {}},
                {300, 20.0, blueRoute, {}},
                {100, 10.0, yellow, {}}
            };

            struct Point address { 7, 'H' };
            struct Shipment shipment { 250, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 0);
        };

        TEST_METHOD(test_assign_case2)
        {

            struct Truck trucks[] = {
                {5000, 50.0, green, {}},
                {5000, 50.0, blueRoute, {}},
                {5000, 50.0, yellow, {}}
            };

            struct Point address { 2, 'K' };
            struct Shipment shipment { 250, 5, address };

            int result = assignPackage(map, trucks, shipment);
            Assert::AreEqual(result, -1);
        };


        TEST_METHOD(test_assign_case3)
        {

            struct Truck trucks[] = {
                {10, 100.00, green, {}},
                {50, 50.00, blueRoute, {}},
                {90, 50.00, yellow, {}}
            };

            struct Point address { 1, 'X' };
            struct Shipment shipment { -1, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, -1);
        };

        TEST_METHOD(test_assign_case4)
        {

            struct Truck trucks[] = {
                {100, 10.00, green, {}},
                {2500, 100.00, blueRoute, {}},
                {100, 50.00, yellow, {}}
            };

            struct Point address { 3, 'V' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, -1);
        };

        TEST_METHOD(test_valid_case1)
        {
            struct Point address { 7, 'H' };
            struct Shipment shipment { 20, 2, address };

            bool result = valid(shipment, finalMap);
            Assert::AreEqual(result, true);
        };


        TEST_METHOD(test_valid_case2)
        {
            struct Point address { 2, 'B' };
            struct Shipment shipment { 1000, 5, address };

            bool result = valid(shipment, finalMap);
            result = validShip(shipment);
            Assert::AreEqual(result, true);
        };



        TEST_METHOD(test_valid_case3)
        {
            struct Point address { 9, 'H' };
            struct Shipment shipment { -1, 5, address };

            bool result = valid(shipment, finalMap);
            result = validShip(shipment);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_valid_case4)
        {
            struct Point address { 4, 'H' };
            struct Shipment shipment { INT_MAX, 2, address };

            bool result = valid(shipment, finalMap);
            result = validShip(shipment);
            Assert::AreEqual(result, false);
        };

        TEST_METHOD(test_space_case1)
        {
            struct Truck truck = { 2000, 50.00, blueRoute, {} };

            struct Point address { 4, 'H' };
            struct Shipment shipment { 20, 2, address };

            bool result = checkSpace(truck, shipment);
            Assert::AreEqual(result, true);
        };


        TEST_METHOD(test_space_case2)
        {
            struct Truck truck = { 5000, 250.00, blueRoute, {} };

            struct Point address { 2, 'H' };
            struct Shipment shipment { 4000, 7, address };

            bool result = checkSpace(truck, shipment);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_space_case3)
        {
            struct Truck truck = { 5000, 250.00, blueRoute, {} };
            struct Point address { 4, 'H' };
            struct Shipment shipment { -1, 5, address };

            bool result = checkSpace(truck, shipment);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_space_case4)
        {
            struct Truck truck = { 10, 250.00, blueRoute, {} };
            struct Point address { 8, 'K' };
            struct Shipment shipment { 3000, 2, address };

            bool result = checkSpace(truck, shipment);
            Assert::AreEqual(result, false);
        };


        /*TEST_METHOD(test_check_divert1) {
            struct Point address = { 2, 'Q' };
            struct Shipment shipment = { 500, 5, address };
            struct Shipment packages[500] = { Shipment{0,0,0} };
            packages[0] = shipment;

            const struct Route greenRoute = getGreenRoute();

            struct Truck truck = {
                1000,          // weight
                80,            // volume
                greenRoute,     // const Route (must match `truckRoute` type)
                packages[0]       // packages array
            };

            struct Route result = divert(finalMap, &truck, truck.packages[0], 0);


            Assert::AreEqual(4, result.numPoints);
        */

        //cases  2-4 use the wrong method of testing

          /*TEST_METHOD(test_check_divert2)
          {

              struct Truck trucks[] = {
                  {1000, 80, yellow, {}},

              };
              struct Point address { 'C', '8' };
              struct Shipment shipment { 1000, 2, address };

              int result = divert(finalMap, trucks, shipment, 0);
              Assert::AreEqual(0, result);
          }

          TEST_METHOD(test_check_divert3)
          {

              struct Truck trucks[] = {
                  {1000, 80, yellow, {}},

              };
              struct Point address { 'C', '8' };
              struct Shipment shipment { 3000, 2, address };

              int result = divert(finalMap, trucks, shipment, 0);
              Assert::AreEqual(-1, result);
          }

          TEST_METHOD(test_check_divert4)
          {

              struct Truck trucks[] = {
                  {1000, 80, blueRoute, {}},

              };
              struct Point address { 'X', '28' };
              struct Shipment shipment { 1000, 2, address };

              int result = divert(finalMap, trucks, shipment, 0);
           *  Assert::AreEqual(-1, result);};*/
         

        TEST_METHOD(test_eqPt)
        {
            const struct Point p1 = { 9, 13 };
            const struct Point p2 = { 9, 13 };
            int result = eqPt(p1, p2);

            Assert::AreEqual(1, result);

        }

        TEST_METHOD(test_eqPt2)
        {
            const struct Point p1 = { 2, 10 };
            const struct Point p2 = { 5, 10 };
            int result = eqPt(p1, p2);

            Assert::AreEqual(0, result);

        }

        TEST_METHOD(test_eqPt3)
        {
            const struct Point p1 = { 3, 11 };
            const struct  Point p2 = { 3, 20 };
            int result = eqPt(p1, p2);

            Assert::AreEqual(0, result);

        }

        //Added an extra test - Kaitlyn
        TEST_METHOD(test_eqPt4)
        {
            const struct Point p1 = { 8, 16 };
            const struct  Point p2 = { 7, 14 };
            int result = eqPt(p1, p2);

            Assert::AreEqual(0, result);

        }

        TEST_METHOD(test_eqPt5)
        {
            const struct Point p1 = { 0, 0 };
            const struct Point p2 = { 24, 24 };
            int result = eqPt(p1, p2);

            Assert::AreEqual(0, result);

        }

    };
}

namespace WhiteBoxTests {
    //Test Series 1
    const struct Map map = populateMap();

    struct Route blueRoute = getBlueRoute();
    struct Route yellow = getYellowRoute();
    struct Route green = getGreenRoute();

    const struct Map map1 = addRoute(&map, &blueRoute);
    const struct Map map2 = addRoute(&map1, &green);
    const struct Map finalMap = addRoute(&map2, &yellow);


    TEST_CLASS(WhiteBoxTests) {
    public:
        TEST_METHOD(test_checkSpace1)
        {
            Truck testTruck = { 4000, 200, {0}, {0} };
            Shipment testPackage = { 500, 40, {0,0} };

            bool result = checkSpace(testTruck, testPackage);
            Assert::AreEqual(result, true);
        }
        TEST_METHOD(test_checkSpace2)
        {
            Truck testTruck = { 4900, 100, {0}, {0} };
            Shipment testPackage = { 200, 10, {0,0} };

            bool result = checkSpace(testTruck, testPackage);
            Assert::AreEqual(result, false);
        }
        TEST_METHOD(test_checkSpace3)
        {
            Truck testTruck = { 4500, 245, {0}, {0} };
            Shipment testPackage = { 500, 5, {0,0} };

            bool result = checkSpace(testTruck, testPackage);
            Assert::AreEqual(result, true);
        }
        TEST_METHOD(test_checkSpace4)
        {
            Truck testTruck = { 3000, 245, {0}, {0} };
            Shipment testPackage = { 300, 20, {0,0} };

            bool result = checkSpace(testTruck, testPackage);
            Assert::AreEqual(result, false);
        }
        TEST_METHOD(test_valid1) {

            Shipment testPackage = { 1, 0.5, {1, 'B'} };

            bool result = valid(testPackage, map);
            Assert::AreEqual(result, true);

        }
        TEST_METHOD(test_valid2) {

            Shipment testPackage = { 5001, 2, {2, 'B'} };

            bool result = validShip(testPackage);
            Assert::AreEqual(result, false);

        }
        TEST_METHOD(test_valid3) {

            Shipment testPackage = { 10, 2, {0, 'G'} };

            bool result = valid(testPackage, map);
            Assert::AreEqual(result, false);

        }
        TEST_METHOD(test_valid4) {

            Shipment testPackage = { 20, 2, {26, 'A'} };

            bool result = valid(testPackage, map);
            Assert::AreEqual(result, false);

        }
        TEST_METHOD(test_assign1) {

            struct Truck trucks[] = {
                {2000, 80.0, green, {}},
                {1500, 90.0, blueRoute, {}},
                {0, 0.0, yellow, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 0);
        }
        TEST_METHOD(test_assign2) {
            struct Truck trucks[] = {
                {5000, 250.0,blueRoute , {}},
                {1500, 90.0, green, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 1);
        }
        TEST_METHOD(test_assign3) {
            struct Truck trucks[] = {
                {2000, 80.0,blueRoute , {}},
                {1500, 90.0, green, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 1);
        }
        TEST_METHOD(test_assign4) {
            struct Truck trucks[] = {
                {5000, 250.0,blueRoute , {}},
                {5000, 250.0, green, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, -1);
        }
        TEST_METHOD(test_max1) {
            struct Truck trucks[] = {
                {4500, 245.0, green, {}},
                {0, 0.0,blueRoute, {}},
                {0, 0.0, yellow, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 0);
        }
        TEST_METHOD(test_max2) {
            struct Truck trucks[] = {
                {4900, 245.0, green, {}},
                {4900, 245.0,blueRoute, {}},
                {4900, 245.0, yellow, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, -1);
        }
        TEST_METHOD(test_max3) {
            struct Truck trucks[] = {
                {4500, 247.0, green, {}},
                {4500, 247.0,blueRoute, {}},
                {4500, 247.0, yellow, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, -1);
        }
        TEST_METHOD(test_max4) {
            struct Truck trucks[] = {
                {5000, 250.0, green, {}},
                {1500, 90.0,blueRoute, {}},
                {0, 0.0, yellow, {}}
            };

            struct Point address { 7, 'F' };
            struct Shipment shipment { 500, 5, address };

            int result = assignPackage(finalMap, trucks, shipment);
            Assert::AreEqual(result, 1);
        }
        TEST_METHOD(test_slot1) {
            struct Point address { 7, 'F' };
            Shipment shipmentArr[2]{ Shipment{ 500, 5, address}, Shipment{0, 0, address} };

            int result = findNextAvailableSlot(shipmentArr, 2);
            Assert::AreEqual(1, result);
        }


        TEST_METHOD(test_slot2) {
            struct Point address { 7, 'F' };
            Shipment shipmentArr[2]{ Shipment{ 500, 5, address}, Shipment{300, 0, address} };

            int result = findNextAvailableSlot(shipmentArr, 2);
            Assert::AreEqual(-1, result);
        }


        TEST_METHOD(test_slot3) {
            struct Point address { 7, 'F' };
            Shipment shipmentArr[3]{ Shipment{ 500, 5, address}, Shipment{0, 0, address}, Shipment{0, 0, address} };

            int result = findNextAvailableSlot(shipmentArr, 3);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(test_slot4) {
            struct Point address { 7, 'F' };
            Shipment shipmentArr[500]{};

            int result = findNextAvailableSlot(shipmentArr, 500);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(test_path1) { //test path doesnt work
            struct Point start { 1, 'A' };
            struct Point end { 5, 'E' };

            struct Route result = shortestPath(&map, start, end);
            Assert::AreEqual(9, result.numPoints);

        }

        TEST_METHOD(test_path2) {
            struct Point start { 10, 'K' };
            struct Point end { 17, 'K' };

            struct Route result = shortestPath(&map, start, end);
            Assert::AreEqual(9, result.numPoints);

        }


        TEST_METHOD(test_path3) {
            struct Point start { 6, 'E' };
            struct Point end { 2, 'H' };

            struct Route result = shortestPath(&map, start, end);
            Assert::AreEqual(0, result.numPoints);

        }

        TEST_METHOD(test_path4) {
            struct Point start { 18, 'V' };
            struct Point end { 7, 'Y' };

            struct Route result = shortestPath(&map, start, end);
            Assert::AreEqual(15, result.numPoints);

        }

        TEST_METHOD(test_check_divert1)
        {


            struct Point address { 8, 'P' };

            struct Truck trucks[] = {
              {1000, 80, green, {} },
              {2000, 40, yellow, {{500, 5, address}}},
              {1500, 90.0,blueRoute, {}}
            };

            struct Route result = divert(finalMap, trucks, trucks[1].packages[0], 1);

            Assert::AreEqual(8, result.numPoints);
        }

        TEST_METHOD(test_check_divert2)
        {


            struct Point address { 0, 'A' };

            struct Truck trucks[] = {
              {1000, 80, green, {} },
              {2000, 40, yellow, {{-1, 5, address}}},
              {1500, 90.0,blueRoute, {}}
            };

            struct Route result = divert(finalMap, trucks, trucks[1].packages[0], 1);

            Assert::AreEqual(0, result.numPoints);
        }

        TEST_METHOD(test_check_divert3)
        {


            struct Point address { 15, '0' };

            struct Truck trucks[] = {
              {1000, 80, green, {} },
              {2000, 40, yellow, {{-1, 5, address}}},
              {1500, 90.0,blueRoute, {}}
            };

            struct Route result = divert(finalMap, trucks, trucks[1].packages[0], 1);

            Assert::AreEqual(0, result.numPoints);
        }

        TEST_METHOD(test_check_divert4)
        {


            struct Point address { 15, 'Q' };

            struct Truck trucks[] = {
              {1000, 80, green, {} },
              {2000, 40, yellow, {{-1, 5, address}}},
              {1500, 90.0,blueRoute, {}}
            };

            struct Route result = divert(finalMap, trucks, trucks[1].packages[0], 1);
            Assert::AreEqual(12, result.numPoints);

        }
         
        

    };

}

namespace IntegrationTests {
    //Test Series 1
    const struct Map map = populateMap();

    struct Route blueRoute = getBlueRoute();
    struct Route yellow = getYellowRoute();
    struct Route green = getGreenRoute();

    const struct Map map1 = addRoute(&map, &blueRoute);
    const struct Map map2 = addRoute(&map1, &green);
    const struct Map finalMap = addRoute(&map2, &yellow);


    TEST_CLASS(IntegrationTests) {
    public:

        TEST_METHOD(IT101) {
            Shipment testPackage = { 50, 2, {2,'Q'}};

            Truck truck = { 3000, 100, green, {} };

            bool result1 = checkSpace(truck, testPackage);
            bool result = validShip(testPackage);
            Assert::AreEqual(result, result1); //both must be true.
        }

        TEST_METHOD(IT102) {
            Shipment testPackage = { -10, 2, {2,'Q'} };

            Truck truck = { 1000, 50, green, {} };

           
            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = checkSpace(truck, testPackage);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false); 
        }

        TEST_METHOD(IT103) {
            Shipment testPackage = { 500, 3, {2,'Q'} };

            Truck truck = { 2000, 75, green, {} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = checkSpace(truck, testPackage);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT104) {
            Shipment testPackage = { 1000, 5, {2,'Q'} };

            Truck truck = { 4000, 245, green, {} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = checkSpace(truck, testPackage);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT201) {
            Shipment testPackage = { 200, 2, {2,'F'} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = valid(testPackage, finalMap);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT202) {
            Shipment testPackage = { 100, 2, {3,'D'} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = valid(testPackage, finalMap);
                Assert::AreEqual(false, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT203) {
            Shipment testPackage = { 30, 3, {6,'H'} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = valid(testPackage, finalMap);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT204) {
            Shipment testPackage = { 6000, 2, {8,'T'} };


            bool result = validShip(testPackage);
            if (result == true) {
                bool result1 = valid(testPackage, finalMap);
                Assert::AreEqual(result, result1);
            }
            else Assert::AreEqual(result, false);
        }

        TEST_METHOD(IT401) {
            Shipment testPackage = { 100, 5, {8,'K'} };

            Truck truck[] = {
            {1000, 50, blueRoute, {}} };

            
            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 0);
        }

        TEST_METHOD(IT402) {
            Shipment testPackage = { 100, 5.0, {8,'K'} };

            Truck truck[] = {
            { 5000, 250, blueRoute, {} } ,
                {0,0, green, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 1);
        }

        TEST_METHOD(IT403) {
            Shipment testPackage = { 100, 5.0, {2,'B'} };

            Truck truck[] = {
            { 5000, 250, blueRoute, {} } ,
                {0,0, green, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 1);
        }

        TEST_METHOD(IT404) {
            Shipment testPackage = { 100, 5.0, {2,'B'} };

            Truck truck[] = {
            { 5000, 250, blueRoute, {} } ,
             {5000,250, green, {} } ,
            { 5000, 250, yellow, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, -1);
        }

        TEST_METHOD(IT301) {
            Shipment testPackage = { 100, 5, {3,'K'} };

            Truck truck[] = {
            { 500, 25, blueRoute, {} } ,
                {500,25, green, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 1);
        }

        TEST_METHOD(IT302) {
            Shipment testPackage = { 100, 5.0, {22,'B'} };

            Truck truck[] = {
            { 500, 25, blueRoute, {} } ,
             {100,25, green, {} } ,
            { 500, 25, yellow, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 2);
        }

        TEST_METHOD(IT303) {
            Shipment testPackage = { 100, 5.0, {22,'B'} };

            Truck truck[] = {
           { 5000, 250, blueRoute, {} } ,
            {5000,250, green, {} } ,
           { 5000, 250, yellow, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, -1);
        }

        TEST_METHOD(IT304) {
            Shipment testPackage = { 100, 5.0, {3,'M'} };

            Truck truck[] = {
         { 500, 25, blueRoute, {} } ,
         { 500, 25, yellow, {} } };


            int result = assignPackage(finalMap, truck, testPackage);
            Assert::AreEqual(result, 0);
        }

    };
}




/*int main() {
    return 0;


}*/
