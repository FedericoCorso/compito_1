#include "catch2/catch2.hpp"
#include "meccanismo_scara.h"

//già definite in meccanismo_scara.h
#include "pistone.h"
#include "fc_scara.h"
#include "svg.h"


#include <cstring>

TEST_CASE("test sulla correttezza dei valori in uscita dal meccanismo", "[meccanismo]") {
    
    Meccanismo* ret = meccanismo_init(50,60,0,50,200,1);

    REQUIRE( ret->pistone->base == 60);
    REQUIRE( ret->pistone->pos.x == 19);
    REQUIRE( ret->pistone->pos.y == 414);

    REQUIRE( ret->scara->length == 50);
    REQUIRE( ret->scara->origin.x == 50);
    REQUIRE( ret->scara->origin.y == 200);
    REQUIRE( ret->scara->q1 == 90);


    meccanismo_del(ret);    
}

TEST_CASE("test altezza manovella e biella negativa, base pistone negativa", "[meccanismo]") {
    
    Meccanismo* ret2 = meccanismo_init(-50,-60,0,50,200,1);
    
    REQUIRE( ret2->pistone == NULL);

    meccanismo_del(ret2);    
}

TEST_CASE("letteura da file", "[meccanismo]") {
    
    std::string s = svg_read("/home/luca/compito_1/build/tests/meccanismo_test.txt");

    Meccanismo* ret3 = meccanismo_new(s.c_str());

    REQUIRE( ret3->pistone->base == 60);
    REQUIRE( ret3->pistone->pos.x == 120);
    REQUIRE( ret3->pistone->pos.y == 415);

    REQUIRE( ret3->scara->length == 50);
    REQUIRE( ret3->scara->origin.x == 150);
    REQUIRE( ret3->scara->origin.y == 200);
    REQUIRE( ret3->scara->q1 == 90);

    meccanismo_del(ret3);    
}
SCENARIO("utente assegna valori negativi o nulli in ingresso","[meccanismo]"){
    GIVEN("un puntatore a struct meccanismo"){
        Meccanismo* mecch;
        WHEN("utente assegna valori nulli"){
            THEN("impone lunghezza manovella nulla"){
                Meccanismo* ret1 = meccanismo_init(0,60,0,50,200,1);
                REQUIRE(ret1->pistone != NULL);
                REQUIRE(ret1->scara == NULL);
                meccanismo_del(ret1);
            }
            THEN("impone base pistone nulla"){
                Meccanismo* ret1 =meccanismo_init(50,0,0,50,200,1);
                REQUIRE(ret1 -> pistone == NULL);
                REQUIRE(ret1 -> scara != NULL);
                meccanismo_del(ret1);
            }
        }
        WHEN("utente assegna valori negativi"){
            THEN("impone lunghezza manovella negativa"){
                Meccanismo* ret1 = meccanismo_init(-20,60,0,50,200,1);
                REQUIRE(ret1->scara == NULL);
                REQUIRE(ret1->pistone != NULL);
                meccanismo_del(ret1);
            }
            THEN("impone base pistone negativa"){
                Meccanismo* ret1 =meccanismo_init(50,-60,0,50,200,1);
                REQUIRE(ret1-> pistone == NULL);
                REQUIRE(ret1 -> scara != NULL);
                meccanismo_del(ret1);
            }
        }
    }
}