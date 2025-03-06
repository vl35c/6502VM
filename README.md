# 6502 Emulator

Instructions
|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
|---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0 |   |   |   |   |   |   |   |   |   |   |LDY i|   |   |   |   |   |
| 1 |   |   |AND ix|AND iy|   |   |   |   |STA ix|STA iy|LDA ix|LDA iy|   |   |   |   |
| 2 |   |   |   |   |   |   |   |   |   |   |LDX i|   |   |   |   |   |
| 3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 4 |   |   |   |   |   |   |   |   |STY 0|STY 0x|LDY 0|LDY 0x|   |   |   |   |
| 5 |   |   |AND 0|AND 0x|   |   |   |   |STA 0|STA 0x|LDA 0|LDA 0x|   |   |   |   |
| 6 |   |   |   |   |   |   |   |   |STX 0|STX 0y|LDX 0|LDX 0y|   |   |   |   |
| 7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 8 |PHP I|   |PLP I|   |PHA I|   |PLA I|   |   |TYA I|TAY I|   |   |   |   |   |
| 9 |   |   |AND i|AND ay|   |   |   |   |   |STA ay|LDA i|LDA ay|   |   |   |   |
| A |   |   |   |   |   |   |   |   |TXA I|TXS I|TAX I|TSX I|   |   |   |   |
| B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| C |   |   |   |   |   |   |   |   |STY a|   |LDY a|LDY ax|   |   |   |   |
| D |   |   |AND a|AND ax|   |   |   |   |STA a|STA ax|LDA a|LDA ax|   |   |   |   |
| E |   |   |   |   |   |   |   |   |STX a|   |LDX a|LDX ay|   |   |   |   |
| F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |