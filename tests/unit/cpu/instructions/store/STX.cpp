#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word address;
    Bit X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0x86, 0x96, 0x8E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == STX);
        }
    };

    SECTION("executes properly on random value") {

        address = random<Word>(0x5000, 0x7FFF);
        X = random<Byte>();
        cpu.X = X;

        cpu.Execute(STX, address);

        REQUIRE(cpu.Read<Byte>(address) == X);
    };
}