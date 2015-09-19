/* DELAY.H file
 * Date:2015.6.9
 * Auth:Jason.H_{
 */

#ifndef __STATUS_H
#define __STATUS_H

typedef enum {
        SMART_ON = 0x00,
        SMART_OFF = 0x01
}SmartCmd_t;

typedef enum
{
	MOTOR_HALT = 0,
	MOTOR_SLEEP = 1,
	MOTOR_LOW = 2,
	MOTOR_MIDIUM = 3,
	MOTOR_HIGH = 4,
	MOTOR_FLY = 5
}motorPosition_t;

enum {
	MODE_CLOSE = 0,
	MODE_SMART = 1,
	MODE_SLEEP = 2,
    MODE_FLY = 3,
};

typedef struct _device_status_t{
    unsigned char mode;
    unsigned char position;    
}device_status_t;

typedef struct _sensor_status_t{
    unsigned char     air_class;
    unsigned short    dust_value;
}sensor_status_t;

typedef struct _context_status_t{ 
    device_status_t   deviceStatus;
    sensor_status_t   sensorStatus;   
}context_status_t;

extern context_status_t *status;

unsigned char Status_Init(void);
void status_tick(void);
void statusSmartMode(SmartCmd_t cmd);

#endif
