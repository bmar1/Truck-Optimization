#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackBoxTests
{
    //Test Series 1
    const struct Map map = populateMap();

    struct Route blueRoute = getBlueRoute();
    struct Route yellow = getYellowRoute();
    struct Route green = getGreenRoute();

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
            struct Shipment shipment { 2000, 5, address };

            bool result = valid(shipment, finalMap);
            Assert::AreEqual(result, true);
        };



        TEST_METHOD(test_valid_case3)
        {
            struct Point address { 9, 'H' };
            struct Shipment shipment { -1, 5, address };

            bool result = valid(shipment, finalMap);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_valid_case4)
        {
            struct Point address { 4, 'H' };
            struct Shipment shipment { INT_MAX, 2, address };

            bool result = valid(shipment, finalMap);
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


      /*  To be retested//values tweaked.
      TEST_METHOD(test_check_divert1)
        {

            struct Truck trucks[] = {
                {1000, 80, green, {}},
                {2000, 40, yellow, {}}

            };
            struct Point address { 'Q', '2' };
            struct Shipment shipment { 500, 5, address };

            int result = divert(finalMap, trucks, shipment, 0);
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(test_check_divert2)
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
            Assert::AreEqual(-1, result);
        */

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

namespace WhiteBoxTests{
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

            bool result = valid(testPackage, map);
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

    };

}

/*int main() {
    return 0;


}*/
