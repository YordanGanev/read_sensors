typedef enum {
  KP , KD, KQ, MAX_SPEED, START_SPEED, SPEED_DOWN, SLOWDOWN_LEVEL
} E_MOVEMENT_DEFINITIONS;


                                    //  kp,   kd,   kq,   max, start, down, down_level,
const unsigned int settings[11][7] = {  { 45,   60,   25,   155,  50,   135,  60},
                                        { 45,   58,   25,   155,  50,   135,  60},
                                        { 45,   56,   25,   155,  50,   135,  60},
                                        { 45,   54,   25,   155,  50,   135,  60},
                                        { 45,   52,   25,   155,  50,   135,  60},
                                        { 45,   50,   25,   155,  50,   135,  60},
                                        { 45,   48,   25,   155,  50,   135,  60},
                                        { 45,   46,   25,   155,  50,   135,  60},
                                        { 45,   44,   25,   155,  50,   135,  60},
                                        { 45,   42,   25,   155,  50,   135,  60},
                                        { 45,   42,   25,   155,  50,   135,  60} };
                                                  
#define UNSELECTED sizeof(settings) / sizeof(settings)[0]


void setup() {
rule = 0; 
  while (!ir_data_get && (digitalRead (BUTT1) == HIGH) ) {
    if (ir_data_get) {
      ir_data_get = 0;
      switch(ir_data.command) {
        case KEY_0: rule = 0;   break;
        case KEY_1: rule = 1;   break;
        case KEY_2: rule = 2;   break;
        case KEY_3: rule = 3;   break;
        case KEY_4: rule = 4;   break;
        case KEY_5: rule = 5;   break;
        case KEY_6: rule = 6;   break;
        case KEY_7: rule = 7;   break;
        case KEY_8: rule = 8;   break;
        case KEY_9: rule = 9;   break;
        default: 
          rule = UNSELECTED; 
          break;
      }
      
      if (rule != UNSELECTED) 
        break;
    }
  }
//  Serial.println(rule);
  speed = settings[rule][START_SPEED];
  turn_speed_high = settings[rule][MAX_SPEED] * 0.7;
  slow_speed = settings[rule][MAX_SPEED] * 0.3;
}

void loop() {
//-------------PD закон за управление---------------
      quadratic = ( error[0] * error[0] * settings[rule][KQ] ) / 10000;
      if (error < 0)
        error[0] -= quadr;
      else
        error[0] += quadr;
        
      proportional = (settings[rule][KP] * error[0]) / 100;
      
      differential = (settings[rule][KD] * (error[0] - error[3])) / 10;
      
      correction = proportional + differential;
      
      error[3] = error[2];
      error[2] = error[1];
      error[1] = error[0];
}
