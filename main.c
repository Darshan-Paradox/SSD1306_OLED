#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

i2c_inst_t *i2c = i2c1;

#define I2C i2c

#define SDA 6
#define SCL 7

#define SCL_FREQ 400

#include "./oled.h"
#include "./graphics.h"
#include "rfme.h"

void plt_fn(Screen *s, int freq, bool draw)
{
    for (int i = 0; i < 65; i++)
    {
        //int y = (i - 64) * (i - 64);
        float y = 16;
        y += 15 * sin((float)i * 0.0736 * freq);

        if (y < 32)
        {
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
        }
    }
}

void sq_fn(Screen *s, int coeff, bool draw)
{
    for (int i = 0; i < 70; i++)
    {
        //int y = (i - 64) * (i - 64);
        float y = 16;

        for (int n = 1; n < coeff*2; n += 2)
            y += 15 * sin((float)i * 0.0736 * n)/n;

        if (y < 32)
        {
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
        }
    }
}

void tr_fn(Screen *s, int coeff, bool draw)
{
    for (int i = 0; i < 70; i++)
    {
        //int y = (i - 64) * (i - 64);
        float y = 16;
        int sgn = 1;

        for (int n = 1; n < coeff*2; n += 2)
        {
            y += sgn * 12 * sin((float)i * 0.0736 * n)/(n * n);
            sgn *= -1;
        }

        if (y < 32)
        {
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
            draw_pixel(s, i, (int)y, draw);
        }
    }
}

const uint BTN_LED[][2] = {
						   { 1,  2},
						   {16, 17},
						   { 3,  4},
						   {14, 13},
						  };

const uint seq[][4] = {
                        {1, 0, 0, 1},
						{0, 1, 1, 0},
						{1, 0, 1, 0},
						{0, 1, 0, 1},
						{1, 1, 0, 0},
						{0, 0, 1, 1},
						{1, 1, 1, 1},
						{0, 0, 0, 0}
					  };

const uint8_t coeffs_len = 10;
uint8_t coeffs_cnt = 1;

int main()
{
    stdio_init_all();

	for (int i = 0; i < 4; ++i)
	{
		gpio_init(BTN_LED[i][0]);
		gpio_init(BTN_LED[i][1]);
		gpio_set_dir(BTN_LED[i][1], GPIO_OUT);
		gpio_set_dir(BTN_LED[i][0], GPIO_IN);
	}
    OLED_INIT(NULL, 0);

    /*send_cmd(INV_DISP);*/

    SCREEN_INIT();
    render(&screen);

    Screen rfme_logo;
    draw_img(&rfme_logo, rfmeLogo, IMG_LEN, IMG_WIDTH, IMG_HEIGHT, 0, 0);
    sleep_ms(2000);

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 4; j++)
        {
            if (seq[i][j])
                gpio_put(BTN_LED[j][1], 1);	
            else
                gpio_put(BTN_LED[j][1], 0);	
        }
        sleep_ms(1000);
    }
    sleep_ms(500);

    clr_screen(&rfme_logo);

    gpio_put(BTN_LED[0][1], 1);
    draw_text(&screen, "BTN1: Generate", strlen("BTN1: Generate"), 120, 25);
    draw_text(&screen, "sine wave", strlen("sine wave"), 120, 13);
    render(&screen);

    sleep_ms(4000);
    clr_screen(&screen);

    gpio_put(BTN_LED[0][1], 0);
    gpio_put(BTN_LED[1][1], 1);

    draw_text(&screen, "BTN2: Generate", strlen("BTN1: Generate"), 120, 25);
    draw_text(&screen, "square^ wave", strlen("square^ wave"), 120, 13);
    render(&screen);

    sleep_ms(4000);
    clr_screen(&screen);

    gpio_put(BTN_LED[1][1], 0);
    gpio_put(BTN_LED[2][1], 1);

    draw_text(&screen, "BTN3: Generate", strlen("BTN1: Generate"), 120, 25);
    draw_text(&screen, "triangle wave", strlen("triangle wave"), 120, 13);
    render(&screen);

    sleep_ms(4000);
    clr_screen(&screen);

    gpio_put(BTN_LED[2][1], 0);
    gpio_put(BTN_LED[3][1], 1);

    draw_text(&screen, "BTN4: Increase", strlen("BTN4: Increase"), 120, 25);
    draw_text(&screen, "coefficients B_n", strlen("coefficients B_"), 120, 13);
    render(&screen);

    sleep_ms(4000);
    clr_screen(&screen);

    draw_text(&screen, "MAX LIMIT B_:", strlen("MAX LIMIT B_:"), 120, 25);
    draw_text(&screen, "10", strlen("10"), 70, 13);
    render(&screen);

    sleep_ms(1500);
    clr_screen(&screen);

    gpio_put(BTN_LED[3][1], 0);

    while (true)
    {
        draw_text(&screen, "PRESS BTN >", strlen("PRESS BTN >"), 118, 16);
        draw_text(&screen, "to start", strlen("to start"), 118,  8);

        render(&screen);
        if (gpio_get(BTN_LED[0][0]))
        {
            clr_screen(&screen);
            sleep_ms(50);

            gpio_put(BTN_LED[0][1], 1);
            plt_fn(&screen, 1, true);
            sleep_ms(200);
            draw_text(&screen, "sine wave", strlen("sine wave"), 118, 16);
            draw_text(&screen, "freq: 3pi", strlen("freq: 3pi"), 118,  8);

            render(&screen);

            sleep_ms(1500);

            clr_screen(&screen);
            sleep_ms(100);

            gpio_put(BTN_LED[0][1], 0);
        }
        if (gpio_get(BTN_LED[1][0]))
        {
            clr_screen(&screen);
            sleep_ms(50);

            gpio_put(BTN_LED[1][1], 1);

            char str[8];
            sprintf(str, "b_: %d", coeffs_cnt);

            sq_fn(&screen, coeffs_cnt, true);
            sleep_ms(200);
            draw_text(&screen, "sq^ wave", strlen("sq^ wave"), 120, 16);
            draw_text(&screen, str, strlen(str), 118,  8);

            render(&screen);

            sleep_ms(1500);

            clr_screen(&screen);
            sleep_ms(100);

            gpio_put(BTN_LED[1][1], 0);
        }
        if (gpio_get(BTN_LED[2][0]))
        {
            clr_screen(&screen);
            sleep_ms(50);

            gpio_put(BTN_LED[2][1], 1);

            char str[8];
            sprintf(str, "b_: %d", coeffs_cnt);

            tr_fn(&screen, coeffs_cnt, true);
            sleep_ms(200);
            draw_text(&screen, "tr wave", strlen("tr wave"), 120, 16);
            draw_text(&screen, str, strlen(str), 118,  8);

            render(&screen);

            sleep_ms(1500);

            clr_screen(&screen);
            sleep_ms(100);

            gpio_put(BTN_LED[2][1], 0);
        }
        if (gpio_get(BTN_LED[3][0]))
        {
            clr_screen(&screen);
            sleep_ms(50);

            gpio_put(BTN_LED[3][1], 1);

            coeffs_cnt = (coeffs_cnt) % coeffs_len + 1;

            char str[16];
            sprintf(str, "B_: %d", coeffs_cnt);
            draw_text(&screen, "Number of coeffs", strlen("Number of coeffs"), 120, 25);
            draw_text(&screen, str, strlen(str), 70, 12);
            render(&screen);

            sleep_ms(200);
            clr_screen(&screen);

            gpio_put(BTN_LED[3][1], 0);
        }

    }

}
