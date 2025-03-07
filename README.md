# 6502 Emulator
Instructions
|   | z | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |
|---|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| z |   |   |   |   |   |   |   |   |   |   |LDY i|   |   |   |   |   |
| 1 |   |   |AND ix|AND iy|EOR ix|EOR iy|   |   |STA ix|STA iy|LDA ix|LDA iy|   |   |   |   |
| 2 |   |   |   |   |   |   |   |   |   |   |LDX i|   |   |   |   |   |
| 3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 4 |   |   |   |   |   |   |   |   |STY z|STY zx|LDY z|LDY zx|   |   |   |   |
| 5 |   |   |AND z|AND zx|EOR z|EOR zx|   |   |STA z|STA zx|LDA z|LDA zx|   |   |   |   |
| 6 |   |   |   |   |   |   |   |   |STX z|STX zy|LDX z|LDX zy|   |   |   |   |
| 7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 8 |PHP I|   |PLP I|   |PHA I|   |PLA I|   |   |TYA I|TAY I|   |   |   |   |   |
| 9 |   |   |AND i|AND ay|EOR i|EOR ay|   |   |   |STA ay|LDA i|LDA ay|   |   |   |   |
| A |   |   |   |   |   |   |   |   |TXA I|TXS I|TAX I|TSX I|   |   |   |   |
| B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| C |   |   |   |   |   |   |   |   |STY a|   |LDY a|LDY ax|   |   |   |   |
| D |   |   |AND a|AND ax|EOR a|EOR ax|   |   |STA a|STA ax|LDA a|LDA ax|   |   |   |   |
| E |   |   |   |   |   |   |   |   |STX a|   |LDX a|LDX ay|   |   |   |   |
| F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
<br>
# Addressing Modes:
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