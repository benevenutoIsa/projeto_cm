#include <LiquidCrystal.h>
char buffer[3];
// Declaração dos botões
int buttonStart = 5;
int buttonSim = 3;
int buttonNao = 9;

// Declaração Buzzer
int buzzer = 2;

// Declaração dos Leds
int ledVermelho = 13;
int ledVerde = 10;

// Questões
const char* questoesBasicas[] = {
    "1+1=2", 
    "3*2=6", 
    "7-5=3", 
    "10/2=5", 
    "4+9=13", 
    "15-7=8", 
    "12/3=4", 
    "5*6=30", 
    "9+6-4=11"
};
const char* respostasCorretas[] = {
    "SIM", 
    "SIM", 
    "NAO", 
    "SIM", 
    "SIM", 
    "NAO", 
    "SIM", 
    "SIM", 
    "SIM"
};

// Pergunta Final
const char* questoesFinais[] = {
    "2^4=16", 
    "RAIZ DE 144=12", 
    "5+(3*2)=11", 
    "20-3*4+2=10", 
    "3*2+4*2=47"
};
const char* respostasFinaisCorretas[] = {
    "SIM", 
    "SIM", 
    "SIM", 
    "NAO", 
    "NAO"
};

// Jogo da Memória
int armazenaValores[10];
int respostasUsuarioMemoria[10];

// Inicializa os objetos lcd
LiquidCrystal lcd(12, 11, 8, 7, 6, 4);

// Vida
int vida = 2;

bool Temporizador() {
    int contador;
    for (contador = 30; contador > 0; contador--) {
        Serial.println(contador);
        sprintf(buffer, "%02d", contador);
        lcd.setCursor(14, 1);
        lcd.print(buffer);
        delay(1000);
        if (contador <= 5) {
            tone(buzzer, 440);    
        }
        if (digitalRead(buttonSim) == LOW || digitalRead(buttonNao) == LOW) {
            noTone(buzzer); 
            return true; 
        }
    }
    noTone(buzzer); // Certifica que o buzzer é desligado
    return false;
}

void SomAcerto(int buzzer) {
    delay(1000);
    tone(buzzer, 261);
    delay(500); // Aumenta o tempo do som para melhor feedback
}

void SomErro(int buzzer) {
    delay(1000);
    tone(buzzer, 297);
    delay(500); // Aumenta o tempo do som para melhor feedback
}

void SomPulou(int buzzer) {
    delay(1000);
    tone(buzzer, 495);
    delay(500); // Aumenta o tempo do som para melhor feedback
}

void MusicaDerrota(int buzzer) {
    delay(2000);
    tone(buzzer, 330, 400); // MI
    delay(300);
    tone(buzzer, 349, 400); // FA
    delay(350);
    tone(buzzer, 392, 300); // SOL
    delay(350);
    tone(buzzer, 392, 300); // SOL
    delay(500);
}

void MusicaVitoria(int buzzer) {
    Serial.println("A");
    tone(buzzer, 392, 300); // SOL
    delay(350);
    tone(buzzer, 392, 300); // SOL
    delay(350);
    tone(buzzer, 349, 400); // FA
    delay(300);
    tone(buzzer, 330, 400); // MI
    delay(500);
}

void AcendeLeds() {
    for (int i = 0; i < 10; i++) {
        int randomNumber = random(0, 2);
        if (randomNumber == 1) {
            digitalWrite(ledVermelho, HIGH);
            digitalWrite(ledVerde, LOW);
            armazenaValores[i] = 0;
            delay(500);
            digitalWrite(ledVermelho, LOW);
        } else {
            digitalWrite(ledVermelho, LOW);
            digitalWrite(ledVerde, HIGH);
            armazenaValores[i] = 1;
            delay(500);
            digitalWrite(ledVerde, LOW);
        }
        delay(500);
    } 
}

void VerificaMemoria() {
    int contador = 0;
    lcd.clear();
    do {
        Serial.println(contador);
        if (digitalRead(buttonSim) == LOW) {
            respostasUsuarioMemoria[contador] = 0;
            contador++;
            Serial.println(respostasUsuarioMemoria[contador]);
            delay(500);
        } else if (digitalRead(buttonNao) == LOW) {
            respostasUsuarioMemoria[contador] = 1;
            contador++;
            delay(500);
        }
    } while (contador < 10);
}

