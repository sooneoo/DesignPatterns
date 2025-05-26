#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    bool (*condition)(void*);
    void (*action)(void*);
    void * param;
} Rule;


void rule_table_execute(size_t size, Rule * rule_table) {
    for(size_t i = 0; i < size; i++) {
        if(rule_table[i].condition(rule_table[i].param) == true) {
            rule_table[i].action(rule_table[i].param);
        }
    }
}


bool rule1_activate(void * param) {
    return *((bool*) param);
}


void rule1_action(void * param) {
    *((bool*) param) = false;
    printf("rule 1 activated\n");
}


int main(void) {
    bool rule1 = false;
    Rule rule_table[] = {
        {rule1_activate, rule1_action, &rule1}
    };

    rule_table_execute(sizeof(rule_table) / sizeof(*rule_table), rule_table);
    rule1 = true;
    rule_table_execute(sizeof(rule_table) / sizeof(*rule_table), rule_table);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}


