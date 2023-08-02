#include <set.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void testSetsOperations() {
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setUnion, *setIntersection, *setDifference, *setSymmetricDifference;
    Set *setUnionFinal, *setIntersectionFinal, *setDifferenceFinal, *setSymmetricDifferenceFinal;

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);

    setAdd(setB, &i2);
    setAdd(setB, &i3);
    setAdd(setB, &i4);

    setUnionFinal = setCreate(INT);
    setAdd(setUnionFinal, &i1);
    setAdd(setUnionFinal, &i2);
    setAdd(setUnionFinal, &i3);
    setAdd(setUnionFinal, &i4);

    setIntersectionFinal = setCreate(INT);
    setAdd(setIntersectionFinal, &i2);
    setAdd(setIntersectionFinal, &i3);

    setDifferenceFinal = setCreate(INT);
    setAdd(setDifferenceFinal, &i1);

    setSymmetricDifferenceFinal = setCreate(INT);
    setAdd(setSymmetricDifferenceFinal, &i1);
    setAdd(setSymmetricDifferenceFinal, &i4);

    setUnion = setsUnion(setA, setB);
    setIntersection = setsIntersection(setA, setB);
    setDifference = setsDifference(setA, setB);
    setSymmetricDifference = setsSymmetricDifference(setA, setB);

    CU_ASSERT_TRUE(setsEquals(setUnion, setUnionFinal));
    CU_ASSERT_TRUE(setsEquals(setIntersection, setIntersectionFinal));
    CU_ASSERT_TRUE(setsEquals(setDifference, setDifferenceFinal));
    CU_ASSERT_TRUE(setsEquals(setSymmetricDifference, setSymmetricDifferenceFinal));

    setDestroy(setA, NULL);
    setDestroy(setB, NULL);
    setDestroy(setUnion, NULL);
    setDestroy(setIntersection, NULL);
    setDestroy(setDifference, NULL);
    setDestroy(setSymmetricDifference, NULL);
    setDestroy(setUnionFinal, NULL);
    setDestroy(setIntersectionFinal, NULL);
    setDestroy(setDifferenceFinal, NULL);
    setDestroy(setSymmetricDifferenceFinal, NULL);

}

void setOpSuite() {
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("setOperationTest", NULL, NULL);
    CU_add_test(pSuite, "Set Operations Test", testSetsOperations);
}