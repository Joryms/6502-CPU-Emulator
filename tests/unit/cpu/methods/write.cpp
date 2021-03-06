#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Write Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word address;

    Byte byteValue;
    Word wordValue;

    SECTION("at random address with one byte") {
        address = random<Word>(0x5000, 0x7FFF);
        byteValue = random<Byte>();

        cpu.Write<Byte>(address, byteValue);

        REQUIRE(mem[address] == byteValue);
    };

    SECTION("at random address with two bytes") {
        address = random<Word>(0x5000, 0x7FFF);
        wordValue = random<Word>();

        cpu.Write<Word>(address, wordValue);

        REQUIRE(mem[address] == (Byte) (wordValue >> 8));
        REQUIRE(mem[address + 1] == (Byte) wordValue);
    };
}