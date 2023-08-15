#include <flatset.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_flat_set_union(){
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setUnionAB, setUnionFinalAB = flat_set_create(INT);
    FlatSet setUnionAC, setUnionFinalAC = flat_set_create(INT);
    FlatSet setUnionBC, setUnionFinalBC = flat_set_create(INT);
    FlatSet setUnionABC, setUnionFinalABC = flat_set_create(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i3);

    flat_set_add_element(setB, &i2);
    flat_set_add_element(setB, &i4);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i4);

    flat_set_add_element(setUnionFinalAB, &i1);
    flat_set_add_element(setUnionFinalAB, &i2);
    flat_set_add_element(setUnionFinalAB, &i3);
    flat_set_add_element(setUnionFinalAB, &i4);

    flat_set_add_element(setUnionFinalAC, &i1);
    flat_set_add_element(setUnionFinalAC, &i3);
    flat_set_add_element(setUnionFinalAC, &i4);

    flat_set_add_element(setUnionFinalBC, &i1);
    flat_set_add_element(setUnionFinalBC, &i2);
    flat_set_add_element(setUnionFinalBC, &i4);

    flat_set_add_element(setUnionFinalABC, &i1);
    flat_set_add_element(setUnionFinalABC, &i2);
    flat_set_add_element(setUnionFinalABC, &i3);
    flat_set_add_element(setUnionFinalABC, &i4);

    setUnionAB = flat_set_union(setA, setB);
    setUnionAC = flat_set_union(setA, setC);
    setUnionBC = flat_set_union(setB, setC);
    setUnionABC = flat_set_union(setUnionAB, setC);

    CU_ASSERT_TRUE(flat_set_equals(setUnionAB, setUnionFinalAB));
    CU_ASSERT_TRUE(flat_set_equals(setUnionAC, setUnionFinalAC));
    CU_ASSERT_TRUE(flat_set_equals(setUnionBC, setUnionFinalBC));
    CU_ASSERT_TRUE(flat_set_equals(setUnionABC, setUnionFinalABC));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setUnionAB);
    flat_set_destroy(setUnionAC);
    flat_set_destroy(setUnionBC);
    flat_set_destroy(setUnionABC);
    flat_set_destroy(setUnionFinalAB);
    flat_set_destroy(setUnionFinalAC);
    flat_set_destroy(setUnionFinalBC);
    flat_set_destroy(setUnionFinalABC);
}

void test_flat_set_intersection(){
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setIntersectionAB, setIntersectionFinalAB = flat_set_create(INT);
    FlatSet setIntersectionAC, setIntersectionFinalAC = flat_set_create(INT);
    FlatSet setIntersectionBC, setIntersectionFinalBC = flat_set_create(INT);
    FlatSet setIntersectionABC, setIntersectionFinalABC = flat_set_create(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i2);
    flat_set_add_element(setA, &i3);

    flat_set_add_element(setB, &i2);
    flat_set_add_element(setB, &i4);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i3);
    flat_set_add_element(setC, &i4);

    flat_set_add_element(setIntersectionFinalAB, &i2);

    flat_set_add_element(setIntersectionFinalAC, &i1);
    flat_set_add_element(setIntersectionFinalAC, &i3);

    flat_set_add_element(setIntersectionFinalBC, &i4);

    setIntersectionAB = flat_set_intersection(setA, setB);
    setIntersectionAC = flat_set_intersection(setA, setC);
    setIntersectionBC = flat_set_intersection(setB, setC);
    setIntersectionABC = flat_set_intersection(setIntersectionAB, setC);

    CU_ASSERT_TRUE(flat_set_equals(setIntersectionAB, setIntersectionFinalAB));
    CU_ASSERT_TRUE(flat_set_equals(setIntersectionAC, setIntersectionFinalAC));
    CU_ASSERT_TRUE(flat_set_equals(setIntersectionBC, setIntersectionFinalBC));
    CU_ASSERT_TRUE(flat_set_equals(setIntersectionABC, setIntersectionFinalABC));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setIntersectionAB);
    flat_set_destroy(setIntersectionAC);
    flat_set_destroy(setIntersectionBC);
    flat_set_destroy(setIntersectionABC);
    flat_set_destroy(setIntersectionFinalAB);
    flat_set_destroy(setIntersectionFinalAC);
    flat_set_destroy(setIntersectionFinalBC);
    flat_set_destroy(setIntersectionFinalABC);
}

