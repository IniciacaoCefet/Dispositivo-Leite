
#include "DHT.h"                      //Biblioteca sensor de umidade e temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>                     //Biblioteca de comunicação

#define DHTPIN A1                     //Pino analógico que o sensor de umidade e temperatura está conectado
#define DHTTYPE DHT11                 //definindo o sensor de umidade DHT 11
DHT dht(DHTPIN, DHTTYPE);             //Definindo o nome do sensor de umidade e temperatura
 
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 3
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 

void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  Serial.println("DHTxx test!");      //Identifica o sensor DHT11
  dht.begin();                        //Inicia o sensor de umidade e temperatura
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
  
   
}
 
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
 
void loop()
{
  Temperatura();
  Umidade();
  Temperatura_Liquido();
  
}

void Temperatura_Liquido(){
  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  // Mostra dados no serial monitor
  Serial.print("Temp - Liquido - C: ");
  Serial.println(tempC);
  Serial.print("Temp Min Liquido : ");
  Serial.println(tempMin);
  Serial.print("Temp Max Liquido : ");
  Serial.println(tempMax);
}

void Temperatura(){
  float temperatura = dht.readTemperature(); //Faz a leitura da temperatura do ambiente
  
  //Confere se o sensor foi encontrado
  if(isnan(temperatura)){ 
    Serial.println("Sensor de temperatura não encontrado");
  }else{
    Serial.print("Temperatura: ");
    Serial.print(temperatura);
    Serial.println(" *C");
  }
}

void Umidade(){
  float umidade = dht.readHumidity(); //Faz a leitura da umidade do ambiente

  //Confere se o sensor foi encontrado
  if(isnan(umidade)){
    Serial.println("Sensor de umidade não encontrado");
  }else{
    Serial.print("Umidade: ");
    Serial.print(umidade);
    Serial.println(" %t");
  }
}
