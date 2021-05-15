// ========== Types ==========

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

// Codes

#define AB 0x00
#define ABX 0x01
#define ABY 0x02
#define AC 0x03
#define ID 0x04
#define IDX 0x05
#define IDY 0x06
#define IMM 0x07
#define REL 0x08
#define ZP 0x09
#define ZPX 0x0A
#define ZPY 0x0B

// Instructions

#define LDA 0x00
#define LDX 0x01
#define LDY 0x02
#define PHA 0x03
#define PHP 0x04
#define PLA 0x05
#define PLP 0x06
#define STA 0x07
#define STX 0x08
#define STY 0x09
#define TAX 0x0A
#define TAY 0x0B
#define TSX 0x0C
#define TXA 0x0D
#define TXS 0x0E
#define TYA 0x0F