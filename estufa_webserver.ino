//01/11/2022
//ETEC Zona Leste - 2°DS AMS Tarde
//Auxiliar:
//defines - mapeamento de pinos do NodeMCU esp32
//#define D0    16
//#define D1    5
//#define D2    4
//#define D3    0
//#define D4    2
//#define D5    14
//#define D6    12
//#define D7    13
//#define D8    15
//#define D9    3
//#define D10   1
//#define A0   17


#include <WiFi.h>//biblioteca para wifi
#include <DHT.h>
const char* ssid     = "Joao";//ssid do wifi
const char* password = "Enrique13082005";//senha do wifi
const char* host = "192.168.1.103";// ip do computador

//BOMBA DE AGUA
int releBombaAgua = 15; // relé que liga a bomba de água (D15)
char* estadoBomba = "Desligado";

//SENSOR DE UMIDADE DO SOLO
const int pinoSensor = 13; //PINO UTILIZADO PELO SENSOR DE UMIDADE DO SOLO (Analogico) (D13)
const int pinoSensorD = 4; //PINO UTILIZADO PELO SENSOR DE UMIDADE DO SOLO (Digital) (D4)
int valorLido; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO

int analogSoloSeco = 400; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 150; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

//SENSOR DHT FORA DA ESTUFA
int pinoDhtFora = 12; //pino do sensor (D12)
float umidadeFora; // Umidade fora da estufa
float temperaturaCFora; // Temperatura em Celsius de fora da estufa
float temperaturaFFora; // Temperatura em Fahrenheit de fora da estufa
char* porcentagemUmidadeFora;
DHT dhtFora(pinoDhtFora, DHT11);// Instância de objeto. O Objeto é o sensor DHT

//SENSOR DHT DE DENTRO DA ESTUFA
#define pinDhtDentro 14//pino do sensor (D14)
float umidadeDentro;
float temperaturaCDentro;
float temperaturaFDentro;
char* porcentagemUmidadeDentro;
#define MODELODHT DHT11
DHT dhtDentro(pinDhtDentro, DHT11);

int cont =0;
void setup() {
  Serial.begin(115200);
  dhtFora.begin();// Inicializando o sensor DHT
  dhtDentro.begin();// Inicializando o sensor DHT
  pinMode(releBombaAgua, OUTPUT);// relé que liga a bomba de água
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);//conecta no wifi com ssid e senha

  while (WiFi.status() != WL_CONNECTED) {//enquanto estiver conectando, mostra um ponto
      delay(500);
      Serial.print(".");
  }

  //caso seja conectado com sucesso no wifi
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());//ip do esp32
}

