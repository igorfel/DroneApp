///
/// Created by Igorfel 20/04/16
///
// ClientTestSuite.h
#include <cxxtest/TestSuite.h>

class ClientTestSuite : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        TS_ASSERT(1 + 1 > 1);
        TS_ASSERT_EQUALS(1 + 1, 2);
    }
};
