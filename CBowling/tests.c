#include "CppUTest/TestHarness.h"
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTestExt/MockSupport.h>

#define IN_TEST
extern "C"
{
#include "bowling.c"
}

struct bowling_score *bs = compteur_bowling();

TEST_GROUP(Bowling)
{
    void setup()
    {
        initialise(bs);
    }

    void teardown()
    {
    }
};

TEST(Bowling, initialement_score_egal_zero) 
{
    LONGS_EQUAL(0, calcule_score(bs));
}
TEST(Bowling, apres_un_tir_score_egal_ce_tir)
{
    enregistre_tir(bs,7);
    LONGS_EQUAL(7, calcule_score(bs));
}
TEST(Bowling, apres_deux_tirs_score_egal_somme_des_tirs)
{
    enregistre_tir(bs,3);
    enregistre_tir(bs,2);

    LONGS_EQUAL(5, calcule_score(bs));
}
TEST(Bowling, apres_un_spare_compte_un_tir_de_bonus)
{
    enregistre_tir(bs,3);
    enregistre_tir(bs,7); // spare!!
    enregistre_tir(bs,5); // compte double

    LONGS_EQUAL(20, calcule_score(bs));
}

TEST(Bowling, un_spare_ne_compte_que_sur_un_tour)
{
    enregistre_tir(bs,0);
    enregistre_tir(bs,6); 

    enregistre_tir(bs,4);  // pas un spare !
    enregistre_tir(bs,2);

    LONGS_EQUAL(12, calcule_score(bs));
}

TEST(Bowling, un_strike_compte_deux_de_bonus)
{
    enregistre_tir(bs,10); // strike !

    enregistre_tir(bs,3); 
    enregistre_tir(bs,3); 

    LONGS_EQUAL(22, calcule_score(bs));
}
TEST(Bowling, plusieurs_strikes_accumulent_les_bonnus)
{
    enregistre_tir(bs,10); // strike !
    enregistre_tir(bs,10); // strike !
    enregistre_tir(bs,10); // strike !

    enregistre_tir(bs,3); 
    enregistre_tir(bs,3); 

//    10 10 10 3 3  36
//       10 10      20
//          10 3    13
//             3 3   6
//                  75

    LONGS_EQUAL(75, calcule_score(bs));
}

TEST(Bowling, apres_10_tour_ne_plus_creer_de_bonus) 
{
    for(int i=0; i<12; i++) {
        enregistre_tir(bs, 10);
    }
    LONGS_EQUAL(300, calcule_score(bs));
}

int main(int ac, char** av)
{
  return CommandLineTestRunner::RunAllTests(ac, av);
}
