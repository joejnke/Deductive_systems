/* -- template for writing unit test header files -- 
 *
 * - Change the file name by removing "testTemplate_" string and 
 * by replacing "UnitName" with the name of the unit for which
 * this test is written.
 * 
 * - Replace all "UNITNAME" strings in this file with the name of
 * the unit for which this test is written.
 */

#ifndef UNITNAME_UTEST_H_
#define UNITNAME_UTEST_H_

/*
 * add includes here
 */
#include <string>

/*
 * add namespaces here
 */
using namespace std;

/*
 * test function declarations for each sub unit (function) to be tested
 * 
 * Note: Replace all "SubUnitName" strings in this file with 
 * the name of the sub unit (function) for which the test function is 
 * written.
 */

std::string test_SubUnitName(); // to be replaced

/*
 * Must contain functions
 * 
 * Note: Replace all "UnitName" strings in the below codes
 * with the name of the unit.
 */

int get_UnitNameTestCount();
int get_UnitNamePassedTestCount();

#endif /*UNITNAME_UTEST_H_*/