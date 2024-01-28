#ifndef CONSTANTESENTRASALIDA_H
#define CONSTANTESENTRASALIDA_H

const int tach = 13; // tacometro
const int inyector1 = 12; // inyector 1
const int inyector2 = 11; // inyector 2
const int inyector3 = 10; // inyector 3
const int inyector4 = 9; // inyector 4
const int fanRelay = 8; // señal para activar FAN Relay
const int asdRelay = 7; // señal para activar ASD Relay
const int inyector5 = 6; // inyector 5
const int inyector6 = 5; // inyector 6
const int sensorcmp = 4; // señal del sensor de Leva
const int inyector7 = 3; // inyector 7
const int sensorckp = 2; // señal del sensor de Sigueñal
const int sensorO2 = A0; // señal del sensor de Oxígeno
const int sensorCTL = A1; // señal del sensor CTL
const int sensormap = A2; // señal del sensor MAP o TPS

char terminalRead;

bool tachState = LOW;
bool fanRelayState = LOW;
bool asdRelayState = LOW;
bool inyector1State = LOW;
bool inyector2State = LOW;
bool inyector3State = LOW;
bool inyector4State = LOW;
bool inyector5State = LOW;
bool inyector6State = LOW;
bool inyector7State = LOW;


bool btn_op = true;
bool btn2_op = true;
int counts = 0;
int btn2_counter = 0;
int btn1_counter = 0;
bool programStarted = false;
bool programOn = true;
int prev_sensorckp_state = HIGH;

void setup();
void loop();

#endif
