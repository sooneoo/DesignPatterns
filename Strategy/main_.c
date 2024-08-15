
typedef struct Precond Precond;


typedef struct {
    void ctrl(Precond *);
} Strategy;


struct Precond {
    Strategy * strategy;
    int param;
}


Precond precond_


