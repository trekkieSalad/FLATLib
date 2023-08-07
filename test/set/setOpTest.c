#include <set.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void testSetsUnion(){
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setUnionAB, *setUnionFinalAB = setCreate(INT);
    Set *setUnionAC, *setUnionFinalAC = setCreate(INT);
    Set *setUnionBC, *setUnionFinalBC = setCreate(INT);
    Set *setUnionABC, *setUnionFinalABC = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    setAdd(setA, &i1);
    setAdd(setA, &i3);

    setAdd(setB, &i2);
    setAdd(setB, &i4);

    setAdd(setC, &i1);
    setAdd(setC, &i4);

    setAdd(setUnionFinalAB, &i1);
    setAdd(setUnionFinalAB, &i2);
    setAdd(setUnionFinalAB, &i3);
    setAdd(setUnionFinalAB, &i4);

    setAdd(setUnionFinalAC, &i1);
    setAdd(setUnionFinalAC, &i3);
    setAdd(setUnionFinalAC, &i4);

    setAdd(setUnionFinalBC, &i1);
    setAdd(setUnionFinalBC, &i2);
    setAdd(setUnionFinalBC, &i4);

    setAdd(setUnionFinalABC, &i1);
    setAdd(setUnionFinalABC, &i2);
    setAdd(setUnionFinalABC, &i3);
    setAdd(setUnionFinalABC, &i4);

    setUnionAB = setsUnion(setA, setB);
    setUnionAC = setsUnion(setA, setC);
    setUnionBC = setsUnion(setB, setC);
    setUnionABC = setsUnion(setUnionAB, setC);

    CU_ASSERT_TRUE(setsEquals(setUnionAB, setUnionFinalAB));
    CU_ASSERT_TRUE(setsEquals(setUnionAC, setUnionFinalAC));
    CU_ASSERT_TRUE(setsEquals(setUnionBC, setUnionFinalBC));
    CU_ASSERT_TRUE(setsEquals(setUnionABC, setUnionFinalABC));

    setDestroy(setA);
    setDestroy(setB);
    setDestroy(setC);
    setDestroy(setUnionAB);
    setDestroy(setUnionAC);
    setDestroy(setUnionBC);
    setDestroy(setUnionABC);
    setDestroy(setUnionFinalAB);
    setDestroy(setUnionFinalAC);
    setDestroy(setUnionFinalBC);
    setDestroy(setUnionFinalABC);
}

void testSetIntersection(){
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setIntersectionAB, *setIntersectionFinalAB = setCreate(INT);
    Set *setIntersectionAC, *setIntersectionFinalAC = setCreate(INT);
    Set *setIntersectionBC, *setIntersectionFinalBC = setCreate(INT);
    Set *setIntersectionABC, *setIntersectionFinalABC = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);

    setAdd(setB, &i2);
    setAdd(setB, &i4);

    setAdd(setC, &i1);
    setAdd(setC, &i3);
    setAdd(setC, &i4);

    setAdd(setIntersectionFinalAB, &i2);

    setAdd(setIntersectionFinalAC, &i1);
    setAdd(setIntersectionFinalAC, &i3);

    setAdd(setIntersectionFinalBC, &i4);

    setIntersectionAB = setsIntersection(setA, setB);
    setIntersectionAC = setsIntersection(setA, setC);
    setIntersectionBC = setsIntersection(setB, setC);
    setIntersectionABC = setsIntersection(setIntersectionAB, setC);

    CU_ASSERT_TRUE(setsEquals(setIntersectionAB, setIntersectionFinalAB));
    CU_ASSERT_TRUE(setsEquals(setIntersectionAC, setIntersectionFinalAC));
    CU_ASSERT_TRUE(setsEquals(setIntersectionBC, setIntersectionFinalBC));
    CU_ASSERT_TRUE(setsEquals(setIntersectionABC, setIntersectionFinalABC));

    setDestroy(setA);
    setDestroy(setB);
    setDestroy(setC);
    setDestroy(setIntersectionAB);
    setDestroy(setIntersectionAC);
    setDestroy(setIntersectionBC);
    setDestroy(setIntersectionABC);
    setDestroy(setIntersectionFinalAB);
    setDestroy(setIntersectionFinalAC);
    setDestroy(setIntersectionFinalBC);
    setDestroy(setIntersectionFinalABC);
}

