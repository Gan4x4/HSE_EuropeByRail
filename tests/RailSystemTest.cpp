/*
 * File:   RailSystemTest.cpp
 * Author: anton
 *
 * Created on May 16, 2015, 2:12:19 PM
 */

#include <limits.h>

#include "RailSystemTest.h"


CPPUNIT_TEST_SUITE_REGISTRATION(RailSystemTest);

RailSystemTest::RailSystemTest() {
}

RailSystemTest::~RailSystemTest() {
}

void RailSystemTest::setUp() {
    rs = new RailSystem("services.txt");
}

void RailSystemTest::tearDown() {
    delete rs;
}

void RailSystemTest::testRomeWarsaw() {
    Route actual = rs->getCheapestRoute("Rome","Warsaw");
    CPPUNIT_ASSERT(actual.fee == 175);
    CPPUNIT_ASSERT(actual.distance == 5200);
}
void RailSystemTest::testWarsawParis() {
    Route actual = rs->getCheapestRoute("Warsaw","Paris");
    CPPUNIT_ASSERT(actual.fee == 105);
    CPPUNIT_ASSERT(actual.distance == 4900);
 
}

void RailSystemTest::testLisbonAthens() {
    Route actual = rs->getCheapestRoute("Lisbon","Athens");
    CPPUNIT_ASSERT(actual.fee == 200);
    CPPUNIT_ASSERT(actual.distance == 4450);
}

void RailSystemTest::testNoRoute() {
    Route actual = rs->getCheapestRoute("Paris","Belfast");
    CPPUNIT_ASSERT(actual.fee == INT_MAX);
    CPPUNIT_ASSERT(actual.distance == INT_MAX);
}


