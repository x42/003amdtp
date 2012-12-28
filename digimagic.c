// gcc -o digimagic digimagic.c && ./digimagic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint8_t digiscrt(uint8_t idx, int off) {

	const uint8_t s[256][14] = {
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x6a, 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00 },
		{ 0x69, 0xf6, 0x8a, 0x75, 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00 },
		{ 0x67, 0xf9, 0x86, 0x7a, 0x55, 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf },
		{ 0x66, 0xfa, 0x85, 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00 },
		{ 0x65, 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00 },
		{ 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x2a, 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00 },
		{ 0x29, 0xb6, 0xaa, 0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00 },
		{ 0x27, 0xb9, 0xa6, 0x0a, 0x65, 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef },
		{ 0x26, 0xba, 0xa5, 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00 },
		{ 0x25, 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xba, 0xa5, 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00 },
		{ 0xb9, 0xa6, 0x0a, 0x65, 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00 },
		{ 0xb7, 0xa9, 0x06, 0x6a, 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f },
		{ 0xb6, 0xaa, 0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00 },
		{ 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00 },
		{ 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x4a, 0xc5, 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00 },
		{ 0x49, 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00 },
		{ 0x47, 0xc9, 0xd6, 0xea, 0x15, 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f },
		{ 0x46, 0xca, 0xd5, 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00 },
		{ 0x45, 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xca, 0xd5, 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00 },
		{ 0xc9, 0xd6, 0xea, 0x15, 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00 },
		{ 0xc7, 0xd9, 0xe6, 0x1a, 0x25, 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f },
		{ 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00 },
		{ 0xc5, 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00 },
		{ 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x3a, 0x45, 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00 },
		{ 0x39, 0x46, 0xca, 0xd5, 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00 },
		{ 0x37, 0x49, 0xc6, 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f },
		{ 0x36, 0x4a, 0xc5, 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00 },
		{ 0x35, 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xfa, 0x85, 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00 },
		{ 0xf9, 0x86, 0x7a, 0x55, 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00 },
		{ 0xf7, 0x89, 0x76, 0x5a, 0x35, 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f },
		{ 0xf6, 0x8a, 0x75, 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00 },
		{ 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00 },
		{ 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x5a, 0x35, 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00 },
		{ 0x59, 0x36, 0x4a, 0xc5, 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00 },
		{ 0x57, 0x39, 0x46, 0xca, 0xd5, 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f },
		{ 0x56, 0x3a, 0x45, 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00 },
		{ 0x55, 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00 },
		{ 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x7a, 0x55, 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00 },
		{ 0x79, 0x56, 0x3a, 0x45, 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00 },
		{ 0x77, 0x59, 0x36, 0x4a, 0xc5, 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff },
		{ 0x76, 0x5a, 0x35, 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00 },
		{ 0x75, 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00 },
		{ 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x9a, 0x95, 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00 },
		{ 0x99, 0x96, 0x9a, 0x95, 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00 },
		{ 0x97, 0x99, 0x96, 0x9a, 0x95, 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f },
		{ 0x96, 0x9a, 0x95, 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00 },
		{ 0x95, 0x9b, 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x94, 0x9c, 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x93, 0x9d, 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x92, 0x9e, 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x91, 0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x0a, 0x65, 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00 },
		{ 0x09, 0x66, 0xfa, 0x85, 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00 },
		{ 0x07, 0x69, 0xf6, 0x8a, 0x75, 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf },
		{ 0x06, 0x6a, 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00 },
		{ 0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00 },
		{ 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xaa, 0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00 },
		{ 0xa9, 0x06, 0x6a, 0xf5, 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00 },
		{ 0xa7, 0x09, 0x66, 0xfa, 0x85, 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f },
		{ 0xa6, 0x0a, 0x65, 0xfb, 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00 },
		{ 0xa5, 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00 },
		{ 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xdb, 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xda, 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00 },
		{ 0xd9, 0xe6, 0x1a, 0x25, 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00 },
		{ 0xd7, 0xe9, 0x16, 0x2a, 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f },
		{ 0xd6, 0xea, 0x15, 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00 },
		{ 0xd5, 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00 },
		{ 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xeb, 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xea, 0x15, 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00 },
		{ 0xe9, 0x16, 0x2a, 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00 },
		{ 0xe7, 0x19, 0x26, 0xba, 0xa5, 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf },
		{ 0xe6, 0x1a, 0x25, 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00 },
		{ 0xe5, 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00 },
		{ 0xe4, 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1c, 0x23, 0xbd, 0xa2, 0x0e, 0x61, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1b, 0x24, 0xbc, 0xa3, 0x0d, 0x62, 0xfe, 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x1a, 0x25, 0xbb, 0xa4, 0x0c, 0x63, 0xfd, 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00 },
		{ 0x19, 0x26, 0xba, 0xa5, 0x0b, 0x64, 0xfc, 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00 },
		{ 0x17, 0x29, 0xb6, 0xaa, 0x05, 0x6b, 0xf4, 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf },
		{ 0x16, 0x2a, 0xb5, 0xab, 0x04, 0x6c, 0xf3, 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00 },
		{ 0x15, 0x2b, 0xb4, 0xac, 0x03, 0x6d, 0xf2, 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x14, 0x2c, 0xb3, 0xad, 0x02, 0x6e, 0xf1, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8e, 0x71, 0x5f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8d, 0x72, 0x5e, 0x31, 0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8c, 0x73, 0x5d, 0x32, 0x4e, 0xc1, 0xdf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8b, 0x74, 0x5c, 0x33, 0x4d, 0xc2, 0xde, 0xe1, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x8a, 0x75, 0x5b, 0x34, 0x4c, 0xc3, 0xdd, 0xe2, 0x1e, 0x21, 0xbf, 0x00, 0x00, 0x00 },
		{ 0x89, 0x76, 0x5a, 0x35, 0x4b, 0xc4, 0xdc, 0xe3, 0x1d, 0x22, 0xbe, 0xa1, 0x0f, 0x00 },
		{ 0x87, 0x79, 0x56, 0x3a, 0x45, 0xcb, 0xd4, 0xec, 0x13, 0x2d, 0xb2, 0xae, 0x01, 0x6f },
		{ 0x86, 0x7a, 0x55, 0x3b, 0x44, 0xcc, 0xd3, 0xed, 0x12, 0x2e, 0xb1, 0xaf, 0x00, 0x00 },
		{ 0x85, 0x7b, 0x54, 0x3c, 0x43, 0xcd, 0xd2, 0xee, 0x11, 0x2f, 0x00, 0x00, 0x00, 0x00 },
		{ 0x84, 0x7c, 0x53, 0x3d, 0x42, 0xce, 0xd1, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x83, 0x7d, 0x52, 0x3e, 0x41, 0xcf, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x82, 0x7e, 0x51, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x81, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
		{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // XXX 255 - data missing
	};

	if (off == 0) return idx;
	if (off > 14) return 0x00;
	return s[idx][off-1];
}

void digi_encode(uint8_t *data, int nch) {
	int c;
	uint8_t carry = 0x00;
	uint8_t idx = 0;
	int off = 0;

	for (c=0; c< nch; ++c) {
		if (data[c*3 +1] != 0x00) { off = 0; }

		data[c*3 +1] ^= carry;

		if (off == 0) { idx = data[c*3 +1]; }
		carry=digiscrt(idx, ++off);
	}
}


#if 1 // test code

void hexdump(uint8_t *data, int nch, char *annotation) {
	int c;
	printf("%10s: ", annotation);
	for (c=0; c< nch; ++c) {
		printf("%02x ", data[c*3 +1]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	int nch = 18;
	uint8_t *snd = calloc(3 * nch, sizeof(uint8_t));
	snd[1]=snd[4*3 + 1] = 0x14;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 14 2c b3 ad 16 2a b5 ab 04 6c f3 8d 72 5e 31 4f 00 00\n");

	printf("\n");
	memset(snd, 0, 3 * nch * sizeof(uint8_t));
	snd[1]=snd[4*3 + 1] = 0x85;
	hexdump(snd, nch, "input");
	digi_encode(snd, nch);
	hexdump(snd, nch, "output");
	printf("    expect: 85 7b 54 3c c6 da e5 1b 24 bc a3 0d 62 fe 81 7f 00 00\n");

	free(snd);
	return 0;
}
#endif
