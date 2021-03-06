#define LED_UP_R 3       // R의 핀 번호 3
#define LED_UP_Y 4       // Y의 핀 번호 4
#define LED_UP_G 5       // G의 핀 번호 5

#define LED_DOWN_R 6       // R의 핀 번호 6
#define LED_DOWN_Y 7       // Y의 핀 번호 7
#define LED_DOWN_G 8       // G의 핀 번호 8

#define LED_CAR_R 9       // R의 핀 번호 9
#define LED_CAR_Y 10       // Y의 핀 번호 10
#define LED_CAR_G 11      // G의 핀 번호 11

#define def_dis 21
#define second 1000

String street_name = "jungwang_light";
int r_time = 3;
int y_time = 1;
int g_time = 5;
int distance_1 = 0; //Cm로 계산된 거리값을 저장해두기위해 변수를 선언합니다.
int distance_2 = 0;
int count = 0;
bool person_1 = false;
bool person_2 = false;

int light_time = 0;
int time2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_UP_R, OUTPUT);
  pinMode(LED_UP_Y, OUTPUT);
  pinMode(LED_UP_G, OUTPUT);
  pinMode(LED_DOWN_R, OUTPUT);
  pinMode(LED_DOWN_Y, OUTPUT);
  pinMode(LED_DOWN_G, OUTPUT);
  pinMode(LED_CAR_R, OUTPUT);
  pinMode(LED_CAR_Y, OUTPUT);
  pinMode(LED_CAR_G, OUTPUT);
  Serial.begin(9600); 
}
 
void loop() {

  Serial.print("port 0 ");
  Serial.println(distance_1);
  Serial.print("port 1 ");
  Serial.println(distance_2);

  measureDis();
 


  //Serial.print("count ");
  //Serial.println(count);
  light_time = control_time_light(light_time, r_time, y_time, g_time);
  if (time2 == 10) {
    Serial.println("name "+street_name);
    Serial.print("count ");
    Serial.println(count);
    time2 = -1;
    g_time = set_g_time(count);
    count = 0;
   
  }
  light_time += 1;
  time2 += 1;
  delay(second);
}

int control_time_light(int light_time, int r_time, int y_tim, int g_time){
  if (light_time == 0){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_UP_R, HIGH); 
    digitalWrite(LED_DOWN_R, HIGH);
    digitalWrite(LED_CAR_G, HIGH);      // 초록 불 끄기
  }// 빨간 불 켜기
  else if (light_time == r_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_UP_G, HIGH);
    digitalWrite(LED_DOWN_G, HIGH);
    digitalWrite(LED_CAR_R, HIGH);      // 초록 불 끄기

  }
  else if (light_time == r_time + g_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_UP_Y, HIGH);
    digitalWrite(LED_DOWN_Y, HIGH);
    digitalWrite(LED_CAR_Y, HIGH);      // 초록 불 끄기
  }
  else if (light_time == r_time + g_time + y_time){
    light_time = -1;
  }
  return light_time;
}

void turnOffAll() {              // turnOffAll 함수 정의
  digitalWrite(LED_UP_R, LOW);      // 빨간 불 끄기
  digitalWrite(LED_UP_Y, LOW);      // 노란 불 끄기
  digitalWrite(LED_UP_G, LOW);      // 초록 불 끄기
  digitalWrite(LED_DOWN_R, LOW);      // 빨간 불 끄기
  digitalWrite(LED_DOWN_Y, LOW);      // 노란 불 끄기
  digitalWrite(LED_DOWN_G, LOW);      // 초록 불 끄기
  digitalWrite(LED_CAR_R, LOW);      // 빨간 불 끄기
  digitalWrite(LED_CAR_Y, LOW);      // 노란 불 끄기
  digitalWrite(LED_CAR_G, LOW);      // 초록 불 끄기
}

int set_g_time(int count){
  int temp_g_time = 5 + count;
  if (temp_g_time > 10){
    return 10;
  }
  else {
    return temp_g_time;
  }
}

void measureDis() {
  int volt = map(analogRead(A0), 0, 1023, 0, 5000);
  distance_1 = (27.61 / (volt - 0.1696)) * 1000; 

  counter(distance_1 , 1);
  
  volt = map(analogRead(A1), 0, 1023, 0, 5000);
  distance_2 = (27.61 / (volt - 0.1696)) * 1000; 

  counter(distance_2, 2);
}

void counter(int dis, int port) {
  if (dis < def_dis){
    if (port == 1){
      person_1 = true;
    }
    else {
      person_2 = true;
    }
  }
  else{
    if (port == 1){
      if (person_1 == true){
        count += 1;
        person_1 = false;
      }
    }
    else{
      if (person_2 == true){
        count += 1;
        person_2 = false;
     }
    }
  }
}
