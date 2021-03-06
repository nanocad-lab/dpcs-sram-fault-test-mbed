/* Author: Mark Gottscho
 * UCLA NanoCAD Lab
 * Based on code by Liangzhen Lai
 * For the mbed microcontroller, NSF Variability Expedition Red Mini Cooper board
 * SRAM Fault Map program
 */ 

#include "mbed.h"
#include "power_up.h"
#include "scan.h"
#include "JTAG.h"
#include "march.h"

using namespace std;

Serial _USB_CONSOLE(USBTX, USBRX);
JTAG* _JTAG;
FILE* _FP;

/*int doDroopTest(double nominalVoltage, double droopVoltage) {
    fprintf(_FP, "Droop Voltage %f,,Word Number,Fault Code\n", droopVoltage);
      
    _USB_CONSOLE.printf("-----------------------------------------------------------------\r\n");
    _USB_CONSOLE.printf("------------- BEGINNING MARCH TESTS @ %0.02f V (droop) ----------\r\n", droopVoltage);
    _USB_CONSOLE.printf("-----------------------------------------------------------------\r\n");
    doMarchSS_droopVoltage(nominalVoltage, droopVoltage);
    _USB_CONSOLE.printf("----------------------------------------------------------------\r\n");
    _USB_CONSOLE.printf("---------- TEST SEQUENCE COMPLETE @ %0.02f V (droop) -----------\r\n", droopVoltage);
    _USB_CONSOLE.printf("----------------------------------------------------------------\r\n");
    
    fprintf(_FP, "\n");
    
    return 0;
}*/

/*int voltageDroopMarchTestRoutine(double nominalVoltage, double droopVoltageMin, double droopVoltageMax, double voltageStep) {   
    int iter = 0;
    int test_return = 0;
    
    for (double voltage = droopVoltageMax; voltage >= droopVoltageMin; voltage -= voltageStep) {
        //Init file to write to
        _USB_CONSOLE.printf("** Opening data file...\r\n");
        
        if (iter == 0)
            _FP = fopen("/local/drpmt0.csv", "w");
        else if (iter == 1)
            _FP = fopen("/local/drpmt1.csv", "w");
        else if (iter == 2)
            _FP = fopen("/local/drpmt2.csv", "w");
        else if (iter == 3)
            _FP = fopen("/local/drpmt3.csv", "w");
        else if (iter == 4)
            _FP = fopen("/local/drpmt4.csv", "w");
        else if (iter == 5)
            _FP = fopen("/local/drpmt5.csv", "w");
        else if (iter == 6)
            _FP = fopen("/local/drpmt6.csv", "w");
        else if (iter == 7)
            _FP = fopen("/local/drpmt7.csv", "w");
        else if (iter == 8)
            _FP = fopen("/local/drpmt8.csv", "w");
        else if (iter == 9)
            _FP = fopen("/local/drpmt9.csv", "w");
        else if (iter == 10)
            _FP = fopen("/local/drpmt10.csv", "w");
        else if (iter == 11)
            _FP = fopen("/local/drpmt11.csv", "w");
        else if (iter == 12)
            _FP = fopen("/local/drpmt12.csv", "w");
        else if (iter == 13)
            _FP = fopen("/local/drpmt13.csv", "w");
        else if (iter == 14)
            _FP = fopen("/local/drpmt14.csv", "w");
        else if (iter == 15)
            _FP = fopen("/local/drpmt15.csv", "w");
        else if (iter == 16)
            _FP = fopen("/local/drpmt16.csv", "w");
        else if (iter == 17)
            _FP = fopen("/local/drpmt17.csv", "w");
        else if (iter == 18)
            _FP = fopen("/local/drpmt18.csv", "w");
        else if (iter == 19)
            _FP = fopen("/local/drpmt19.csv", "w");
        else if (iter == 20)
            _FP = fopen("/local/drpmt20.csv", "w");
        else
            _FP = fopen("/local/drpmtUNK.csv", "w");
            
        if (_FP == NULL) {
            _USB_CONSOLE.printf("** !!! ERROR: Couldn't open data file, iter %d\r\n", iter);
            return 1;
        }
        
        test_return = doDroopTest(nominalVoltage, voltage);
  
        //Close file for data
        if (_FP)
            fclose(_FP);
            
        if (test_return == 1) {
            _USB_CONSOLE.printf("!!! ERROR: Test failed to complete at SRAM droop voltage of %0.02f V, terminating.\r\n", voltage);
            return 1;
        }
        
        iter++;
    }
   
    return 0;
}*/

