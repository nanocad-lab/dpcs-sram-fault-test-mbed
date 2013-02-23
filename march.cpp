#include "JTAG.h"
#include "march.h"
#include "mbed.h"
#include "scan.h"

using namespace std;

extern Serial _USB_CONSOLE;
extern JTAG* _JTAG;
extern FILE* _FP;

int marchSS_M0(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
        
    //March SS element M0
    _USB_CONSOLE.printf("Element M0...\r\n");
    value = ZERO;
    for (address = base_addr; address <= end_addr; address += stride) {
        //w0
        _JTAG->writeMemory(address, value);
        iter++;
    }
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    
    return 0;
}

int marchSS_M1(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
    int error = 0;
    int error_byte0 = 0;
    int error_byte1 = 0;
    int error_byte2 = 0;
    int error_byte3 = 0;
    
    //March SS element M1
    _USB_CONSOLE.printf("Element M1...\r\n");
    fprintf(_FP, "Bank %lu,M1,", bankNum); //Write to results file that we are on element M1
    
    for (address = base_addr; address <= end_addr; address += stride) {
        error = 0;
        error_byte0 = 0;
        error_byte1 = 0;
        error_byte2 = 0;
        error_byte3 = 0;
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
           
        //w0
        value = ZERO;
        _JTAG->writeMemory(address, value);
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
        
        //w1
        value = ONE;
        _JTAG->writeMemory(address, value);
        
        error = error_byte3 + error_byte2 + error_byte1 + error_byte0;
        fprintf(_FP, "%d,%d,", iter*stride, error); //Log the address (within bank) and the error code (0-15).
      
        iter++;
    }
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    fprintf(_FP, "\n"); //newline for next element in results file
    
    return 0;
}

int marchSS_M2(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
    int error = 0;
    int error_byte0 = 0;
    int error_byte1 = 0;
    int error_byte2 = 0;
    int error_byte3 = 0;
    
    //March SS element M2
    _USB_CONSOLE.printf("Element M2...\r\n");
    fprintf(_FP, "Bank %lu,M2,", bankNum); //Write to results file that we are on element M2
    
    for (address = base_addr; address <= end_addr; address += stride) {
        error = 0;
        error_byte0 = 0;
        error_byte1 = 0;
        error_byte2 = 0;
        error_byte3 = 0;
        
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //w1
        value = ONE;
        _JTAG->writeMemory(address, value);
        
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //w0
        value = ZERO;
        _JTAG->writeMemory(address, value);
        
        error = error_byte3 + error_byte2 + error_byte1 + error_byte0;
        fprintf(_FP, "%d,%d,", iter*stride, error); //Log the address (within bank) and the error code (0-15).        iter++;
    }
    
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    fprintf(_FP, "\n");
    
    return 0;
}

int marchSS_M3(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
    int error = 0;
    int error_byte0 = 0;
    int error_byte1 = 0;
    int error_byte2 = 0;
    int error_byte3 = 0;
    
    //March SS element M3
    _USB_CONSOLE.printf("Element M3...\r\n");
    fprintf(_FP, "Bank %lu,M3,", bankNum); //Write to results file that we are on element M3

    for (address = end_addr; address >= base_addr && address <= end_addr; address -= stride) {
        error = 0;
        error_byte0 = 0;
        error_byte1 = 0;
        error_byte2 = 0;
        error_byte3 = 0;
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
        
        //w0
        value = ZERO;
        _JTAG->writeMemory(address, value);
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
            
        //w1
        value = ONE;
        _JTAG->writeMemory(address, value);
        
        error = error_byte3 + error_byte2 + error_byte1 + error_byte0;
        fprintf(_FP, "%d,%d,", iter*stride, error); //Log the address (within bank) and the error code (0-15).
        iter++;
    }
    
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    fprintf(_FP, "\n");
    
    return 0;
}

