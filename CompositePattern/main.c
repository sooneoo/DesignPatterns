#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct Widget Widget;


typedef void (*WidgetDrawCallback)(Widget *);


typedef struct Widget {
    WidgetDrawCallback draw;
    bool visible;
}Widget;


#define WIDGET(T) ((Widget*) (T))


void widget_draw(Widget * self) {
    if(self->visible == true && self->draw != NULL)
        self->draw(self);
}


typedef struct {
    Widget widget;
    int16_t x, y;
}WidgetIcon;


static void __icon_draw(WidgetIcon * self) {
    (void) self;
    // Code for draw of icon
    printf("WidgetIcon {x: %d, y: %d}", self->x, self->y);
}


WidgetIcon widget_icon_new(int16_t x, int16_t y) {
    return (WidgetIcon) {{(WidgetDrawCallback) __icon_draw, true}, x, y};
}


typedef struct {
    Widget widget;

    int16_t x, y;
    int16_t width, height;

    size_t length;
    Widget ** children;
}WidgetWindow;


static void __window_draw(WidgetWindow * self) {
    // Code for draw of window
    printf("WidgetWindow {x:%d, y: %d, width: %d, height: %d, lenght: %lld"
            , self->x, self->y, self->width, self->height, self->length);

    // drawing of children widget
    if(self->children != NULL) {
        for(size_t i = 0; i < self->length; i++) {
            printf(", ");
            widget_draw(self->children[i]);
        }
    }

    printf("}\n");
}


WidgetWindow widget_window_new(
    int16_t width, int16_t height, size_t length, Widget ** children) {
    return (WidgetWindow) {
        {
            (WidgetDrawCallback) __window_draw
            , true
        }
        , 0, 0
        , width, height
        , length, children
    };
}


#define size(T)sizeof((T))/sizeof(*(T))


int main(void) {
    // widget icon initialization
    WidgetIcon icon_1 = widget_icon_new(10, 10);
    WidgetIcon icon_2 = widget_icon_new(10, 10);

    // children list containing widget icons for displaying in window
    Widget * children[] = {WIDGET(&icon_1), WIDGET(&icon_2)};

    //widget window initialization
    WidgetWindow window = widget_window_new(800, 600, size(children), children);

    //draw all widgets
    widget_draw(WIDGET(&window));

    printf("Program exit..\n");
    return EXIT_SUCCESS;
}





