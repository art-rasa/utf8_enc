/* This driver program encodes Unicode code points into UTF-8 encoded 
 * bytes, displays the resulting characters and prints their byte/bit 
 * patterns. 
 */

#include <stdio.h>
#include <stdbool.h>
#include "utf8.h"

int main(int argc, char * argv[]) 
{
    unsigned int code = 0;
    unsigned char utf8[5];
    int nbyte = 0;
    
    puts("UTF-8 encoder");
    puts("-------------");
    printf("This program encodes Unicode code points using UTF-8 ");
    printf("variable-width encoding.");
    puts("");
    printf("Enter Unicode code points as positive numbers. ");
    printf("Several code points can be entered at once, separated by ");
    printf("spaces. Enter 0 to exit.");
    puts("");
    
    while (true)
    {
        printf("> ");
        
        if ((scanf("%u", &code) < 1) || (code == 0)) 
        {
            break;
        }
        
        utf8_encode(code, utf8);
        
        printf("code: %u\tchar: \"%s\"\tbytes: ", code, utf8);
        for (nbyte = 0; nbyte < 5; nbyte++) 
        {
            if (utf8[nbyte] > '\0')
            {
                print_bits((unsigned int)utf8[nbyte], 8);
            }
        }
        puts("");
    }
    
    return 0;
}













