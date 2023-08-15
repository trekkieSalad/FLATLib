#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void flat_set_basic_suite();
void flat_set_eval_suite();
void flat_set_operation_test();

void add_all_tests() {
    flat_set_basic_suite();
    flat_set_eval_suite();
    flat_set_operation_test();
}

int main() {
    
    CU_initialize_registry();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    add_all_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}