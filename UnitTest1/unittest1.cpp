#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include <string>
#include "C:/Users/Michal/Source/Repos/console-app/Counter.h"

using namespace std;

TEST_CASE("Test 1") {
	string text="ahoj";
	string text1="dobry den";
	string text2 = " ";
	REQUIRE(counterznak(text) == 4, counterword(text1) == 9, counterznak(text2)==0);

}
TEST_CASE("Test 2")
{
	string text = "ahoj";
	string text1 = "dobry den";
	string text2 = " ";
	REQUIRE(counterword(text) == 1,counterword(text1)==2, counterword(text2) == 0);
}
TEST_CASE("Test 3")
{
	string text = "ahoj";
	string text1 = "dobry\nden\nprajem";
	REQUIRE(counterword(text) == 1, counterword(text1)==3);
}



