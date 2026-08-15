#include <stdio.h>
#include <string.h>

//strlen() function
int my_strlen(char s[])  //hello ; "hello" is stored in a read-only memory block as: 'h','e','l','l','o','\0'
{
    int i = 0;

    while (s[i] != '\0') //'\0' (null terminator)
        i++;

/* * ++i vs i++
 * - i++ (Post): "Use the value, THEN increment."
 * - ++i (Pre):  "Increment, THEN use the value."
 * * IN A LOOP:
 * If they are on a line by themselves (like i++;), they do the same thing.
 * * ANALOGY:
 * - i++: Buy the toy now, pay later.
 * - ++i: Pay for the toy now, get it later.
 */

    return i;
}

int main() {
 
/* ---------------------------------------------------------------
 * DATA TYPE SIZES AND RANGES (Common 64-bit Systems)
 * ---------------------------------------------------------------
 * TYPE           SIZE (Bytes)   FORMAT   RANGE
 * char           1 byte         %d/%c    -128 to 127
 * unsigned char  1 byte         %u       0 to 255
 * short          2 bytes        %hd      -32,768 to 32,767
 * int            4 bytes        %d       -2,147,483,648 to 2,147,483,647
 * unsigned int   4 bytes        %u       0 to 4,294,967,295 (u)
 * long           8 bytes        %ld      -9e18 to 9e18
 * unsigned long  8 bytes        %lu      0 to 1.8e19 (ul)
 * float          4 bytes        %f       ~7 decimal digits
 * double         8 bytes        %f/%lf   ~15 decimal digits
 * ---------------------------------------------------------------
 *
 * * 1 BYTE vs 4 BYTES:
 * - 1 Byte (char): 8 bits. Good for letters and tiny numbers (-128 to 127).
 * - 4 Bytes (int): 32 bits. Standard for most math (-2.1B to 2.1B).
 * * Analogy: A cup (1 byte) vs. A gallon jug (4 bytes).
 * * If you pour a gallon into a cup, it spills (OVERFLOW).
 */

    printf("\n------Integer------\n\n");	
    printf("Size of 1234: %zu bytes\n", sizeof(1234));

/* sizeof() - THE "MEASURING TAPE" OPERATOR
 * 1. TYPE: It is an OPERATOR, not a function (calculated at compile-time).
 * 2. PURPOSE: Returns the size of a type or variable in BYTES.
 * 3. FORMAT: Use %zu in printf to display the result.
 * 4. WHY USE IT? To write "portable" code that works on both 32-bit and 64-bit systems where 'int' sizes might differ.
 */

    printf("Size of 1234L: %zu bytes\n", sizeof(1234L));   // l/L     
    printf("Size of 1234U: %zu bytes\n", sizeof(1234U));   // u/U   
    printf("Size of 1234UL: %zu bytes\n", sizeof(1234UL)); // ul/UL
    
    printf("\n------Double & Float------\n\n");
    printf("723.5 = %f\n", 723.5);
    printf("1e-2 = %f\n", 1e-2);   // 1e-2 means 1 / 10^2
    printf("Size of 854.1 = %zu bytes\n", sizeof(854.1));  //If there is no suffix like f or F, its data type is double.
    printf("Size of 1-e2 = %zu bytes\n", sizeof(1e-2));
    printf("Size of 854.1f = %zu bytes\n", sizeof(854.1f));
    printf("Size of 854.1F = %zu bytes\n", sizeof(854.1F));

    printf("\n------Octal & Hexadecimal------\n\n");
    printf("Decimal 44 = %d\n", 44);
    printf("Octal 044 = %d\n", 044);    //octal = 0
    printf("Hexa 0x2F = %d\n", 0x2F);   //hexadecimal = 0x
    printf("Hexa 0x1f = %d\n", 0x1f);
    printf("0XFUL = %lu\n", 0XFUL);
    printf("0xD = %d\n", 0xD);

    printf("\n------Character------\n\n");
    printf("'x' = %d\n", 'x');
    printf("'0' = %d\n", '0');
    printf("0 = %d\n", 0);
    printf("'\\0' = %d\n", '\0');
    printf("'a' + 1 = %c\n", 'a' + 1);
    printf("'Z' - 'A' = %d\n", 'Z' - 'A');

    printf("\n------Escape Sequence------\n\n");

    */* \a   alert (bell) character     ||   \\   backslash
      * \b   backspace                  ||   \?   question mark
      * \f   formfeed                   ||   \'   single quote
      * \n   newline                    ||   \"   double quote
      * \r   carriage return            ||   \ooo octal number
      * \t   horizontal tab             ||   \xhh hexadecimal number
      * \v   vertical tab
    */

    #define BAB '\044'   // BAB represents the '$' character ; A backslash followed immediately by numbers (without an 'x') means Octal (Base-8)
    #define LLA '\055'
    printf("BAB value: %d\n", BAB);
    printf("LLA value: %d\n", LLA);    //octal = \0 ... (0 - 7)
    printf("'\\xb' = %d\n", '\xb');    //hexadecimal = \x...(0 - 9, a/A, b/B, c/C, d/D, e/E, f/F)
    printf("'\\x7' = %d\n", '\x7');
    
    printf("\n------Constants Expression------\n\n");
    #define MAXLINE 1000
    char line [MAXLINE+1];

    #define LEAP 1
    int days = 31 + 28 + LEAP + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31;

    printf("Array size = %ld\n", sizeof(line));
    printf("Total days in a leap year = %d\n", days);

    printf("\n------String Constants------\n\n");	       
    char *s1 = "Hello World";
    char *s2 = "";
    char *s3 = "He said, \"Hello!\"";
    printf("%s\n", s1);
    printf("'%s'\n", s2);
    printf("%s\n", s3);

/* * EXPLAINING: char *str = "hello";
 
 * * 1. HOW IT WORKS: 
 *      - "hello" is stored in a read-only memory block as: 'h','e','l','l','o','\0'
 *      - 'str' is a POINTER that stores the memory address of the first letter ('h').
 *      - The '\0' (null terminator) tells functions like printf where the string ends.
 * * 2. THE BENEFIT:
 *      - Efficiency: We only move a tiny memory address around, not the whole word.
 * * 3. FLEXIBILITY BENEFIT:
        * Because 'str' is just an address, I can change it!
        * str++ makes the pointer jump to the next letter.
        * I can process "hello" starting from any letter 
        * WITHOUT making a copy of the word in memory.
 */

    printf("\n------String Concatenation------\n\n");
    //These are same btw
    char *ss1 = "hello, " "world";
    char *ss2 = "hello, world";

    printf("s1: %s\n", ss1);
    printf("s2: %s\n", ss2);
    printf("Are they equal? = %s\n", strcmp(ss1, ss2) == 0? "YES" : "NO");

/* * EXPLAINING: strcmp(s1, s2) == 0 ? "YES" : "NO"
 
 * 1. strcmp(s1, s2): Compares letters. Returns 0 ONLY if they match perfectly.
 * 2. == 0: We check if the result is 0 (meaning 'Equal').
 * 3. The '?' Trick: This is a Ternary Operator. 
 * - If the result is True (0 == 0), it picks "YES".
     * WHY == 0?
     * strcmp doesn't return "True/False". It returns the DIFFERENCE.
     * - If Difference is 0: The strings match perfectly.
     * - If Difference is not 0: The strings are different.
     * This is why we check '== 0' to confirm they are equal
     * - If the result is False, it picks "NO".
 * * BENEFIT: It turns a boring computer number (0) into a human word ("YES").
 
 */
    
    char *long_str = "This is a very long string that " "spans multiple lines in the source code" "but is actually one continuous string.";
    printf("\n%s\n", long_str);

/*
### **Internal Representation of Strings**

**Key Facts:**
1. A string is technically an **array of characters**
2. Every string has a null character `'\0'` at the end
3. Physical storage = number of characters + 1 (for `'\0'`)
4. No inherent limit to string length
5. Programs must scan to find the length

**Memory Layout:**
```
"hello" is stored as: ['h']['e']['l']['l']['o']['\0']
                       0    1    2    3    4    5
*/
    //Example:

    char str[] = "hello";
    printf("String: %s\n", str);
    printf("strlen(): %zu\n", strlen(str));        // Returns the length of string, which is 5 (excludes '\0')
    printf("sizeof(): %zu\n", sizeof(str));        // 6 (includes '\0')
    
    // Show each character including '\0'
    printf("\nCharacter breakdown:\n");
    for (int i = 0; i < sizeof(str); i++) {
        
	if (str[i] == '\0')  printf("[%d]: '\\0' (null, value = %d)\n", i, str[i]);
        else  printf("[%d]: '%c' (value = %d)\n", i, str[i], str[i]);
    }
  
    printf("\n------strlen() function------\n\n");
    //strlen() function declared in <string.h>
    char *test1 = "hello";
    char *test2 = "";
    char *test3 = "hello, world";

    printf("Standard strlen vs Custom my_strlen:\n");
    printf("'%s': %zu vs %d\n", test1, strlen(test1), my_strlen(test1));
    printf("'%s': %zu vs %d\n", test2, strlen(test2), my_strlen(test2));
    printf("'%s': %zu vs %d\n", test3, strlen(test3), my_strlen(test3));

    printf("\n------Enumeration Constants------\n\n");
    //Start at 0, increment by 1
    //Values of YES & NO
    enum boolean {YES, NO};
    printf("YES = %d\n", YES);
    printf("NO = %d\n", NO);
     
    enum boolean flag = YES;
    if(flag == YES) printf("Flag is YES!\n");

    printf("\n------Explicit Values------\n\n");
    enum escapes {BELL = '\a', BACKSPACE = '\b', TAB = '\t',NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
    enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};
    printf("--- Escape Characters ---\n");
    printf("BELL = %d\n", BELL);           
    printf("BACKSPACE = %d\n", BACKSPACE); 
    printf("TAB = %d\n", TAB);             
    printf("NEWLINE = %d\n", NEWLINE);     
    printf("VTAB = %d\n", VTAB);           
    printf("RETURN = %d\n\n", RETURN);     
    
    printf("--- Months ---\n");
    printf("JAN = %d\n", JAN);   
    printf("FEB = %d\n", FEB);   
    printf("MAR = %d\n", MAR);  
    printf("APR = %d\n", APR);  
    printf("MAY = %d\n", MAY); 
    printf("JUN = %d\n", JUN);  
    printf("JUL = %d\n", JUL);       
    printf("AUG = %d\n", AUG);   
    printf("SEP = %d\n", SEP);   
    printf("OCT = %d\n", OCT);   
    printf("NOV = %d\n", NOV);   
    printf("DEC = %d\n", DEC);

//Important Rules for enumeration
// VALID - different enumerations
    enum colors { RED, GREEN, BLUE };
    enum traffic { RED_LIGHT, YELLOW, GREEN_LIGHT }; // OK - different enum

// INVALID - same enumeration with duplicate names
// enum test { RED, BLUE, RED }; // ERROR!

// VALID - same enumeration with duplicate values
    enum test { A = 1, B = 1, C = 2 }; // OK - duplicate values allowed

//Advantages of Enumeration over #define

/* Using #define:

    #define JAN 1
    #define FEB 2
    #define MAR 3
- ... must define each one

- Using enum - much easier!
    enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
*/
    return 0;
}

