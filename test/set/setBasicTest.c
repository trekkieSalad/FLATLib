#include <set.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void testSetCreate() {
    Set *set = setCreate(INT);
    CU_ASSERT_NOT_EQUAL(set, NULL);
    CU_ASSERT_NOT_EQUAL(set->buckets, NULL);
    CU_ASSERT_EQUAL(set->size, 11);
    CU_ASSERT_EQUAL(set->type, INT);
    CU_ASSERT_EQUAL(set->hashFunction, getHashFunction(INT));
    CU_ASSERT_EQUAL(set->equalsFunction, getEqualsFunction(INT));
    CU_ASSERT_EQUAL(set->toStringFunction, getToStringFunction(INT));
    setDestroy(set);

    set = setCreate(FLOAT);
    CU_ASSERT_NOT_EQUAL(set, NULL);
    CU_ASSERT_NOT_EQUAL(set->buckets, NULL);
    CU_ASSERT_EQUAL(set->size, 11);
    CU_ASSERT_EQUAL(set->type, FLOAT);
    CU_ASSERT_EQUAL(set->hashFunction, getHashFunction(FLOAT));
    CU_ASSERT_EQUAL(set->equalsFunction, getEqualsFunction(FLOAT));
    CU_ASSERT_EQUAL(set->toStringFunction, getToStringFunction(FLOAT));
    setDestroy(set);
}

void testSetAdd() {
    Set *set = setCreate(INT);
    setAdd(set, &(int){1});
    setAdd(set, &(int){2});
    setAdd(set, &(int){3});
    setAdd(set, &(int){4});
    setAdd(set, &(int){11});
    setAdd(set, &(int){12});
    setAdd(set, &(int){13});

    CU_ASSERT_TRUE(setContains(set, &(int){1}));
    CU_ASSERT_TRUE(setContains(set, &(int){2}));
    CU_ASSERT_TRUE(setContains(set, &(int){3}));
    CU_ASSERT_TRUE(setContains(set, &(int){4}));
    CU_ASSERT_FALSE(setContains(set, &(int){5}));
    CU_ASSERT_FALSE(setContains(set, &(int){6}));
    CU_ASSERT_FALSE(setContains(set, &(float){1}));
    CU_ASSERT_FALSE(setContains(set, &(char){2}));

    setDestroy(set);

    set = setCreate(FLOAT);
    setAdd(set, &(float){1.0});
    setAdd(set, &(float){2.0});
    setAdd(set, &(float){3.0});
    setAdd(set, &(float){4.0});

    CU_ASSERT_TRUE(setContains(set, &(float){1.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){2.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){3.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){4.0}));
    CU_ASSERT_FALSE(setContains(set, &(float){5.0}));
    CU_ASSERT_FALSE(setContains(set, &(float){6.0}));
    CU_ASSERT_FALSE(setContains(set, &(int){1}));
    CU_ASSERT_FALSE(setContains(set, &(char){2.0}));

    setDestroy(set);
}

void testSetRemove() {
    Set *set = setCreate(INT);
    setAdd(set, &(int){1});
    setAdd(set, &(int){2});
    setAdd(set, &(int){3});
    setAdd(set, &(int){4});

    CU_ASSERT_TRUE(setContains(set, &(int){1}));
    CU_ASSERT_TRUE(setContains(set, &(int){2}));
    CU_ASSERT_TRUE(setContains(set, &(int){3}));
    CU_ASSERT_TRUE(setContains(set, &(int){4}));
    
    setRemove(set, &(int){1});
    setRemove(set, &(int){3});

    CU_ASSERT_FALSE(setContains(set, &(int){1}));
    CU_ASSERT_TRUE(setContains(set, &(int){2}));
    CU_ASSERT_FALSE(setContains(set, &(int){3}));
    CU_ASSERT_TRUE(setContains(set, &(int){4}));

    setDestroy(set);

    set = setCreate(FLOAT);
    setAdd(set, &(float){1.0});
    setAdd(set, &(float){2.0});
    setAdd(set, &(float){3.0});
    setAdd(set, &(float){4.0});

    CU_ASSERT_TRUE(setContains(set, &(float){1.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){2.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){3.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){4.0}));

    setRemove(set, &(float){1.0});
    setRemove(set, &(float){3.0});

    CU_ASSERT_FALSE(setContains(set, &(float){1.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){2.0}));
    CU_ASSERT_FALSE(setContains(set, &(float){3.0}));
    CU_ASSERT_TRUE(setContains(set, &(float){4.0}));

    setDestroy(set);
}

