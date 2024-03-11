#include "constantesentradasalida.h"
#include "rpm.h"
#include "anchodepulso.h"


// Variable para almacenar el estado de la mezcla rica
bool mezclaRica = false;
const long interval = 1500; // intervalo de tiempo que dura el asdRelay encendido una ves que verifica el pulso del sensorckp
unsigned long previousMillis = 0;
int numCilindros = 6; // Número de cilindros del motor
int numDientesVolante = 6; // Número de dientes del volante o del distribuidor / 2, que corresponden a una vuelta del cigüeñal
int numInyectoresActivos = 2; // Número inyectores que estaran activos
float voltageCTL = 0.0;
float temperature = 0.0;
const float setTemp = 70.0; // Temperatura deseada en grados Celsius para ativar relay del Fan

// Variable para activar el tiempo de impresion de cadena de texto
const unsigned long vueltasMotorParaImprimir = 100; // Número de vueltas del motor para imprimir cadena de texto
volatile unsigned long vueltasMotor = 0;
int prevRpm = 0.0;

// Variable para activar modo prueba remota
bool modoPrueba = false; 

// Variable global para activar o desactivar el uso del sensor de leva 1 activa u 0 desactiva
int usarSensorLeva = 0; // Puedes cambiar este valor según tus necesidades

// Variable global para activar o desactivar manualmente el uso del sensor de oxígeno 1 activa u 0 desactiva
extern int usarSensorO2 = 1;


void setup()
{

    Serial.begin(9600); // Inicializar el puerto serial
    Serial.println("Biemvenido al sistema EFI secuencial programable de SpeedNeo V1, version del software 1.3.1");
    
    pinMode(tach, OUTPUT);
    pinMode(asdRelay, OUTPUT);
    pinMode(fanRelay, OUTPUT);
    pinMode(inyector1, OUTPUT);
    pinMode(inyector2, OUTPUT);
    pinMode(inyector3, OUTPUT);
    pinMode(inyector4, OUTPUT);
    pinMode(inyector5, OUTPUT);
    pinMode(inyector6, OUTPUT);
    pinMode(inyector7, OUTPUT);
    
    attachInterrupt(digitalPinToInterrupt(sensorckp), updateRPM, FALLING);

    digitalWrite(tach, LOW); // solo para establecer condicion de arranque
    digitalWrite(asdRelay, HIGH); // solo para establecer condicion de arranque
    digitalWrite(fanRelay, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector1, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector2, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector3, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector4, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector5, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector6, LOW); // solo para establecer condicion de arranque
    digitalWrite(inyector7, LOW); // solo para establecer condicion de arranque

    digitalWrite(tach, tachState);
    digitalWrite(asdRelay, asdRelayState);
    digitalWrite(fanRelay, fanRelayState);
    digitalWrite(inyector1, inyector1State);
    digitalWrite(inyector2, inyector2State);
    digitalWrite(inyector3, inyector3State);
    digitalWrite(inyector4, inyector4State);
    digitalWrite(inyector5, inyector5State);
    digitalWrite(inyector6, inyector6State);
    digitalWrite(inyector7, inyector7State);
 }

void loop()

{
  // Leer desde el puerto serial
  if (Serial.available() > 0) {
    char c = Serial.read();

    // Cambiar al modo de prueba
    if (c == 'p') {
      modoPrueba = true;
      Serial.println("Modo de prueba activado");
    }

    // Cambiar al modo de inyección
    else if (c == 'x') {
      modoPrueba = false;
      Serial.println("Modo de inyección activado");
    }
  }

  // Comportamiento para el modo de prueba
  if (modoPrueba) {
    prueba_remota();
  }

  // Comportamiento para el modo de inyección
  else {
    inyeccion(); // Asegúrate de tener una función llamada 'inyeccion'
  }
}
void updateRPM()
{
  // CALCULO DE RPM BASADO EN LOS DIENTES DEL VOLANTE O DISTRIBUIDOR
    unsigned long currentTime = micros(); // Obtiene el tiempo actual en microsegundos
  // Calcula las RPM: (60 millones de microsegundos por minuto / número de dientes) / diferencia de tiempo entre pulsos
    rpm = (60000000 / numDientesVolante) / (currentTime - prevTime); 
    prevTime = lastTime; // Actualiza el tiempo previo al último tiempo registrado
    lastTime = currentTime; // Actualiza el último tiempo registrado al tiempo actual
    vueltasMotor++; // Incrementa las vueltas del motor
}

