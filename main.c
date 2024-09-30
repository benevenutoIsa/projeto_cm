//Declaração dos botões
int buttonStart = 5;
int buttonSim = 3;
int buttonNao = 9;

//Declaração Buzzer
int buzzer = 2;

//Músicas Tocadas
int somPulou; // Definir Som

//Declaração dos Leds
int ledVermelho = 13;
int ledVerde = 10;

// Questões
String questoesBasicas[10];
String respostasCorretas[10];

//Pergunta Final
String questoesFinais[5];
String respostasFinaisCorretas[5];

// Jogo da Memória
int armazenaValores[10];
int respostasUsuarioMemoria[10];

//Vida
int vida = 1;

bool Temporizador(){
	int contador;
  for(contador = 30; contador > 0; contador--){
  	Serial.println(contador);
    delay(1000);
    if(contador <= 5){
		tone(buzzer,440);    
    }
     if (digitalRead(buttonSim) == LOW || digitalRead(buttonNao) == LOW) {
      noTone(buzzer); 
      return true; 
    }
  }
  noTone(buzzer);
  return false;
}

void SomAcerto(int buzzer){
	delay(1000);
  	tone(buzzer,261);
}

void SomErro(int buzzer){
	delay(1000);
  	tone(buzzer,297);
}

void SomPulou(int buzzer){
	delay(1000);
  	tone(buzzer,495);
}

void MusicaDerrota(int buzzer){
    delay(2000);
    tone(buzzer, 330, 400); //MI
  	delay(300);
  	tone(buzzer, 349, 400); //FA
  	delay(350);
  	tone(buzzer, 392, 300); //SOL
  	delay(350);
  	tone(buzzer, 392, 300); //SOL
  	delay(500);
  	
}

void MusicaVitoria(int buzzer){
    delay(2000);
    tone(buzzer, 392, 300); //SOL
    delay(350);
    tone(buzzer, 392, 300); //SOL
    delay(350);
    tone(buzzer, 349, 400); //FA
    delay(300);
    tone(buzzer, 330, 400); //MI
  	delay(500);
}

void AcendeLeds(){
	for(int i = 0; i < 10; i++){
      	int randomNumber = random(0,2);
		if(randomNumber == 0){
          digitalWrite(ledVermelho, HIGH);
          digitalWrite(ledVerde,LOW);
          armazenaValores[i] = 0;
          delay(500);
        	digitalWrite(ledVermelho,LOW);
		} else {
          digitalWrite(ledVermelho,LOW);
          digitalWrite(ledVerde,HIGH);
          armazenaValores[i] = 1;
          delay(500);
          digitalWrite(ledVerde,LOW);
		}
      delay(500);
	} 
}

void VerificaMemoria(){
  int contador = 0;
	do{
      Serial.println(contador);
		if(digitalRead(buttonSim) == LOW){
			respostasUsuarioMemoria[contador] = 0;
			contador++;
          	Serial.println(respostasUsuarioMemoria[contador]);
          	delay(500);
		} else if (digitalRead(buttonNao) == LOW){
			respostasUsuarioMemoria[contador] = 1;
			contador++;
          	delay(500);
		}
	}while(contador < 10);
}

bool SequenciaEstaCerta(){
  for(int i = 0; i<10 ;i++){
		if(respostasUsuarioMemoria[i] != armazenaValores[i]){
			return false;
		}
	}
  return true;
}


int FasePerguntas(){
  int randomNumber;
  for (int i = 0; i < 5; i++) {	
    String respostaUsuario;
    randomNumber = random(0, 10);
    String pergunta = questoesBasicas[randomNumber];
    String respostaCorreta = respostasCorretas[randomNumber]; 
    if(Temporizador()){
      if (digitalRead(buttonSim) == LOW) {
        respostaUsuario = "Sim";
      } else if (digitalRead(buttonNao) == LOW) {
        respostaUsuario = "Não";
      }

      if (!respostaUsuario.equals(respostaCorreta)) {
        vida--;
        SomErro(buzzer);
        if(vida<=0){
        	MusicaDerrota(buzzer);
          	return 0;
        }
      } else {
        SomAcerto(buzzer);
      }
    } else {
      	vida--;
    	SomPulou(buzzer);
      if(vida <=0){
      	MusicaDerrota(buzzer);
      }
    }
    delay(500);  
  }
  return 1; 
}


int FasePerguntaFinal(){
  int randomNumber;
  String respostaUsuario;
  randomNumber = random(0, 5);
  String pergunta = questoesFinais[randomNumber];
  String respostaCorreta = respostasFinaisCorretas[randomNumber];
  if(Temporizador()){
    if (digitalRead(buttonSim) == LOW) {
      respostaUsuario = "Sim";
    } else if (digitalRead(buttonNao) == LOW) {
      respostaUsuario = "Não";
    }
    if (!respostaUsuario.equals(respostaCorreta)) {
      MusicaDerrota(buzzer);
      return 0;  
    } else {
    	MusicaVitoria(buzzer);
    }
  } else {
  	MusicaDerrota(buzzer);
  }
  return 1; 
}

void setup() {
// put your setup code here, to run once:

pinMode(3,INPUT_PULLUP); // Botão Start
pinMode(5,INPUT_PULLUP); // Botão Sim
pinMode(9,INPUT_PULLUP); // Botão Não
pinMode(2,OUTPUT); // Buzzer
pinMode(13,OUTPUT); // Led Vermelho
pinMode(10,OUTPUT); // Led Verde
  
Serial.begin(9600);

}

void loop() {
  if (digitalRead(buttonStart) == LOW) {
    delay(500);

    vidas = 2;

    AcendeLeds();
    VerificaMemoria();
    
    if (SequenciaEstaCerta()) {
      MusicaVitoria(buzzer);
      Serial.println("Você acertou a sequência!");

      // Iniciar fase de perguntas
      if (FasePerguntas() == 1) {
        Serial.println("Você passou para a pergunta final.");
        
        // Iniciar fase final
        FasePerguntaFinal();
      }
    } else {
      MusicaDerrota(buzzer);
      Serial.println("Você errou a sequência.");
    }
  }
}