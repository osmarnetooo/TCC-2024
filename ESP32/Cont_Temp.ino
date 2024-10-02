#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

#define col  16 //Define o número de colunas do display utilizado
#define lin   2 //Define o número de linhas do display utilizado
#define ende  0x27 //Define o endereço do display

// Configurações do Firebase
#define FIREBASE_HOST "https://monitoramento-de-abelhas-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "34A8OW2aKIyogAYvvWuVZ4OQeaPXXzLOxWgGPDBN"

// Configurações do Wi-Fi
#define WIFI_SSID "brisa-OsmarNeto"
#define WIFI_PASSWORD "uzddbzip"

// Inicializa o display no endereço 0x27
LiquidCrystal_I2C lcd(0x27, col, lin);

// Pino de comunicação do sensor DS18B20
#define ONE_WIRE_BUS 4

// Configura a instância para o sensor de temperatura
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int pino_sensor = 18; // Pino do sensor reflexivo
int valor = 1;       // Variável de leitura do sensor
int contador = 0;    // Contador de abelhas

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {

  lcd.init(); //Inicializa a comunicação com o display já conectado
  lcd.clear(); //Limpa a tela do display
  lcd.backlight(); // Liga a luz de fundo do LCD

  // Inicializa comunicação Serial
  Serial.begin(115200);

  // Inicializa o sensor de temperatura
  sensors.begin();

  // Configuração do pino do sensor reflexivo
  pinMode(pino_sensor, INPUT);

  // Conectando ao Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Conectado ao Wi-Fi");
  
  /*lcd.setCursor(0, 0); //Para teste
  lcd.print("WI-FI conectado");
  delay(1000);
  */
  
  // Configuração do Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Inicializa o Firebase com a configuração e autenticação
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Exibição inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("TCC 2024");
  lcd.setCursor(0, 1);
  lcd.print("Ufersa PDF");
  //delay(1000); //Para teste
}

void mostrarTemperatura() {
  // Solicita a leitura da temperatura
  sensors.requestTemperatures();

  // Obtém a temperatura em Celsius
  float temperaturaC = sensors.getTempCByIndex(0);

  // Atualiza a temperatura no LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperaturaC);
  lcd.print(" C  ");

  // Mostra a temperatura no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.print(temperaturaC);
  Serial.println(" C");

  // Atualiza o valor no Firebase
  if (Firebase.setFloat(firebaseData, "/sensores/Temperatura", temperaturaC)) {
    Serial.println("Temperatura enviada ao Firebase");
  } else {
    Serial.println("Erro ao enviar temperatura: " + firebaseData.errorReason());
  }
}

void loop() {
  // Leitura do sensor reflexivo
  valor = digitalRead(pino_sensor);

  // Verifica se algum objeto foi detectado (valor = 0)
  if (valor == 0) {
    contador++;  // Incrementa o contador

    lcd.setCursor(0, 1);
    lcd.print("Contador: ");
    lcd.print(contador);

    // Mostra o valor no Serial Monitor
    Serial.print("Contador: ");
    Serial.println(contador);

    // Atualiza o valor no Firebase
    if (Firebase.setInt(firebaseData, "/sensores/Contador", contador)) {
      Serial.println("Contador enviado ao Firebase");
    } else {
      Serial.println("Erro ao enviar contador: " + firebaseData.errorReason());
    }

    // Aguarda até que o objeto saia da frente do sensor
    while (digitalRead(pino_sensor) == 0) {
      delay(100);
    }
  }

  // Chama a função para mostrar a temperatura
  mostrarTemperatura();

  // Delay para evitar leituras muito frequentes
  delay(1000);
}
