#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <flatlib.h>
#include <stdlib.h>

void test_flat_pointer_type(){
    char c = 'a';
    unsigned char uc = 'b';
    short s = 1;
    unsigned short us = 2;
    int i = 3;
    unsigned int ui = 4;
    long l = 5;
    unsigned long ul = 6;
    long long ll = 7;
    unsigned long long ull = 8;
    float f = 9.0;
    double d = 10.0;
    char * str = "Hello";
    FlatSet set = flat_set_create(INT);
    FlatTuple t = flat_tuple_create(FLAT_POINTER_CREATOR(1), FLAT_POINTER_CREATOR(2));
    FlatPointer fpchar = FLAT_POINTER_CREATOR(c);
    FlatPointer fpuchar = FLAT_POINTER_CREATOR(uc);
    FlatPointer fpshort = FLAT_POINTER_CREATOR(s);
    FlatPointer fpushort = FLAT_POINTER_CREATOR(us);
    FlatPointer fpint = FLAT_POINTER_CREATOR(i);
    FlatPointer fpuint = FLAT_POINTER_CREATOR(ui);
    FlatPointer fplong = FLAT_POINTER_CREATOR(l);
    FlatPointer fpulong = FLAT_POINTER_CREATOR(ul);
    FlatPointer fpllong = FLAT_POINTER_CREATOR(ll);
    FlatPointer fpullong = FLAT_POINTER_CREATOR(ull);
    FlatPointer fpfloat = FLAT_POINTER_CREATOR(f);
    FlatPointer fpdouble = FLAT_POINTER_CREATOR(d);
    FlatPointer fpstr = FLAT_POINTER_CREATOR(str);
    FlatPointer fpset = FLAT_POINTER_CREATOR(set);
    FlatPointer fptuple = FLAT_POINTER_CREATOR(t);

    CU_ASSERT_EQUAL(CHAR, flat_pointer_get_type(fpchar));
    CU_ASSERT_EQUAL(UCHAR, flat_pointer_get_type(fpuchar));
    CU_ASSERT_EQUAL(SHORT, flat_pointer_get_type(fpshort));
    CU_ASSERT_EQUAL(USHORT, flat_pointer_get_type(fpushort));
    CU_ASSERT_EQUAL(INT, flat_pointer_get_type(fpint));
    CU_ASSERT_EQUAL(UINT, flat_pointer_get_type(fpuint));
    CU_ASSERT_EQUAL(LONG, flat_pointer_get_type(fplong));
    CU_ASSERT_EQUAL(ULONG, flat_pointer_get_type(fpulong));
    CU_ASSERT_EQUAL(LONG_LONG, flat_pointer_get_type(fpllong));
    CU_ASSERT_EQUAL(ULONG_LONG, flat_pointer_get_type(fpullong));
    CU_ASSERT_EQUAL(FLOAT, flat_pointer_get_type(fpfloat));
    CU_ASSERT_EQUAL(DOUBLE, flat_pointer_get_type(fpdouble));
    CU_ASSERT_EQUAL(STRING, flat_pointer_get_type(fpstr));
    CU_ASSERT_EQUAL(SET, flat_pointer_get_type(fpset));
    CU_ASSERT_EQUAL(TUPLE, flat_pointer_get_type(fptuple));

    flat_set_destroy(set);
    flat_tuple_destroy(t);

    flat_pointer_destroy(fpchar);
    flat_pointer_destroy(fpuchar);
    flat_pointer_destroy(fpshort);
    flat_pointer_destroy(fpushort);
    flat_pointer_destroy(fpint);
    flat_pointer_destroy(fpuint);
    flat_pointer_destroy(fplong);
    flat_pointer_destroy(fpulong);
    flat_pointer_destroy(fpllong);
    flat_pointer_destroy(fpullong);
    flat_pointer_destroy(fpfloat);
    flat_pointer_destroy(fpdouble);
    flat_pointer_destroy(fpstr);
    flat_pointer_destroy(fpset);
    flat_pointer_destroy(fptuple);
}

