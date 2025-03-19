#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackBoxTests
{
    //Test Series 1
    const struct Map map = populateMap();

    struct Route blueRoute = getBlueRoute();
    struct Route yellow = getYellowRoute();
    struct Route green = getGreenRoute();
    struct Map routeMap = addRoute(&map, &blueRoute);
    struct Map routeMap = addRoute(&map, &yellow);
    struct Map routeMap = addRoute(&map, &green);
    TEST_CLASS(MappingTest){
        
       /* FIX THESE TESTS TO HAVE ASSERTIONS!
       TEST_METHOD(test_printMap_case1)
        {
            int base1 = 1;
            int alphaCols = 1;
            printMap(&map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case2)
        {
            int base1 = 8;
            int alphaCols = 0;
            printMap(&map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case3)
        {
            int base1 = 20;
            int alphaCols = 1;
            printMap(&map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case4)
        {
            int base1 = 0;
            int alphaCols = 1;
            printMap(&map, base1, alphaCols);
        }
        */
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
            struct Point p2 = { 1, 6 };

            double result = distance(&p1, &p2);
            Assert::AreEqual(result, 4.0, 0.0001);
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
                {2000, 200.00, green, {}},
                {5000, 250.00, blueRoute, {}},
                {10, 250.00, yellow, {}}
            };

            struct Point address{'2','Q'};
            struct Shipment shipment { 250, 10.0, address };

            int result = assignPackage(map, trucks, shipment);
            Assert::AreEqual(result, 0);
        };

        TEST_METHOD(test_assign_case2)
        {

            struct Truck trucks[] = {
                {10, 250.00, green, {}},
                {5000, 250.00, blueRoute, {}},
                {10, 250.00, yellow, {}}
            };

            struct Point address { '12', 'D' };
            struct Shipment shipment { 200, 5.0, address };

            int result = assignPackage(map, trucks, shipment);
            Assert::AreEqual(result, 0);
        };


        TEST_METHOD(test_assign_case3)
        {

            struct Truck trucks[] = {
                {10, 200.00, green, {}},
                {5000, 250.00, blueRoute, {}},
                {90, 250.00, yellow, {}}
            };

            struct Point address { '1', 'X' };
            struct Shipment shipment { -1, 5.0, address };

            int result = assignPackage(map, trucks, shipment);
            Assert::AreEqual(result, -1);
        };

        TEST_METHOD(test_assign_case4)
        {

            struct Truck trucks[] = {
                {0, 200.00, green, {}},
                {5000, 250.00, blueRoute, {}},
                {100, 250.00, yellow, {}}
            };

            struct Point address { '9', 'H' };
            struct Shipment shipment { 3000, 1, address };

            int result = assignPackage(map, trucks, shipment);
            Assert::AreEqual(result, 0);
        };

        TEST_METHOD(test_valid_case1)
        {
            struct Point address {'9', 'H' };
            struct Shipment shipment { 20, 2, address };

            bool result = valid(shipment, map);
            Assert::AreEqual(result, true);
        };


        TEST_METHOD(test_valid_case2)
        {
            struct Point address { '2', 'B' };
            struct Shipment shipment { 4000, 7, address };

            bool result = valid(shipment, map);
            Assert::AreEqual(result, true);
        };



        TEST_METHOD(test_valid_case3)
        {
            struct Point address { '9', 'M' };
            struct Shipment shipment { -1, 5, address };

            bool result = valid(shipment, map);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_valid_case4)
        {
            struct Point address { '4', 'H' };
            struct Shipment shipment { INT_MAX, 2, address };

            bool result = valid(shipment, map);
            Assert::AreEqual(result, false);
        };

        TEST_METHOD(test_space_case1)
        {
            struct Truck trucks[] = { {5000, 250.00, blueRoute, {} } };

            struct Point address { '4', 'H' };
            struct Shipment shipment { 20, 2, address };

            bool result = checkSpace(trucks[1], shipment);
            Assert::AreEqual(result, true);
        };



        TEST_METHOD(test_space_case2)
        {
            struct Truck trucks[] = { {5000, 250.00, blueRoute, {} } };

            struct Point address { '2', 'H' };
            struct Shipment shipment { 4000, 7, address };

            bool result = checkSpace(trucks[1], shipment);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_space_case3)
        {
            struct Truck trucks[] = { {5000, 250.00, blueRoute, {} } };
            struct Point address { '4', 'H' };
            struct Shipment shipment { -1, 5, address };

            bool result = checkSpace(trucks[1], shipment);
            Assert::AreEqual(result, false);
        };


        TEST_METHOD(test_space_case4)
        {
            struct Truck trucks[] = { {10, 250.00, blueRoute, {} } };
            struct Point address { '8', 'K' };
            struct Shipment shipment { 3000, 2, address };

            bool result = checkSpace(trucks[1], shipment);
            Assert::AreEqual(result, false);
        };




    };
}

int main() {
    return 0;


}
