#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void flat_pointer_suite();

void add_all_tests() {
    flat_pointer_suite();
}

int main() {
    
    CU_initialize_registry();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    add_all_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}