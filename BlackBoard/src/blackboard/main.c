#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
Návrhový vzor Blackboard (Nástěnka) je architektonický vzor, který se skvěle hodí pro situace, kdy máte mnoho nezávislých modulů (expertů), kteří potřebují spolupracovat na řešení komplexního problému, aniž by o sobě museli vědět.

Klíčové komponenty Blackboardu:
    Blackboard (Nástěnka): Centrální sdílená paměť (v C obvykle globální nebo statická struktura). Je to jediný zdroj pravdy.
    Knowledge Sources (Zdroje znalostí): Tyto moduly "pozorují" nástěnku a podle toho, co tam vidí, na ni dopisují své výsledky nebo mění svůj stav.
    Controller (Koordinátor): Hlídač, který určuje, kdy má který modul dostat slovo (ve vašem případě to může být prostý časovač nebo hlavní smyčka).
*/

typedef enum {
    PowerManager_State_Off
    , PowerManager_State_Standby
    , PowerManager_State_On
} PowerManager_State;


typedef struct {
    PowerManager_State state;
    int8_t timer;
} PowerManager;

#define FOREVER_DELAY -1
#define OFF_DELAY 20


PowerManager power_manager(PowerManager_State init_state) {
    return(PowerManager) {
        .state = init_state
        , .timer = OFF_DELAY
    };
}


void power_manager_set_on(PowerManager * self) {
    self->state = PowerManager_State_On;
}


void power_manager_set_off(PowerManager * self, int8_t off_delay) {
    self->state = PowerManager_State_Standby;
    self->timer = off_delay;
}


void power_manager_task(PowerManager * self) {
    if(self->state == PowerManager_State_Standby) {
        if(self->timer > 0) {
            self->timer --;
        } else if (self->timer == 0) {
            self->state = PowerManager_State_Off;
        }
    }
}


typedef struct {
    bool IGN;
    bool PHON;
} IO;


IO io(void) {
    return (IO) {0};
}


void io_task(IO * self) {
    (void) self;
    //read IO
}


typedef struct {
    bool enable;
    uint8_t stop_delay;
} Preheater;


Preheater preheater(void) {
    return (Preheater) {0};
}


void preheater_task(Preheater * self) {
    if(self->stop_delay > 0) {
        self->stop_delay --;
    }
}


void preheater_set_on(Preheater * self) {
    if(self->enable == false && self->stop_delay == 0) {
        self->enable = true;
    }
}

void preheater_set_off(Preheater * self) {
    if(self->enable == true) {
        self->enable = false;
        self->stop_delay = 100;
    }
}


typedef struct {
    IO keyboard;
    Preheater preheater;
    PowerManager power_manager;
} BlackBoard;


BlackBoard black_board(void) {
    return (BlackBoard) {
        .keyboard = io()
        , .preheater = preheater()
        , .power_manager = power_manager(PowerManager_State_Off)
    };
}


void black_board_task(BlackBoard * self) {
    io_task(&self->keyboard);

    if(self->keyboard.PHON == true) {
       preheater_set_on(&self->preheater);
    } else {
       preheater_set_off(&self->preheater);
    }

    preheater_task(&self->preheater);

    if(self->keyboard.IGN == true) {
        power_manager_set_on(&self->power_manager);
    } else if(self->preheater.enable == true || self->preheater.stop_delay > 0) {
        power_manager_set_off(&self->power_manager, FOREVER_DELAY);
    } else if(self->keyboard.IGN == false && self->power_manager.state != PowerManager_State_Off) {
        power_manager_set_off(&self->power_manager, OFF_DELAY);
    }

    power_manager_task(&self->power_manager);
}



int main(void) {
    BlackBoard system_controller = black_board();

    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);
    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);
    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);

    system_controller.keyboard.PHON = true;

    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);

    system_controller.keyboard.IGN = true;

    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);

    system_controller.keyboard.PHON = false;


    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);

    system_controller.keyboard.IGN = false;

    black_board_task(&system_controller);
    printf("%d %d\n", system_controller.power_manager.state, system_controller.power_manager.timer);

    printf("program exit..\n");
    return EXIT_SUCCESS;
}


