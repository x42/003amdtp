#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "digimagic.h"

/* these need to be identical to digimagic.c */
#define BYTE_PER_SAMPLE (4)
#define MAGIC_DIGI_BYTE (2)

#define MAGIC_BYTE_OFF(x) ( ( (x) * BYTE_PER_SAMPLE ) + MAGIC_DIGI_BYTE )

static void hexdump(__u8 const * const data, const int nch, const char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c = 0; c < nch; ++c) {
		printf("%02x ", data[MAGIC_BYTE_OFF(c)]);
	}
	printf("\n");
}

static void hexdump_x(__u8 const * const data, const int nch, const char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c = 0; c < nch; ++c) {
		printf("%02x ", data[c]);
	}
	printf("\n");
}

static int hexcmp(__u8 const * const d1, __u8 const * const expect, const int nch) {
	int c;
	for (c = 0; c < nch; ++c) {
		if (d1[MAGIC_BYTE_OFF(c)] != expect[c]) {
			printf ("! test failed\n");
			return 1;
		}
	}
	return 0;
}

/*  ----- OLD SIMPLE API ----- */

/* this is unsuitable for continuous en/de coding. since it does not retain state.  */

#define BYTE_PER_SAMPLE (4)
#define MAGIC_BYTE_OFF(x) ( ( (x) * BYTE_PER_SAMPLE ) + MAGIC_DIGI_BYTE )

static void digi_encode(__u8 * const data, const int nch) {
	int c;
	DigiMagic state;
	digi_state_reset(&state);

	for (c = 0; c < nch; ++c) {
		digi_encode_step(&state, (__be32*) &data[c * BYTE_PER_SAMPLE]);
	}
}

static void digi_decode(__u8 * const data, const int nch) {
	int c;
	DigiMagic state;
	digi_state_reset(&state);

	for (c = 0; c < nch; ++c) {
		digi_decode_step(&state, (__be32*) &data[c * BYTE_PER_SAMPLE]);
	}
}

static void digi_encode_qmap(__be32 * const buffer, __u8 *pcm_quadlets, const int nch) {
	int c;
	DigiMagic state;
	digi_state_reset(&state);

	for (c = 0; c < nch; ++c) {
		digi_encode_step(&state, &buffer[pcm_quadlets[c]]);
	}
}


static void digi_decode_qmap(__be32 * const buffer, __u8 *pcm_quadlets, const int nch) {
	int c;
	DigiMagic state;
	digi_state_reset(&state);

	for (c = 0; c < nch; ++c) {
		digi_decode_step(&state, &buffer[pcm_quadlets[c]]);
	}
}

static int docheck (__u8 * const data, __u8 const * const expect, const int nch) {
	int rv;
	hexdump(data, nch, "input");
	digi_encode(data, nch);
	hexdump(data, nch, "output");
	hexdump_x(expect, nch, "expect");
	rv = hexcmp(data, expect, nch);
	printf("\n");
	return rv;
}

int main(int argc, char **argv) {
	int i;
	int err = 0;
	const int nch = 18;
	__u8 *snd = calloc(BYTE_PER_SAMPLE * nch, sizeof(__u8));

	__u8 *pcm_quadlets = calloc(nch, sizeof(__u8));
	for (i = 0; i < nch; ++i) pcm_quadlets[i] = i;

	printf("# of channels: %d\n", 18);

	printf("1) encoder tests..\n");

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	const __u8 cmp0[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	err |= docheck(snd, cmp0, nch);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(4)] = 0x14;
	const __u8 cmp1[] = {0x14, 0x2c, 0xb3, 0xad, 0x16, 0x2a, 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00};
	err |= docheck(snd, cmp1, nch);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(6)] = 0x49;
	const __u8 cmp2[] = {0x49, 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00};
	err |= docheck(snd, cmp2, nch);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(6)] = 0xfd;
	const __u8 cmp3[] = {0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	err |= docheck(snd, cmp3, nch);

	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(6)] = 0x05;
	const __u8 cmp4[] = {0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x37, 0x49, 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe};
	err |= docheck(snd, cmp4, nch);

	printf("2) QMAP encoder test:\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(4)] = 0x85;
	const __u8 cmp5[] = {0x85, 0x7b, 0x54, 0x3c, 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00};

	hexdump(snd, nch, "input");
	digi_encode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "output");
	hexdump_x(cmp5, nch, "expect");
	err |= hexcmp(snd, cmp5, nch);


	printf("\n3) encode+decode test:\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(6)] = 0x05;
	const __u8 cmp6[] = {0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "encoded");
	digi_decode(snd, nch);
	hexdump(snd, nch, "decoded");
	hexdump_x(cmp6, nch, "expect");
	err |= hexcmp(snd, cmp6, nch);

	printf("\n4) QMAP encode+decode test:\n");
	memset(snd, 0, BYTE_PER_SAMPLE * nch * sizeof(__u8));
	snd[MAGIC_BYTE_OFF(0)] = snd[MAGIC_BYTE_OFF(9)] = 0xf9;
	const __u8 cmp7[] = {0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	hexdump(snd, nch, "input");
	digi_encode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "encoded");
	digi_decode_qmap((__be32*)snd, pcm_quadlets, nch);
	hexdump(snd, nch, "decoded");
	hexdump_x(cmp7, nch, "expect");
	err |= hexcmp(snd, cmp7, nch);

	free(snd);
	free(pcm_quadlets);

	return err;
}
