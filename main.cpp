#include <cstdio>
#include <functional>
#include <iostream>
#include <ostream>
#include "bidirectional_grid.h"
#include "debug_particle.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

constexpr float FPS = 30;
constexpr int SCREEN_W = 1000;
constexpr int SCREEN_H = 1000;
constexpr int RESOLUTION = 10;
constexpr int COLS = SCREEN_W / RESOLUTION;
constexpr int ROWS = SCREEN_H / RESOLUTION;

auto grid = std::make_shared<BidirectionalGrid>();

// @formatter:off
void init();
bool update();
void draw();
// @formatter:on

int main(int argc, char **argv) {
    printf("[particulator - main] welcome to particulator!\n");
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "failed to install mouse!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to install keyboard!\n");
        return -1;
    }

    if (!al_init_primitives_addon()) {
        fprintf(stderr, "failed to initialize allegro primitives addon!\n");
        return -1;
    }

    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = nullptr;
    bool booting = true;
    bool redraw = true;

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }

    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    init();

    while (true) {
        if (al_is_event_queue_empty(event_queue)) {
            if (!(booting || redraw))
                continue;
            redraw = false;
            draw();
            al_flip_display();
        }

        al_wait_for_event(event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                if (!booting) redraw = update();
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                goto end;
            default: break;
        }

        if (booting)
            booting = false;
    }

end:
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}

void init() {
    printf("[particulator - init] everything ok. initializing...\n");
    grid->init(COLS, ROWS);

    for (int x = 1; x < COLS - 1; ++x) {
        for (int y = 0; y < 4; ++y) {
            grid->set(x, y, std::make_shared<DebugParticle>());
        }
    }
}

bool update() {
    return grid->update();
}

void draw() {
    grid->draw(RESOLUTION);
}
