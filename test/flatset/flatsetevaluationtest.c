#include <flatset.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_flat_set_equals() {
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setD = flat_set_create(INT);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i2);
    flat_set_add_element(setA, &i3);
    flat_set_add_element(setA, &i4);

    flat_set_add_element(setB, &i3);
    flat_set_add_element(setB, &(int){1});
    flat_set_add_element(setB, &i4);
    flat_set_add_element(setB, &i2);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i2);
    flat_set_add_element(setC, &i3);
    flat_set_add_element(setC, &i4);
    flat_set_add_element(setC, &i5);

    flat_set_add_element(setD, &i1);
    flat_set_add_element(setD, &i2);
    flat_set_add_element(setD, &i3);

    i1 = 9;

    CU_ASSERT_TRUE(flat_set_equals(setA, setB));
    CU_ASSERT_FALSE(flat_set_equals(setA, setC));
    CU_ASSERT_FALSE(flat_set_equals(setA, setD));
    CU_ASSERT_FALSE(flat_set_equals(setC, setD));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setD);
}

void test_flat_set_subset() {
    FlatSet setA = flat_set_create(INT);
    FlatSet setB = flat_set_create(INT);
    FlatSet setC = flat_set_create(INT);
    FlatSet setD = flat_set_create(INT);
    FlatSet setE = flat_set_create(INT);

    FlatSet setF = flat_set_create(STRING);
    FlatSet setG = flat_set_create(STRING);
    FlatSet setH = flat_set_create(STRING);

    int i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;

    flat_set_add_element(setA, &i1);
    flat_set_add_element(setA, &i2);
    flat_set_add_element(setA, &i3);
    flat_set_add_element(setA, &i4);

    flat_set_add_element(setB, &i3);
    flat_set_add_element(setB, &i1);
    flat_set_add_element(setB, &i4);
    flat_set_add_element(setB, &i2);

    flat_set_add_element(setC, &i1);
    flat_set_add_element(setC, &i2);
    flat_set_add_element(setC, &i3);
    flat_set_add_element(setC, &i4);
    flat_set_add_element(setC, &i5);

    flat_set_add_element(setD, &i1);
    flat_set_add_element(setD, &i2);
    flat_set_add_element(setD, &i3);

    flat_set_add_element(setE, &i1);
    flat_set_add_element(setE, &i2);
    flat_set_add_element(setE, &i3);
    flat_set_add_element(setE, &i5);

    flat_set_add_element(setF, &(char *){"Hello"});
    flat_set_add_element(setF, &(char *){"World"});
    flat_set_add_element(setF, &(char *){"Foo"});

    flat_set_add_element(setG, &(char *){"Hello"});
    flat_set_add_element(setG, &(char *){"World"});

    flat_set_add_element(setH, &(char *){"Foo"});

    CU_ASSERT_TRUE(flat_set_is_subset_of(setA, setB));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setB, setA));

    CU_ASSERT_TRUE(flat_set_is_subset_of(setA, setC));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setA, setD));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setD, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setA, setE));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setE, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setA, setF));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setA, setG));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setG, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setA, setH));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setH, setA));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setD));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setD, setC));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setE));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setE, setC));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setF));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setC));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setG));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setG, setC));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setC, setH));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setH, setC));

    CU_ASSERT_TRUE(flat_set_is_subset_of(setD, setE));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setE, setD));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setD, setF));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setD));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setD, setG));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setG, setD));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setD, setH));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setH, setD));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setE, setF));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setE));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setE, setG));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setG, setE));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setE, setH));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setH, setE));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setG));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setG, setF));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setF, setH));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setH, setF));

    CU_ASSERT_FALSE(flat_set_is_subset_of(setG, setH));
    CU_ASSERT_FALSE(flat_set_is_subset_of(setH, setG));

    CU_ASSERT_TRUE(flat_set_is_subset_of(setA, setA));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setB, setB));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setC, setC));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setD, setD));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setE, setE));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setF, setF));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setG, setG));
    CU_ASSERT_TRUE(flat_set_is_subset_of(setH, setH));

    flat_set_destroy(setA);
    flat_set_destroy(setB);
    flat_set_destroy(setC);
    flat_set_destroy(setD);
    flat_set_destroy(setE);
    flat_set_destroy(setF);
    flat_set_destroy(setG);
    flat_set_destroy(setH);
}

void flat_set_eval_suite() {
    CU_pSuite setEvalSuite = NULL;

    setEvalSuite = CU_add_suite("setEvaluationTests", NULL, NULL);
    CU_add_test(setEvalSuite, "Set equals evaluation", test_flat_set_equals);
    CU_add_test(setEvalSuite, "Set subset evaluation", test_flat_set_subset);
}