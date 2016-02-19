/*
 * File:   RailSystemTest.h
 * Author: anton
 *
 * Created on May 16, 2015, 2:12:18 PM
 */

#ifndef RAILSYSTEMTEST_H
#define	RAILSYSTEMTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../RailSystem.h"

class RailSystemTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(RailSystemTest);
    CPPUNIT_TEST(testWarsawParis);
    CPPUNIT_TEST(testLisbonAthens);
    CPPUNIT_TEST(testRomeWarsaw);
    CPPUNIT_TEST(testNoRoute);
    CPPUNIT_TEST_SUITE_END();

public:
    RailSystemTest();
    virtual ~RailSystemTest();
    void setUp();
    void tearDown();

private:
    RailSystem* rs;
    void testWarsawParis();
    void testLisbonAthens();
    void testRomeWarsaw();
    void testNoRoute();

};

#endif	/* RAILSYSTEMTEST_H */

