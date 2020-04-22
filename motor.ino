#define IN3 5 //el input3 del puente h, se conecta al pin 5
#define IN4 4 //el input4 del puente h, se conecta al pin 4

void setup() 
{
  Serial.begin(9600); //se inicia la comunicación entre el Arduino y el ordenador
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() 
{
  //El motor se inicia y comienza a girar en un sentido
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 

  //El motor gira en sentido contrario
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  //se apaga el motor
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  delay(10000); //se esperan 10segundos antes de volver a empezar
}
