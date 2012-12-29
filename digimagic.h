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
#ifndef DIGIMAGIC_H
#define DIGIMAGIC_H

#include <linux/types.h>

/** prepare raw audio data for sending to digi003
 *
 * This function takes a pointer to interleaved audio data. Each sample must
 * be BYTE_PER_SAMPLE bytes long and there must be nch samples.
 *
 * It rewrites the byte MAGIC_DIGI_BYTE of each sample according to
 * digidesign003(TM) magic(TM).
 *
 * @param data interleaved audio-data to be rewritten in place
 * @param nch number of channels per frame
 */
void digi_encode(__be32 * const data, const int nch);

/**
 * test function -- detect byte
 */
void digi_encode_dummy(__be32 * const data, const int nch);

/** decode audio data received from a digi003
 *
 * see \ref digi_encode for details
 *
 * @param data interleaved audio-data to be rewritten in place
 * @param nch number of channels per frame
 */
void digi_decode(__be32 * const data, const int nch);
#endif

