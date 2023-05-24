#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    potentPlaceholder, sensorPotentiometer)
#pragma config(Sensor, in3,    gyroPlaceholder, sensorGyro)
#pragma config(Sensor, in5,    expanderVoltage, sensorAnalog)
#pragma config(Sensor, dgtl2,  encoderPlaceholder, sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ultPlaceholder, sensorSONAR_inch)
#pragma config(Sensor, dgtl8,  jumperPlaceholder, sensorTouch)
#pragma config(Sensor, I2C_2,  encoderPlaceholder, sensorQuadEncoderOnI2CPort,    , AutoAssign )
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Make sure to go to Window>Menu>Super User to view every option in the Motor and Sensor Setup

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

#include "lcdLib.c"

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// Start of functions (Placeholders used)

void ArmUp()
{
	motor[armYRight] = 127;
	motor[armYLeft] = 127;
	motor[armInnerRight] = 127;
	motor[armInnerLeft] = 127;
}

void ArmStop()
{
	motor[armYRight] = 0;
	motor[armYLeft] = 0;
	motor[armInnerRight] = 0;
	motor[armInnerLeft] = 0;
}

void ArmDown()
{
	motor[armYRight] = -127;
	motor[armYLeft] = -127;
	motor[armInnerRight] = -127;
	motor[armInnerLeft] = -127;
}

void DriveForward()
{
	motor[motorBackLeft] = 127;
	motor[motorBackRight] = 100;
	motor[motorFrontLeft] = 100;
	motor[motorFrontRight] = 100;
}

void DriveForwardSlow()
{
	motor[motorBackLeft] = 127/2;
	motor[motorBackRight] = 100/2;
	motor[motorFrontLeft] = 100/2;
	motor[motorFrontRight] = 100/2;
}

void DriveBackwards()
{
	motor[motorBackLeft] = -127;
	motor[motorBackRight] = -127;
	motor[motorFrontLeft] = -127;
	motor[motorFrontRight] = -127;
}

void DriveBackwardsSlow()
{
	motor[motorBackLeft] = -127/2;
	motor[motorBackRight] = -100/2;
	motor[motorFrontLeft] = -100/2;
	motor[motorFrontRight] = -100/2;
}

void TurnPointLeft()
{
	motor[motorBackLeft] = -127/1.25;
	motor[motorBackRight] = 127/1.25;
	motor[motorFrontLeft] = -127/1.25;
	motor[motorFrontRight] = 127/1.25;
}

void TurnPointRight()
{
	motor[motorBackLeft] = 127/1.25;
	motor[motorBackRight] = -127/1.25;
	motor[motorFrontLeft] = 127/1.25;
	motor[motorFrontRight] = -127/1.25;
}

void TurnSwingRight()
{
	motor[motorBackLeft] = 127/1.25;
	motor[motorBackRight] = 0;
	motor[motorFrontLeft] = 127/1.25;
	motor[motorFrontRight] = 0;
}

void TurnSwingLeft()
{
	motor[motorBackLeft] = 0;
	motor[motorBackRight] = 127/1.25;
	motor[motorFrontLeft] = 0;
	motor[motorFrontRight] = 127/1.25;
}

void DriveStop()
{
	motor[motorBackLeft] = 0;
	motor[motorBackRight] = 0;
	motor[motorFrontLeft] = 0;
	motor[motorFrontRight] = 0;
}

void ClawOpen()
{
	motor[motorClawRight] = -127;
	motor[motorClawLeft] = -127;
}

void ClawStop()
{
	motor[motorClawRight] = 0;
	motor[motorClawLeft] = 0;
}

void ClawClose()
{
	motor[motorClawRight] = 127;
	motor[motorClawLeft] = 127;
}

// Start of Tasks