void test_flat_pointer_value(){
    char c = 'a';
    unsigned char uc = 'b';
    short s = 1;
    unsigned short us = 2;
    int i = 3;
    unsigned int ui = 4;
    long l = 5;
    unsigned long ul = 6;
    long long ll = 7;
    unsigned long long ull = 8;
    float f = 9.0;
    double d = 10.0;
    char * str = "Hello";
    FlatSet set = flat_set_create(INT);
    FlatTuple t = flat_tuple_create(FLAT_POINTER_CREATOR(1), FLAT_POINTER_CREATOR(2));
    FlatPointer fpchar = FLAT_POINTER_CREATOR(c);
    FlatPointer fpuchar = FLAT_POINTER_CREATOR(uc);
    FlatPointer fpshort = FLAT_POINTER_CREATOR(s);
    FlatPointer fpushort = FLAT_POINTER_CREATOR(us);
    FlatPointer fpint = FLAT_POINTER_CREATOR(i);
    FlatPointer fpuint = FLAT_POINTER_CREATOR(ui);
    FlatPointer fplong = FLAT_POINTER_CREATOR(l);
    FlatPointer fpulong = FLAT_POINTER_CREATOR(ul);
    FlatPointer fpllong = FLAT_POINTER_CREATOR(ll);
    FlatPointer fpullong = FLAT_POINTER_CREATOR(ull);
    FlatPointer fpfloat = FLAT_POINTER_CREATOR(f);
    FlatPointer fpdouble = FLAT_POINTER_CREATOR(d);
    FlatPointer fpstr = FLAT_POINTER_CREATOR(str);
    FlatPointer fpset = FLAT_POINTER_CREATOR(set);
    FlatPointer fptuple = FLAT_POINTER_CREATOR(t);

    CU_ASSERT_EQUAL(c, FLAT_POINTER_TO_CHAR(fpchar));
    CU_ASSERT_EQUAL(uc, FLAT_POINTER_TO_UCHAR(fpuchar));
    CU_ASSERT_EQUAL(s, FLAT_POINTER_TO_SHORT(fpshort));
    CU_ASSERT_EQUAL(us, FLAT_POINTER_TO_USHORT(fpushort));
    CU_ASSERT_EQUAL(i, FLAT_POINTER_TO_INT(fpint));
    CU_ASSERT_EQUAL(ui, FLAT_POINTER_TO_UINT(fpuint));
    CU_ASSERT_EQUAL(l, FLAT_POINTER_TO_LONG(fplong));
    CU_ASSERT_EQUAL(ul, FLAT_POINTER_TO_ULONG(fpulong));
    CU_ASSERT_EQUAL(ll, FLAT_POINTER_TO_LONG_LONG(fpllong));
    CU_ASSERT_EQUAL(ull, FLAT_POINTER_TO_ULONG_LONG(fpullong));
    CU_ASSERT_EQUAL(f, FLAT_POINTER_TO_FLOAT(fpfloat));
    CU_ASSERT_EQUAL(d, FLAT_POINTER_TO_DOUBLE(fpdouble));
    CU_ASSERT_STRING_EQUAL(str, FLAT_POINTER_TO_STRING(fpstr));
    CU_ASSERT_TRUE(flat_set_equals(set, FLAT_POINTER_TO_SET(fpset)));
    CU_ASSERT_TRUE(flat_tuple_equals(t, FLAT_POINTER_TO_TUPLE(fptuple)));

    flat_set_destroy(set);
    flat_tuple_destroy(t);

    flat_pointer_destroy(fpchar);
    flat_pointer_destroy(fpuchar);
    flat_pointer_destroy(fpshort);
    flat_pointer_destroy(fpushort);
    flat_pointer_destroy(fpint);
    flat_pointer_destroy(fpuint);
    flat_pointer_destroy(fplong);
    flat_pointer_destroy(fpulong);
    flat_pointer_destroy(fpllong);
    flat_pointer_destroy(fpullong);
    flat_pointer_destroy(fpfloat);
    flat_pointer_destroy(fpdouble);
    flat_pointer_destroy(fpstr);
    flat_pointer_destroy(fpset);
    flat_pointer_destroy(fptuple);
}

