#include <set.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void testSetCreate() {

    for (int i = 0; i < _TYPE_COUNT ; i++){        
        Set *set = setCreate(i);
        CU_ASSERT_NOT_EQUAL(set, NULL);
        CU_ASSERT_NOT_EQUAL(set->buckets, NULL);
        CU_ASSERT_EQUAL(set->size, 11);
        CU_ASSERT_EQUAL(set->type, i);
        CU_ASSERT_EQUAL(set->hashFunction, getHashFunction(i));
        CU_ASSERT_EQUAL(set->equalsFunction, getEqualsFunction(i));
        CU_ASSERT_EQUAL(set->toStringFunction, getToStringFunction(i));
        CU_ASSERT_EQUAL(set->cloneFunction, getCloneFunction(i));
        CU_ASSERT_EQUAL(set->freeFunction, getFreeFunction(i));
        setDestroy(set);
    }
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

    setDestroy(set);

    set = setCreate(STRING);
    setAdd(set, &(char *){"1"});
    setAdd(set, &(char *){"2"});
    setAdd(set, &(char *){"3"});
    setAdd(set, &(char *){"4"});
    setAdd(set, &(char *){"11"});
    setAdd(set, &(char *){"12"});
    setAdd(set, &(char *){"a"});
    CU_ASSERT_TRUE(setContains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"2"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"3"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"4"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"a"}));
    CU_ASSERT_FALSE(setContains(set, &(char *){"5"}));
    CU_ASSERT_FALSE(setContains(set, &(char *){"6"}));
    CU_ASSERT_FALSE(setContains(set, &(char *){"hola"}));

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

    set = setCreate(STRING);
    setAdd(set, &(char *){"1"});
    setAdd(set, &(char *){"2"});
    setAdd(set, &(char *){"hola"});
    setAdd(set, &(char *){"adios"});

    CU_ASSERT_TRUE(setContains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"2"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"hola"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"adios"}));

    setRemove(set, &(char *){"1"});
    setRemove(set, &(char *){"hola"});

    CU_ASSERT_FALSE(setContains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"2"}));
    CU_ASSERT_FALSE(setContains(set, &(char *){"hola"}));
    CU_ASSERT_TRUE(setContains(set, &(char *){"adios"}));

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
    Set *inset6 = setCreate(STRING);
    Set *inset7 = setCreate(STRING);

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

    setAdd(inset6, &(char *){"Bye"});
    setAdd(inset6, &(char *){"Hello"});
    setAdd(inset6, &(char *){"Good morning"});

    setAdd(inset7, &(char *){"Dinner"});
    setAdd(inset7, &(char *){"Lunch"});
    setAdd(inset7, &(char *){"Breakfast"});
    setAdd(inset7, &(char *){"Dessert"});

    setAdd(set, inset1);
    setAdd(set, inset2);
    setAdd(set, inset3);

    CU_ASSERT_EQUAL(setNElements(set), 3);
    CU_ASSERT_TRUE(setContains(set, inset1));
    CU_ASSERT_TRUE(setContains(set, inset2));
    CU_ASSERT_TRUE(setContains(set, inset3));
    CU_ASSERT_TRUE(setContains(set, inset4));
    CU_ASSERT_FALSE(setContains(set, inset5));

    setDestroy(set);

    set = setCreate(SET);
    setAdd(set, inset5);
    setAdd(set, inset6);
    setAdd(set, inset7);

    CU_ASSERT_EQUAL(setNElements(set), 3);
    CU_ASSERT_TRUE(setContains(set, inset5));
    CU_ASSERT_TRUE(setContains(set, inset6));
    CU_ASSERT_TRUE(setContains(set, inset7));
    CU_ASSERT_FALSE(setContains(set, inset1));

    setDestroy(set);
    setDestroy(inset1);
    setDestroy(inset2);
    setDestroy(inset3);
    setDestroy(inset4);
    setDestroy(inset5);
    setDestroy(inset6);
    setDestroy(inset7);

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