#include "snake.h"

gboolean game_tick(gpointer data) {
    (void)data;  /* Suppress unused parameter warning */

    /*
     * If the game is not in an active playable state,
     * skip all logic but keep the timer alive so the
     * game over / pause screens remain visible.
     */
    if (!gs.running || gs.game_over || gs.paused)
        return G_SOURCE_CONTINUE;

    /* ══════════════════════════════════════════════════
       STEP 1 — Apply buffered direction
       The player may have pressed a key between ticks.
       gs.next_dir holds the most recent requested direction.
       We apply it here, but ONLY if it's not a 180° reversal
       (you can't go directly backwards into yourself).
       ══════════════════════════════════════════════════ */
    Direction nd = gs.next_dir;

    if ((nd == DIR_UP    && gs.dir != DIR_DOWN)  ||
        (nd == DIR_DOWN  && gs.dir != DIR_UP)    ||
        (nd == DIR_LEFT  && gs.dir != DIR_RIGHT) ||
        (nd == DIR_RIGHT && gs.dir != DIR_LEFT)) {
        gs.dir = nd;  /* Safe to apply — not a reversal */
    }
    /* If it WAS a reversal, gs.dir stays unchanged */

    /* ══════════════════════════════════════════════════
       STEP 2 — Calculate new head position
       Start from the current head (body[0]) and move
       one cell in the current direction.
       ══════════════════════════════════════════════════ */
    Point new_head = gs.body[0];  /* Copy current head position */

    switch (gs.dir) {
        case DIR_UP:    new_head.y--; break;  /* y decreases going up    */
        case DIR_DOWN:  new_head.y++; break;  /* y increases going down  */
        case DIR_LEFT:  new_head.x--; break;  /* x decreases going left  */
        case DIR_RIGHT: new_head.x++; break;  /* x increases going right */
    }

    /* ══════════════════════════════════════════════════
       STEP 3 — Wall collision detection
       Check if the new head is outside the grid boundaries.
       ══════════════════════════════════════════════════ */
    if (new_head.x < 0 || new_head.x >= GRID_COLS ||
        new_head.y < 0 || new_head.y >= GRID_ROWS) {

        /* Snake hit a wall — game over */
        gs.game_over = TRUE;

        /* Update high score if current score beats it */
        if (gs.score > gs.high_score)
            gs.high_score = gs.score;

        gtk_widget_queue_draw(canvas);  /* Trigger redraw to show game over screen */
        return G_SOURCE_CONTINUE;
    }

    /* ══════════════════════════════════════════════════
       STEP 4 — Self collision detection
       Check if the new head overlaps with any body segment.

       IMPORTANT: We check up to length-1 (exclude the tail).
       The tail will move away this tick, so it's safe to
       occupy that cell — unless the snake just ate food
       (in which case the tail doesn't move).
       ══════════════════════════════════════════════════ */
    for (int i = 0; i < gs.length - 1; i++) {
        if (gs.body[i].x == new_head.x &&
            gs.body[i].y == new_head.y) {

            /* Snake bit itself — game over */
            gs.game_over = TRUE;

            if (gs.score > gs.high_score)
                gs.high_score = gs.score;

            gtk_widget_queue_draw(canvas);
            return G_SOURCE_CONTINUE;
        }
    }
