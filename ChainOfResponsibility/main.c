#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
    bool is_value;
    uint8_t value;
} Opt_Value;


typedef struct SysCfg {
    bool (*write)(struct SysCfg*, uint8_t, uint8_t);
    Opt_Value (*read)(struct SysCfg*, uint8_t);
    struct SysCfg * tail;
} SysCfg;


#define sys_cfg(r, w, t) (SysCfg) {                     \
    .write = (bool(*)(SysCfg*, uint8_t, uint8_t)) (w)   \
    , .read = (Opt_Value(*)(SysCfg*, uint8_t)) (r)      \
    , .tail = (t)                                       \
}


bool sys_cfg_write(SysCfg * self, uint8_t address, uint8_t value) {
    if(self != NULL) {
        return self->write(self, address, value);
    } else {
        return false;
    }
}


Opt_Value sys_cfg_read(SysCfg * self, uint8_t address) {
    if(self != NULL) {
        return self->read(self, address);
    } else {
        return (Opt_Value) {.is_value = false};
    }
}


typedef struct {
    SysCfg super;
    uint8_t mem_buff[20];
} SysCfg_Local;


static bool sys_cfg_local_write(SysCfg_Local * self, uint8_t address, uint8_t value) {
    if(address < 20) {
        self->mem_buff[address] = value;
        return true;
    } else {
        return sys_cfg_write(self->super.tail, address - 20, value);
    }
}


static Opt_Value sys_cfg_local_read(SysCfg_Local * self, uint8_t address) {
    if(address < 20) {
        return (Opt_Value) {.is_value = true, .value = self->mem_buff[address]};
    } else {
        return sys_cfg_read(self->super.tail, address - 20);
    }
}


typedef struct {
    SysCfg super;
    uint8_t mem_buff[40];
} SysCfg_Extern;


static bool sys_cfg_extern_write(SysCfg_Extern * self, uint8_t address, uint8_t value) {
    if(address < 40) {
        self->mem_buff[address] = value;
        return true;
    } else {
        return sys_cfg_write(self->super.tail, address - 40, value);
    }
}


static Opt_Value sys_cfg_extern_read(SysCfg_Extern * self, uint8_t address) {
    if(address < 40) {
        return (Opt_Value) {.is_value = true, .value = self->mem_buff[address]};
    } else {
        return sys_cfg_read(self->super.tail, address - 40);
    }
}


static void test_read_write(SysCfg * self) {
    const uint8_t local_address = 10;

    if(sys_cfg_write(self, local_address, 42) == true) {
        printf("local write success\n");
    } else {
        printf("local write fail!\n");
    }

    Opt_Value local_val = sys_cfg_read(self, local_address);

    if(local_val.is_value == true) {
        printf("local read success: %d\n\n", local_val.value);
    } else {
        printf("local read fail!\n");
    } 

    const uint8_t extern_address = 30;

    if(sys_cfg_write(self, extern_address, 27) == true) {
        printf("extern write success\n");
    } else {
        printf("extern write fail!\n");
    }

    Opt_Value extern_val = sys_cfg_read(self, extern_address);

    if(local_val.is_value == true) {
        printf("extern read success: %d\n\n", extern_val.value);
    } else {
        printf("extern read fail!\n");
    } 

    const uint8_t unknown_address = 60;

    if(sys_cfg_write(self, unknown_address, 7) == true) {
        printf("extern write success\n");
    } else {
        printf("extern write fail!\n");
    }

    Opt_Value invalid_val = sys_cfg_read(self, unknown_address);

    if(invalid_val.is_value == true) {
        printf("extern read success: %d\n", invalid_val.value);
    } else {
        printf("extern read fail!\n");
    } 
}


int main(void) {
    SysCfg_Extern sys_cfg_extern = {
        .super = sys_cfg(sys_cfg_extern_read, sys_cfg_extern_write, NULL)
        
    };

    SysCfg_Local sys_cfg_local = {
        .super = sys_cfg(sys_cfg_local_read, sys_cfg_local_write, &sys_cfg_extern.super)
    };

    test_read_write(&sys_cfg_local.super);

    printf("program exit..\n");
    return EXIT_SUCCESS;
}



