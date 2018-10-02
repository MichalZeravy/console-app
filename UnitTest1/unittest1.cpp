#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include <string>
#include "C:/Users/Michal/Source/Repos/console-app/Counter.h"

using namespace std;

TEST_CASE("Test 1") {
	string text="ahoj";
	string text1 = "dobry den";
	REQUIRE(counterznak(text)==4, counterword(text1)==9);

}
TEST_CASE("Test 2")
{
	string text = "ahoj";
	string text1 = "dobry den prajem";
	REQUIRE(counterword(text) == 1,counterword(text1)==3);
}
TEST_CASE("Test 3")
{
	string text = "ahoj";
	string text1 = "dobry \n den prajem";
	REQUIRE(counterword(text) == 3, counterword(text1));
}



