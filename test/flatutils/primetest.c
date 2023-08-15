#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <prime.h>

void testPrimeEvaluate() {
    CU_ASSERT_EQUAL(next_prime_size(2), 5);
    CU_ASSERT_EQUAL(next_prime_size(3), 7);
    CU_ASSERT_EQUAL(next_prime_size(4), 11);
    CU_ASSERT_EQUAL(next_prime_size(5), 11);
    CU_ASSERT_EQUAL(next_prime_size(6), 13);
    CU_ASSERT_EQUAL(next_prime_size(7), 17);
    CU_ASSERT_EQUAL(next_prime_size(8), 17);
    CU_ASSERT_EQUAL(next_prime_size(9), 19);
    CU_ASSERT_EQUAL(next_prime_size(10), 23);
    CU_ASSERT_EQUAL(next_prime_size(11), 23);
    CU_ASSERT_EQUAL(next_prime_size(12), 29);
    CU_ASSERT_EQUAL(next_prime_size(13), 29);
    CU_ASSERT_EQUAL(next_prime_size(14), 29);
    CU_ASSERT_EQUAL(next_prime_size(15), 31);
    CU_ASSERT_EQUAL(next_prime_size(25), 53);
    CU_ASSERT_EQUAL(next_prime_size(50), 101);
    CU_ASSERT_EQUAL(next_prime_size(75), 151);
    CU_ASSERT_EQUAL(next_prime_size(100), 211);
    CU_ASSERT_EQUAL(next_prime_size(1501), 3011);
    CU_ASSERT_EQUAL(next_prime_size(10501), 21011);
}

void primeSuite() {
    CU_pSuite suite = CU_add_suite("Prime", NULL, NULL);
    CU_add_test(suite, "Prime Evaluate", testPrimeEvaluate);
}