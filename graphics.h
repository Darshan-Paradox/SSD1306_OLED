#ifndef GRAPHICS_H

#define GRAPHICS_H

#include <ctype.h>

#include "oled.h"
#include "font.h"

#define PIXEL(x, y) (x + ((int)(y / 8) * 128))

typedef enum Alignment
{
    LEFT,
    RIGHT,
    CENTER
}
Alignment;

typedef struct Screen
{
    //(0, 0)
    uint8_t start_col;
    uint8_t start_page;

    //(WIDTH, HEIGHT)
    uint8_t end_col;
    uint8_t end_page;

    uint16_t buflen;
    uint8_t buffer[BUF_LEN];
}
Screen;

#define SCREEN_INIT() Screen screen = {.start_col = 0, .end_col = (OLED_WIDTH - 1), .start_page = 0, .end_page = (NUM_PAGES - 1), .buflen = BUF_LEN, .buffer = { 0x00 }}

void render     (Screen *s);
bool is_pixel_on(Screen *s, uint8_t x, uint8_t y);
void draw_pixel (Screen *s, uint8_t x, uint8_t y, bool rend);
void clr_screen (Screen *s);

void stroke_line    (Screen *s, int x1, int y1, int x2, int y2, bool draw);
void stroke_rect    (Screen *s, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool draw);
void fill_rect      (Screen *s, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool draw);
void stroke_circle  (Screen *s, uint8_t x, uint8_t y, int r, bool draw);
void fill_circle    (Screen *s, uint8_t x, uint8_t y, int r, bool draw);
void stroke_polygon (Screen *s, int sides, bool closed, int *x, int *y, bool draw);
void fill_polygon(Screen *s, int sides, bool closed, int *x, int *y, bool draw);

void draw_text(Screen *s, char *str, int len, uint8_t x, uint8_t y);

void draw_img(Screen *s, uint8_t *img, int img_len, uint8_t width, uint8_t height, uint8_t off_x, uint8_t off_y);

//====================================================================================================

void render(Screen *s)
{
    uint8_t cmds[] = {
        COL_ADDR,
        s->start_col,
        s->end_col,
        PAGE_ADDR,
        s->start_page,
        s->end_page,
    };
    send_cmd_list(cmds, count_of(cmds));
    send_buf(s->buffer, s->buflen);

    send_cmd(DISP_ON_RAM);
}

bool is_pixel_on(Screen *s, uint8_t x, uint8_t y)
{
    uint8_t offset = y % PAGE_HEIGHT;
    uint8_t page = y / PAGE_HEIGHT;

    int index = page * OLED_WIDTH + x;

    if (s->buffer[index] >> offset == 1) return true;
    return false;
}

void draw_pixel(Screen *s, uint8_t x, uint8_t y, bool rend)
{
    uint8_t offset = y % PAGE_HEIGHT;
    uint8_t page = y / PAGE_HEIGHT;

    int index = page * OLED_WIDTH + x;

    uint8_t mask = 0x01;
    s->buffer[index] |= (mask << (offset));

    if (rend)
        render(s);
}

void clr_screen(Screen *s)
{
    memset(s->buffer, 0x00, BUF_LEN);
    render(s);
}

void stroke_line(Screen *s, int x1, int y1, int x2, int y2, bool draw)
{
    if (x1 == x2)
    {
        if (y1 > y2)
        {
            y1 ^= y2;
            y2 ^= y1;
            y1 ^= y2;
        }
        for (int i = y1; i <= y2; i++)
            draw_pixel(s, x1, i, draw);
        return;
    }


    if (x1 > x2)
    {
        x1 ^= x2, y1 ^= y2;
        x2 ^= x1, y2 ^= y1;
        x1 ^= x2, y1 ^= y2;
    }
    float slope = (float)(y2 - y1)/(float)(x2 - x1);
    for (int i = x1; i <= x2; i++)
        draw_pixel(s, i, (int)(y1 + slope * (i - x1)), draw);
}

