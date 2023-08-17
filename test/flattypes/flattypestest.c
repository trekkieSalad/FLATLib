#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <flatlib.h>

void test_flat_type_evaluate() {
    FlatSet x = flat_set_create(INT);
    flat_set_add_element(x, &(int){1});
    flat_set_add_element(x, &(int){2});
    flat_set_add_element(x, &(int){3});
    flat_pointer fp = FLAT_POINTER_CREATOR(x);
    flat_pointer fp2 = FLAT_POINTER_CREATOR(5);
    printf("%s\n", flat_pointer_to_string(fp));
    printf("%s\n", flat_pointer_to_string(fp2));

    flat_free(fp);
    flat_free(fp2);
}

void flat_type_suite() {
    CU_pSuite suite = CU_add_suite("Types", NULL, NULL);
    CU_add_test(suite, "Type Evaluation", test_flat_type_evaluate);
}

void add_all_tests() {
    flat_type_suite();
}

int main() {
    
    int x= CU_initialize_registry();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    add_all_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}