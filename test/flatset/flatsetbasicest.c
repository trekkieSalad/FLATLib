#include <flatset.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_flat_set_create() {

    for (int i = 0; i < _TYPE_COUNT ; i++){        
        FlatSet set = flat_set_create(i);
        /*CU_ASSERT_NOT_EQUAL(set, NULL);
        CU_ASSERT_NOT_EQUAL(set->buckets, NULL);
        CU_ASSERT_EQUAL(set->size, 11);
        CU_ASSERT_EQUAL(set->type, i);
        CU_ASSERT_EQUAL(set->hashFunction, getHashFunction(i));
        CU_ASSERT_EQUAL(set->equalsFunction, getEqualsFunction(i));
        CU_ASSERT_EQUAL(set->toStringFunction, getToStringFunction(i));
        CU_ASSERT_EQUAL(set->cloneFunction, getCloneFunction(i));
        CU_ASSERT_EQUAL(set->freeFunction, getFreeFunction(i));*/
        flat_set_destroy(set);
    }
}

void test_flat_set_add() {
    FlatSet set = flat_set_create(INT);
    flat_set_add_element(set, &(int){1});
    flat_set_add_element(set, &(int){2});
    flat_set_add_element(set, &(int){3});
    flat_set_add_element(set, &(int){4});
    flat_set_add_element(set, &(int){11});
    flat_set_add_element(set, &(int){12});
    flat_set_add_element(set, &(int){13});

    CU_ASSERT_TRUE(flat_set_contains(set, &(int){1}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){2}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){3}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){4}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){5}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){6}));

    flat_set_destroy(set);

    set = flat_set_create(FLOAT);
    flat_set_add_element(set, &(float){1.0});
    flat_set_add_element(set, &(float){2.0});
    flat_set_add_element(set, &(float){3.0});
    flat_set_add_element(set, &(float){4.0});

    CU_ASSERT_TRUE(flat_set_contains(set, &(float){1.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){2.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){3.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){4.0}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(float){5.0}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(float){6.0}));

    flat_set_destroy(set);

    set = flat_set_create(STRING);
    flat_set_add_element(set, &(char *){"1"});
    flat_set_add_element(set, &(char *){"2"});
    flat_set_add_element(set, &(char *){"3"});
    flat_set_add_element(set, &(char *){"4"});
    flat_set_add_element(set, &(char *){"11"});
    flat_set_add_element(set, &(char *){"12"});
    flat_set_add_element(set, &(char *){"a"});
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"2"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"3"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"4"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"a"}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(char *){"5"}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(char *){"6"}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(char *){"hola"}));

    flat_set_destroy(set);
}

void test_flat_set_remove() {
    FlatSet set = flat_set_create(INT);
    flat_set_add_element(set, &(int){1});
    flat_set_add_element(set, &(int){2});
    flat_set_add_element(set, &(int){3});
    flat_set_add_element(set, &(int){4});

    CU_ASSERT_TRUE(flat_set_contains(set, &(int){1}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){2}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){3}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){4}));
    
    flat_set_remove_element(set, &(int){1});
    flat_set_remove_element(set, &(int){3});

    CU_ASSERT_FALSE(flat_set_contains(set, &(int){1}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){2}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){3}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){4}));

    flat_set_destroy(set);

    set = flat_set_create(FLOAT);
    flat_set_add_element(set, &(float){1.0});
    flat_set_add_element(set, &(float){2.0});
    flat_set_add_element(set, &(float){3.0});
    flat_set_add_element(set, &(float){4.0});

    CU_ASSERT_TRUE(flat_set_contains(set, &(float){1.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){2.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){3.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){4.0}));

    flat_set_remove_element(set, &(float){1.0});
    flat_set_remove_element(set, &(float){3.0});

    CU_ASSERT_FALSE(flat_set_contains(set, &(float){1.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){2.0}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(float){3.0}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(float){4.0}));

    flat_set_destroy(set);

    set = flat_set_create(STRING);
    flat_set_add_element(set, &(char *){"1"});
    flat_set_add_element(set, &(char *){"2"});
    flat_set_add_element(set, &(char *){"hola"});
    flat_set_add_element(set, &(char *){"adios"});

    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"2"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"hola"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"adios"}));

    flat_set_remove_element(set, &(char *){"1"});
    flat_set_remove_element(set, &(char *){"hola"});

    CU_ASSERT_FALSE(flat_set_contains(set, &(char *){"1"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"2"}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(char *){"hola"}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(char *){"adios"}));

    flat_set_destroy(set);
}

