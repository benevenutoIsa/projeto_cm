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

//Respostas
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

//Resposta Final
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

//Função de temporizador 
bool Temporizador() {
    int contador; //inicia o contador
    for (contador = 30; contador > 0; contador--) { //inicicaliza o valor do contador como 30 e vai ate 0
        Serial.println(contador);
        sprintf(buffer, "%02d", contador); //transforma o contador em string e armazena na variavel buffer
        lcd.setCursor(14, 1); //posiciona o cursos no lcd
        lcd.print(buffer); //printa o buffer no lcd
        delay(1000);  //delay de 1segundo
        if (contador <= 5) { //quando o contador chegar no numero 5 ou menor que isso 
            tone(buzzer, 440);  //toca um som no buzzer
            noTone(buzzer);
        }
        if (digitalRead(buttonSim) == LOW || digitalRead(buttonNao) == LOW) { //quando um dos botões forem apertados
            noTone(buzzer); //desliga o buzzzer
            return true; 
        }
    }
    noTone(buzzer); // certifica que o buzzer é desligado
    return false;
}

//Função de som de acerto 
void SomAcerto(int buzzer) {
    delay(1000);
    tone(buzzer, 261);
    delay(500); // aumenta o tempo do som para melhor feedback
}

//Função de som de erro 
void SomErro(int buzzer) {
    delay(1000);
    tone(buzzer, 297);
    delay(500); // aumenta o tempo do som para melhor feedback
}

//Função de som de pular a questão 
void SomPulou(int buzzer) {
    delay(1000);
    tone(buzzer, 495);
    delay(500); // aumenta o tempo do som para melhor feedback
}

//Função de som de derrota 
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

//Função de som de vitoria 
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

//Jogo da memoria
//Função de acender os leds
void AcendeLeds() {
    for (int i = 0; i < 10; i++) { //acende os leds 10 vezes
        int randomNumber = random(0, 2); //gera um numero aleatorio
        if (randomNumber == 1) { //se o numero gerado for igual a 1
            digitalWrite(ledVermelho, HIGH); //acende o led vermelho
            digitalWrite(ledVerde, LOW); //apaga o led verde
            armazenaValores[i] = 0; //armazena 0 na posição i do array
            delay(500);  
            digitalWrite(ledVermelho, LOW); //apaga led vermelho 
        } else { //seNão
            digitalWrite(ledVermelho, LOW); //apaga o led vermelho
            digitalWrite(ledVerde, HIGH); //acende o led verde
            armazenaValores[i] = 1; //armazena 1 na posição i do array 
            delay(500);
            digitalWrite(ledVerde, LOW); //apaga o led verde
        }
        delay(500);
    } 
}

//Função de armazenar os valores gerados pelo usuario
void VerificaMemoria() {
    int contador = 0; //inicia o contador em 0
    lcd.clear(); //limpa o lcd
    do {
        Serial.println(contador);
        if (digitalRead(buttonSim) == LOW) {  //se o botão SIM for apertado 
            respostasUsuarioMemoria[contador] = 0;  //armazena 0 no array RespostaUsuarioMemoria na posição referente ao contador 
            contador++;  //soma +1 no contador 
            Serial.println(respostasUsuarioMemoria[contador]); 
            delay(500);
        } else if (digitalRead(buttonNao) == LOW) { //se o botão NAO for apertado 
            respostasUsuarioMemoria[contador] = 1; //armazena 1 no array RespostaUsuarioMemoria na posição referente ao contador 
            contador++;
            delay(500);
        }
    } while (contador < 10); //repete o laço enquanto o contador for menor que 10 
}

//Função de verificar se a sequencia digitada pelo usuario esta correta 
bool SequenciaEstaCerta() {
    lcd.clear();  //limpa lcd
    for (int i = 0; i < 10; i++) {  //para cada posição no array 
        if (respostasUsuarioMemoria[i] != armazenaValores[i]) {  //compara os valores dos dois arrays
            lcd.setCursor(0, 0);  //seta o cursor na posição 0 
            lcd.print("Sequencia Incorreta");  //se o restorno da comparação for falso ele retorna "Sequencia Incorreta" no lcd
            return false;
        }
    }
    return true; //se o restorno das comparações forem iguais ele retorna true 
}