void stroke_rect(Screen *s, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool draw)
{
    for (int i = x; i < x + w; i++)
    {
        draw_pixel(s, i, y, draw);
        draw_pixel(s, i, y + h - 1, draw);
    }
    for (int j = y; j < y + h; j++)
    {
        draw_pixel(s, x, j, draw);
        draw_pixel(s, x + w - 1, j, draw);
    }
}

void fill_rect(Screen *s, uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool draw)
{
    for (int j = y; j < y + h; j++)
    {
        for (int i = x; i < x + w; i++)
        {
            draw_pixel(s, i, j, draw);
        }
    }
}

void stroke_circle(Screen *s, uint8_t x, uint8_t y, int r, bool draw)
{
    int _r;
    for (int i = 0; i < OLED_WIDTH; i++)
        for (int j = 0; j < OLED_HEIGHT; j++)
        {
            _r = (i - x) * (i - x) + (j - y) * (j - y);
            if (_r >= r*r - 4 && _r <= r*r + 4)
                draw_pixel(s, i, j, draw);
        }
}

void fill_circle(Screen *s, uint8_t x, uint8_t y, int r, bool draw)
{
    int _r;
    for (int i = 0; i < OLED_WIDTH; i++)
        for (int j = 0; j < OLED_HEIGHT; j++)
        {
            _r = (i - x) * (i - x) + (j - y) * (j - y);
            if (_r <= r*r + 2)
                draw_pixel(s, i, j, draw);
        }
}

void stroke_polygon(Screen *s, int sides, bool closed, int *x, int *y, bool draw)
{
    for (int i = 0; i < (sides - (int)(!closed)); i++)
    {
        int x1 = x[i], x2 = x[(i + 1) % sides];
        int y1 = y[i], y2 = y[(i + 1) % sides];
        stroke_line(s, x1, y1, x2, y2, draw);
    }
}

void fill_polygon(Screen *s, int sides, bool closed, int *x, int *y, bool draw)
{
    stroke_polygon(s, sides, closed, x, y, draw);
    for (int i = 0; i < OLED_WIDTH; i++)
    {
        int cnt = 0;
        for (int j = 0; j < OLED_HEIGHT - 1; j++)
        {
            if (is_pixel_on(s, i, j) ^ is_pixel_on(s, i, j + 1))
                ++cnt;
            if ((cnt >> 1) & 1)
                draw_pixel(s, i, j, draw);
        }
    }
}

void static draw_character(Screen *s, char c, uint8_t x, uint8_t y)
{
    c = toupper(c);
    uint8_t index = 0;

    if (c >= 'A' && c <= 'Z')
        index = c - 'A' + 1;
    if (c >= '0' && c <= '9')
        index = c - '0' + 27;

    switch (c)
    {
        case '.':
            index = 37;
            break;
        case ':':
            index = 38;
            break;
        case ',':
            index = 39;
            break;
        case '^':
            index = 40;
            break;
        case '_':
            index = 41;
            break;
        case '>':
            index = 42;
            break;
    }

    draw_font(&(s->buffer[PIXEL(x, y)]), index);
}

void draw_text(Screen *s, char *str, int len, uint8_t x, uint8_t y)
{
    for (int i = 0; i < len; i++)
    {
        draw_character(s, str[i], x, y);
        x -= FONT_SIZE;
    }
}

void draw_img(Screen *s, uint8_t *img, int img_len, uint8_t width, uint8_t height, uint8_t off_x, uint8_t off_y)
{
    s->start_col = off_x;
    s->start_page = off_y;
    s->end_col = width + off_x + - 1;
    s->end_page = height/PAGE_HEIGHT + off_y - 1;

    s->buflen = (s->end_col - s->start_col) * (s->end_page - s->start_page + 1);

    clr_screen(s);

    memcpy(s->buffer, img, img_len*sizeof(uint8_t));

    render(s);
}

#endif
