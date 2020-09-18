#include "unity.h"
#include "salloc.h"
#include "complementary_filter.h"
complementary_filter test_complementary_filter;
float test_alpha_gain=0.5;
float test_beta_gain=0.7;
void setUp(void)
{
    test_complementary_filter= complementary_filter_ctor();
}

void tearDown(void)
{
    test_complementary_filter=NULL;
}
void test_complementary_filter_set_gain_if_sum_of_gains_exceeds_1_then_second_gain_is_recalculated(void)
{
   complementary_filter_set_alpha_gain(test_complementary_filter,test_alpha_gain);
    complementary_filter_set_alpha_gain(test_complementary_filter,test_beta_gain);
    float sum=complementary_filter_get_alpha_gain(test_complementary_filter)+complementary_filter_get_beta_gain(test_complementary_filter);
    TEST_ASSERT_EQUAL_FLOAT(1,sum);
}
void test_complementary_filter_set_alpha_gain_if_alpha_gain_exceeds_1_then_set_gain_to_1(void)
{
    complementary_filter_set_alpha_gain(test_complementary_filter,1.2);
    TEST_ASSERT_TRUE((complementary_filter_get_alpha_gain(test_complementary_filter))<=1);
}
void test_complementary_filter_set_beta_gain_if_beta_gain_exceeds_1_then_set_gain_to_1(void)
{
    complementary_filter_set_beta_gain(test_complementary_filter,1.2);
    TEST_ASSERT_TRUE((complementary_filter_get_beta_gain(test_complementary_filter))<=1);
}
void test_comlementary_filter_set_apha_gain_if_gain_is_negative_then_multiply_by_minus_1(void)
{
    complementary_filter_set_alpha_gain(test_complementary_filter,-1);
    TEST_ASSERT_TRUE((complementary_filter_get_alpha_gain(test_complementary_filter))>=0);
}
void test_complementary_filter_calculate_output(void)
{
    float test_output=2.9;
    complementary_filter_set_alpha_gain(test_complementary_filter,0.1f);
    float output= complementary_filter_calculate_output(test_complementary_filter,2,3);
    TEST_ASSERT_EQUAL_FLOAT(test_output,output);
}