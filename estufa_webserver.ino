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
const char* ssid     = "Joao";//ssid do wifi
const char* password = "Enrique13082005";//senha do wifi
const char* host = "192.168.1.103";// ip do computador

int releBombaAgua = 15; // relé que liga a bomba de água (D15)
char* estadoBomba = "Desligado";

const int pinoSensor = 13; //PINO UTILIZADO PELO SENSOR (D13)
int valorLido; //VARIÁVEL QUE ARMAZENA O PERCENTUAL DE UMIDADE DO SOLO
int umidadeSolo = 0; //mostra umidade do solo
int analogSoloSeco = 400; //VALOR MEDIDO COM O SOLO SECO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int analogSoloMolhado = 150; //VALOR MEDIDO COM O SOLO MOLHADO (VOCÊ PODE FAZER TESTES E AJUSTAR ESTE VALOR)
int percSoloSeco = 0; //MENOR PERCENTUAL DO SOLO SECO (0% - NÃO ALTERAR)
int percSoloMolhado = 100; //MAIOR PERCENTUAL DO SOLO MOLHADO (100% - NÃO ALTERAR)

void setup() {
  Serial.begin(115200);
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
  umidadeSolo = analogRead(pinoSensor);
  //MOSTRA VALORES DA UMIDADE DO SOLO
  Serial.print("Umidade do solo: "); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.print(valorLido); //IMPRIME NO MONITOR SERIAL O PERCENTUAL DE UMIDADE DO SOLO
  Serial.print("%"); //IMPRIME O CARACTERE NO MONITOR SERIAL
  Serial.print("  |  Analogico: ");
  Serial.println(analogRead(pinoSensor));
   //MOSTRA VALORES DA UMIDADE DO SOLO
    
  if(analogRead(pinoSensor) <= 5000){//caso o valor lido seja menor que 3000 ele desliga a bomba (quanto maior o número, mais seca está aterra)
    digitalWrite(releBombaAgua, HIGH);    // liga rele desligando a bomba
    estadoBomba = "Desligado";
  }
  else{
    digitalWrite(releBombaAgua, LOW);   // dessliga rele ligando a bomba
    estadoBomba = "Ligado";
  }


  // URL que será passada para o arquivo salvar.php para passar os valores
  String url = "/estufa_webserver/salvar.php?";
         url += "estadoBomba=";
         url += estadoBomba;
         url += "&umidadeSolo=";
         url += umidadeSolo;

  Serial.print("Requesting URL: ");
  Serial.println(url);

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

  // Leia todas as linhas da resposta do servidor e imprima-as em Serial
  while(client.available()) { 
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  delay(100);
                       
}
