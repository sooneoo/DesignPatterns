/*
 * command pattern is used for separation of control of given class from its implementation
 * this can dynamicaly change its behavioral od change controled class object
 */
#include <stdio.h>
#include <stdlib.h>


/*
 * command class containing abstract callback function 
 */
typedef struct {
    void (*execute)(void *);
} Command;


#define command(T)(Command) {.execute = (void(*)(void*)) (T)}
#define command_execute(T, S) (T)->execute((S))

/*
 * simple player class which is controlled by prepared commands
 */
typedef struct {
    float x;
    float y;
} Player;


Player player(float x, float y) {
    return (Player) {
        .x = x
        , .y = y  
    };
}


/*
 * input stream contains configuration of command for every configured key
 */
typedef struct {
    Command * jump;
    Command * duck;
} InputStream;


/*
 * command callback for player jump
 */
void command_player_jump(Player * self) {
    printf("(%f %f) player jump\n", self->x, self->y);
}


/*
 * command callback for player duck
 */
void command_player_duck(Player * self) {
    printf("(%f %f) player duck\n", self->x, self->y);
}


InputStream input_stream(Command * jump, Command * duck) {
    return (InputStream) {
        .jump = jump
        , .duck = duck
    };
}


/*
 * stream interacting on input key event, this stream return command regarding to given input key
 * thaks to this it is possible dynamicaly change the reaction for given key 
 */
Command * input_stream_loop(InputStream * self, char key) {
    if(key == 'w') {
        return self->jump;
    } else if(key == 's') {
        return self->duck;
    } else {
        return NULL;
    }
}


int main(void) {
    Player p1 = player(10, 20);
    Command cmd_jump = command(command_player_jump);
    Command cmd_duck = command(command_player_duck);
    InputStream input_handler = input_stream((Command*) &cmd_jump, (Command*) &cmd_duck);

    Command * cmd = input_stream_loop(&input_handler, 'w');
    
    if(cmd != NULL) {
        command_execute(cmd, &p1);
    }

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}