//Jogo das Perguntas
//Função das pergunts basicas 
int FasePerguntas() {
  lcd.clear();  //limpa lcd
  int randomNumber; //inicia a variavel randomNumber 
    for (int i = 0; i < 5; i++) {   //percorre o laço 5 vezes 
        String respostaUsuario;  //inicia a string de resposta
        randomNumber = random(0, 8);  //gera um numero aleatorio
        String respostaCorreta = respostasCorretas[randomNumber]; //armazena a resposta correta na posição do numero aleatorio na string resposta correta
        
        lcd.setCursor(0, 0);  //seta o cursos 0
        lcd.print(questoesBasicas[randomNumber]);  //printa a questão no lcd
        
        delay(1000);
        if (Temporizador()) { //chama a função temporizador 
            if (digitalRead(buttonSim) == LOW) {  //se o temporizador for verdadeiro e o botão sim for apertado
                respostaUsuario = "SIM";  //a resposta do usuario vai ser SIM
            } else if (digitalRead(buttonNao) == LOW) {  //se o botão não for apertado
                respostaUsuario = "NAO";  //a respota do usuario vai ser NÃO
            }

            if (!respostaUsuario.equals(respostaCorreta)) {  //compara as respostas e se estiverem diferente 
                lcd.clear();  //limpa lcd
                lcd.setCursor(0, 0);  //seta o cursor na posição 0
                lcd.print("Resposta Errada");  //printa "Resposta Errada"
                vida--;  //diminui a vida do jogador
                SomErro(buzzer);  //toca o som de erro 
                delay(2000);
                lcd.clear();  //limpa o lcd
                if (vida <= 0) { //se a vida for menor=0
                    MusicaDerrota(buzzer);  //toca musica derrota
                    lcd.clear();  //limpa lcd
                    lcd.setCursor(0, 0);  //seta o cursor na posição 0
                    lcd.print("Fim de Jogo"); //printa "Fim de jogo"
                    delay(2000);
                    lcd.clear(); //limpa lcd
                    return 0;
                }
            } else {   //se as respostas forem iguais 
                lcd.clear(); //limpa lcd
                lcd.setCursor(0, 0);  //seta o cursor na posição 0
                lcd.print("Resposta Certa"); //printa "Resposta Certa"
                SomAcerto(buzzer);  //toca o som de acerto 
                delay(1000);
                lcd.clear();  //limpa lcd
            }
        } else { //caso quando o tempo acaba
            lcd.clear();  //limpa lcd
            lcd.setCursor(0, 0); //seta o cursor na posição 0
            lcd.print("Tempo Esgotado");  //printa "Tempo Esgotado"
            vida--;  //diminui a vida do jogador
            SomPulou(buzzer);  //toca o som de pular rodada
            delay(2000);
            lcd.clear();  //limpa lcd
            if (vida <= 0) {  //caso se a vida do jogador esgotar
                lcd.clear();  //limpa lcd
                lcd.setCursor(0, 0);   //seta o cursor na posição 0
                lcd.print("Fim de Jogo");  //printa "Fim de jogo"
                MusicaDerrota(buzzer);  //toca a musica de derrota
                delay(2000);  
                lcd.clear();  //limpa lcd
                return 0;
            }
        }
        delay(500);  
    }
    return 1; 
}