void testSetsDifference(){
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setDifferenceAB, *setDifferenceFinalAB = setCreate(INT);
    Set *setDifferenceBA, *setDifferenceFinalBA = setCreate(INT);
    Set *setDifferenceAC, *setDifferenceFinalAC = setCreate(INT);
    Set *setDifferenceCA, *setDifferenceFinalCA = setCreate(INT);
    Set *setDifferenceBC, *setDifferenceFinalBC = setCreate(INT);
    Set *setDifferenceCB, *setDifferenceFinalCB = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);

    setAdd(setB, &i2);
    setAdd(setB, &i4);

    setAdd(setC, &i1);
    setAdd(setC, &i3);
    setAdd(setC, &i4);

    setAdd(setDifferenceFinalAB, &i1);
    setAdd(setDifferenceFinalAB, &i3);

    setAdd(setDifferenceFinalBA, &i4);

    setAdd(setDifferenceFinalAC, &i2);

    setAdd(setDifferenceFinalCA, &i4);

    setAdd(setDifferenceFinalBC, &i2);

    setAdd(setDifferenceFinalCB, &i1);
    setAdd(setDifferenceFinalCB, &i3);

    setDifferenceAB = setsDifference(setA, setB);
    setDifferenceBA = setsDifference(setB, setA);
    setDifferenceAC = setsDifference(setA, setC);
    setDifferenceCA = setsDifference(setC, setA);
    setDifferenceBC = setsDifference(setB, setC);
    setDifferenceCB = setsDifference(setC, setB);

    CU_ASSERT_TRUE(setsEquals(setDifferenceAB, setDifferenceFinalAB));
    CU_ASSERT_TRUE(setsEquals(setDifferenceBA, setDifferenceFinalBA));
    CU_ASSERT_TRUE(setsEquals(setDifferenceAC, setDifferenceFinalAC));
    CU_ASSERT_TRUE(setsEquals(setDifferenceCA, setDifferenceFinalCA));
    CU_ASSERT_TRUE(setsEquals(setDifferenceBC, setDifferenceFinalBC));
    CU_ASSERT_TRUE(setsEquals(setDifferenceCB, setDifferenceFinalCB));

    setDestroy(setA);
    setDestroy(setB);
    setDestroy(setC);
    setDestroy(setDifferenceAB);
    setDestroy(setDifferenceBA);
    setDestroy(setDifferenceAC);
    setDestroy(setDifferenceCA);
    setDestroy(setDifferenceBC);
    setDestroy(setDifferenceCB);
    setDestroy(setDifferenceFinalAB);
    setDestroy(setDifferenceFinalBA);
    setDestroy(setDifferenceFinalAC);
    setDestroy(setDifferenceFinalCA);
    setDestroy(setDifferenceFinalBC);
    setDestroy(setDifferenceFinalCB);

}

