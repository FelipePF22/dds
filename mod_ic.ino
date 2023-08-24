#include<AD9833.h>
#define FSY 10
AD9833 ger(FSY);
int teste =0;
float freq, fase,F_start,F_stop,F_inc = 1, tempo = 5.0;
WaveformType waveType;

void setup() {
  Serial.begin(9600);
  ger.Begin();
  ger.EnableOutput(false);
}

void loop() {
 if (Serial.available())
 {
char tecla = Serial.read();
 
 if(tecla =='F')
 {
    frequencia();
 }
 if(tecla =='P')
 {
     phase();
 }
  if(tecla =='T')
 {
    triangular();
  }
    if(tecla =='S')
 {
    seno();
  }   
   if(tecla =='Q')
 {
   quadrado();
  }
  if (tecla=='R')
    {
     Serial.println("Frequencia de inicio: ");
     delay(4000); // espera 4s
     F_start=Serial.parseFloat();// pede para escrever o valor da frequencia
     Serial.print(F_start); // imprime esse valor 0
     Serial.println();
     Serial.println("Frequencia final: ");
     delay(4000); // espera 4s
     F_stop=Serial.parseFloat();// pede para escrever o valor da frequencia
     Serial.print(F_stop); // imprime esse valor 
     Serial.println();
     teste = 1;
     Serial.println("Tipo de onda: ");
     delay(4000);
      }
    }
   }
   void frequencia(){
     Serial.println("Frequencia: ");
     delay(4000); // espera 4s
     freq=Serial.parseFloat();// pede para escrever o valor da frequencia
     Serial.print(freq); // imprime esse valor 
     ger.SetFrequency(REG0, freq); // atualiza a frequência no registrador REG0
     Serial.println(); 
   }
   void phase(){
     Serial.println("Fase: ");
     delay(4000); // espera 4s
     fase=Serial.parseFloat();// pede para escrever o valor da frequencia
     Serial.print(fase); // imprime esse valor 
     ger.SetPhase(REG0, fase); // atualiza a frequência no registrador REG0 
     Serial.println(); 
   }
   void triangular(){
    WaveformType waveType = TRIANGLE_WAVE; //define o tipo de onda 
    ger.SetWaveform(REG0,waveType);//registra o tipo de onda no registrador REG0
    ger.ApplySignal(waveType, REG0, freq, REG0, fase); // aplica o sinal de onda, com a frequencia, o tipo de onda e a fase definidos acima 
    ger.EnableOutput(true);// ativa o comando reset para a aplicação da forma de onda  
     if(teste==1)
    {
       uint16_t atraso = (tempo * 1000.0) / ((uint16_t)((F_stop - F_start) / F_inc) + 1); // calculo do tempo para cada incremento(no qual utiliza os 16 bits do atmega 328p)
       if ( atraso == 0 ) atraso = 1;
       ger.ApplySignal(TRIANGLE_WAVE,REG0,F_start);
       ger.EnableOutput(true);
       ger.SetFrequency(REG0,F_start-F_inc);
         for ( float i = F_start ; i <= F_stop; i += F_inc ) {
               ger.IncrementFrequency(REG0,F_inc);
               delay(atraso); 
        }
    }
    teste=0;
    F_inc = 1;
   }
   void seno(){
    WaveformType waveType = SINE_WAVE; //define o tipo de onda 
    ger.SetWaveform(REG0,waveType);//registra o tipo de onda no registrador REG0
    ger.ApplySignal(waveType, REG0, freq, REG0, fase); // aplica o sinal de onda, com a frequencia, o tipo de onda e a fase definidos acima 
    ger.EnableOutput(true);// ativa o comando reset para a aplicação da forma de onda  
    if(teste==1)
    {
       uint16_t atraso = (tempo * 1000.0) / ((uint16_t)((F_stop - F_start) / F_inc) + 1); // calculo do tempo para cada incremento(no qual utiliza os 16 bits do atmega 328p)
       if ( atraso == 0 ) atraso = 1;
       ger.ApplySignal(SINE_WAVE,REG0,F_start);
       ger.EnableOutput(true);
       ger.SetFrequency(REG0,F_start-F_inc);
         for ( float i = F_start ; i <= F_stop; i += F_inc ) {
               ger.IncrementFrequency(REG0,F_inc);
               delay(atraso); 
        }
    }
    teste=0;
    F_inc = 1;
   }
   void quadrado(){
     WaveformType waveType = SQUARE_WAVE; //define o tipo de onda 
    ger.SetWaveform(REG0,waveType);//registra o tipo de onda no registrador REG0
    ger.ApplySignal(waveType, REG0, freq, REG0, fase); // aplica o sinal de onda, com a frequencia, o tipo de onda e a fase definidos acima 
    ger.EnableOutput(true);// ativa o comando reset para a aplicação da forma de onda  
     if(teste==1)
    {
       uint16_t atraso = (tempo * 1000.0) / ((uint16_t)((F_stop - F_start) / F_inc) + 1); // calculo do tempo para cada incremento(no qual utiliza os 16 bits do atmega 328p)
       if ( atraso == 0 ) atraso = 1;
       ger.ApplySignal(SQUARE_WAVE,REG0,F_start);
       ger.EnableOutput(true);
       ger.SetFrequency(REG0,F_start-F_inc);
         for ( float i = F_start ; i <= F_stop; i += F_inc ) {
               ger.IncrementFrequency(REG0,F_inc);
               delay(atraso); 
        }
    }
    teste=0;
    F_inc = 1;
   }
