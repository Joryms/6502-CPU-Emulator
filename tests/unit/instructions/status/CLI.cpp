#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CLI instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte I;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x58
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CLI);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        I = 0;
        cpu.I = I;

        cpu.Execute(CLI, 0x00);

        REQUIRE(cpu.I == 0);
    };

    SECTION("executes correctly on set flag") {
        
        I = 1;
        cpu.I = I;

        cpu.Execute(CLI, 0x00);

        REQUIRE(cpu.I == 0);
    };
}