#include "stdafx.h"
#define CATCH_CONFIG_MAIN
#include "include/catch.hpp"
#include <string>
#include "../Counter.h"

using namespace std;

TEST_CASE("Test 1") {
	string text="ahoj";
	string text1="dobry den";
	string text2 = " ";
	REQUIRE( spocitaj<_char>(text1) == 8, spocitaj<_char>(text2)==0);

}
TEST_CASE("Test 2")
{
	string text = "ahoj";
	string text1 = "dobry den";
	string text2 = " ";
	REQUIRE(spocitaj<_word>(text) == 1, spocitaj<_word>(text1)==2, spocitaj<_word>(text2) == 0);
}
TEST_CASE("Test 3")
{
	string text = "ahoj";
	string text1 = "dobry\nden\nprajem";
	REQUIRE(spocitaj<_line>(text) == 1, spocitaj<_line>(text1)==3);
}



