#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <prime.h>

void testPrimeEvaluate() {
    CU_ASSERT_EQUAL(nextPrimeSize(2), 5);
    CU_ASSERT_EQUAL(nextPrimeSize(3), 7);
    CU_ASSERT_EQUAL(nextPrimeSize(4), 11);
    CU_ASSERT_EQUAL(nextPrimeSize(5), 11);
    CU_ASSERT_EQUAL(nextPrimeSize(6), 13);
    CU_ASSERT_EQUAL(nextPrimeSize(7), 17);
    CU_ASSERT_EQUAL(nextPrimeSize(8), 17);
    CU_ASSERT_EQUAL(nextPrimeSize(9), 19);
    CU_ASSERT_EQUAL(nextPrimeSize(10), 23);
    CU_ASSERT_EQUAL(nextPrimeSize(11), 23);
    CU_ASSERT_EQUAL(nextPrimeSize(12), 29);
    CU_ASSERT_EQUAL(nextPrimeSize(13), 29);
    CU_ASSERT_EQUAL(nextPrimeSize(14), 29);
    CU_ASSERT_EQUAL(nextPrimeSize(15), 31);
    CU_ASSERT_EQUAL(nextPrimeSize(25), 53);
    CU_ASSERT_EQUAL(nextPrimeSize(50), 101);
    CU_ASSERT_EQUAL(nextPrimeSize(75), 151);
    CU_ASSERT_EQUAL(nextPrimeSize(100), 211);
    CU_ASSERT_EQUAL(nextPrimeSize(1501), 3011);
    CU_ASSERT_EQUAL(nextPrimeSize(10501), 21011);
}

void primeSuite() {
    CU_pSuite suite = CU_add_suite("Prime", NULL, NULL);
    CU_add_test(suite, "Prime Evaluate", testPrimeEvaluate);
}