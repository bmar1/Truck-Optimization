#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackBoxTests
{
    TEST_CLASS(MappingTest)
    {
        struct Map map = populateMap();
    public:
        TEST_METHOD(test_printMap_case1)
        {
            int base1 = 1;
            int alphaCols = 1;
            printMap(map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case2)
        {
            int base1 = 8;
            int alphaCols = 0;
            printMap(map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case3)
        {
            int base1 = 20;
            int alphaCols = 1;
            printMap(map, base1, alphaCols);
        }
        TEST_METHOD(test_printMap_case4)
        {
            int base1 = 0;
            int alphaCols = 1;
            printMap(map, base1, alphaCols);
        }
        TEST_METHOD(test_distance_case1)
        {
            struct Point p1 = { 3, 4 };
            struct Point p2 = { 3, 4 };

            double result = distance(p1, p2);
            Assert::AreEqual(result, 0.0, 0.0001);
        }
        TEST_METHOD(test_distance_case2)
        {
            struct Point p1 = { 1, 2 };
            struct Point p2 = { 1, 6 };

            double result = distance(p1, p2);
            Assert::AreEqual(result, 4.0, 0.0001);
        }
        TEST_METHOD(test_distance_case3)
        {
            struct Point p1 = { 1, 1 };
            struct Point p2 = { 4, 5 };

            double result = distance(p1, p2);
            Assert::AreEqual(result, 5.0, 0.0001);
        }
        TEST_METHOD(test_distance_case4)
        {
            struct Point p1 = { 1, 4 };
            struct Point p2 = { 1, 10 };

            double result = distance(p1, p2);
            Assert::AreEqual(result, 6.0, 0.0001);
        }
    };
}
