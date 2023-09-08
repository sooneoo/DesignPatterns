/*
** Imutable objects are object which are constant and it 
** is not possible to change its internal state. This is save
** protection for mutlithread access for rewriting the value 
*/

#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int x;
    int y;
}Point;


#define Point(x, y) (Point){(x), (y)}


Point
point_shift(Point self, int x, int y)
{
    return Point(self.x + x, self.y + y);
}


#define point_show(p) \
    printf("Point {x: %d, y: %d}\n", p.x, p.y)


int
main(void)
{
    const Point p1 = Point(3, 4);

    point_show(p1);

    const Point p2 = point_shift(p1, 2, 7);

    printf("\nafter shift\n");
    point_show(p1);
    point_show(p2);

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}
