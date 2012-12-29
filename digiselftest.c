#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "digimagic.h"

/* these need to be identical to digimagic.c */
#define BYTE_PER_SAMPLE (4)
#define MAGIC_DIGI_BYTE (2)

#define MAGIC_BYTE_OFF(x) ( (x * BYTE_PER_SAMPLE) + MAGIC_DIGI_BYTE )

static void hexdump(__u8 *data, int nch, char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c=0; c< nch; ++c) {
		printf("%02x ", data[MAGIC_BYTE_OFF(c)]);
	}
	printf("\n");
}


int main(int argc, char **argv) {
	int i;
	const int nch = 18;
	__u8 *snd = calloc(BYTE_PER_SAMPLE * nch, sizeof(__u8));

	__u8 *pcm_quadlets = calloc(nch, sizeof(__u8));
	for (i=0; i<nch; ++i) pcm_quadlets[i]=i;

	printf("# of channels: %d\n", 18);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(4)] = 0x14;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 14 2c b3 ad 16 2a b5 ab 04 6c f3 8d 72 5e 31 4f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(4)] = 0x85;
	hexdump(snd, nch, "input");
	digi_encode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 85 7b 54 3c c6 da e5 1b 24 bc a3 0d 62 fe 81 7f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(6)] = 0x49;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 49 c6 da e5 1b 24 f5 8b 74 5c 33 4d c2 de e1 1f 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(6)] = 0xfd;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: fd 82 7e 51 3f 00 fd 82 7e 51 3f 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(6)] = 0x05;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 05 6b f4 8c 73 5d 37 49 c6 da e5 1b 24 bc a3 0d 62 fe\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(6)] = 0x05;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "encoded");
	digi_decode(snd, nch);
	hexdump(snd, nch, "decoded");
	printf("    expect: 05 00 00 00 00 00 05 00 00 00 00 00 00 00 00 00 00 00\n");

	printf("\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)]=snd[MAGIC_BYTE_OFF(9)] = 0xf9;
	hexdump(snd, nch, "input");
	digi_encode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "encoded");
	digi_decode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "decoded");
	printf("    expect: f9 00 00 00 00 00 00 00 00 f9 00 00 00 00 00 00 00 00\n");

	free(snd);
	free(pcm_quadlets);
	return 0;
}
