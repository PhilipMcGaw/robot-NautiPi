#include <unity.h>

void test_basic() {
    TEST_ASSERT_EQUAL(1, 1);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_basic);
    UNITY_END();
}
