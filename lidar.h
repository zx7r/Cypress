#include "project.h"

/* LIDAR Slave-Address*/
#define LIDAR_ADDR          (0x62)
/* LIDAR Registers*/
#define ACQ_COMMAND         (0x00)
#define STATUS              (0x01)
#define SIG_COUNT_VAL       (0x02)
#define ACQ_CONFIG_REG      (0x04)
#define FULL_DELAY_HIGH     (0x0f)
#define FULL_DELAY_LOW      (0x10)
#define THRESHOLD_BYPASS    (0x1c)
#define FULL_DELAY          (0x8f)

/* different modes */
#define MODE_SHORT_RANGE    (0x02)
#define MODE_MEDIUM_RANGE   (0x03)
#define MODE_MAX_RANGE      (0x04)

// Fkt zum Initialisieren des Lidar-Sensors
void InitLidar(uint8 mode);
// Fkt zum Resetten des Lidar-Sensors
void ResetLidar();
// Fkt zum Auslesen der gemessenen Distanz
uint16 ReadDistLidar();

// Lidar-spezifische I2C-Funktionen
uint8 ReadRegLidar(uint8 regAddr);
void WriteRegLidar(uint8 regAddr, uint8 value);

/* [] END OF FILE */
