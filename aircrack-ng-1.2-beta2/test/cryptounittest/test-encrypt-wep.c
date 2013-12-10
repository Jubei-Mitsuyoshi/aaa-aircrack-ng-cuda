/*
 *
 * test-encrypt-wep.c
 *
 * Copyright (C) 2012 Carlos Alberto Lopez Perez <clopez@igalia.com>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto.h"
#include "tests.h"

#define BLEN 256
#define KLEN 13



int main(int argc, char **argv)
{
    argc = argc; // remove warning not-used argc
    int error=0;

    static unsigned char expected[BLEN] =
             "\x72\xea\x7c\xf3\x62\xd0\x63\xb6\xf6\x3b\xd6\xfc\x1c\x6c\xc0\x18"
             "\xd0\x10\x23\xd6\x86\x4e\x04\xf0\x0e\xc7\x34\xca\x66\x34\x01\xac"
             "\x46\xd4\x7d\x15\x24\xa7\xaa\xb0\x06\x01\x4f\x9f\x61\x1c\x4e\x6d"
             "\x54\x22\x83\x6f\x36\x43\x12\x01\x07\xb8\xdb\x3c\x32\xc6\xe2\x5f"
             "\x66\x4e\x7e\x55\x4f\x5d\x61\x30\x8a\xb9\xb7\x11\xcb\xae\xe9\x68"
             "\x66\x10\x7d\xe7\x39\x29\xef\xb0\x69\xca\xec\xcf\x2c\x68\x57\x52"
             "\x62\x4f\x89\xd6\x58\x05\xe3\x6a\xa1\xd1\xc8\x2c\x0b\x2d\xe4\xc9"
             "\x73\xd7\xb0\x4f\x65\x57\xa2\x19\xc7\xbf\xa1\xa7\x43\x49\x51\x14"
             "\xa4\x12\x24\x15\xb1\x71\x39\xde\x5e\x95\x15\xb4\xb9\xb5\x61\x57"
             "\xbf\x43\x24\xe2\xb8\x9f\x38\x2f\x45\x29\xfa\x95\x80\x18\x0d\x5d"
             "\x41\x35\x2a\x83\x44\x37\x71\xcb\x80\x3d\x9d\xc4\xdc\xc4\x26\xea"
             "\x28\xb9\xa7\x2b\x40\x56\x27\xee\xbc\xfa\xf7\x98\x09\x33\xd1\xe3"
             "\x85\x79\x0d\xd8\x87\xa3\xfe\x8e\x37\xc4\x48\xbf\x66\x86\xfa\x49"
             "\x0e\x0f\xf2\x82\x42\xfe\x87\xcd\x18\xb0\x8a\x91\xbb\x97\x9b\x4e"
             "\x92\x36\xb2\x47\x12\xf0\xeb\x09\xdc\x7a\xdf\x60\xdf\xcd\x19\x7c"
             "\x2d\x72\x4e\x3a\x6d\x8f\x53\x8e\xe1\x03\xeb\x44\x4a\x02\x9f\x52";
    static unsigned char key[KLEN] =
             "\x6E\x9C\x7A\x91\x9F\xB8\xAE\x93\xC1\xAB\x80\x3C\x09";
    static unsigned char input[BLEN] =
             "\x91\xCE\xFF\xF0\x9B\x76\xB1\xC7\xB3\xAE\xE9\xB6\x39\xE2\xE2\xCB"
             "\x46\xBB\x20\xDA\xEF\x0D\xD8\x65\x75\x37\xFF\x8B\x78\x49\x39\x6E"
             "\x08\x6D\x93\x0A\x40\xD1\xA7\xE6\x22\x6B\xFF\x94\x21\xA8\x0E\xDB"
             "\x33\x2B\x4B\x88\x19\x6C\x94\x0E\xF3\xD8\xCC\xCB\xAF\x99\x89\x49"
             "\x4F\x4B\x42\x4F\xF4\x96\xA6\xD3\xC9\x00\xB7\xC7\x11\x63\x95\x0E"
             "\x29\x71\x0A\x38\xC2\x04\xDF\xB5\x01\xAA\xCA\x86\x47\x4A\xA3\x41"
             "\xE6\x1A\x00\xA7\xD6\xFF\xE7\x89\x64\xB5\x38\x2A\x5D\xBC\x13\x94"
             "\x8E\x0C\x93\xB6\xC8\x4E\x4F\xC6\x06\x9B\xEF\x9B\x56\xE3\x90\x54"
             "\xCB\x34\x64\x0B\x3D\x12\x02\x62\xFE\xDC\xA8\x8E\x38\xCE\x36\x3A"
             "\xE8\x4D\xF0\xED\x71\x59\xE5\xED\xA4\xB1\x12\xEB\xD5\x83\xA6\xC9"
             "\x5C\x76\x98\x8D\x1B\xCB\x3C\x31\xF5\x10\xFE\x40\xCC\x83\x27\xE6"
             "\xDF\xB9\xE1\x84\xFC\xC3\xCC\x8D\x7A\xA3\xE5\x61\x56\x92\xAD\x7C"
             "\xA2\x62\x46\x6F\x5C\xA0\x16\xC4\x52\xDB\xF6\x75\xE1\x35\x22\x91"
             "\xE8\x81\x87\x13\xC1\xC1\x0A\xB0\xBE\x20\xE7\xF5\x55\x55\x0C\xF3"
             "\x99\x67\x53\xAF\x35\x15\xA9\x48\x72\xD8\xEB\x4A\xCF\x5B\xF5\xB6"
             "\xBC\x30\x24\xCB\xFD\x6C\x5C\xF5\x62\x5C\xFD\xA5\x65\xD9\xD4\xD7";


    unsigned char buffer[BLEN]; memcpy(&buffer, &input, BLEN);


    encrypt_wep( buffer, BLEN, key, KLEN );
    error += test(buffer,expected,BLEN,argv[0]);

    decrypt_wep( buffer, BLEN, key, KLEN );
    error += test(buffer,input,BLEN,argv[0]);


    return error;
}