int standardMarchTests(double minVoltage, double maxVoltage, double voltageStep, unsigned int lowAddr, unsigned int highAddr, int bankNum) {
    int iter = 0;
    int test_return = 0;
    
    for (double voltage = maxVoltage; voltage >= minVoltage; voltage -= voltageStep) {
        //Init file to write to
        _USB_CONSOLE.printf("** Opening data file...\r\n");
        if (iter == 0)
            _FP = fopen("/local/data0.csv", "w");
        else if (iter == 1)
            _FP = fopen("/local/data1.csv", "w");
        else if (iter == 2)
            _FP = fopen("/local/data2.csv", "w");
        else if (iter == 3)
            _FP = fopen("/local/data3.csv", "w");
        else if (iter == 4)
            _FP = fopen("/local/data4.csv", "w");
        else if (iter == 5)
            _FP = fopen("/local/data5.csv", "w");
        else if (iter == 6)
            _FP = fopen("/local/data6.csv", "w");
        else if (iter == 7)
            _FP = fopen("/local/data7.csv", "w");
        else if (iter == 8)
            _FP = fopen("/local/data8.csv", "w");
        else if (iter == 9)
            _FP = fopen("/local/data9.csv", "w");
        else if (iter == 10)
            _FP = fopen("/local/data10.csv", "w");
        else if (iter == 11)
            _FP = fopen("/local/data11.csv", "w");
        else if (iter == 12)
            _FP = fopen("/local/data12.csv", "w");
        else if (iter == 13)
            _FP = fopen("/local/data13.csv", "w");
        else if (iter == 14)
            _FP = fopen("/local/data14.csv", "w");
        else if (iter == 15)
            _FP = fopen("/local/data15.csv", "w");
        else if (iter == 16)
            _FP = fopen("/local/data16.csv", "w");
        else if (iter == 17)
            _FP = fopen("/local/data17.csv", "w");
        else if (iter == 18)
            _FP = fopen("/local/data18.csv", "w");
        else if (iter == 19)
            _FP = fopen("/local/data19.csv", "w");
        else if (iter == 20)
            _FP = fopen("/local/data20.csv", "w");
        else
            _FP = fopen("/local/dataUNK.csv", "w");
            
        if (_FP == NULL) {
            _USB_CONSOLE.printf("** !!! ERROR: Couldn't open data file, iter %d\r\n", iter);
            return 1;
        }
        
        _USB_CONSOLE.printf("---------> Setting SRAM voltage: %0.03f V <--------\r\n", voltage);
        adjustSRAMVoltage(voltage);
        _USB_CONSOLE.printf("---------> Low addr:\t0x%08X <--------\r\n", lowAddr);
        _USB_CONSOLE.printf("---------> High addr:\t0x%08X <--------\r\n", highAddr);
        _USB_CONSOLE.printf("---------> Bank num:\t%d <--------\r\n", bankNum);
    
        
        fprintf(_FP, "Voltage %f,,Effective Byte Address,Fault Code\n", voltage);
           
        _USB_CONSOLE.printf("-----------------------------------------------------\r\n");
        _USB_CONSOLE.printf("---------- BEGINNING MARCH TESTS @ %0.03f V ---------\r\n", voltage);
        _USB_CONSOLE.printf("-----------------------------------------------------\r\n");
        test_return = doMarchSS(lowAddr, highAddr, bankNum);
        _USB_CONSOLE.printf("-----------------------------------------------------\r\n");
        _USB_CONSOLE.printf("---------- COMPLETED MARCH TESTS @ %0.03f V ---------\r\n", voltage);
        _USB_CONSOLE.printf("-----------------------------------------------------\r\n");
        
        fprintf(_FP, "\n");
        
        
        //Close file for data
        if (_FP)
            fclose(_FP);
            
        if (test_return == 1) {
            _USB_CONSOLE.printf("!!! ERROR: Test failed to complete at SRAM voltage of %0.02f V, terminating.\r\n", voltage);
            return 1;
        }
        
        iter++;
    }

    return 0;
}


