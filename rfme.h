#define IMG_WIDTH 120
#define IMG_HEIGHT 32
#define IMG_LEN count_of(rfmeLogo)

static uint8_t rfmeLogo[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x58, 0xa0, 0x58, 0xe0, 0x98, 0x60, 0xd8, 0xa0, 0x58, 0x60, 0xd8, 0xa0, 0x58, 0x60, 0xd8, 0xa0, 0x58, 0x60, 0xd8, 0xa0, 0x58, 0xe0, 0x18, 0xf0, 0x00, 0x00, 0x40, 0x90, 0x28, 0x40, 0xb0, 0x40, 0x28, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x40, 0x98, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0xa0, 0x10, 0x60, 0x88, 0x50, 0x20, 0x48, 0x10, 0x20, 0x08, 0x80, 0x40, 0xe0, 0x10, 0xe8, 0x50, 0xa8, 0x00, 0x00, 0x00, 0x38, 0x40, 0xb8, 0x60, 0x98, 0x60, 0xd8, 0x50, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0xc0, 0xb8, 0x60, 0x98, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x02, 0x85, 0x42, 0xa5, 0x42, 0xa5, 0x42, 0xa1, 0x47, 0xa0, 0x45, 0x23, 0x04, 0x03, 0x04, 0xd3, 0xad, 0x5a, 0xe5, 0x1e, 0xf1, 0x0e, 0x01, 0x00, 0xa0, 0x4a, 0x95, 0x68, 0x83, 0x2c, 0x51, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x50, 0xa0, 0x48, 0xb4, 0x02, 0x6d, 0x90, 0x25, 0x9a, 0x61, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0xa0, 0x40, 0x18, 0xe0, 0x0a, 0x54, 0xaa, 0x11, 0x0a, 0xa5, 0x08, 0xc3, 0x20, 0xc1, 0xa0, 0x40, 0xa0, 0xc0, 0x3a, 0xc5, 0xba, 0x6d, 0x93, 0x6c, 0x1b, 0x00, 0x00, 0x80, 0x60, 0x80, 0x70, 0xa0, 0x5b, 0xa4, 0xdb, 0x36, 0xc9, 0x76, 0x9d, 0x63, 0xbe, 0xc4, 0x38, 0xe0, 0x98, 0x60, 0xd8, 0x20, 0xff, 0x84, 0x7b, 0x96, 0x69, 0x16, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xb0, 0x48, 0xb4, 0x6a, 0x9d, 0x72, 0x0d, 0x3a, 0x07, 0x14, 0x0b, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0xbd, 0x52, 0xad, 0x5a, 0xe5, 0x5b, 0x0a, 0x00, 0x80, 0x54, 0x29, 0xc6, 0x18, 0x62, 0x8d, 0x60, 0x09, 0xd0, 0x24, 0x58, 0x82, 0x35, 0x4a, 0x10, 0x27, 0x08, 0x02, 0x25, 0xc8, 0x15, 0xaa, 0x11, 0x66, 0x88, 0x25, 0xc0, 0x10, 0xa8, 0x54, 0xa2, 0x0c, 0xb1, 0x46, 0x08, 0x13, 0x04, 0x02, 0x01, 0x18, 0x00, 0x1e, 0x80, 0x0f, 0x18, 0x07, 0x19, 0x06, 0x1d, 0x02, 0xef, 0x98, 0x67, 0xda, 0x35, 0xce, 0x39, 0x03, 0x00, 0xd0, 0x2d, 0xf6, 0x89, 0x77, 0xac, 0x53, 0x0d, 0x02, 0x05, 0x02, 0x05, 0x0b, 0x04, 0x03, 0x0a, 0x05, 0x02, 0x05, 0x0a, 0xc5, 0x3a, 0xd7, 0xa8, 0x77, 0x8a, 0xbd, 0x01, 0x00, 0x00, 0x00, 0x80, 0xb4, 0x4a, 0xb7, 0x58, 0xe7, 0x1d, 0xf2, 0x4d, 0xbb, 0x64, 0x9f, 0x70, 0x8f, 0x74, 0xcb, 0x3c, 0xe3, 0x1c, 0xeb, 0x55, 0x2e, 0x71, 0x0f, 0x34, 0x0b, 0x00, 0x00, 0x48, 0x32, 0x45, 0x9a, 0x20, 0xd7, 0x08, 0x32, 0x05, 0x0a, 0x10, 0x03, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x50, 0xa5, 0x1a, 0xa0, 0x4f, 0x90, 0x65, 0x0a, 0x15, 0x00, 0xd5, 0x02, 0xe0, 0x32, 0xc8, 0x34, 0xea, 0x16, 0xf9, 0x86, 0x7d, 0x92, 0x6f, 0x98, 0x67, 0xdc, 0x22, 0xdf, 0x68, 0x97, 0x79, 0xc6, 0x3d, 0xd2, 0x2d, 0x56, 0x39, 0x06, 0x0b, 0x00, 0x00, 0x15, 0x2a, 0x55, 0xae, 0x59, 0xe6, 0x1d, 0xf3, 0x4c, 0xb3, 0x6e, 0x99, 0x66, 0xdb, 0x2c, 0xf3, 0x0c, 0xf7, 0x58, 0xa7, 0x5a, 0xb5, 0xcb, 0x3c, 0xe3, 0x5c, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00};