void test_flat_set_difference(){
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setDifferenceAB, setDifferenceFinalAB = flat_set_create(INT);
    FlatSet setDifferenceBA, setDifferenceFinalBA = flat_set_create(INT);
    FlatSet setDifferenceAC, setDifferenceFinalAC = flat_set_create(INT);
    FlatSet setDifferenceCA, setDifferenceFinalCA = flat_set_create(INT);
    FlatSet setDifferenceBC, setDifferenceFinalBC = flat_set_create(INT);
    FlatSet setDifferenceCB, setDifferenceFinalCB = flat_set_create(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i2);
    flat_set_add_element(setA, &i3);

    flat_set_add_element(setB, &i2);
    flat_set_add_element(setB, &i4);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i3);
    flat_set_add_element(setC, &i4);

    flat_set_add_element(setDifferenceFinalAB, &i1);
    flat_set_add_element(setDifferenceFinalAB, &i3);

    flat_set_add_element(setDifferenceFinalBA, &i4);

    flat_set_add_element(setDifferenceFinalAC, &i2);

    flat_set_add_element(setDifferenceFinalCA, &i4);

    flat_set_add_element(setDifferenceFinalBC, &i2);

    flat_set_add_element(setDifferenceFinalCB, &i1);
    flat_set_add_element(setDifferenceFinalCB, &i3);

    setDifferenceAB = flat_set_difference(setA, setB);
    setDifferenceBA = flat_set_difference(setB, setA);
    setDifferenceAC = flat_set_difference(setA, setC);
    setDifferenceCA = flat_set_difference(setC, setA);
    setDifferenceBC = flat_set_difference(setB, setC);
    setDifferenceCB = flat_set_difference(setC, setB);

    CU_ASSERT_TRUE(flat_set_equals(setDifferenceAB, setDifferenceFinalAB));
    CU_ASSERT_TRUE(flat_set_equals(setDifferenceBA, setDifferenceFinalBA));
    CU_ASSERT_TRUE(flat_set_equals(setDifferenceAC, setDifferenceFinalAC));
    CU_ASSERT_TRUE(flat_set_equals(setDifferenceCA, setDifferenceFinalCA));
    CU_ASSERT_TRUE(flat_set_equals(setDifferenceBC, setDifferenceFinalBC));
    CU_ASSERT_TRUE(flat_set_equals(setDifferenceCB, setDifferenceFinalCB));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setDifferenceAB);
    flat_set_destroy(setDifferenceBA);
    flat_set_destroy(setDifferenceAC);
    flat_set_destroy(setDifferenceCA);
    flat_set_destroy(setDifferenceBC);
    flat_set_destroy(setDifferenceCB);
    flat_set_destroy(setDifferenceFinalAB);
    flat_set_destroy(setDifferenceFinalBA);
    flat_set_destroy(setDifferenceFinalAC);
    flat_set_destroy(setDifferenceFinalCA);
    flat_set_destroy(setDifferenceFinalBC);
    flat_set_destroy(setDifferenceFinalCB);

}