bool SequenciaEstaCerta() {
    lcd.clear();
    for (int i = 0; i < 10; i++) {
        if (respostasUsuarioMemoria[i] != armazenaValores[i]) {
            lcd.setCursor(0, 0);
            lcd.print("Sequencia Incorreta");
            return false;
        }
    }
    return true;
}

int FasePerguntas() {
  lcd.clear();  
  int randomNumber;
    for (int i = 0; i < 5; i++) {    
        String respostaUsuario;
        randomNumber = random(0, 8); 
        String respostaCorreta = respostasCorretas[randomNumber];
        
        lcd.setCursor(0, 0);
        lcd.print(questoesBasicas[randomNumber]);
        
        delay(1000);
        if (Temporizador()) {
            if (digitalRead(buttonSim) == LOW) {
                respostaUsuario = "SIM";
            } else if (digitalRead(buttonNao) == LOW) {
                respostaUsuario = "NAO";
            }

            if (!respostaUsuario.equals(respostaCorreta)) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Resposta Errada");
                vida--;
                SomErro(buzzer);
                delay(2000);
                lcd.clear();
                if (vida <= 0) {
                    MusicaDerrota(buzzer);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Fim de Jogo");
                    delay(2000);
                    lcd.clear();
                    return 0;
                }
            } else {
                lcd.clear();
                lcd.setCursor(0, 0);  
                lcd.print("Resposta Certa");
                SomAcerto(buzzer);
                delay(1000);
                lcd.clear();
            }
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Tempo Esgotado");
            vida--;
            SomPulou(buzzer);
            delay(2000);
            lcd.clear();
            if (vida <= 0) {
                lcd.clear();
                lcd.setCursor(0, 0);  
                lcd.print("Fim de Jogo");
                MusicaDerrota(buzzer);
                delay(2000);
                lcd.clear();
                return 0;
            }
        }
        delay(500);  
    }
    return 1; 
}

int FasePerguntaFinal() {
    int randomNumber;
    String respostaUsuario;
    randomNumber = random(0, 4);
    
    lcd.setCursor(0, 0);
    lcd.print("Pergunta Final");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(questoesFinais[randomNumber]);
    
    String respostaCorreta = respostasFinaisCorretas[randomNumber];
    delay(1000);
    if (Temporizador()) {
        if (digitalRead(buttonSim) == LOW) {
            respostaUsuario = "SIM";
        } else if (digitalRead(buttonNao) == LOW) {
            respostaUsuario = "NAO";
        }
        if (!respostaUsuario.equals(respostaCorreta)) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Resposta Errada");
            MusicaDerrota(buzzer);
            delay(1000);
            lcd.clear();
            lcd.print("Fim de Jogo");
            return 0;  
        } else {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Resposta Certa");
            MusicaVitoria(buzzer);
            delay(1000);
            lcd.clear();
            lcd.print("Parabens voce ganhou!");
        }
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Tempo Esgotado");
        MusicaDerrota(buzzer);
        return 0;
    }
    return 1; 
}

void setup() {
    pinMode(3, INPUT_PULLUP); // Botão Sim
    pinMode(5, INPUT_PULLUP); // Botão Start
    pinMode(9, INPUT_PULLUP); // Botão Não
    pinMode(2, OUTPUT); // Buzzer
    pinMode(ledVerde, OUTPUT); // LED Verde
    pinMode(ledVermelho, OUTPUT); // LED Vermelho

    Serial.begin(9600);
    lcd.begin(16, 2);
}

void loop() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pressione Start");
    while (digitalRead(buttonStart) == HIGH) {}

    vida = 2; // Reinicia a vida no início do jogo
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Jogo de Memoria");
    delay(1000);
    
    AcendeLeds();
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Repita a Sequencia");
    delay(1000);
    
    VerificaMemoria();
    
    if (!SequenciaEstaCerta()) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Você Perdeu");
        MusicaDerrota(buzzer);
        delay(2000);
        lcd.clear();
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Acertou a Sequencia");
        delay(1000);
        
        if (FasePerguntas() == 1) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Fase Final");
            delay(1000);
            
            if (FasePerguntaFinal() == 0) {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Game Over");
                delay(2000);
            }
        }
    }
}