void prueba_remota()
{
  // CONTROL POR BLUETO0T PARA SPEEDNEO V1 LA CUAL COMPRUEBA TODAS LAS SALIDAS DE LA PLACA POR MEDIO REMOTO

   if (asdRelayState == HIGH) {
    digitalWrite(asdRelay, HIGH); // Encender el inyector
    delay(2000); // Esperar 10 ms
    digitalWrite(asdRelay, LOW); // Apagar el inyector
    delay(1000); // Esperar 20 ms
  } else {
    digitalWrite(asdRelay, LOW); // Apagar el inyector
  }
  
     if (fanRelayState == HIGH) {
    digitalWrite(fanRelay, HIGH); // Encender el inyector
    delay(5000); // Esperar 10 ms
    digitalWrite(fanRelay, LOW); // Apagar el inyector
    delay(0); // Esperar 20 ms
  } else {
    digitalWrite(fanRelay, LOW); // Apagar el inyector
  }

    if (tachState == HIGH) {
    digitalWrite(tach, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(tach, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(tach, LOW); // Apagar el inyector
  }

  if (inyector1State == HIGH) {
    digitalWrite(inyector1, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector1, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector1, LOW); // Apagar el inyector
  }

    if (inyector2State == HIGH) {
    digitalWrite(inyector2, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector2, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector2, LOW); // Apagar el inyector
  }
  
      if (inyector3State == HIGH) {
    digitalWrite(inyector3, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector3, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector3, LOW); // Apagar el inyector
  }

      if (inyector4State == HIGH) {
    digitalWrite(inyector4, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector4, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector4, LOW); // Apagar el inyector
  }

      if (inyector5State == HIGH) {
    digitalWrite(inyector5, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector5, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector5, LOW); // Apagar el inyector
  }

      if (inyector6State == HIGH) {
    digitalWrite(inyector6, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector6, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector6, LOW); // Apagar el inyector
  }

      if (inyector7State == HIGH) {
    digitalWrite(inyector7, HIGH); // Encender el inyector
    delay(10); // Esperar 10 ms
    digitalWrite(inyector7, LOW); // Apagar el inyector
    delay(250); // Esperar 20 ms
  } else {
    digitalWrite(inyector7, LOW); // Apagar el inyector
  }

  if (Serial.available() > 0) {
    terminalRead = Serial.read();
//........................................................................
    if (terminalRead == '1') {
      asdRelayState = HIGH;
      Serial.println("asdRelay(1-a) on"); 
    }

    if (terminalRead == 'a') {
      asdRelayState = LOW;
      Serial.println("asdRelay (a) off");
    }
//........................................................................
    if (terminalRead == '2') {
      fanRelayState = HIGH;
      Serial.println("fanRelay (2-b) on");
    }

    if (terminalRead == 'b') {
      fanRelayState = LOW;
      Serial.println("fanRelay (b) off");
    }
//.......................................................................
    if (terminalRead == '3') {
      inyector1State = HIGH;
      Serial.println("inyector1 (3-c) on"); 
    }

    if (terminalRead == 'c') {
      inyector1State = LOW;
      Serial.println("inyector1 (c) off"); 
    }
//........................................................................
    if (terminalRead == '4') {
      inyector2State = HIGH;
      Serial.println("inyector2 (4-d) on");
    }

    if (terminalRead == 'd') {
      inyector2State = LOW;
      Serial.println("inyector2 (d) off");
     
    }
//........................................................................   
    if (terminalRead == '5') {
      inyector3State = HIGH;
      Serial.println("inyector3 (5-e) on");
    }

    if (terminalRead == 'e') {
      inyector3State = LOW;
      Serial.println("inyector3 (e) off");
    }
//........................................................................    
    if (terminalRead == '6') {
      inyector4State = HIGH;
      Serial.println("inyector4 (6-f) on");
    }

    if (terminalRead == 'f') {
      inyector4State = LOW;
      Serial.println("inyector4 (f) off");
    }
 //........................................................................   
        if (terminalRead == '7') {
      inyector5State = HIGH;
      Serial.println("inyector5 (7-g) on");
    }

    if (terminalRead == 'g') {
      inyector5State = LOW;
      Serial.println("inyector5 (g) off");
    }
//........................................................................    
        if (terminalRead == '8') {
      inyector6State = HIGH;
      Serial.println("inyector6 (8-h) on");
    }

    if (terminalRead == 'h') {
      inyector6State = LOW;
      Serial.println("inyector6 (h) off");
    }
 //........................................................................  
         if (terminalRead == '9') {
      inyector7State = HIGH;
      Serial.println("inyector7 (9-i) on");
    }

    if (terminalRead == 'i') {
      inyector7State = LOW;
      Serial.println("inyector7 (i) off");
    } 
 //........................................................................    
         if (terminalRead == 'z') {
      tachState = HIGH;
      Serial.println("tach (z-j) on");
    }

    if (terminalRead == 'j') {
      tachState = LOW;
      Serial.println("tach (j) off");
    }     
  }
}

void inyeccion()

{
if ((digitalRead(sensorcmp) == LOW || usarSensorLeva == 0) && !programStarted) {
        // Si usarSensorLeva es igual a 0, esta parte del código se ejecutará
        // independientemente del estado del sensor de leva
        while (digitalRead(sensorcmp) == LOW && usarSensorLeva == 1) {}
        programStarted = true;
    }

    if (programStarted && digitalRead(sensorckp) != prev_sensorckp_state && btn2_op) { // asegura que inicie el programa si lee señal del sensor de sigueñal, para que arranque la secuencia desde el inyector 1.
        prev_sensorckp_state = digitalRead(sensorckp);
        if (btn_op)
        {
            counts++;
            btn2_counter++;
            if (counts > numInyectoresActivos)counts = 1;
            btn_op = false;
            btn2_op = false;
        }

      // Lectura de sensores
      
    // Leer los valores de los sensores MAP/TPS y de oxígeno
    int valorSensorMap = analogRead(sensormap);
    int valorSensorO2 = analogRead(sensorO2);

    // Convertir señal del sensor de oxígeno a voltaje (0-5V)
    float voltageO2 = map(valorSensorO2, 0, 1023, 0, 5000) / 1000.0;

    // Leer el valor del sensor CTL y convertirlo a voltaje (0-5V)
    int valorSensorCTL = analogRead(sensorCTL);
    float voltageCTL = valorSensorCTL * (5.0 / 1023.0);

    // Convertir el voltaje del sensor CTL a temperatura
    float temperature = voltageCTL * (110.0 / 5.0); // Conversión de voltaje a temperatura

    // Calcular el ancho de pulso teniendo en cuenta la mezcla rica
    float anchoPulso = calcularAnchoDePulso(valorSensorMap, valorSensorO2, temperature);

    float voltage = map(analogRead(sensormap), 0,1023,0,5000)/1000.0; // Convertir señal MAP a voltaje (0-5V)


    // Verificar si la temperatura está dentro del rango de arranque
   if (temperature < TEMPERATURA_ARRANQUE) {
       // Activar la mezcla rica
       mezclaRica = true;
     } else if (temperature >= TEMPERATURA_APAGADO) {
      // Desactivar la mezcla rica
      mezclaRica = false;
     }

if (vueltasMotor % vueltasMotorParaImprimir == 0) {
    // Crear una cadena de texto con todos los valores
    String dataString = "RPM: " + String(rpm) + " | Ancho de pulso: " + String(anchoPulso) + "ms | Temperatura: " + String(temperature) + "C | Sensor MAP: " + String(voltage, 2) + "V | Sensor O2: " + String(voltageO2, 2) + "V | Sensor CTL: " + String(voltageCTL, 2) + "V";
    Serial.println(dataString);
    prevRpm = rpm;
}
        switch (counts)
        {
            case 1:
                if (numInyectoresActivos >=1) digitalWrite(inyector1, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=1) digitalWrite(inyector1, LOW);
                break;
            case 2:
                if (numInyectoresActivos >=2) digitalWrite(inyector2, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=2) digitalWrite(inyector2, LOW);
                break;
            case 3:
                if (numInyectoresActivos >=3) digitalWrite(inyector3, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=3) digitalWrite(inyector3, LOW);
                break;
            case 4:
                if (numInyectoresActivos >=4) digitalWrite(inyector4, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=4) digitalWrite(inyector4, LOW);
                break;
            case 5:
                if (numInyectoresActivos >=5) digitalWrite(inyector5, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=5) digitalWrite(inyector5, LOW);
                break;
            case 6:
                if (numInyectoresActivos >=6) digitalWrite(inyector6, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=6) digitalWrite(inyector6, LOW);
                break;
            case 7:
                if (numInyectoresActivos >=7) digitalWrite(inyector7, HIGH);
                delay(anchoPulso);
                if (numInyectoresActivos >=7) digitalWrite(inyector7, LOW);
                break;
     
            default:
                counts = 0;
                digitalWrite(inyector1, LOW);
                digitalWrite(inyector2, LOW);
                digitalWrite(inyector3, LOW);
                digitalWrite(inyector4, LOW);
                digitalWrite(inyector5, LOW);
                digitalWrite(inyector6, LOW);
                digitalWrite(inyector7, LOW);
                break;
        }

        if (btn2_counter == numInyectoresActivos)
       
            {
            btn2_counter = 0;
            btn1_counter++;
            if (digitalRead(sensorcmp) == LOW && btn1_counter == 1)
            {
              programOn = false;
            }
        }

        if (!programOn) {
            digitalWrite(inyector1, LOW);
            digitalWrite(inyector2, LOW);
            digitalWrite(inyector3, LOW);
            digitalWrite(inyector4, LOW);
            digitalWrite(inyector5, LOW);
            digitalWrite(inyector6, LOW);
            digitalWrite(inyector7, LOW);

            while (digitalRead(sensorcmp) == LOW) {}
            btn1_counter = 0;
            programOn = true;
        }
    }
    else
    {
    prev_sensorckp_state = digitalRead(sensorckp);
    if (prev_sensorckp_state == HIGH)
    {
      btn_op = true;
      btn2_op = true;
    }
    }

   // condicion para activar el Relay de encendido y bomba de combustible
    unsigned long currentMillis = millis();
    if (digitalRead(sensorckp) == LOW)
    {
        digitalWrite(asdRelay, HIGH);
        previousMillis = currentMillis;
    }
    else if (currentMillis - previousMillis >= interval)
    {
        digitalWrite(asdRelay, LOW);
    }

    // condicion para activar el Relay del electro ventilador
    int valorSensorCTL = analogRead(sensorCTL);
    float voltageCTL = valorSensorCTL * (5.0 / 1023.0);
    float temperature = voltageCTL * (110.0 / 5.0); // Conversión de voltaje a temperatura
    if (temperature >= setTemp + 1)
    {
      digitalWrite(fanRelay, HIGH); // Encender el ventilador
    }
    else if (temperature <= setTemp - 1)
    {
      digitalWrite(fanRelay, LOW); // Apagar el ventilador
    }
  }
 
