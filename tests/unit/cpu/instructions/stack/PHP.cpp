#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PHP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Bit N;
    Bit V;
    Bit B;
    Bit D;
    Bit I;
    Bit Z;
    Bit C;

    Byte received;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x08
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PHP);
        }
    };

    SECTION("executes properly on random P value") {
        
        N = random<Bit>();
        V = random<Bit>();
        B = random<Bit>();
        D = random<Bit>();
        I = random<Bit>();
        Z = random<Bit>();
        C = random<Bit>();

        cpu.N = N;
        cpu.V = V;
        cpu.B = B;
        cpu.D = D;
        cpu.I = I;
        cpu.Z = Z;
        cpu.C = C;
        
        cpu.Execute(PHP, 0);

        received = mem[0x0100];

        REQUIRE(cpu.S == 0x01);

        REQUIRE((received & 0b10000000) >> 7 == N);
        REQUIRE((received & 0b01000000) >> 6 == V);
        REQUIRE((received & 0b00010000) >> 4 == B);
        REQUIRE((received & 0b00001000) >> 3 == D);
        REQUIRE((received & 0b00000100) >> 2 == I);
        REQUIRE((received & 0b00000010) >> 1 == Z);
        REQUIRE((received & 0b00000001) == C);
    };
}