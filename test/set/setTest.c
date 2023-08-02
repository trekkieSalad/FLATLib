#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void setBasicSuite();
void setOpSuite();

void add_all_tests() {
    setBasicSuite();
    setOpSuite();
}

/*int main() {
    CU_initialize_registry();
    add_all_tests();
    CU_pSuite basicSuite = CU_get_suite("Basic Set Test Suite");
    CU_pSuite opSuite = CU_get_suite("Operation Set Test Suite");
    CU_run_suite(basicSuite);
    CU_run_suite(opSuite);
    CU_cleanup_registry();
    return CU_get_error();
}*/


int main() {
    
    CU_initialize_registry();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    add_all_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}