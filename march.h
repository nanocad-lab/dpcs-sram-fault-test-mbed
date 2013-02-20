#ifndef MARCH_H
#define MARCH_H

using namespace std;

#ifndef MARCH_CONSTANTS
#define MARCH_CONSTANTS

#define SRAMBANK0_BASE_ADDR 0x00000000
#define SRAMBANK1_BASE_ADDR 0x60000000
#define SRAMBANK0_END_ADDR 0x00001FFC
#define SRAMBANK1_END_ADDR 0x60001FFC
#define ADDR_INCR 0x00000001

#endif

int doMarchSS();
int doMarchSS_SRAMBank0();
int doMarchSS_SRAMBank1();

int marchSS_M0(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);
int marchSS_M1(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);
int marchSS_M2(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);
int marchSS_M3(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);
int marchSS_M4(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);
int marchSS_M5(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride);

#endif