void test_flat_pointer_operations(){
    int i = 3;
    char c = 'a';
    char * str = "Hello";
    FlatSet set = flat_set_create(INT);
    flat_set_add_element(set, &(int){1});
    flat_set_add_element(set, &(int){2});
    FlatTuple t = flat_tuple_create(FLAT_POINTER_CREATOR(1), FLAT_POINTER_CREATOR(2));
    FlatPointer fpint = FLAT_POINTER_CREATOR(i);
    FlatPointer fpchar = FLAT_POINTER_CREATOR(c);
    FlatPointer fpstr = FLAT_POINTER_CREATOR(str);
    FlatPointer fpset = FLAT_POINTER_CREATOR(set);
    FlatPointer fptuple = FLAT_POINTER_CREATOR(t);

    char * stri = flat_pointer_to_string(fpint);
    char * strc = flat_pointer_to_string(fpchar);
    char * strs = flat_pointer_to_string(fpstr);
    char * strset = flat_pointer_to_string(fpset);
    char * strtuple = flat_pointer_to_string(fptuple);

    CU_ASSERT_EQUAL(strcmp(stri, "3"), 0);
    CU_ASSERT_EQUAL(strcmp(strc, "a"), 0);
    CU_ASSERT_EQUAL(strcmp(strs, "Hello"), 0);
    CU_ASSERT_EQUAL(strcmp(strset, "{1, 2}"), 0);
    CU_ASSERT_EQUAL(strcmp(strtuple, "(1, 2)"), 0);

    CU_ASSERT_NOT_EQUAL(strcmp(stri, "a"), 0);
    CU_ASSERT_NOT_EQUAL(strcmp(strc, "3"), 0);
    CU_ASSERT_NOT_EQUAL(strcmp(strs, "3"), 0);
    CU_ASSERT_NOT_EQUAL(strcmp(strset, "(1, 2)"), 0);
    CU_ASSERT_NOT_EQUAL(strcmp(strtuple, "{1, 2}"), 0);

    free(stri);
    free(strc);
    free(strs);
    free(strset);
    free(strtuple);

    int i2 = 2;
    char c2 = 'b';
    char * str2 = "World";
    FlatSet set2 = flat_set_create(INT);
    flat_set_add_element(set2, &(int){1});
    flat_set_add_element(set2, &(int){3});
    FlatTuple t2 = flat_tuple_create(FLAT_POINTER_CREATOR(1), FLAT_POINTER_CREATOR(3));
    FlatPointer fpint2 = FLAT_POINTER_CREATOR(i2);
    FlatPointer fpchar2 = FLAT_POINTER_CREATOR(c2);
    FlatPointer fpstr2 = FLAT_POINTER_CREATOR(str2);
    FlatPointer fpset2 = FLAT_POINTER_CREATOR(set2);
    FlatPointer fptuple2 = FLAT_POINTER_CREATOR(t2);

    FlatPointer fpintClone = flat_pointer_clone(fpint);
    FlatPointer fpcharClone = flat_pointer_clone(fpchar);
    FlatPointer fpstrClone = flat_pointer_clone(fpstr);
    FlatPointer fpsetClone = flat_pointer_clone(fpset);
    FlatPointer fptupleClone = flat_pointer_clone(fptuple);

    CU_ASSERT_EQUAL(flat_pointer_equals(fpint, fpchar), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpchar, fpstr), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpstr, fpint), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpset, fptuple), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpset, fpint), 0);

    CU_ASSERT_EQUAL(flat_pointer_equals(fpint, fpintClone), 1);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpchar, fpcharClone), 1);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpstr, fpstrClone), 1);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpset, fpsetClone), 1);
    CU_ASSERT_EQUAL(flat_pointer_equals(fptuple, fptupleClone), 1);

    CU_ASSERT_EQUAL(flat_pointer_equals(fpint, fpint2), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpchar, fpchar2), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpstr, fpstr2), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fpset, fpset2), 0);
    CU_ASSERT_EQUAL(flat_pointer_equals(fptuple, fptuple2), 0);

    CU_ASSERT_EQUAL(flat_pointer_hashcode(fpint), flat_pointer_hashcode(fpintClone));
    CU_ASSERT_EQUAL(flat_pointer_hashcode(fpchar), flat_pointer_hashcode(fpcharClone));
    CU_ASSERT_EQUAL(flat_pointer_hashcode(fpstr), flat_pointer_hashcode(fpstrClone));
    CU_ASSERT_EQUAL(flat_pointer_hashcode(fpset), flat_pointer_hashcode(fpsetClone));
    CU_ASSERT_EQUAL(flat_pointer_hashcode(fptuple), flat_pointer_hashcode(fptupleClone));

    CU_ASSERT_NOT_EQUAL(flat_pointer_hashcode(fpint), flat_pointer_hashcode(fpint2));
    CU_ASSERT_NOT_EQUAL(flat_pointer_hashcode(fpchar), flat_pointer_hashcode(fpchar2));
    CU_ASSERT_NOT_EQUAL(flat_pointer_hashcode(fpstr), flat_pointer_hashcode(fpstr2));
    CU_ASSERT_NOT_EQUAL(flat_pointer_hashcode(fpset), flat_pointer_hashcode(fpset2));
    CU_ASSERT_NOT_EQUAL(flat_pointer_hashcode(fptuple), flat_pointer_hashcode(fptuple2));

    flat_set_destroy(set);
    flat_set_destroy(set2);
    flat_tuple_destroy(t);
    flat_tuple_destroy(t2);

    flat_pointer_destroy(fpint);
    flat_pointer_destroy(fpchar);
    flat_pointer_destroy(fpstr);
    flat_pointer_destroy(fpset);
    flat_pointer_destroy(fptuple);

    flat_pointer_destroy(fpint2);
    flat_pointer_destroy(fpchar2);
    flat_pointer_destroy(fpstr2);
    flat_pointer_destroy(fpset2);
    flat_pointer_destroy(fptuple2);
    
    flat_pointer_destroy(fpintClone);
    flat_pointer_destroy(fpcharClone);
    flat_pointer_destroy(fpstrClone);
    flat_pointer_destroy(fpsetClone);
    flat_pointer_destroy(fptupleClone);
}

void flat_pointer_suite(){
    CU_pSuite suite = CU_add_suite("Types", NULL, NULL);
    CU_add_test(suite, "Flat pointer typation", test_flat_pointer_type);
    CU_add_test(suite, "Flat pointer value", test_flat_pointer_value);
    CU_add_test(suite, "Flat pointer operations", test_flat_pointer_operations);
}