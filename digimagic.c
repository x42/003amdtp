/*
 * Copyright (C) 2012 Robin Gareus <robin@gareus.org>
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

#define BYTE_PER_SAMPLE (4)
#define MAGIC_DIGI_BYTE (1)

#define MAGIC_BYTE_OFF(x) ( (x * BYTE_PER_SAMPLE) + MAGIC_DIGI_BYTE )

/** digi look up table
 *
 * @param idx index byte (audio-sample data) 0x00..0xff
 * @param off channel offset shift
 * @return value to xor with given data
 * */
const uint8_t digiscrt(const uint8_t idx, const int off) {
	/* todo simplify futher: just use bitmasks and << */
	const uint8_t len[16] = {0, 1, 3, 5, 7, 9, 11, 13, 14, 12, 10, 8, 6, 4, 2, 0};

	const uint8_t nib[15] = {0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4, 0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xf};
	const uint8_t hir[15] = {0x0, 0x6, 0xf, 0x8, 0x7, 0x5, 0x3, 0x4, 0xc, 0xd, 0xe, 0x1, 0x2, 0xb, 0xa};
	const uint8_t hio[16] = {0, 11, 12, 6, 7, 5, 1, 4, 3, 0x00, 14, 13, 8, 9, 10, 2};

	if (off==0) return idx;

	const uint8_t ln = idx&0xf;
	if (len[ln] < off) return 0x00;

	const uint8_t hn = (idx>>4)&0xf;
	const uint8_t hr = (hn==0x9) ? 0x9 : hir[(hio[hn]+off)%15];

	return (nib[14 - len[ln] + off]) | (hr<<4);
}


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
void digi_encode(uint8_t * const data, const int nch) {
	int c;
	uint8_t carry = 0x00;
	uint8_t idx = 0;
	int off = 0;

	for (c=0; c< nch; ++c) {
		if (data[MAGIC_BYTE_OFF(c)] != 0x00) { off = 0; }
		data[MAGIC_BYTE_OFF(c)] ^= carry;
		if (off == 0) { idx = data[MAGIC_BYTE_OFF(c)]; }
		carry=digiscrt(idx, ++off);
	}
}

/** decode audio data received from a digi003
 *
 * see \ref digi_encode for details
 *
 * @param data interleaved audio-data to be rewritten in place
 * @param nch number of channels per frame
 */
void digi_decode(uint8_t * const data, const int nch) {
	int c;
	uint8_t carry = 0x00;
	uint8_t idx = 0;
	int off = 0;

	for (c=0; c< nch; ++c) {
		data[MAGIC_BYTE_OFF(c)] ^= carry;
		if (data[MAGIC_BYTE_OFF(c)] != 0x00) {
			off = 0; idx= data[MAGIC_BYTE_OFF(c)] ^ carry;
		}
		carry=digiscrt(idx, ++off);
	}
}


#ifdef TEST_MAIN

void hexdump(uint8_t *data, int nch, char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c=0; c< nch; ++c) {
		printf("%02x ", data[MAGIC_BYTE_OFF(c)]);
	}
	printf("\n");
}


int main(int argc, char **argv) {
	const int nch = 18;
	uint8_t *snd = calloc(BYTE_PER_SAMPLE * nch, sizeof(uint8_t));

	printf("# of channels: %d\n", 18);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[4*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0x14;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 14 2c b3 ad 16 2a b5 ab 04 6c f3 8d 72 5e 31 4f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[4*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0x85;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 85 7b 54 3c c6 da e5 1b 24 bc a3 0d 62 fe 81 7f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[6*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0x49;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 49 c6 da e5 1b 24 f5 8b 74 5c 33 4d c2 de e1 1f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[6*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0xfd;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: fd 82 7e 51 3f 00 fd 82 7e 51 3f 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[6*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0x05;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 05 6b f4 8c 73 5d 37 49 c6 da e5 1b 24 bc a3 0d 62 fe\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(uint8_t));
	snd[MAGIC_DIGI_BYTE]=snd[6*BYTE_PER_SAMPLE + MAGIC_DIGI_BYTE] = 0x05;
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
