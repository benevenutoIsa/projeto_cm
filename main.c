// Declaração dos botões
int buttonStart = 5;
int buttonSim = 9;
int buttonNao = 3;

// Declaração Buzzer
int buzzer = 5;

int ledVermelho = 13;
int ledVerde = 10;

int sequenciaLeds[10];  
int respostaUsuario[10]; 

void GerarSequenciaLeds(int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    int ledEscolhido = random(0, 2); 
    sequenciaLeds[i] = ledEscolhido;

    if (ledEscolhido == 0) {
      digitalWrite(ledVermelho, HIGH);
      delay(500);
      digitalWrite(ledVermelho, LOW);
    } else {
      digitalWrite(ledVerde, HIGH);
      delay(500);
      digitalWrite(ledVerde, LOW);
    }

    delay(300); 
  }
}


void CapturarSequenciaUsuario(int tamanho) {
  int contador = 0;
  
  while (contador < tamanho) {
    Serial.println(contador);
    if (digitalRead(buttonSim) == LOW) {
      respostaUsuario[contador] = 1; 
      contador++;
      delay(1000); 
    } else if (digitalRead(buttonNao) == LOW) {
      respostaUsuario[contador] = 0; 
      contador++;
      delay(1000); 
    }
  }
}

// Função para verificar se a sequência do usuário está correta
bool VerificarSequencia(int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    if (sequenciaLeds[i] != respostaUsuario[i]) {
      return false; 
    }
  }
  return true;
}

//
void MusicaVitoria() {
  tone(buzzer, 392, 300); delay(350); //SOL
  tone(buzzer, 392, 300); delay(350); //SOL
  tone(buzzer, 349, 400); delay(300); //FA
  tone(buzzer, 330, 400); delay(300); //MI
 
}


void MusicaDerrota() {
  tone(buzzer, 330, 300); delay(350); //MI
  tone(buzzer, 294, 400); delay(300); //RE
  tone(buzzer, 262, 400); delay(300); //DO
  // Continue o padrão...
}

void setup() {
  pinMode(buttonStart, INPUT_PULLUP); 
  pinMode(buttonSim, INPUT_PULLUP);   
  pinMode(buttonNao, INPUT_PULLUP);   
  pinMode(buzzer, OUTPUT);            
  pinMode(13, OUTPUT);       
  pinMode(10, OUTPUT);         

  Serial.begin(9600); 
}

void loop() {
  
  
  if (digitalRead(buttonStart) == LOW) {
    delay(500); 

    int tamanhoSequencia = 4;  
    GerarSequenciaLeds(tamanhoSequencia);

    CapturarSequenciaUsuario(tamanhoSequencia);
    
    
    if (VerificarSequencia(tamanhoSequencia)) {
      MusicaVitoria(); 
      Serial.println("A");
    } else {
      MusicaDerrota();
      Serial.println("B");
    }
    delay(2000);
  }
}