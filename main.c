//Declaração dos botões
int buttonStart = 5;
int buttonSim = 3;
int buttonNao = 9;

//Declaração Buzzer
int buzzer = 2;

//Músicas Tocadas
int musicaVitoria[100]; // Definir Música
int musicaDerrota[100]; // Definir Música
int somAcerto; // Definir Som
int somPulou; // Definir Som
int somErrou; // Definir Som
int somTempoAcabando; // Definir Som

//Declaração dos Leds
int ledVermelho = 13;
int ledVerde = 10;

// Questões
String questoesBasicas[10];
String questoesFinais[5];

int armazenaValores[10];
int respostasUsuarioMemoria[10];

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
		} else {
			return true;
		}
	}
}

void MusicaVitoria(int buzzer){
	int musicaVitoria[100];
    delay(2000);
    tone(buzzer, 392, 300); //SOL
    delay(350);
    tone(buzzer, 392, 300); //SOL
    delay(350);
    tone(buzzer, 349, 400); //FA
    delay(300);
    tone(buzzer, 330, 400); //MI
    delay(300);
    tone(buzzer, 392, 300); //SOL
    delay(350);
    tone(buzzer, 392, 300); //SOL
    delay(300);
    tone(buzzer, 349, 400); //FA
    delay(300);
    tone(buzzer, 330, 400); //MI
    delay(300);
    tone(buzzer, 392, 300); //SOL
    delay(300);
    tone(buzzer, 440, 300); //LA
    delay(350);
    tone(buzzer, 392, 300); //SOL
    delay(300);
    tone(buzzer, 349, 300); //FA
    delay(300);
    tone(buzzer, 330, 300); //MI
    delay(300);
    tone(buzzer, 294, 400); //RE
    delay(350);
    tone(buzzer, 294, 300); //RE
    delay(300);
    tone(buzzer, 330, 300); //MI
    delay(300);
    tone(buzzer, 349, 300); //FA
    delay(300);
    tone(buzzer, 294, 300); //RE
    delay(300);
    tone(buzzer, 330, 300); //MI
    delay(300);
    tone(buzzer, 349, 300); //FA
    delay(300);
    tone(buzzer, 294, 300); //RE
    delay(300);
    tone(buzzer, 330, 300); //MI
    delay(300);
    tone(buzzer, 349, 300); //FA
    delay(300);
    tone(buzzer, 392, 300); //SOL
    delay(300);
    tone(buzzer, 440, 300); //LA
    delay(300);
    tone(buzzer, 392, 300); //SOL
    delay(300);
    tone(buzzer, 349, 300); //FA
    delay(350);
    tone(buzzer, 330, 300); //MI
    delay(350);
    tone(buzzer, 294, 400); //RE
    delay(350);
    tone(buzzer,262,600); //DO
    delay(300);
}

int FasePerguntas(){
  int randomNumber;
  	for(int i=0; i<5; i++){	
      	String respostaUsuario;
        randomNumber = random(0,10);
        String pergunta = questoesBasicas[randomNumber];
        if(buttonSim == LOW){
            String repostaUsuario = "Sim";
        } else if (buttonNao == LOW){
            respostaUsuario = "Não";
        }

        if(pergunta.equals(respostaUsuario)){
              return 1;
        }else{
              return 0;
        }
	}
  	
}

int FasePerguntaFinal(){
  	int randomNumber;
  	String respostaUsuario;
	randomNumber = random(0,5);
  	String pergunta = questoesBasicas[randomNumber];
  	if(buttonSim == LOW){
    	String repostaUsuario = "Sim";
    } else if (buttonNao == LOW){
    	String respostaUsuario = "Não";
    }
  
  if(pergunta.equals(respostaUsuario)){
  		return 1;
  }else{
  		return 0;
  }
  	
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

void loop(){
  if(digitalRead(buttonStart) != HIGH){
    delay(500);
  	AcendeLeds();
    VerificaMemoria();
    bool presepada = SequenciaEstaCerta();
    Serial.println(presepada);
    if (presepada == true){
    	MusicaVitoria(buzzer);
      	int proximafase = FasePerguntas();
      if(proximafase == 1){
      	MusicaVitoria(buzzer);
        int faseFinal = FasePerguntaFinal();}
    //} else {
      	//musica de derrota
    }
  }
}