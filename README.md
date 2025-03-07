# 6502 Emulator
Instructions
|   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
|---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 0 |   |   |   |   |   |   |   |   |   |   |LDY i|   |   |   |   |   |
| 1 |ORA ix|ORA iy|AND ix|AND iy|EOR ix|EOR iy|   |   |STA ix|STA iy|LDA ix|LDA iy|   |   |   |   |
| 2 |   |   |   |   |   |   |   |   |   |   |LDX i|   |   |   |   |   |
| 3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 4 |   |   |   |   |   |   |   |   |STY z|STY zx|LDY z|LDY zx|   |   |   |   |
| 5 |ORA z|ORA zx|AND z|AND zx|EOR z|EOR zx|   |   |STA z|STA zx|LDA z|LDA zx|   |   |   |   |
| 6 |   |   |   |   |   |   |   |   |STX z|STX zy|LDX z|LDX zy|   |   |   |   |
| 7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 8 |PHP I|   |PLP I|   |PHA I|   |PLA I|   |   |TYA I|TAY I|   |   |   |   |   |
| 9 |ORA i|ORA ay|AND i|AND ay|EOR i|EOR ay|   |   |   |STA ay|LDA i|LDA ay|   |   |   |   |
| A |   |   |   |   |   |   |   |   |TXA I|TXS I|TAX I|TSX I|   |   |   |   |
| B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| C |   |   |   |   |   |   |   |   |STY a|   |LDY a|LDY ax|   |   |   |   |
| D |ORA a|ORA ax|AND a|AND ax|EOR a|EOR ax|   |   |STA a|STA ax|LDA a|LDA ax|   |   |   |   |
| E |   |   |   |   |   |   |   |   |STX a|   |LDX a|LDX ay|   |   |   |   |
| F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
<br>

# Addressing Modes:<br>

i - immediate<br>
z - zero page<br>
zx - zero page X<br>
zy - zero page Y<br>
a - absolute<br>
ax - absolute X<br>
ay - absolute Y<br>
ix - indirect X<br>
iy - indirect Y<br>
I - implicit<br>