#include <Servo.h> //se incluye la librería del servomotor
#define SERVO 11 //se asigna el pin 11 al servomotor
#define ECHO_PIN 8 //el echo va al pin 8
#define TRIGGER_PIN 9 //el trigger va al pin 9
#define IN3 5 //el input3 del puente h se conecta al pin 5
#define IN4 4 //el input4 del puente h se conecta al pin 4
#define ENB 6

enum Estados{INICIO, MEDIR};

int tiempo, distancia; //se crean las variables globales tiempo y distancia de tipo float
Servo servomotor; //se crea la variable servomotor de tipo servo
int posicion_inicial = 0;
Estados Estado;
int angulo;
int velocidad = 200;

void setup() 
{
  Serial.begin(9600); //se incia la comunicación serie del Arduino con el ordenador
  pinMode(ECHO_PIN, INPUT); //se define echo como entrada
  pinMode(TRIGGER_PIN, OUTPUT); //se define trigger como salida ya que es el que emite la onda
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  reset_hw(); //reinicializa la posición del servo
}

void reset_hw() //reinicializa la posición del servomotor
{
  servomotor.attach(SERVO); //se vincula el pin 11 al servo
  servomotor.write(0);
  delay(1000);
  servomotor.detach();
  Estado = INICIO;
}

void loop() 
{
  char dato;

  switch(Estado)
  {
    case INICIO: if (Serial.available()>0)
                 {
                    if(Serial.read() == '1')
                    {
                      digitalWrite(IN3, HIGH);
                      digitalWrite(IN4, LOW);
                      digitalWrite(ENB, velocidad);
                      Estado = MEDIR;
                      angulo = 0;
                      servomotor.attach(SERVO);
                    }

                    else
                       if(Serial.read() == '0')
                      {
                        digitalWrite(IN3, LOW);
                        digitalWrite(IN4, LOW);
                        digitalWrite(ENB, 0);
                        servomotor.detach();
                      }
                 }
                 break;
    case MEDIR : distancia = ultrasonidos(tiempo);
                 if(angulo<180)
                 {
                    Serial.write(distancia); //envía datos de la distancia
                    Serial.write(angulo); //envía datos del ángulo
                    angulo++; //incrementa el ángulo en una unidad
                    servomotor.write(angulo); //gira el servomotor al nuevo ángulo
                    delay(50);
                 }
                 else
                 {
                  Estado = INICIO;  //giro completado
                  servomotor.write(0);  //servomotor a origen
                  delay(1000);
                  servomotor.detach();
                 }
                 break;
  }
}


int ultrasonidos(int) //se crea una función que calcula la distancia que hay entre el sensor y un objeto delante suya
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH); //se emite la onda deultrasonidos de 10 microsegundos
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  tiempo = pulseIn(ECHO_PIN, HIGH); //se guarda el tiempo que tarda la onda en ir y volver al rebotar contra un objeto

  distancia = (tiempo/2)/29.2; //se calcula la mitad de la distancia que ha tardado la onda en ir y volver
  
  Serial.print("Distancia: ");
  Serial.println(distancia);

  return distancia;
}