task BatteryLCD() //Aka the second LDC Screen
{
	// Initalizes the second LCD on UART1
	vexLcdInit(UART1);
	// Backlight Control
	vexLcdBacklight(1);

	string VoltLn1;
	string VoltLn2;

	while(true)
	{

		sprintf(VoltLn1, "MBa %1.1f EBa %1.1f", nAvgBatteryLevel/1000, (SensorValue[in5]*(5.48/184.7)/10);
		sprintf(VoltLn2, "BBa %1.1f", BackupBatteryLevel/1000);

		vexLcdSet(0, VoltLn1);
		vexLcdSet(1, VoltLn2);

	}
}

task DriveControl() // Drive Control
{
	while(true)
	{
		motor[motorFrontRight] = vexRT[Ch3] - vexRT[Ch1];
		motor[motorBackRight] =  vexRT[Ch3] - vexRT[Ch1];
		motor[motorFrontLeft] = vexRT[Ch3] + vexRT[Ch1];
		motor[motorBackLeft] =  vexRT[Ch3] + vexRT[Ch1];
	}
}

task SoundControl()
{
	while(1 == 1)
	{

		switch(SoundIndicate)
		{
		case 1:
			SoundIndicate = 0;
			break;

		case 2:
			SoundIndicate = 0;
			break;

		case 3:
			SoundIndicate = 0;
			break;

		case 4:
			SoundIndicate = 0;
			break;
		}

		EndTimeSlice();

	}
}

void sensorInit() // The function for initalizing the gyroscope, includes all the waits and etc.
{
	//Gyroscope in analog port 1
	SensorType[gyro] = sensorNone;
	wait1Msec(250);
	SensorType[gyro] = sensorGyro;
	wait1Msec(2550);
	playTone(440,25);
}

// This is where the LCD Screen code is located.

int autonSelect = 1; //Default Autonomous

void pre_auton() // LCD Screen Code
{
	bStopTasksBetweenModes = true;
	bDisplayCompetitionStatusOnLcd = false;

	int countMin = 0;
	int countMax = 6;
	int counter = countMin;
	string str[7] = {"Pgrm1","Pgrm2","Pgrm3","Pgrm4","Pgrm5","Pgrm6","Pgrm7"}; //Program Names
	bLCDBacklight = true;
	bStopTasksBetweenModes = true;
	bDisplayCompetitionStatusOnLcd = false;

	startTask(BatteryLCD);

	while(bIfiRobotDisabled == true)
	{

		if(nLCDButtons == 1)
		{
			if(counter == countMin)
			{
				counter = countMax;
			}

			else
			{
				counter--;
			}

			clearLCDLine(0);
			clearLCDLine(1);
			wait1Msec(250);
		}

		else if(nLCDButtons == 4)
		{
			if(counter == countMax)
			{
				counter = countMin;
			}

			else
			{
				counter++;
			}

			clearLCDLine(0);
			clearLCDLine(1);
			wait1Msec(250);
		}

		else if(nLCDButtons == 2)
		{
			clearLCDLine(0);
			clearLCDLine(1);
			if(counter != countMin) autonSelect = counter;

			else sensorInit();

			wait1Msec(250);
			displayLCDCenteredString(0,str[counter]);
			displayLCDCenteredString(1,"Selected!");
			wait1Msec(400);
			clearLCDLine(0);
			clearLCDLine(1);
			wait1Msec(250);
		}

		else
		{
			displayLCDCenteredString(0,str[counter]);
			displayLCDCenteredString(1,"<    Select    >");
		}

	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Tasks                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task autonomous()
{

	startTask(BatteryLCD);

	switch(autonSelect)
	{

	case 1: //Program Option 1

		wait1Msec(true);

		break;

	case 2: //Program Option 2

		wait1Msec(true);

		break;

	case 3: //Program Option 3

		wait1Msec(true);

		break;

	case 4: //Program Option 4

		wait1Msec(true);

		break;

	case 5: //Program Option 5

		wait1Msec(true);

		break;

	case 6: //Program Option 6

		wait1Msec(true);

		break;

	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	// User control code here, inside the loop

	startTask(DriveControl);
	startTask(BatteryLCD);

	while(true)
	{
		wait1Msec(1000);
	}
}