int marchSS_M4(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
    int error = 0;
    int error_byte0 = 0;
    int error_byte1 = 0;
    int error_byte2 = 0;
    int error_byte3 = 0;
    
    //March SS element M4
    _USB_CONSOLE.printf("Element M4...\r\n");
    fprintf(_FP, "Bank %lu,M4,", bankNum); //Write to results file that we are on element M4

    for (address = end_addr; address >= base_addr && address <= end_addr; address -= stride) {
        error = 0;
        error_byte0 = 0;
        error_byte1 = 0;
        error_byte2 = 0;
        error_byte3 = 0;
        
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //w1
        value = ONE;
        _JTAG->writeMemory(address, value);
        
        //r1
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ONE & BYTE_MASK)
            error_byte3 = ERROR_BYTE3;
            
        //w0
        value = ZERO;
        _JTAG->writeMemory(address, value);
        
        error = error_byte3 + error_byte2 + error_byte1 + error_byte0;
        fprintf(_FP, "%d,%d,", iter*stride, error); //Log the address (within bank) and the error code (0-15).
        iter++;
    }
    
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    fprintf(_FP, "\n");
    
    return 0;
}

int marchSS_M5(unsigned int bankNum, unsigned int base_addr, unsigned int end_addr, unsigned int stride) {
    int iter = 0;
    unsigned int value;
    unsigned int address;
    int error = 0;
    int error_byte0 = 0;
    int error_byte1 = 0;
    int error_byte2 = 0;
    int error_byte3 = 0;
    
    //March SS element M5
    _USB_CONSOLE.printf("Element M5...\r\n");
    fprintf(_FP, "Bank %lu,M5,", bankNum); //Write to results file that we are on element M5

    value = ZERO;
    for (address = base_addr; address <= end_addr; address += stride) {
        error = 0;
        error_byte0 = 0;
        error_byte1 = 0;
        error_byte2 = 0;
        error_byte3 = 0;
        
        //r0
        value = _JTAG->readMemory(address);
        //Compute fault code for all possible combinations of byte-wise errors in this word
        if (value >> BYTE0_SHIFT & BYTE_MASK != ZERO)
            error_byte0 = ERROR_BYTE0;
        if (value >> BYTE1_SHIFT & BYTE_MASK != ZERO)
            error_byte1 = ERROR_BYTE1;
        if (value >> BYTE2_SHIFT & BYTE_MASK != ZERO)
            error_byte2 = ERROR_BYTE2;
        if (value >> BYTE3_SHIFT & BYTE_MASK != ZERO)
            error_byte3 = ERROR_BYTE3;
        
        error = error_byte3 + error_byte2 + error_byte1 + error_byte0;
        fprintf(_FP, "%d,%d,", iter*stride, error); //Log the address (within bank) and the error code (0-15).
            
        iter++;
    }
    
    _USB_CONSOLE.printf("Finished %d iterations with stride of %d B, total space tested: %d B\r\n", iter, stride, (end_addr - base_addr)+stride);
    fprintf(_FP, "\n");
    
    return 0;
}

int doMarchSS_SRAMBank0() {  
    marchSS_M0(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    marchSS_M1(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    marchSS_M2(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    marchSS_M3(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    marchSS_M4(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    marchSS_M5(0, SRAMBANK0_BASE_ADDR, SRAMBANK0_END_ADDR, ADDR_INCR);      
    
    return  0;
}

int doMarchSS_SRAMBank1() {
    marchSS_M0(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    marchSS_M1(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    marchSS_M2(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    marchSS_M3(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    marchSS_M4(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    marchSS_M5(1, SRAMBANK1_BASE_ADDR, SRAMBANK1_END_ADDR, ADDR_INCR);      
    
    return  0;
}

//Based on Hamdioui et. al March SS 2002
int doMarchSS() {
    int retval = 0;
    _USB_CONSOLE.printf("...March SS on SRAM Bank 0...\r\n");
    retval += doMarchSS_SRAMBank0();
    _USB_CONSOLE.printf("...March SS on SRAM Bank 1...\r\n");
    retval += doMarchSS_SRAMBank1(); 
    
    return retval;
}