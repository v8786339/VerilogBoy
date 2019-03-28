/*
 *  VerilogBoy
 *
 *  Copyright (C) 2019  Wenting Zhang <zephray@outlook.com>
 *
 *  This file is partially derived from PicoRV32 project:
 *  Copyright (C) 2017  Clifford Wolf <clifford@clifford.at>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms and conditions of the GNU General Public License,
 *  version 2, as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "misc.h"
#include "term.h"
#include "usb.h"
#include "usb_gamepad.h"

#define led_grn *((volatile uint32_t *)0x03000004)
#define led_red *((volatile uint32_t *)0x03000008)

void main()
{
    char msg[127];
    led_red = 0;
    
    // Set interrupt mask to zero (enable all interrupts)
    // This is a PicoRV32 custom instruction 
    asm(".word 0x0600000b");

    term_goto(0,4);
    printf("Pano Logic G1, PicoRV32 @ 100MHz, LPDDR @ 100MHz.\n");
    usb_init();
    led_grn = 1;
    term_clear();
	while (1) {
        led_grn = 1;
        delay_ms(10);
        led_grn = 0;
        delay_ms(10);
        usb_event_poll();
        term_goto(0,0);
        printf("%04x, %d, %d, %d, %d\n", gp_buttons, gp_analog[0], gp_analog[1], gp_analog[2], gp_analog[3]);
    }
}
