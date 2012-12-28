// gcc -o digimagic digimagic.c && ./digimagic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BYTE_PER_SAMPLE (4)
#define MAGIC_DIGI_BYTE (1)

#define MAGIC_BYTE_OFF(x) ( (x * BYTE_PER_SAMPLE) + MAGIC_DIGI_BYTE)

const uint8_t digiscrt(const uint8_t idx, const int off) {
	/* todo simplify futher to bitmask and << */
	const uint8_t len[16] = {0, 1, 3, 5, 7, 9, 11, 13, 14, 12, 10, 8, 6, 4, 2, 0};

	const uint8_t nib[15] = {0x8, 0x7, 0x9, 0x6, 0xa, 0x5, 0xb, 0x4, 0xc, 0x3, 0xd, 0x2, 0xe, 0x1, 0xf};
	const uint8_t hir[15] = {0x0, 0x6, 0xf, 0x8, 0x7, 0x5, 0x3, 0x4, 0xc, 0xd, 0xe, 0x1, 0x2, 0xb, 0xa};
	const uint8_t hio[16] = {0, 11, 12, 6, 7, 5, 1, 4, 3, 0x00, 14, 13, 8, 9, 10, 2};

	if (off==0) return idx;

	const uint8_t ln = idx&0xf;
	if (len[ln] < off) return 0x00;

	const uint8_t hn = (idx>>4)&0xf;
	const uint8_t hr = hn==0x9?0x9 : hir[(hio[hn]+off)%15];

	return (nib[14 - len[ln] + off]) | (hr<<4);
}


void digi_encode(uint8_t *data, int nch) {
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


#if 1 // test code

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

	free(snd);
	return 0;
}
#endif
