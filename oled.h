#ifndef OLED_H

#define OLED_H

#include "hardware/i2c.h"

#ifndef I2C
#define     I2C                 i2c_default

#define     SDA                 PICO_DEFAULT_I2C_SDA_PIN
#define     SCL                 PICO_DEFAULT_I2C_SCL_PIN

#define     SCL_FREQ               400
#endif

#define     OLED_ADDR           _u(0x3C)
#define     OLED_HEIGHT            32
#define     OLED_WIDTH             128

#define     COL_ADDR            _u(0x21)
#define     PAGE_ADDR           _u(0x22)

/* Contrast value ranges from 0x80 to 0x8F */
#define     CONTRAST            _u(0x81) //increase the value to increase constrast 

#define     ENTIRE_DISP_ON      _u(0xA5)
#define     DISP_ON_RAM         _u(0xA4)

#define     NORM_DISP           _u(0xA6)
#define     INV_DISP            _u(0xA7)

#define     DISP_OFF            _u(0xAE)
#define     DISP_ON             _u(0xAF)

#define     MEM_ADDR_MODE       _u(0x20)
#define     PAGE_ADDR_MODE      _u(0x02)
#define     HOR_ADDR_MODE       _u(0x00)
#define     VER_ADDR_MODE       _u(0x01)

#define     PAGE_HEIGHT         _u(8)
#define     NUM_PAGES           (OLED_HEIGHT / PAGE_HEIGHT)
#define     BUF_LEN             (NUM_PAGES * OLED_WIDTH)

#define     DISP_START_LINE     _u(0x40)
#define     DISP_OFFSET         _u(0xD3)
#define     SEG_REMAP           _u(0xA0)
#define     MUX_RATIO           _u(0xA8)
#define     COM_OUT_DIR         _u(0xC0)
#define     COM_PIN_CONFIG      _u(0xDA)
#define     PRECHARGE_PERIOD    _u(0xD9)
#define     VCOM_DESEL          _u(0xDB)
#define     CHARGE_PUMP         _u(0x8D)

#define     SCRL_OFF            _u(0x2E)

#define     DISP_CLK            _u(0xD5)
#define     CLK_FREQ_DIV        _u(0x80)

void send_cmd(uint8_t cmd);

void send_cmd_list(uint8_t *buf, int num);

void send_buf(uint8_t buf[], int buflen);

void OLED_INIT(uint8_t *cmds, int cmdlen);

//====================================================================================================

void send_cmd(uint8_t cmd)
{
    uint8_t buf[2] = {0x80, cmd};
    i2c_write_blocking(I2C, OLED_ADDR, buf, 2, false);
}

void send_cmd_list(uint8_t *cmd, int length)
{
    for (int i = 0; i < length; i++)
        send_cmd(cmd[i]);
}

void send_buf(uint8_t buf[], int buflen)
{
    uint8_t *temp_buf = malloc(buflen + 1);

    temp_buf[0] = 0x40;
    memcpy(temp_buf + 1, buf, buflen);

    i2c_write_blocking(I2C, OLED_ADDR, temp_buf, buflen + 1, false);

    free(temp_buf);
}

void OLED_INIT(uint8_t *cmds, int cmdlen)
{
    i2c_init(I2C, SCL_FREQ * 1000);

    gpio_set_function(SDA, GPIO_FUNC_I2C);
    gpio_set_function(SCL, GPIO_FUNC_I2C);

    if (cmds != NULL)
    {
        send_cmd_list(cmds, cmdlen);
        return;
    }

    uint8_t default_cmds[] = {
        //[>Set display off<]
        DISP_OFF,

        //[>memory map<]
        MEM_ADDR_MODE,
        HOR_ADDR_MODE,

        //[>resolution and layout<]
        DISP_START_LINE,
        SEG_REMAP | 0x01,
        MUX_RATIO,
        OLED_HEIGHT - 1,
        COM_OUT_DIR | 0x08,
        DISP_OFFSET,
        0x00,
        COM_PIN_CONFIG,
        0x02,

        //[>timing and driving scheme<]
        DISP_CLK,
        CLK_FREQ_DIV,
        PRECHARGE_PERIOD,
        0xF1,
        VCOM_DESEL,
        0x30,

        //[>display<]
        CONTRAST,
        0xFF,
        DISP_ON_RAM,
        NORM_DISP,
        CHARGE_PUMP,
        0x14,
        SCRL_OFF,
        DISP_ON
    };

    send_cmd_list(default_cmds, count_of(default_cmds));
}

#endif
