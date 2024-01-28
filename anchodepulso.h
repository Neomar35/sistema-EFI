
// CALCULO DE TIEMPO DE INYECCION CONTROLADO POR TEMPERATURA Y SONDA LANDA O2


float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


const int MIN_ANCHO_PULSO = 0 ;
const int MAX_ANCHO_PULSO = 17;
const float TEMPERATURA_ARRANQUE = 0.0; // Temperatura de arranque en °C
const float TEMPERATURA_APAGADO = 60.0; // Temperatura de apagado en °C
const float PORCENTAJE_COMBUSTIBLE_EXTRA = 0.2; // Porcentaje de combustible extra (20%)


   float calcularAnchoDePulso(float valorSensorMap, float valorSensorO2, float temperature) {
  // Calcular el ancho de pulso en función del valor invertido del sensor MAP/TPS
  float delayTime = mapFloat(valorSensorMap, 1023.0, 0.0, MIN_ANCHO_PULSO, MAX_ANCHO_PULSO);
  // Serial.println("Delay Time calcularAnchoDePulso: " + String(delayTime));

   // Serial.println("Temperatura: " + String(temperature)+ "C");

  // Verificar si la temperatura está dentro del rango de arranque
  if (temperature < TEMPERATURA_APAGADO) {
    // Si la temperatura es menor a 60°C, agregar un 20% al ancho de pulso
    float porcentajeExtra = 0.2;
    delayTime += delayTime * porcentajeExtra;
    // Serial.println("Porcentaje Extra: " + String(porcentajeExtra));
   // Serial.println("Delay Time después de ajustar por temperatura: " + String(delayTime));
  }


  // Verificar si se debe usar el sensor de oxígeno en el cálculo del ancho de pulso
  if (valorSensorO2 != 0) {
    // Si el valor del sensor de oxígeno no es cero, ajustar el ancho de pulso en función de su valor
    float voltageO2 = mapFloat(valorSensorO2, 0.0, 1023.0, 0.0, 5000.0) / 1000.0;
    float ajusteO2 = voltageO2 - 2.5;

    if (ajusteO2 < 0) {
      // Si el ajuste es negativo, aumentar el ancho de pulso
      delayTime += mapFloat(ajusteO2, -2.5, 0.0, 0.2, 1.0);
      // Serial.println("Delay Time después de aumentar por ajuste O2 negativo: " + String(delayTime));
    } else {
      // Si el ajuste es positivo, disminuir el ancho de pulso
      delayTime -= mapFloat(ajusteO2, 0.0, 2.5, 0.2, 1.0);
      // Serial.println("Delay Time después de disminuir por ajuste O2 positivo: " + String(delayTime));
    }
  }

  return delayTime;
}
