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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "digimagic.h"

#define BYTE_PER_SAMPLE (4)
#define MAGIC_DIGI_BYTE (1)

#define MAGIC_BYTE_OFF(x) ( (x * BYTE_PER_SAMPLE) + MAGIC_DIGI_BYTE )

/** digi look up table
 *
 * @param idx index byte (audio-sample data) 0x00..0xff
 * @param off channel offset shift
 * @return salt to XOR with given data
 * */
static const uint8_t digiscrt(const uint8_t idx, const int off) {
	/* TODO simplify further: just use bit-masks and shift operators
	 * should be possible somehow :)
	 * */

	/** the length of the added pattern only depends on the lower nibble
	 * of the last non-zero data */
	const uint8_t len[16] = {0, 1, 3, 5, 7, 9, 11, 13, 14, 12, 10, 8, 6, 4, 2, 0};

	/** the lower nibble of the salt. Interleaved sequence.
	 * this is walked backwards according to len[] */
	const uint8_t nib[15] = {0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4, 0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xf};

	/** circular list for upper nibble. */
	const uint8_t hir[15] = {0x0, 0x6, 0xf, 0x8, 0x7, 0x5, 0x3, 0x4, 0xc, 0xd, 0xe, 0x1, 0x2, 0xb, 0xa};
	/** start offset for upper nibble mapping */
	const uint8_t hio[16] = {0, 11, 12, 6, 7, 5, 1, 4, 3, 0x00, 14, 13, 8, 9, 10, 2};

	/* the first byte is identical to itself */
	if (off==0) return idx;

	const uint8_t ln = idx&0xf;
	if (len[ln] < off) return 0x00;

	const uint8_t hn = (idx>>4)&0xf;
	const uint8_t hr = (hn==0x9) ? 0x9 : hir[(hio[hn]+off)%15];

	return (nib[14 - len[ln] + off]) | (hr<<4);
}


void digi_encode(__be32 * const data, const int nch) {
	int c;
	uint8_t carry = 0x00;
	uint8_t idx = 0;
	int off = 0;

	for (c=0; c< nch; ++c) {
		if ( ((data[c]>>8)&0xff) != 0x00) { off = 0; }
		data[c] ^= carry<<8;
		if (off == 0) { idx = (data[c]>>8)&0xff; }
		carry=digiscrt(idx, ++off);
	}
}

void digi_encode_dummy(__be32 * const data, const int nch) {
	int c;
	for (c=0; c< nch; ++c) {
		data[c] &= 0xffff00ff;
	}
}

void digi_decode(__be32 * const data, const int nch) {
	int c;
	uint8_t carry = 0x00;
	uint8_t idx = 0;
	int off = 0;

	for (c=0; c< nch; ++c) {
		data[c] ^= carry<<8;
		if ((data[c]&0x0000ff00) != 0x00) {
			off = 0; idx= ((data[c]>>8)&0xff) ^ carry;
		}
		carry=digiscrt(idx, ++off);
	}
}


#ifdef TEST_MAIN

static void hexdump(__be32 *data, int nch, char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c=0; c< nch; ++c) {
		printf("%02x ", (data[c]>>8)&0xff);
	}
	printf("\n");
}


int main(int argc, char **argv) {
	const int nch = 18;
	__be32 *snd = calloc(nch, sizeof(__be32));

	printf("# of channels: %d\n", 18);

	memset(snd, 0, nch * sizeof(__be32));
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[4] = 0x00001400;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 14 2c b3 ad 16 2a b5 ab 04 6c f3 8d 72 5e 31 4f 00 00\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[4] = 0x00008500;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 85 7b 54 3c c6 da e5 1b 24 bc a3 0d 62 fe 81 7f 00 00\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[6] = 0x00004900;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 49 c6 da e5 1b 24 f5 8b 74 5c 33 4d c2 de e1 1f 00 00\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[6] = 0x0000fd00;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: fd 82 7e 51 3f 00 fd 82 7e 51 3f 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[6] = 0x00000500;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 05 6b f4 8c 73 5d 37 49 c6 da e5 1b 24 bc a3 0d 62 fe\n");

	printf("\n");
	memset(snd, 0, nch * sizeof(__be32));
	snd[0]=snd[6] = 0x00000500;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "encoded");
	digi_decode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 05 00 00 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00\n");

	free(snd);
	return 0;
}
#endif
