#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <flatPointer.h>
#include <set.h>

void testTypeEvaluate() {
    Set x = setCreate(INT);
    setAdd(x, &(int){1});
    setAdd(x, &(int){2});
    setAdd(x, &(int){3});
    flat_pointer fp = NEW_FLAT_POINTER(x);
    printf("%s\n", setToString(FLAT_POINTER_TO_SET(fp)));
    
    flat_free(fp);
    
}

void typeSuite() {
    CU_pSuite suite = CU_add_suite("Types", NULL, NULL);
    CU_add_test(suite, "Type Evaluation", testTypeEvaluate);
}

void add_all_tests() {
    typeSuite();
}

int main() {
    
    CU_initialize_registry();
    CU_basic_set_mode(CU_BRM_VERBOSE);
    add_all_tests();
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}