void test_flat_set_symmetric_difference(){
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setSymmetricDifferenceAB, setSymmetricDifferenceFinalAB = flat_set_create(INT);
    FlatSet setSymmetricDifferenceAC, setSymmetricDifferenceFinalAC = flat_set_create(INT);
    FlatSet setSymmetricDifferenceBC, setSymmetricDifferenceFinalBC = flat_set_create(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i2);
    flat_set_add_element(setA, &i3);

    flat_set_add_element(setB, &i2);
    flat_set_add_element(setB, &i4);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i3);
    flat_set_add_element(setC, &i4);

    flat_set_add_element(setSymmetricDifferenceFinalAB, &i1);
    flat_set_add_element(setSymmetricDifferenceFinalAB, &i3);
    flat_set_add_element(setSymmetricDifferenceFinalAB, &i4);

    flat_set_add_element(setSymmetricDifferenceFinalAC, &i2);
    flat_set_add_element(setSymmetricDifferenceFinalAC, &i4);

    flat_set_add_element(setSymmetricDifferenceFinalBC, &i1);
    flat_set_add_element(setSymmetricDifferenceFinalBC, &i2);
    flat_set_add_element(setSymmetricDifferenceFinalBC, &i3);

    setSymmetricDifferenceAB = flat_set_symmetric_difference(setA, setB);
    setSymmetricDifferenceAC = flat_set_symmetric_difference(setA, setC);
    setSymmetricDifferenceBC = flat_set_symmetric_difference(setB, setC);

    CU_ASSERT_TRUE(flat_set_equals(setSymmetricDifferenceAB, setSymmetricDifferenceFinalAB));
    CU_ASSERT_TRUE(flat_set_equals(setSymmetricDifferenceAC, setSymmetricDifferenceFinalAC));
    CU_ASSERT_TRUE(flat_set_equals(setSymmetricDifferenceBC, setSymmetricDifferenceFinalBC));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setSymmetricDifferenceAB);
    flat_set_destroy(setSymmetricDifferenceAC);
    flat_set_destroy(setSymmetricDifferenceBC);
    flat_set_destroy(setSymmetricDifferenceFinalAB);
    flat_set_destroy(setSymmetricDifferenceFinalAC);
    flat_set_destroy(setSymmetricDifferenceFinalBC);
}

void test_flat_set_power(){
    FlatSet auxIntSet = flat_set_create(INT), auxCharSet = flat_set_create(CHAR);
    FlatSet powerIntSet, finalPowerIntSet = flat_set_create(SET);
    FlatSet powerCharSet, finalPowerCharSet = flat_set_create(SET);
    int i1 = 1, i2 = 2, i3 = 3;
    char c1 = 'a', c2 = 'b', c3 = 'c';

    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i1);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i2);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i3);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_destroy(auxIntSet);
    auxIntSet = flat_set_create(INT);
    flat_set_add_element(auxIntSet, &i2);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i3);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_destroy(auxIntSet);
    auxIntSet = flat_set_create(INT);
    flat_set_add_element(auxIntSet, &i3);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i1);
    flat_set_add_element(finalPowerIntSet, auxIntSet);
    flat_set_add_element(auxIntSet, &i2);

    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c1);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c2);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c3);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_destroy(auxCharSet);
    auxCharSet = flat_set_create(CHAR);
    flat_set_add_element(auxCharSet, &c2);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c3);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_destroy(auxCharSet);
    auxCharSet = flat_set_create(CHAR);
    flat_set_add_element(auxCharSet, &c3);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c1);
    flat_set_add_element(finalPowerCharSet, auxCharSet);
    flat_set_add_element(auxCharSet, &c2);

    powerIntSet = flat_set_power(auxIntSet);
    powerCharSet = flat_set_power(auxCharSet);

    CU_ASSERT_TRUE(flat_set_equals(powerIntSet, finalPowerIntSet));
    CU_ASSERT_TRUE(flat_set_equals(powerCharSet, finalPowerCharSet));
    CU_ASSERT_FALSE(flat_set_equals(powerIntSet, powerCharSet));

    flat_set_destroy(auxIntSet);
    flat_set_destroy(auxCharSet);
    flat_set_destroy(powerIntSet);
    flat_set_destroy(powerCharSet);
    flat_set_destroy(finalPowerIntSet);
    flat_set_destroy(finalPowerCharSet);
}

void flat_set_operation_test() {
    CU_pSuite pSuite = NULL;

    pSuite = CU_add_suite("setOperationTest", NULL, NULL);
    CU_add_test(pSuite, "Set union", test_flat_set_union);
    CU_add_test(pSuite, "Set intersection", test_flat_set_intersection);
    CU_add_test(pSuite, "Set difference", test_flat_set_difference);
    CU_add_test(pSuite, "Set symmetric difference", test_flat_set_symmetric_difference);
    CU_add_test(pSuite, "Set power", test_flat_set_power);
}