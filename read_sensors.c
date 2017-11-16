//-------------------------- Sensors and position -------------------------
#define SENSORS_NR  6
const unsigned int sensors[SENSORS_NR] = { A2, A3, A4, A5, A6, A7 };

//---------  Array index -------
#define RIGHT_SIDE_SENS  0
#define RIGHT_FRONT_SENS 1
#define DOHIO_LEFT_SENS  3
#define DOHIO_RIGHT_SENS 2
#define LEFT_FRONT_SENS  4
#define LEFT_SIDE_SENS   5

//===================== Read sensors  and scale ==================
void read_position(void) {
  unsigned char sens;
  unsigned int tmp_value;

  sensor_min[RIGHT_SIDE_SENS]  = analogRead(sensors[RIGHT_SIDE_SENS]) / 2;
  sensor_min[RIGHT_FRONT_SENS]  = analogRead(sensors[RIGHT_FRONT_SENS]) / 2;
  sensor_min[LEFT_FRONT_SENS]  = analogRead(sensors[LEFT_FRONT_SENS]) / 2;
  sensor_min[LEFT_SIDE_SENS]  = analogRead(sensors[LEFT_SIDE_SENS]) / 2;

  //-------------- Read Left sensors ------------
  PORTD  |= B00000100; // set OPT_ENABLE_ONE on HIGH
  delayMicroseconds(200);    // Wait for lighting
  for (sens = 0; sens < 2; sens++) {
    tmp_value = analogRead(sensors[sens]) / 2;
      if (tmp_value > sensor_min[sens])
        sensor_values[sens] = tmp_value -  sensor_min[sens];
      else if ( tmp_val == ssensor_min[sens])
        sensor_value[sens] = 1; // negative num and 0 cause issues !
      else
        sensor_values[sens] = tmp_value;
  }
  sensor_values[DOHIO_RIGHT]  = analogRead(sensors[DOHIO_RIGHT_SENS]) / 2;    // Right dohio sensor

  //-------------- Read Right sensors ------------
  PORTD  = (PORTD & B11111011) | B00001000; // set OPT_ENABLE_ONE on LOW and OPT_ENABLE_TWO on HIGH
  delayMicroseconds(200);    // Wait for lighting
  sensor_values[DOHIO_LEFT]  = analogRead(sensors[DOHIO_LEFT_SENS]) / 2;       // Left dohio sensor
  for (sens = 4; sens < SENSORS_NR; sens++) {
    tmp_value =  analogRead(sensors[sens]) / 2;
      if (tmp_value > sensor_min[sens]) 
        sensor_values[sens]  = tmp_value -  sensor_min[sens];
      else if ( tmp_val == ssensor_min[sens])
        sensor_value[sens] = 1; // negative num and 0 cause issues !
      else 
        sensor_values[sens] = tmp_value; 
  }
  PORTD &= B11110111; // set OPT_ENABLE_TWO on LOW
}
