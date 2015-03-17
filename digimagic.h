/*
 * Copyright (C) 2012 Robin Gareus <robin@gareus.org>
 * Copyright (C) 2012 Damien Zammit <damien@zamaudio.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DIGIMAGIC_H_INCLUDED
#define DIGIMAGIC_H_INCLUDED

#include <linux/types.h>

struct DigiMagic {
	__u8 carry;
	__u8 idx;
	unsigned int off;
};

typedef struct DigiMagic DigiMagic;

/**
 */
void digi_state_reset(DigiMagic *state);

/**
 */
void digi_encode_step(DigiMagic *state, __be32 * const buffer);

/**
 */
void digi_decode_step(DigiMagic *state, __be32 * const buffer);

#endif

