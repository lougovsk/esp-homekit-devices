/**
 * my92xx LED Driver
 * Based on the C++ driver by Xose Pérez
 * Copyright (c) 2016 - 2026 MaiKe Labs
 * Copyright (C) 2017 - 2018 Xose Pérez for the Arduino compatible library
 *  
 * This code is a C port of the my92xx LED Driver Library by Xose Perez
 * the original C++ implementation is https://github.com/xoseperez/my92xx
 * Some functions were adjusted but mainly it's a copy paste of the library mentioned above.
 * Original comments are kept.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIGHTBULB_MY92XX_DRIVER_H
#define LIGHTBULB_MY92XX_DRIVER_H

typedef enum my92xx_model_num_channels {
        MY92XX_MODEL_MY9291_NUMCHANNELS = 0X04,
        MY92XX_MODEL_MY9231_NUMCHANNELS = 0X03,
} my92xx_model_num_channels_t;

typedef enum my92xx_cmd_one_shot_t {
        MY92XX_CMD_ONE_SHOT_DISABLE = 0X00,
        MY92XX_CMD_ONE_SHOT_ENFORCE = 0X01,
} my92xx_cmd_one_shot_t;

typedef enum my92xx_cmd_reaction_t {
        MY92XX_CMD_REACTION_FAST = 0X00,
        MY92XX_CMD_REACTION_SLOW = 0X01,
} my92xx_cmd_reaction_t;

typedef enum my92xx_cmd_bit_width_t {
        MY92XX_CMD_BIT_WIDTH_16 = 0X00,
        MY92XX_CMD_BIT_WIDTH_14 = 0X01,
        MY92XX_CMD_BIT_WIDTH_12 = 0X02,
        MY92XX_CMD_BIT_WIDTH_8 = 0X03,
} my92xx_cmd_bit_width_t;

typedef enum my92xx_cmd_frequency_t {
        MY92XX_CMD_FREQUENCY_DIVIDE_1 = 0X00,
        MY92XX_CMD_FREQUENCY_DIVIDE_4 = 0X01,
        MY92XX_CMD_FREQUENCY_DIVIDE_16 = 0X02,
        MY92XX_CMD_FREQUENCY_DIVIDE_64 = 0X03,
} my92xx_cmd_frequency_t;

typedef enum my92xx_cmd_scatter_t {
        MY92XX_CMD_SCATTER_APDM = 0X00,
        MY92XX_CMD_SCATTER_PWM = 0X01,
} my92xx_cmd_scatter_t;

typedef struct {
        my92xx_cmd_scatter_t scatter:1;
        my92xx_cmd_frequency_t frequency:2;
        my92xx_cmd_bit_width_t bit_width:MY92XX_CMD_BIT_WIDTH_12;
        my92xx_cmd_reaction_t reaction:1;
        my92xx_cmd_one_shot_t one_shot:1;
        unsigned char resv:1;
} __attribute__ ((aligned(1), packed)) my92xx_cmd_t;



#define MY92XX_COMMAND_DEFAULT { \
    .scatter = MY92XX_CMD_SCATTER_APDM, \
    .frequency = MY92XX_CMD_FREQUENCY_DIVIDE_1, \
    .bit_width = MY92XX_CMD_BIT_WIDTH_16, \
    .reaction = MY92XX_CMD_REACTION_FAST, \
    .one_shot = MY92XX_CMD_ONE_SHOT_DISABLE, \
    .resv = 0 \
}

void my92xx_configure(uint8_t di_pin, uint8_t dcki_pin, uint8_t numChips);

void my92xx_start();
void my92xx_stop();
void my92xx_set_freq(const uint16_t freq);
void my92xx_set_duty(const uint8_t gpio, const uint16_t duty, uint16_t dithering);
uint16_t my92xx_get_duty(const uint8_t gpio);
void my92xx_new_channel(const uint8_t gpio, const bool inverted);

#endif