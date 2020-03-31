/* -- template for implementing unit test header file -- 
 *
 * - Change the file name by removing "testTemplate_" string and 
 * by replacing "UnitName" with the name of the unit for which
 * this test is written.
 * 
 * Note: Remove this and all template block comments below after done
 * with the implementations.
 */

/*
 * add includes here
 */
#include <string>

/*
 * add namespaces here
 */
using namespace std;

/*
 * Must contain variables
 */
int testCount = 0;
int passedTestCount = 0;
std::string testResult;

/*
 * add variables here
 */

/*
 * Add implementations here
 * Implementations of test function declarations for each sub
 * unit (function) to be tested.
 * 
 * Note: Replace all "SubUnitName" strings in this file with 
 * the name of the sub unit (function) for which the test function is 
 * written.
 */

std::string test_SubUnitName() // to be replaced
{
    /*
     * WRITE TEST CODE HERE
     * Note: Update testResult to 
     *          testResult = "\nTest SubUnitName(): "
     *          testResult += "\nPass" // if test passed
     *          testResult += "\nFail" // if test failed
     */

    return testResult;
}

/*
 * Implementation of must contain functions
 * 
 * Note: Replace all "UnitName" strings in the below codes
 * with the name of the unit.
 */
int get_UnitNameTestCount() {
    return testCount;
}

int get_UnitNamePassedTestCount() {
    return passedTestCount;
}