void loop() {
  // Use a classe WiFiClient para criar conexões TCP
  WiFiClient client;
  const int httpPort = 80;

  //caso tenha um erro na conexão
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  /* 
   *  LOW - desliga relé e liga a lampada
   *  HIGH - liga relé e desliga a lampada
   */
  valorLido = constrain(analogRead(pinoSensor),analogSoloMolhado,analogSoloSeco); //MANTÉM valorLido DENTRO DO INTERVALO (ENTRE analogSoloMolhado E analogSoloSeco)
  valorLido = map(valorLido,analogSoloMolhado,analogSoloSeco,percSoloMolhado,percSoloSeco); //EXECUTA A FUNÇÃO "map" DE ACORDO COM OS PARÂMETROS PASSADOS

  //PEGA VALOR DO SENSOR DHT DE FORA DA ESTUFA
  umidadeFora = dhtFora.readHumidity();
  temperaturaCFora = dhtFora.readTemperature();
  temperaturaFFora = dhtFora.readTemperature(true);
  
  //PEGA VALOR DO SENSOR DHT DE DENTRO DA ESTUFA
  umidadeDentro  = dhtDentro.readHumidity();
  temperaturaCDentro = dhtDentro.readTemperature();
  temperaturaFDentro = dhtDentro.readTemperature(true);
  
  //MOSTRA VALORES DA UMIDADE DO SOLO
  Serial.print("Umidade do solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLido); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.print("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
  Serial.print("  |  Analogico: ");
  Serial.print(analogRead(pinoSensor));
  Serial.print("  |  Digital: ");
  Serial.println(analogRead(pinoSensor));
   //MOSTRA VALORES DA UMIDADE DO SOLO

  //Liga ou desliga a bomba  
  if(analogRead(pinoSensor) <= 5000){//caso o valor lido seja menor que 3000 ele desliga a bomba (quanto maior o número, mais seca está a terra)
    digitalWrite(releBombaAgua, HIGH);    // liga rele desligando a bomba
    estadoBomba = "Desligado";
  }
  else{
    digitalWrite(releBombaAgua, LOW);   // dessliga rele ligando a bomba
    estadoBomba = "Ligado";
  }

  if(digitalRead(pinoSensorD)){//caso esteja sem umidade
    digitalWrite(releBombaAgua, LOW);   // dessliga rele ligando a bomba
    estadoBomba = "Ligado";
  }else{
    digitalWrite(releBombaAgua, HIGH);    // liga rele desligando a bomba
    estadoBomba = "Desligado";
  }
  
  //mostra estado da bomba
  Serial.print("Estado da Bomba: ");//Mostra se a bomba de água está ligada ou desligada
  Serial.println(estadoBomba);

  //mostra dados do sensor dht de fora da estufa
  if (isnan(umidadeFora) || isnan(temperaturaCFora) || isnan(temperaturaFFora)) {
    Serial.println("Falha na leitura do sensor DHT de fora da estufa!");
  }else{
    Serial.print("Sensor DHT de fora   - Umidade: " + (String)umidadeFora + " %  |  "); // Funções de exibição dos valores
    Serial.print("Temperatura: " + (String)temperaturaCFora + " *C  |  "); // Funções de exibição dos valores
    Serial.println("Temperatura: " + (String)temperaturaFFora + " *F"); // Funções de exibição dos valores
  }
  //mostra dados do sensor dht de dentro da estufa
  if (isnan(umidadeDentro) || isnan(temperaturaCDentro) || isnan(temperaturaFDentro)) {
    Serial.println("Falha na leitura do sensor DHT de dentro da estufa!");
  } else {
    Serial.print("Sensor DHT de dentro - Umidade:  ");
    Serial.print(umidadeDentro);
    Serial.print(" | Temperatura: ");
    Serial.print(temperaturaCDentro);
    Serial.print("°C - ");
    Serial.print(temperaturaFDentro);
    Serial.println("°F");
  }

  // URL que será passada para o arquivo salvar.php para passar os valores
  String url = "/estufa_webserver/salvar.php?";
         url += "estadoBomba=";//estado da bomba
         url += estadoBomba;//estado da bomba
         url += "&umidadeSolo=";//umidade do solo
         url += analogRead(pinoSensor);//umidade do solo

         
         url += "&umidadeFora=";//umidade de fora da estufa
         url += umidadeFora;//umidade de fora da estufa
         url += "&temperaturaCFora=";//temperatura em Celsius de fora da estufa
         url += temperaturaCFora;//temperatura em Celsius fora da estufa
         url += "&temperaturaFFora=";//temperatura em Fahrenheit  de fora da estufa
         url += temperaturaFFora;//temperatura em Fahrenheit  fora da estufa
         
         url += "&umidadeDentro=";//umidade de dentro da estufa
         url += umidadeDentro;//umidade de dentro da estufa
         url += "&temperaturaCDentro=";//temperatura em Celsius de dentro da estufa
         url += temperaturaCDentro;//temperatura em Celsius dentro da estufa
         url += "&temperaturaFDentro=";//temperatura em Fahrenheit  de dentro da estufa
         url += temperaturaFDentro;//temperatura em Fahrenheit  dentro da estufa

  // Isso enviará a solicitação para o servidor
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
    }  
  }
  
  while(cont <=0){//mostra conexão apenas uma vez
    Serial.print("Requesting URL: ");
    Serial.println(url);
    // Leia todas as linhas da resposta do servidor e imprima-as em Serial
    while(client.available()) { 
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    cont ++;
  }
  Serial.println("");

  delay(5000);
                       
}