//Pergunta final 
int FasePerguntaFinal() {
    int randomNumber; //inicia a variavel randomNumber 
    String respostaUsuario; //inicia a string de resposta
    randomNumber = random(0, 4);  //gera um numero aleatorio
    
    lcd.setCursor(0, 0);  //seta o cursor na posição 0
    lcd.print("Pergunta Final");  //printa "Pergunta Final"
    lcd.clear();  //limpa lcd
    lcd.setCursor(0, 0);  //seta o cursor na posição 0
    lcd.print(questoesFinais[randomNumber]);  //printa a pergunta final localizada no numero aleatorio gerado 
    
    String respostaCorreta = respostasFinaisCorretas[randomNumber];  //armazena a resposta correta na posição do numero aleatorio na string resposta correta
    delay(1000);
    if (Temporizador()) {  //chama a função temporizador 
        if (digitalRead(buttonSim) == LOW) {  //se o temporizador for verdadeiro e o botão sim for apertado
            respostaUsuario = "SIM";  //a resposta do usuario vai ser SIM
        } else if (digitalRead(buttonNao) == LOW) {  //se o botão não for apertado
            respostaUsuario = "NAO";  //a respota do usuario vai ser NÃO
        }
        if (!respostaUsuario.equals(respostaCorreta)) {  //se o usuario colocar uma resposta diferente da correta  
            lcd.clear();  //limpa lcd
            lcd.setCursor(0, 0);  //seta o cursor na posição 0
            lcd.print("Resposta Errada");  //printa "Resposta Errada"
            MusicaDerrota(buzzer);  //toca musica de derrota
            delay(1000);
            lcd.clear();  //limpa lcd
            lcd.print("Fim de Jogo");  //printa "Fim de Jogo"
            return 0;  
        } else {
            lcd.clear();  //limpa lcd
            lcd.setCursor(0, 0);  //seta o cursor na posição 0
            lcd.print("Resposta Certa");   //printa "Resposta Certa"
            MusicaVitoria(buzzer);    //toca musica de vitoria
            delay(1000);
            lcd.clear();  //limpa lcd
            lcd.print("Parabens voce ganhou!"); //printa "Parabens voce ganhou!"
        }
    } else {  //caso o tempo do temporizador se esgote
        lcd.clear();  //limpa lcd
        lcd.setCursor(0, 0);  //seta o cursor na posição 0
        lcd.print("Tempo Esgotado");  //printa "Tempo Esgotado"
        MusicaDerrota(buzzer);   //toca musica de vitoria
        return 0;
    }
    return 1; 
}


//inicia o setup
void setup() {
    pinMode(3, INPUT_PULLUP); // Botão Sim
    pinMode(5, INPUT_PULLUP); // Botão Start
    pinMode(9, INPUT_PULLUP); // Botão Não
    pinMode(2, OUTPUT); // Buzzer
    pinMode(ledVerde, OUTPUT); // LED Verde
    pinMode(ledVermelho, OUTPUT); // LED Vermelho

    Serial.begin(9600);  //inicia o serial
    lcd.begin(16, 2);   //inicia o lcd
}

//inicia o loop
void loop() {
    lcd.clear();  //limpa lcd
    lcd.setCursor(0, 0);  //seta o cursor na posição 0
    lcd.print("Pressione Start");  //aparece a mensagem para inicar o jogo 
    while (digitalRead(buttonStart) == HIGH) {} 

    vida = 2; // Reinicia a vida no início do jogo
    lcd.clear();  //limpa lcd
    lcd.setCursor(0, 0);  //seta o cursor na posição 0
    lcd.print("Jogo de Memoria");  //aparece a mensagem dizendo que ira começar o jogo da memoria
    delay(1000);
    
    AcendeLeds();  //chama função de acender os leds para o jogo
    
    lcd.clear();  //limpa lcd
    lcd.setCursor(0, 0);  //seta o cursor na posição 0
    lcd.print("Repita a Sequencia"); //aparece a mensagem indicando que chegou a vez do usuario repetir a sequencia 
    delay(1000);
    
    VerificaMemoria();  //verifica se os valores referente a sequencia são iguais 
    
    if (!SequenciaEstaCerta()) {  //se a sequencias estiver diferente da correta 
        lcd.clear();  //limpa lcd
        lcd.setCursor(0, 0);  //seta o cursor na posição 0
        lcd.print("Você Perdeu"); //printa "Você Perdeu"
        MusicaDerrota(buzzer);  //toca musica de derrota
        delay(2000);
        lcd.clear();  //limpa lcd
    } else {  //caso as sequencias estejam iguais 
        lcd.clear();  //limpa lcd
        lcd.setCursor(0, 0);  //seta o cursor na posição 0
        lcd.print("Acertou a Sequencia");  //printa "Acertou a Sequencia"
        delay(1000);
        
        if (FasePerguntas() == 1) {  //se todas as respostas estiverem certas 
            lcd.clear();  //limpa lcd
            lcd.setCursor(0, 0);  //seta o cursor na posição 0
            lcd.print("Fase Final");  //printa "Fase Final"
            delay(1000);
            
            if (FasePerguntaFinal() == 0) {  //se as respostas estiverem erradas 
                lcd.clear();  //limpa lcd
                lcd.setCursor(0, 0);  //seta o cursor na posição 0
                lcd.print("Game Over");  //printa "Game Over"
                delay(2000);
            }
        }
    }
}
