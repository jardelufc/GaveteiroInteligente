// OHMIMETRO - LEITURA DA RESISTÊNCIA NÃO-FIXA

float R_fixa = 560.0;        // Resistência fixa do divisor de tensão
char  pino_leitura = 18;     // Pino para a leitura dos valores da tensão entre os resistores
int   leitura = 0;           // Armazena o valor lido pela entrada analógica (valor entre 0 e 1023)
float Vx = 0.0;              // Calcula o valor lido pela entrada analóica em volts (entre 0 e 5 volts)
float resultado = 0.0; 

void setup(){                                            
  Serial.begin(9600);              // Configuraçao do serial monitor
  while(!Serial){
  }
  pinMode(pino_leitura, INPUT); 
  Serial.println("Resistência flutuante: ");
  leitura = analogRead(pino_leitura); 
  Vx = (5.0*leitura)/1023.0;
  resultado = ((5*R_fixa)/Vx) - R_fixa;
  Serial.println(resultado);
}

void loop() {
// 
} 
