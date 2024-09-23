//Declaração dos botões
int buttonStart = 1;
int buttonSim = 2;
int buttonNao = 3;

//Declaração Buzzer
int buzzer = 5;

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
String questoesBasicas[1000];
String questoesFinais[100];

// Armazena Valores Memória
int armazenaValores[10];
int respostasUsuario[10];

void AcendeLeds(){
int randomNumber = random(0,1);
for(int i = 0; i < 10; i++){
    if(num == 0){
    digitalWrite(ledVermelhor, HIGH);
    digitalWrite(ledVerde,LOW);
    armazenaValores[i] = 0;
    } else if(num == 1) {
    digitalWrite(ledVermelho,LOW);
    digitalWrite(ledVerde,HIGH);
    armazenaValores[i] = 1;
        }
    }
}

void VerificaMemoria(){
do{
    if(botaoSim == LOW){
    respostasUsuario[contador] = 0;
    contador++;
    } else if (botaoNao == LOW){
    respostasUsuario[contador] = 1;
    contador++;
    }while(contador < 10);
        int SequenciaEstaCerta(){
        for(int i = 0;i<10;i++){
            if(respostasUsuario[i] == armazenaValores[i]){
              return 1;
              } else {
              return 0;
        }
     }
  }


void setup() {
//base dos inputs e outputs para conectar no arduino

pinMode(1,INPUT_PULLUP); // Botão Start
pinMode(2,INPUT_PULLUP); // Botão Sim
pinMode(3,INPUT_PULLUP); // Botão Não
pinMode(5,OUTPUT); // Buzzer
pinMode(13,OUTPUT); // Led Vermelho
pinMode(10,OUTPUT); // Led Verde

}

void loop() {
}

