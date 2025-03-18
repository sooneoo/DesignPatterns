#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Observer {
    void (*on_event)(struct Observer *);
} Observer;


#define OBSERVER(T) ((Observer*)(T))


typedef struct {
    Observer observer;
    float x;
    float y;
} Player;


void player_on_ground_position(Player * self) {
    printf("(%f x %f) player on the ground\n", self->x, self->y);
}


// simple constructor for Player class
#define player(_x, _y) (Player) {                                       \
    .observer = {                                                       \
        .on_event = (void(*)(Observer*)) player_on_ground_position      \
    }                                                                   \
    , .x = (_x)                                                         \
    , .y = (_y)                                                         \
}


typedef enum {
    Observer_Player_1
    , Observer_SIZE
} Observer_ID;


typedef struct {
    size_t size;
    Observer * observer[Observer_SIZE];
} Subject;


#define subject() (Subject){0}


void subject_subscribe(Subject * self, size_t ID, Observer * observer) {
    self->observer[ID] = observer;
    self->size++;
}


void subject_notify(Subject * self) {
    for(size_t i = 0; i < self->size; i++) {
        // check if given player is on the ground and emit event
        self->observer[i]->on_event(self->observer[i]);
    }
}


int main(void) {
    Player p1 = player(100, 100);
    Subject p_subject = subject();

    subject_subscribe(&p_subject, Observer_Player_1, OBSERVER(&p1));
    subject_notify(&p_subject);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}