void testSetsSymmetricDifference(){
    Set *setA = setCreate(INT);
    Set *setB = setCreate(INT);
    Set *setC = setCreate(INT);
    Set *setSymmetricDifferenceAB, *setSymmetricDifferenceFinalAB = setCreate(INT);
    Set *setSymmetricDifferenceAC, *setSymmetricDifferenceFinalAC = setCreate(INT);
    Set *setSymmetricDifferenceBC, *setSymmetricDifferenceFinalBC = setCreate(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    setAdd(setA, &i1);
    setAdd(setA, &i2);
    setAdd(setA, &i3);

    setAdd(setB, &i2);
    setAdd(setB, &i4);

    setAdd(setC, &i1);
    setAdd(setC, &i3);
    setAdd(setC, &i4);

    setAdd(setSymmetricDifferenceFinalAB, &i1);
    setAdd(setSymmetricDifferenceFinalAB, &i3);
    setAdd(setSymmetricDifferenceFinalAB, &i4);

    setAdd(setSymmetricDifferenceFinalAC, &i2);
    setAdd(setSymmetricDifferenceFinalAC, &i4);

    setAdd(setSymmetricDifferenceFinalBC, &i1);
    setAdd(setSymmetricDifferenceFinalBC, &i2);
    setAdd(setSymmetricDifferenceFinalBC, &i3);

    setSymmetricDifferenceAB = setsSymmetricDifference(setA, setB);
    setSymmetricDifferenceAC = setsSymmetricDifference(setA, setC);
    setSymmetricDifferenceBC = setsSymmetricDifference(setB, setC);

    CU_ASSERT_TRUE(setsEquals(setSymmetricDifferenceAB, setSymmetricDifferenceFinalAB));
    CU_ASSERT_TRUE(setsEquals(setSymmetricDifferenceAC, setSymmetricDifferenceFinalAC));
    CU_ASSERT_TRUE(setsEquals(setSymmetricDifferenceBC, setSymmetricDifferenceFinalBC));

    setDestroy(setA);
    setDestroy(setB);
    setDestroy(setC);
    setDestroy(setSymmetricDifferenceAB);
    setDestroy(setSymmetricDifferenceAC);
    setDestroy(setSymmetricDifferenceBC);
    setDestroy(setSymmetricDifferenceFinalAB);
    setDestroy(setSymmetricDifferenceFinalAC);
    setDestroy(setSymmetricDifferenceFinalBC);
}

void testSetPower(){
    Set *auxIntSet = setCreate(INT), *auxCharSet = setCreate(CHAR);
    Set *powerIntSet, *finalPowerIntSet = setCreate(SET);
    Set *powerCharSet, *finalPowerCharSet = setCreate(SET);
    int i1 = 1, i2 = 2, i3 = 3;
    char c1 = 'a', c2 = 'b', c3 = 'c';

    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i1);
    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i2);
    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i3);
    setAdd(finalPowerIntSet, auxIntSet);
    setDestroy(auxIntSet);
    auxIntSet = setCreate(INT);
    setAdd(auxIntSet, &i2);
    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i3);
    setAdd(finalPowerIntSet, auxIntSet);
    setDestroy(auxIntSet);
    auxIntSet = setCreate(INT);
    setAdd(auxIntSet, &i3);
    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i1);
    setAdd(finalPowerIntSet, auxIntSet);
    setAdd(auxIntSet, &i2);

    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c1);
    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c2);
    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c3);
    setAdd(finalPowerCharSet, auxCharSet);
    setDestroy(auxCharSet);
    auxCharSet = setCreate(CHAR);
    setAdd(auxCharSet, &c2);
    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c3);
    setAdd(finalPowerCharSet, auxCharSet);
    setDestroy(auxCharSet);
    auxCharSet = setCreate(CHAR);
    setAdd(auxCharSet, &c3);
    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c1);
    setAdd(finalPowerCharSet, auxCharSet);
    setAdd(auxCharSet, &c2);

    powerIntSet = powerSet(auxIntSet);
    powerCharSet = powerSet(auxCharSet);

    CU_ASSERT_TRUE(setsEquals(powerIntSet, finalPowerIntSet));
    CU_ASSERT_TRUE(setsEquals(powerCharSet, finalPowerCharSet));
    CU_ASSERT_FALSE(setsEquals(powerIntSet, powerCharSet));

    setDestroy(auxIntSet);
    setDestroy(auxCharSet);
    setDestroy(powerIntSet);
    setDestroy(powerCharSet);
    setDestroy(finalPowerIntSet);
    setDestroy(finalPowerCharSet);
}

void setOpSuite() {
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("setOperationTest", NULL, NULL);
    CU_add_test(pSuite, "Set union", testSetsUnion);
    CU_add_test(pSuite, "Set intersection", testSetIntersection);
    CU_add_test(pSuite, "Set difference", testSetsDifference);
    CU_add_test(pSuite, "Set symmetric difference", testSetsSymmetricDifference);
    CU_add_test(pSuite, "Set power", testSetPower);
}