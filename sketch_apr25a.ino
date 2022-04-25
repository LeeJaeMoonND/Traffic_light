#define LED_R 3       // R의 핀 번호 3
#define LED_Y 4       // Y의 핀 번호 4
#define LED_G 5       // G의 핀 번호 5
#define def_dis 11
int r_time = 3;
int y_time = 1;
int g_time = 5;
int distance = 0; //Cm로 계산된 거리값을 저장해두기위해 변수를 선언합니다.
int count = 0;
bool person = false;
int time1 = 0;
int time2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y, OUTPUT);
  pinMode(LED_G, OUTPUT);
  Serial.begin(9600); 
}
 
void loop() {
  int second = 1000;

  measureDis();
  if (time1 == 0){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_R, HIGH); 
  }// 빨간 불 켜기
  else if (time1 == r_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_G, HIGH);
  }
  else if (time1 == r_time + g_time){
    turnOffAll();                  // 불 다 끄기
    digitalWrite(LED_Y, HIGH);
  }
  else if (time1 == r_time + g_time + y_time){
    time1 = -1;
  }
  if (time2 == 60) {
    time2 = -1;
    g_time = set_g_time(count);
    count = 0;
  }
  time1 += 1;
  time2 += 1;
  Serial.println(time2);
  delay(second);
}
int set_g_time(int count){
  int temp_g_time = 5 + count / 3;
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

    Serial.println(distance);
    Serial.println(count);

    counter(distance);
}
void turnOffAll() {              // turnOffAll 함수 정의
  digitalWrite(LED_R, LOW);      // 빨간 불 끄기
  digitalWrite(LED_Y, LOW);      // 노란 불 끄기
  digitalWrite(LED_G, LOW);      // 초록 불 끄기
}

void counter(int dis) {
  if (dis != def_dis){
    person = true;
  }
  else{
    if (person == true){
      count += 1;
      person = false;
    }
  }
}
