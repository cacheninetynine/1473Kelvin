/*
 Copyright 2024 cachewave

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include <iostream>
#include <algorithm>
#include <fstream>

unsigned char tape[512000] = {0};
unsigned char* ptr = tape;
unsigned char* ptr2 = tape;
unsigned char hold = 255;

/*
 Hold is set to 255
 others set to 0

 1 - Modify main pointer by helper pointer
 2 - Move main pointer by helper pointer

 3 - Swaps main pointer and helper pointer (value)

 4 - Set helper pointer's position to main pointer
 5 - Move helper pointer by negative main pointer

 6 - Set helper pointer to program counter
 7 - Set program counter to helper pointer

 8 - Jump to next line if helper pointer bigger than main pointer, otherwise jump to start without resetting anything
 9 - Jump to next line if main pointer bigger than helper pointer, otherwise jump to start without resetting anything

 A - Jump to next line if main pointer bigger than the hold value, otherwise jump to start without resetting anything
 B - Jump to next line if main pointer smaller than the hold value, otherwise jump to start without resetting anything

 C - Sets the hold value to main pointer
 D - Sets the main pointer to the hold value

 E - Request user input and set main pointer to it

 F - Output main pointer value
*/

// https://stackoverflow.com/a/868894   thanks
char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

void kelvin(char* input)
{

    std::ifstream file(input);
    if (!file.good())
    {
        std::cout << "Not good!" << std::endl;
        return;
    }

    char code[32000];
    file.get(code,32000);

    char command;
    unsigned int pc;

    for (pc = 0; code[pc] != 0; ++pc)
    {
        command = code[pc];

        switch (command)
        {
            case '1':
            {
                *ptr += *ptr2;
                break;
            }
            case '2':
            {
                ptr += *ptr2;
                break;
            }
            case '3':
            {
                unsigned char tmp = *ptr;
                *ptr = *ptr2;
                *ptr2 = tmp;
                break;
            }
            case '4':
            {
                ptr2 = ptr;
                break;
            }
            case '5':
            {
                ptr2 -= *ptr;
                break;
            }
            case '6':
            {
                *ptr2 = pc;
                break;
            }
            case '7':
            {
                pc = *ptr2;
                break;
            }
            case '8':
            {
                if (!(*ptr2 >= *ptr)) {
                    pc = 0;
                }
                break;
            }
            case '9':
            {
                if (!(*ptr >= *ptr2)) {
                    pc = 0;
                }
                break;
            }
            case 'A': // 10
            {
                if (!(*ptr >= hold)) {
                    pc = 0;
                }
                break;
            }
            case 'B': // 11
            {
                if (!(*ptr < hold)) {
                    pc = 0;
                }
                break;
            }
            case 'C': // 12
            {
                hold = *ptr;
                break;
            }
            case 'D': // 13
            {
                *ptr = hold;
                break;
            }
            case 'E': // 14
            {
                *ptr = getchar();
                break;
            }
            case 'F': // 15
            {
                putchar(*ptr);
                break;
            }
        }
    }
}

int main(int argc, char **argv)
{
    char * filename = getCmdOption(argv, argv + argc, "-f");
    if (!filename)
    {
        std::cout << "Usage: ofstk -f <filename>" << std::endl;
        return 1;
    }
    kelvin(filename);
    putchar('\n');
    return 0;
}