void test_flat_set_repetition(){
    FlatSet set = flat_set_create(INT);
    flat_set_add_element(set, &(int){1});
    flat_set_add_element(set, &(int){2});
    flat_set_add_element(set, &(int){3});
    flat_set_add_element(set, &(int){4});
    flat_set_add_element(set, &(int){1});
    flat_set_add_element(set, &(int){2});
    flat_set_add_element(set, &(int){3});
    flat_set_add_element(set, &(int){4});

    CU_ASSERT_EQUAL(flat_set_cardinality(set), 4);
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){1}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){2}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){3}));
    CU_ASSERT_TRUE(flat_set_contains(set, &(int){4}));

    flat_set_remove_element(set, &(int){1});
    flat_set_remove_element(set, &(int){2});
    flat_set_remove_element(set, &(int){3});
    flat_set_remove_element(set, &(int){4});

    CU_ASSERT_FALSE(flat_set_contains(set, &(int){1}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){2}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){3}));
    CU_ASSERT_FALSE(flat_set_contains(set, &(int){4}));

    flat_set_destroy(set);
}

void test_flat_set_composition(){
    FlatSet set = flat_set_create(SET);
    FlatSet inset1 = flat_set_create(INT);
    FlatSet inset2 = flat_set_create(INT);
    FlatSet inset3 = flat_set_create(INT);
    FlatSet inset4 = flat_set_create(INT);
    FlatSet inset5 = flat_set_create(STRING);
    FlatSet inset6 = flat_set_create(STRING);
    FlatSet inset7 = flat_set_create(STRING);

    flat_set_add_element(inset1, &(int){1});
    flat_set_add_element(inset1, &(int){3});
    flat_set_add_element(inset1, &(int){8});

    flat_set_add_element(inset2, &(int){1});
    flat_set_add_element(inset2, &(int){2});
    flat_set_add_element(inset2, &(int){3});
    flat_set_add_element(inset2, &(int){4});

    flat_set_add_element(inset3, &(int){1});

    flat_set_add_element(inset4, &(int){1});
    flat_set_add_element(inset4, &(int){2});
    flat_set_add_element(inset4, &(int){3});
    flat_set_add_element(inset4, &(int){4});

    flat_set_add_element(inset5, &(char *){"Hello"});

    flat_set_add_element(inset6, &(char *){"Bye"});
    flat_set_add_element(inset6, &(char *){"Hello"});
    flat_set_add_element(inset6, &(char *){"Good morning"});

    flat_set_add_element(inset7, &(char *){"Dinner"});
    flat_set_add_element(inset7, &(char *){"Lunch"});
    flat_set_add_element(inset7, &(char *){"Breakfast"});
    flat_set_add_element(inset7, &(char *){"Dessert"});

    flat_set_add_element(set, inset1);
    flat_set_add_element(set, inset2);
    flat_set_add_element(set, inset3);

    CU_ASSERT_EQUAL(flat_set_cardinality(set), 3);
    CU_ASSERT_TRUE(flat_set_contains(set, inset1));
    CU_ASSERT_TRUE(flat_set_contains(set, inset2));
    CU_ASSERT_TRUE(flat_set_contains(set, inset3));
    CU_ASSERT_TRUE(flat_set_contains(set, inset4));
    CU_ASSERT_FALSE(flat_set_contains(set, inset5));

    flat_set_destroy(set);

    set = flat_set_create(SET);
    flat_set_add_element(set, inset5);
    flat_set_add_element(set, inset6);
    flat_set_add_element(set, inset7);

    CU_ASSERT_EQUAL(flat_set_cardinality(set), 3);
    CU_ASSERT_TRUE(flat_set_contains(set, inset5));
    CU_ASSERT_TRUE(flat_set_contains(set, inset6));
    CU_ASSERT_TRUE(flat_set_contains(set, inset7));
    CU_ASSERT_FALSE(flat_set_contains(set, inset1));

    flat_set_destroy(set);
    flat_set_destroy(inset1);
    flat_set_destroy(inset2);
    flat_set_destroy(inset3);
    flat_set_destroy(inset4);
    flat_set_destroy(inset5);
    flat_set_destroy(inset6);
    flat_set_destroy(inset7);

}

void flat_set_basic_suite() {
    CU_pSuite setBasicSuite = NULL;

    setBasicSuite = CU_add_suite("setBasicTest", NULL, NULL);
    CU_add_test(setBasicSuite, "Set creation", test_flat_set_create);
    CU_add_test(setBasicSuite, "Element addition", test_flat_set_add);
    CU_add_test(setBasicSuite, "Element removal", test_flat_set_remove);
    CU_add_test(setBasicSuite, "Element repetition", test_flat_set_repetition);
    CU_add_test(setBasicSuite, "Set composed", test_flat_set_composition);
}