#define SIM900 Serial1
 
char respuesta[120];
 
char latitude[15];
char longitude[15];
char altitude[15];
char speedOTG[10];
 
void setup() {
   Serial1.begin(9600);
 Serial.begin(9600);
 delay(100);
  enviarAT("AT", "OK", 1000); // Cuelga la llamada
  enviarAT("AT+CPIN?", "OK", 1000);
  while ( enviarAT("AT+CREG?", "+CREG: 0,1", 1000) == 0 )
  {
    delay(100);
  }
  Serial.println("Conectado a la red.");
  enviarAT("AT+CLIP=1\r", "OK", 1000); // Activamos la identificacion de llamadas
  enviarAT("AT+CMGF=1\r", "OK", 1000); //Configura el modo texto para enviar o recibir mensajes
  enviarAT("AT+CGPSPWR=1\r", "OK", 1000);
}
 
void loop() {
  char r = 0;
  //Envíamos y recibimos datos
 if (Serial.available() > 0){
  r = Serial.read();
 }
 if(r == 'c'){
  Serial.println("chamada");
  enviarAT("ATD925707069;", "OK", 1000);
 }
 if(r == 's'){
  char sms[20] = "es coco\x1A \r\n";
  char aux_str[50];
  Serial.println("Enviando SMS...");
    enviarAT("AT+CMGF=1\r", "OK", 1000); //Comando AT para mandar un SMS
    sprintf(aux_str, "AT+CMGS=\"925707069\"", strlen(sms)); //Numero al que vamos a enviar el mensaje
    //Texto del mensaje
    if (enviarAT(aux_str, ">", 10000) == 1)
    {
      enviarAT(sms, "OK", 10000);
    }
    Serial.println("SMS enviado");
   
 }
 if(r == 'g'){
    Serial.println("Finding GPS");
    while ( enviarAT("AT+CGPSSTATUS?", "+CGPSSTATUS: Location 3D Fix", 1000) == 0 )
  {
    delay(5000);
  }
  int x = 0;
  char gps[80];
  while ( SIM900.available() != 0) SIM900.read();
  enviarAT("AT+CGPSOUT\r", "OK",1000);
  //enviarAT("AT+CGPSINF=0\r", "OK", 1000);
 /* Serial.println(respuesta);
    strtok(respuesta, ",");
    strcpy(longitude,strtok(NULL, ",")); // Gets longitude
    strcpy(latitude,strtok(NULL, ",")); // Gets latitude
    strcpy(altitude,strtok(NULL, ".")); // Gets altitude
    strtok(NULL, ",");    
    strtok(NULL, ",");
    strtok(NULL, ",");
    strtok(NULL, ",");
    strcpy(speedOTG,strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
    
    Serial.println(longitude);
    Serial.println(latitude);
    Serial.println(altitude);
    Serial.println(speedOTG);*/
    
 }
 
}
 
 
int enviarAT(String ATcommand, char* resp_correcta, unsigned int tiempo)
{
 
  int x = 0;
  bool correcto = 0;
 
  unsigned long anterior;
 
  memset(respuesta, '\0', 100); // Inicializa el string
  delay(100);
  while ( SIM900.available() > 0) SIM900.read(); // Limpia el buffer de entrada
  SIM900.println(ATcommand); // Envia el comando AT
  x = 0;
  anterior = millis();
  // Espera una respuesta
  do {
    // si hay datos el buffer de entrada del UART lee y comprueba la respuesta
    if (SIM900.available() != 0)
    {
        respuesta[x] = SIM900.read();
        x++;
      // Comprueba si la respuesta es correcta
      if (strstr(respuesta, resp_correcta) != NULL)
      {
        correcto = 1;
      }
    }
  }
  // Espera hasta tener una respuesta
  while ((correcto == 0) && ((millis() - anterior) < tiempo));
  Serial.println(respuesta);
 
  return correcto;
 
  }
