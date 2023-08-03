#include <set.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void testSetEquals() {
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setD = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);
    setAdd(setA, &i4);

    setAdd(setB, &i3);
    setAdd(setB, &i1);
    setAdd(setB, &i4);
    setAdd(setB, &i2);

    setAdd(setC, &i1);
    setAdd(setC, &i2);
    setAdd(setC, &i3);
    setAdd(setC, &i4);
    setAdd(setC, &i5);

    setAdd(setD, &i1);
    setAdd(setD, &i2);
    setAdd(setD, &i3);

    CU_ASSERT_TRUE(setsEquals(setA, setB));
    CU_ASSERT_FALSE(setsEquals(setA, setC));
    CU_ASSERT_FALSE(setsEquals(setA, setD));
    CU_ASSERT_FALSE(setsEquals(setC, setD));

    setDestroy(setA, NULL);
    setDestroy(setB, NULL);
    setDestroy(setC, NULL);
    setDestroy(setD, NULL);
}

void testSetSubset() {
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setD = setCreate(INT);
    Set *setE = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);
    setAdd(setA, &i4);

    setAdd(setB, &i3);
    setAdd(setB, &i1);
    setAdd(setB, &i4);
    setAdd(setB, &i2);

    setAdd(setC, &i1);
    setAdd(setC, &i2);
    setAdd(setC, &i3);
    setAdd(setC, &i4);
    setAdd(setC, &i5);

    setAdd(setD, &i1);
    setAdd(setD, &i2);
    setAdd(setD, &i3);

    setAdd(setE, &i1);
    setAdd(setE, &i2);
    setAdd(setE, &i3);
    setAdd(setE, &i5);

    CU_ASSERT_TRUE(setIsSubsetOf(setA, setB));
    CU_ASSERT_TRUE(setIsSubsetOf(setB, setA));

    CU_ASSERT_TRUE(setIsSubsetOf(setA, setC));
    CU_ASSERT_FALSE(setIsSubsetOf(setC, setA));

    CU_ASSERT_FALSE(setIsSubsetOf(setA, setD));
    CU_ASSERT_TRUE(setIsSubsetOf(setD, setA));

    CU_ASSERT_FALSE(setIsSubsetOf(setA, setE));
    CU_ASSERT_FALSE(setIsSubsetOf(setE, setA));

    CU_ASSERT_FALSE(setIsSubsetOf(setC, setD));
    CU_ASSERT_TRUE(setIsSubsetOf(setD, setC));

    CU_ASSERT_FALSE(setIsSubsetOf(setC, setE));
    CU_ASSERT_TRUE(setIsSubsetOf(setE, setC));

    CU_ASSERT_TRUE(setIsSubsetOf(setD, setE));
    CU_ASSERT_FALSE(setIsSubsetOf(setE, setD));

    CU_ASSERT_TRUE(setIsSubsetOf(setA, setA));
    CU_ASSERT_TRUE(setIsSubsetOf(setB, setB));
    CU_ASSERT_TRUE(setIsSubsetOf(setC, setC));
    CU_ASSERT_TRUE(setIsSubsetOf(setD, setD));
    CU_ASSERT_TRUE(setIsSubsetOf(setE, setE));

    setDestroy(setA, NULL);
    setDestroy(setB, NULL);
    setDestroy(setC, NULL);
    setDestroy(setD, NULL);
    setDestroy(setE, NULL);
}

void setEvalSuite() {
    CU_pSuite setEvalSuite = NULL;

    setEvalSuite = CU_add_suite("setEvaluationTests", NULL, NULL);
    CU_add_test(setEvalSuite, "Set equals evaluation", testSetEquals);
    CU_add_test(setEvalSuite, "Set subset evaluation", testSetSubset);
}