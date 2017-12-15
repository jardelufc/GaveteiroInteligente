#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <Servo.h>  //incluir a biblioteca de servo

Servo myservo;  //Inclusao do servo
int n = 0;  //Entradas seriais
int pos = 0;  //Posição zero para o servop
//////////////////////////////////////////////////
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);  //Ativando a porta serial
  myservo.attach(8);  //Pino do servo+arduino
  myservo.write(0);  //Servo setado com valor zero
  Serial.flush();  //Limpando a memoria do serial
  Serial.println("Digite: \n 1 - Abrir (90º) \n 2 - Fechar (0º)");  //criação de um cabeçalho no serial
  /////////////////////////////////////
  Serial.println("ATIVANDO IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("ATIVADO IRin");
}

String leStringSerial(){
  String conteudo = "";
  char caractere;
 
  while(Serial.available() > 0) {
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
    
  Serial.print("Recebi: ");
  Serial.println(conteudo);
    
  return conteudo;
}

void loop(){
 
    if (irrecv.decode(&results)) {
      Serial.println("tesssssssssssste: ");
      Serial.println(results.value, BIN);
      
      irrecv.resume(); // Receive the next value
      
      
    if (results.value == 851901943) {
      myservo.write(0);
      Serial.print("Fechou");
      Serial.println(results.value, BIN);
      delay(1000);
      irrecv.resume(); // Receive the next value
    }
    
    if (results.value == 1053031451){
      myservo.write(90);
      Serial.print("Abriu");
      Serial.println(results.value, BIN);
      delay(1000);
      irrecv.resume(); // Receive the next value
    }
    Serial.flush();
  }
  
}

