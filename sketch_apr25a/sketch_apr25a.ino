#define LED_R 3       // R의 핀 번호 3
#define LED_Y 4       // Y의 핀 번호 4
#define LED_G 5       // G의 핀 번호 5
#define def_dis 9
#define second 1000

String street_name = "jungwang_light";
int r_time = 3;
int y_time = 1;
int g_time = 5;
int distance = 0; //Cm로 계산된 거리값을 저장해두기위해 변수를 선언합니다.
int count = 0;
bool person = false;
int light_time = 0;
int time2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  Serial.begin(9600); 
}
 
void loop() {
  
  measureDis();
  //Serial.println(distance);
  //Serial.print("count ");
  //Serial.println(count);
  light_time = control_time_light(light_time, r_time, y_time, g_time);
  if (time2 == 60) {
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
    digitalWrite(LED_R, HIGH); 
  }// 빨간 불 켜기
  else if (light_time == r_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_G, HIGH);
  }
  else if (light_time == r_time + g_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_Y, HIGH);
  }
  else if (light_time == r_time + g_time + y_time){
    light_time = -1;
  }
  return light_time;
}

void turnOffAll() {              // turnOffAll 함수 정의
  digitalWrite(LED_R, LOW);      // 빨간 불 끄기
  digitalWrite(LED_Y, LOW);      // 노란 불 끄기
  digitalWrite(LED_G, LOW);      // 초록 불 끄기
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

    distance = (27.61 / (volt - 0.1696)) * 1000; 

    counter(distance);
    //Serial.println(distance);

}

void counter(int dis) {
  if (dis != def_dis && dis != def_dis -1){
    person = true;
  }
  else{
    if (person == true){
      count += 1;
      person = false;
    }
  }
}
