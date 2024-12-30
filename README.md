# 1473 Kelvin

Self-modifying esolang.

c++11 should work

| Instruction | Description |
| --- | --- |
| 1 | Modify `main` pointer by `helper` pointer |
| 2 | Move `main` pointer by `helper` pointer's value |
| 3 | Swap `main` and `helper` pointers (value) |
| 4 | Move `helper` pointer by `main` pointer's value |
| 5 | Move `helper` pointer by negative `main` pointer |
| 6 | Set `helper` pointer to program counter |
| 7 | Set program counter to `helper` pointer |
| 8 | Jump to next line if `helper` pointer is greater than `main` pointer, otherwise jump to start without resetting anything |
| 9 | Jump to next line if `main` pointer is greater than `helper` pointer, otherwise jump to start without resetting anything |
| A | Jump to next line if `main` pointer is greater than hold value, otherwise jump to start without resetting anything |
| B | Jump to next line if `main` pointer is less than hold value, otherwise jump to start without resetting anything |
| C | Set the hold value to `main` pointer |
| D | Set the `main` pointer to the hold value |
| E | Request input and set `main` pointer to it |
| F | Output `main` pointer value |
| G | Swap `main` and `helper` pointers (position) |

Usage : `ofstk -f <filename>`
