#include "CppUTest/TestHarness.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>
#define IN_TEST 
extern "C"
{
#include "rent.c"
}

TEST_GROUP(MyCode)
{
    void setup()
    {
        memset(Orders, 0, sizeof(Orders));
    }

    void teardown()
    {
    }
};


TEST(MyCode, given_one_order_result_is_order_revenue)
{

    int nb_orders = 1;
    init_order(0,"ORDERONE",0,5,100);
    LONGS_EQUAL(100, process_orders(nb_orders));
}

TEST(MyCode, given_two_competing_orders_result_is_best) 
{

    int nb_orders = 2;
    init_order(0,"ORDERONE",0,5,100);
    init_order(1,"ORDERTWO",0,5,140);
    LONGS_EQUAL(140, process_orders(nb_orders));
}
TEST(MyCode, given_two_competing_orders_with_first_best_result_is_best) 
{

    int nb_orders = 2;
    init_order(0,"ORDERONE",0,5,140);
    init_order(1,"ORDERTWO",0,5,100);
    LONGS_EQUAL(140, process_orders(nb_orders));
    STRCMP_EQUAL("ORDERTWO",Orders[0].trade_id);
    STRCMP_EQUAL("ORDERONE",Orders[1].trade_id);
}

TEST(MyCode, given_two_compatible_orders_result_is_sum) 
{
    int nb_orders = 2;
    init_order(0,"ORDERONE",0,5,100);
    init_order(1,"ORDERTWO",5,9,140);
    LONGS_EQUAL(240, process_orders(nb_orders));
}
TEST(MyCode, given_several_compatible_and_competing_orders_result_is_best_revenue) 
{
    int nb_orders = 4;

    init_order(0,"ORDERONE",0,5,100);
    init_order(1,"ORDERTWO",3,10,140);
    init_order(2,"ORDERNO3",5,9,70);
    init_order(3,"ORDERNO4",6,9,80);
    LONGS_EQUAL(180, process_orders(nb_orders));
}
int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
