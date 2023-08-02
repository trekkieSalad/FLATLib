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
    setDestroy(set, NULL);

    set = setCreate(FLOAT);
    CU_ASSERT_NOT_EQUAL(set, NULL);
    CU_ASSERT_NOT_EQUAL(set->buckets, NULL);
    CU_ASSERT_EQUAL(set->size, 11);
    CU_ASSERT_EQUAL(set->type, FLOAT);
    CU_ASSERT_EQUAL(set->hashFunction, getHashFunction(FLOAT));
    CU_ASSERT_EQUAL(set->equalsFunction, getEqualsFunction(FLOAT));
    CU_ASSERT_EQUAL(set->toStringFunction, getToStringFunction(FLOAT));
    setDestroy(set, NULL);
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

    setDestroy(set, NULL);

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

    setDestroy(set, NULL);
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

    setDestroy(set, NULL);

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

    setDestroy(set, NULL);
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

    setDestroy(set, NULL);
}

void setBasicSuite() {
    CU_pSuite setBasicSuite = NULL;

    setBasicSuite = CU_add_suite("setBasicTest", NULL, NULL);
    CU_add_test(setBasicSuite, "Set creation", testSetCreate);
    CU_add_test(setBasicSuite, "Element addition", testSetAdd);
    CU_add_test(setBasicSuite, "Element removal", testSetRemove);
    CU_add_test(setBasicSuite, "Element repetition", testSetRepetition);
}