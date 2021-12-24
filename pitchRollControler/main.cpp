#include <iostream>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "MPU6050/MPU6050_6Axis_MotionApps_V6_12.h"

MPU6050 mpu;


bool dmpReady = false;  
uint8_t mpuIntStatus;   
uint8_t devStatus;
uint16_t packetSize;    
uint16_t fifoCount;     
uint8_t fifoBuffer[64]; 

Quaternion q;
VectorFloat gravity;
float ypr[3];           
float yaw, pitch, roll;

volatile bool mpuInterrupt = false;     
void dmpDataReady() {
    mpuInterrupt = true;
}

int main() {
    stdio_init_all();
    
    i2c_init(i2c_default, 400 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    
    gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
	while (!stdio_usb_connected()) { 
		gpio_put(PICO_DEFAULT_LED_PIN, 1);
		sleep_ms(250);
		gpio_put(PICO_DEFAULT_LED_PIN, 0);
		sleep_ms(250);
	}

    mpu.initialize();
    devStatus = mpu.dmpInitialize();
    if (devStatus == 0)  {
        mpu.setDMPEnabled(true);                
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;                        
        packetSize = mpu.dmpGetFIFOPacketSize();      
    } else {                                          
    	std::cout<<"DMP Initialization failed (code "<<devStatus<<")"<<std::endl;
        sleep_ms(2000);
    }
    yaw = 0.0;
    pitch = 0.0;
    roll = 0.0;

    while(true) {
        if (!dmpReady);                                                    
        mpuInterrupt = true;
        fifoCount = mpu.getFIFOCount();                                           
        if ((mpuIntStatus & 0x10) || fifoCount == 1024){
            mpu.resetFIFO();                                                      
            std::cout<<"FIFO overflow!"<<std::endl;
        } else if (mpuIntStatus & 0x01) {    
            while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();        
            mpu.getFIFOBytes(fifoBuffer, packetSize);                             
            fifoCount -= packetSize;                                           
			mpu.dmpGetQuaternion(&q, fifoBuffer);
			mpu.dmpGetGravity(&gravity, &q);
			mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
			pitch = ypr[1] * 180 / PI;
			roll = ypr[2] * 180 / PI;
			std::cout<<pitch<<" "<<roll<<std::endl;
        }
    }

    return 0;
}
