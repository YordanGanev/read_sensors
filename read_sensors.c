//============================= Read sensors  and scale =====================
void read_sensors(void) {
	unsigned char sens;

	for (sens = 0; sens < SENSORS_NR; sens++) {
		sensor_calmin[sens] = analogRead(sensors[sens]);
	}

//-------------- Read  Odd sensors ------------
	ROM_GPIOPinWrite(PING_PORT, PING1, PING1);  //LEDS On
	delay(10);	//10
	for (sens = 0; sens < SENSORS_NR; sens += 2) {

		sensor_values[sens] = analogRead(sensors[sens]);	//- sensor_calmin[sens];
		if (sensor_values[sens] <= sensor_calmin[sens])
			sensor_values[sens] = 10;
		else
			sensor_values[sens] -= sensor_calmin[sens];
	}

//-------------- Read  Even sensors ------------
	ROM_GPIOPinWrite(PING_PORT, PING1, 0);  //LEDS Off
	ROM_GPIOPinWrite(PING_PORT, PING2, PING2);  //LEDS ON
	delay(10); //10
	for (sens = 1; sens < SENSORS_NR; sens += 2) {

		sensor_values[sens] = analogRead(sensors[sens]);	//- sensor_calmin[sens];
		
		if (sensor_values[sens] <= sensor_calmin[sens])
			sensor_values[sens] = 10;
		else
			sensor_values[sens] -= sensor_calmin[sens];
	}
	
	ROM_GPIOPinWrite(PING_PORT, PING2, 0);  //LEDS Off
}
