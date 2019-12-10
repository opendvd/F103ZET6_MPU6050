#include "global.h"
#include "mpu6050.h"

float acc[3], gyr[3], temp;
u16 dma_butter[100];
int main(void)
{
	short Accel[3], Gyro[3], Temp;
	
    //MPU6050≥ı ºªØ
	MPU6050_Init();
	
	while(1)
	{
		MPU6050ReadAcc(Accel);
		acc[0] = (float)Accel[0]/32768*2;
		acc[1] = (float)Accel[1]/32768*2;
		acc[2] = (float)Accel[2]/32768*2;
		
		MPU6050ReadGyro(Gyro);
		gyr[0] = (float)Gyro[0]/32768*2000;
		gyr[1] = (float)Gyro[1]/32768*2000;
		gyr[2] = (float)Gyro[2]/32768*2000;
		
		MPU6050_ReturnTemp(&Temp);
		temp = 36.53+((float)Temp)/340;
	}
	
}