int main()
{    
    DigitalOut FINISH_FLAG (LED3);
    DigitalOut RESET (p21); 
    
    double duty_cycle = 0.5;
    double voltage = 1;
    PLL clk;
    
    unsigned int value;
    unsigned int address;
    
    int retval = 0;
    
    double vmin = 1;
    double vmax = 1;
    double vstep = 0;
    unsigned int lowAddr = SRAMBANK0_BASE_ADDR;
    unsigned int highAddr = SRAMBANK0_END_ADDR;
    int bankNum = 0;
    
          
    // power up chip with voltage
    _USB_CONSOLE.printf("** Resetting power...\r\n");
    powerReset();
    _USB_CONSOLE.printf("** Powering up test chip...\r\n");
    _USB_CONSOLE.printf("** Setting global voltages: %f V\r\n", voltage);
    powerUp(voltage);
    
    _USB_CONSOLE.printf("** Resetting test chip...\r\n");
    RESET = 0;
    wait(1);
    RESET = 1;

    // set the clock frequency to 20 MHz
    _USB_CONSOLE.printf("** Setting test chip clock frequency to 20 MHz\r\n");
    clk.setPLL(20);

    // Init _JTAG and halt processor
    _USB_CONSOLE.printf("** Initializing JTAG...\r\n");
    _JTAG = new JTAG;
    _JTAG->DAP_enable();
    address = 0xE000EDF0;
    value = 0xA05F0003;
    _JTAG->writeMemory(address, value);
    value = _JTAG->readMemory(address);

    _USB_CONSOLE.printf("** Halting processor...\r\n");   
    if (value&0x00000003 != 0x00000003) { //Check to make sure CPU halted
        _USB_CONSOLE.printf("** !!! ERROR: Processor FAILED TO HALT!\r\n");
        return 1;
    }
        
    //Set SRAM bank 0 offset address
    _USB_CONSOLE.printf("** Setting SRAM bank 0 offset address to 0x%X\r\n", 0x0);
    address = 0x44000008;
    value = 1; //This sets the offset address to 0x000000000
    _JTAG->writeMemory(address, value);
         
    _USB_CONSOLE.printf("** Init success!\r\n");
    
    
    ////////////////////////////////
    _USB_CONSOLE.printf("****************************************************************\r\n");
    _USB_CONSOLE.printf("****************** Starting SRAM_fault_map *********************\r\n");
    _USB_CONSOLE.printf("******************** Author: Mark Gottscho *********************\r\n");
    _USB_CONSOLE.printf("*************** Based on code by Liangzhen Lai *****************\r\n");
    _USB_CONSOLE.printf("************* UCLA NanoCAD Lab, www.nanocad.ee.ucla.edu ********\r\n");
    _USB_CONSOLE.printf("****************************************************************\r\n\r\n");
    
    vmin = 0.449;
    vmax = 0.700;
    vstep = 0.025;
    lowAddr = SRAMBANK0_BASE_ADDR;
    highAddr = SRAMBANK0_BASE_ADDR+K1_INC;
    //highAddr = SRAMBANK0_BASE_ADDR+K8_INC; //FIXME: Is K1_INC or K8_INC the correct one?
    bankNum = 0;
    
    retval = standardMarchTests(vmin, vmax, vstep, lowAddr, highAddr, bankNum);
 
    if (retval != 0)
        _USB_CONSOLE.printf("** Testing failed!\r\n");
        
    _USB_CONSOLE.printf("** Powering down test chip...\r\n");
    powerDown();
    
    _USB_CONSOLE.printf("** Done!\r\n");
    while(1) {
        FINISH_FLAG = !FINISH_FLAG;
        wait(1);
    }
    return 0;
}
