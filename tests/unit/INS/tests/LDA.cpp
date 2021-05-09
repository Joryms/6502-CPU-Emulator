#include "catch2/catch.hpp"
#include "../constants.hpp"

// Immediate Test Case Zero Value

// LDA Test Case

namespace LDA {

    void testOne(Mem& mem, CPU& cpu) {

        for (int value = 0x00; value <= 0xFF; value++) {
            
            // Reset CPU

            cpu.Reset( mem );

            // Add script

            mem[cpu.PC] = value;
            
            // Run instruction for value at PC

            cpu.LDA( mem, cpu.PC );
        
            // Assertions
        
            REQUIRE( cpu.A == value ); // Ensure values match up

            if ( value >= 0x80 ) {
                REQUIRE( cpu.N == 1 );
            }
            else {
                REQUIRE( cpu.N == 0 );
            }

            if ( value == 0x00 ) {
                REQUIRE( cpu.Z == 1 );
            }
            else {
                REQUIRE( cpu.Z == 0 );
            } 
        }
    }

    TEST_CASE( "LDA Instruction" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[8] = { 0xA9, 0xA5, 0xB5, 0xAD, 0xBD, 0xB9, 0xA1, 0xB1 };

        // Vars for script

        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );

            // Get value at index

            Byte ins = OPCodes[i];

            // Add script

            mem[cpu.PC] = value;
            
            // Run script

            cpu.Run( mem, ins, cpu.PC );
        
            // Assertions
        
            REQUIRE( cpu.A == value ); // Ensure values match up
        }
    }

    TEST_CASE( "LDA Instruction OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}