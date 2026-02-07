#include <stdio.h>

#define MAX_STUDENTS 50    // Descriptive constant name

// External variable with descriptive name
    
int total_student_count = 0;

int main() {
    
    // === Valid variable names ===
    
    int count;
    int counter2;
    int _valid;        // Valid but not recommended
    int temperature;
    int x;
    int i;

    /* * Names are made up of letters and digits
       * The first character must be a letter
       * The underscore _ counts as a letter
    */    
    
    // int 2count;       // ERROR: starts with digit
    // int my-var;       // ERROR: contains hyphen
    // int my var;       // ERROR: contains space
    // int int;          // ERROR: keyword
    // int for;          // ERROR: keyword
    
    // Case sensitivity demonstration
    
    int variable = 10;
    int Variable = 20;
    int VARIABLE = 30;
    
    printf("variable = %d\n", variable);   // 10
    printf("Variable = %d\n", Variable);   // 20
    printf("VARIABLE = %d\n", VARIABLE);   // 30
    
    printf("\nThese are THREE different variables!\n");

    // Traditional practice
    int loop_counter = 0;      // lower case for variables
    #define MAX_SIZE 100       // upper case for constants
   
    // === Length of Variable Names ===
  
    /* * Internal Names (local variables, function names):

          - At least the first 31 characters are significant
          - Can be longer, but only first 31 characters matter

       * External Names (assemblers, loaders):

          - Standard guarantees uniqueness for only 6 characters
          - May be restricted to a single case
          - Keywords (like if, else, int, float) are reserved and must be in lower case
    */

    int this_is_a_very_long_variable_name_for_demonstration = 42;
    int this_is_a_very_long_variable_name_for_different_use = 100;
    
    // Long internal names (first 31 chars significant)

    printf("\n\nLong name 1: %d\n", this_is_a_very_long_variable_name_for_demonstration);
    printf("Long name 2: %d\n", this_is_a_very_long_variable_name_for_different_use);

    // These are different because they differ within first 31 characters
    
    int variable_name_one = 1;
    int variable_name_two = 2;

    printf("\n\nvariable_name_one: %d\n", variable_name_one);
    printf("variable_name_two: %d\n", variable_name_two);
    
    // === Choosing Good Variable Names ===

    /* * Recommendations:

       - Choose names that are related to the purpose of the variable
       - Names should be unlikely to get mixed up typographically
       - Use short names for local variables (especially loop indices)
       - Use longer names for external variables
       - Avoid Similar-Looking Names
    */  

     // Good: Short names for loop indices
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Loop body
        }
    }
    
    // Good: Descriptive names for important variables
    int student_age = 20;
    double account_balance = 1500.50;
    char first_initial = 'J';
    
    // Bad examples (for demonstration only)
    int y = 20;           // Not descriptive enough for important data
    int tmp = 100;        // Too generic
    int asdfgh = 5;       // Meaningless
    
    // Good: Related to purpose
    int days_in_week = 7;
    int hours_in_day = 24;
    double pi = 3.14159;
    
    printf("\n\nStudent age: %d\n", student_age);
    printf("Account balance: %.2f\n", account_balance);
    printf("Days in week: %d\n", days_in_week);
 
    /* === Reserved Keywords in C ===
     * auto        double      int         struct
       break       else        long        switch
       case        enum        register    typedef
       char        extern      return      union
       const       float       short       unsigned
       continue    for         signed      void
       default     goto        sizeof      volatile
       do          if          static      while 
     
      - You can't use these keywords.
      - These will cause ERRORS - keywords cannot be variable names:
         int int;
         int for;
         int while;
         int if;
         int return;
   */
    
    // But you can use them as part of a name:
    int for_loop_counter = 0;      // OK
    int while_condition = 1;       // OK
    int if_statement_count = 5;    // OK

    printf("\n\nfor_loop_counter: %d\n", for_loop_counter);
    printf("while_condition: %d\n", while_condition);
    printf("if_statement_count: %d\n", if_statement_count);
    
    return 0;
}