void testSetRepetition(){
    Set *set = setCreate(INT);
    setAdd(set, &(int){1});
    setAdd(set, &(int){2});
    setAdd(set, &(int){3});
    setAdd(set, &(int){4});
    setAdd(set, &(int){1});
    setAdd(set, &(int){2});
    setAdd(set, &(int){3});
    setAdd(set, &(int){4});

    CU_ASSERT_EQUAL(setNElements(set), 4);
    CU_ASSERT_TRUE(setContains(set, &(int){1}));
    CU_ASSERT_TRUE(setContains(set, &(int){2}));
    CU_ASSERT_TRUE(setContains(set, &(int){3}));
    CU_ASSERT_TRUE(setContains(set, &(int){4}));

    setRemove(set, &(int){1});
    setRemove(set, &(int){2});
    setRemove(set, &(int){3});
    setRemove(set, &(int){4});

    CU_ASSERT_FALSE(setContains(set, &(int){1}));
    CU_ASSERT_FALSE(setContains(set, &(int){2}));
    CU_ASSERT_FALSE(setContains(set, &(int){3}));
    CU_ASSERT_FALSE(setContains(set, &(int){4}));

    setDestroy(set);
}

void testSetComposed(){
    Set *set = setCreate(SET);
    Set *inset1 = setCreate(INT);
    Set *inset2 = setCreate(INT);
    Set *inset3 = setCreate(INT);
    Set *inset4 = setCreate(INT);
    Set *inset5 = setCreate(STRING);

    setAdd(inset1, &(int){1});
    setAdd(inset1, &(int){3});
    setAdd(inset1, &(int){8});

    setAdd(inset2, &(int){1});
    setAdd(inset2, &(int){2});
    setAdd(inset2, &(int){3});
    setAdd(inset2, &(int){4});

    setAdd(inset3, &(int){1});

    setAdd(inset4, &(int){1});
    setAdd(inset4, &(int){2});
    setAdd(inset4, &(int){3});
    setAdd(inset4, &(int){4});

    setAdd(inset5, &(char *){"Hello"});

    setAdd(set, inset1);
    setAdd(set, inset2);
    setAdd(set, inset3);

    char *str = setToString(set);
    printf("%s\n", str);
    free(str);

    str = setToString(inset1);
    printf("%s\n", str);
    free(str);

    CU_ASSERT_EQUAL(setNElements(set), 3);
    CU_ASSERT_TRUE(setContains(set, inset1));
    CU_ASSERT_TRUE(setContains(set, inset2));
    CU_ASSERT_TRUE(setContains(set, inset3));
    CU_ASSERT_FALSE(setContains(set, inset4));
    CU_ASSERT_FALSE(setContains(set, inset5));

    setDestroy(set);
    setDestroy(inset1);
    setDestroy(inset2);
    setDestroy(inset3);
    setDestroy(inset4);
    setDestroy(inset5);
}

void setBasicSuite() {
    CU_pSuite setBasicSuite = NULL;

    setBasicSuite = CU_add_suite("setBasicTest", NULL, NULL);
    CU_add_test(setBasicSuite, "Set creation", testSetCreate);
    CU_add_test(setBasicSuite, "Element addition", testSetAdd);
    CU_add_test(setBasicSuite, "Element removal", testSetRemove);
    CU_add_test(setBasicSuite, "Element repetition", testSetRepetition);
    CU_add_test(setBasicSuite, "Set composed", testSetComposed);
}