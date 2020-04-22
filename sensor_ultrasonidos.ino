#define ECHO_PIN 8 //el echo va al pin 8
#define TRIGGER_PIN 9 //el trigger va al pin 9

float tiempo, distancia;

void setup() 
{
  Serial.begin(9600); //se incia la comunicación serie del Arduino con el ordenador
  pinMode(ECHO_PIN, INPUT); //se define echo como entrada
  pinMode(TRIGGER_PIN, OUTPUT); //se define trigger como salida ya que es el que emite la onda
}


void loop() 
{
  distancia = ultrasonidos(tiempo);
}


float ultrasonidos(float) //se crea una función que calcula la distancia que hay entre el sensor y un objeto delante suya
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
