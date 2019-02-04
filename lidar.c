#include "stdio.h"
#include <lidar.h>

/*
    Funktion zum Initialisieren des Lidar-Sensors.
*/
void InitLidar(uint8 mode) {
    uint8 value_SIG_COUNT_VAL = 0x00;
    uint8 value_ACQ_CONFIG_REG = 0x00;
    uint8 value_THRESHOLD_BYPASS = 0x00;
    
    switch(mode) {
        case MODE_SHORT_RANGE:
            value_SIG_COUNT_VAL = 0x1d;
            value_ACQ_CONFIG_REG = 0x08;
            value_THRESHOLD_BYPASS = 0x00;
            break;
        case MODE_MEDIUM_RANGE:
            value_SIG_COUNT_VAL = 0x80;
            value_ACQ_CONFIG_REG = 0x00;
            value_THRESHOLD_BYPASS = 0x00;
            break;
        case MODE_MAX_RANGE:
            value_SIG_COUNT_VAL = 0xff;
            value_ACQ_CONFIG_REG = 0x08;
            value_THRESHOLD_BYPASS = 0x00;
            break;
        default:
            break;
    }
    
    WriteRegLidar(SIG_COUNT_VAL, value_SIG_COUNT_VAL);
    WriteRegLidar(ACQ_CONFIG_REG, value_ACQ_CONFIG_REG);
    WriteRegLidar(THRESHOLD_BYPASS, value_THRESHOLD_BYPASS); 
}

/*
    Sendet reset command (LIDAR braucht 22 ms dafür)
*/
void ResetLidar() {
    WriteRegLidar(ACQ_COMMAND, 0x00);
    CyDelay(30);
}

/*
    Fkt zum Auslesen der gemessenen Distanz
*/
uint16 ReadDistLidar() {
    uint16 distance = 0x0000;
    uint8 highByte = 0x00;
    uint8 lowByte = 0x00;
    
    /* 1. set bias correction */
    WriteRegLidar(ACQ_COMMAND, 0x04);
    CyDelay(20);
    
    /* 2. read Distance */
    i2c_I2CMasterClearStatus();
    
    i2c_I2CMasterSendStart(LIDAR_ADDR, i2c_I2C_WRITE_XFER_MODE, 50);
    i2c_I2CMasterWriteByte(FULL_DELAY, 50);
    i2c_I2CMasterSendStop(50);
    
    i2c_I2CMasterSendStart(LIDAR_ADDR, i2c_I2C_READ_XFER_MODE, 50);
    i2c_I2CMasterReadByte(i2c_I2C_ACK_DATA, &lowByte, 50);
    i2c_I2CMasterReadByte(i2c_I2C_ACK_DATA, &highByte, 50);
    i2c_I2CMasterSendStop(50);
    
    distance = (highByte << 8) | lowByte;
    
    return distance;
}

uint8 ReadRegLidar(uint8 regAddr) {

    uint8 ReadByte = 0x00;
    
    CyDelay(10);
    i2c_I2CMasterClearStatus();
    
    i2c_I2CMasterSendStart(LIDAR_ADDR, i2c_I2C_WRITE_XFER_MODE, 50);
    i2c_I2CMasterWriteByte(regAddr, 50);
    i2c_I2CMasterSendStop(50);
    
    i2c_I2CMasterSendStart(LIDAR_ADDR, i2c_I2C_READ_XFER_MODE, 50);
    i2c_I2CMasterReadByte(i2c_I2C_ACK_DATA, &ReadByte, 50);
    i2c_I2CMasterSendStop(50);
    
    return ReadByte;
}

void WriteRegLidar(uint8 regAddr, uint8 value) {

    CyDelay(10);
    i2c_I2CMasterClearStatus();
    
    i2c_I2CMasterSendStart(LIDAR_ADDR, i2c_I2C_WRITE_XFER_MODE, 50);
    i2c_I2CMasterWriteByte(regAddr, 50);
    i2c_I2CMasterWriteByte(value, 50);
    i2c_I2CMasterSendStop(50);

}

/* [] END OF FILE */
