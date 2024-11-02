// =========== DEFINE PIN =================================
#define AmotorR PE13
#define AmotorL PB10
#define BmotorL PE6
#define BmotorR PB6
#define CmotorR PC8
#define CmotorL PC9
#define DmotorR PB7
#define DmotorL PE5

#define AmotorENC PC15
#define BmotorENC PE4
#define CmotorENC PE3
#define DmotorENC PE2

#define PinEnable PE7
#define emergency PA0

//============ DEFINE VARIABEL BUAT PID ===================
float Kp = 1.0;
float Ki = 0.0;
float Kd = 0.0;

// ========== FUNGSI HOLONOMIC =============================
void holonomic(float vx, float vy, float vz) {
    float SpeedA = (-0.35 * vx) + (0.35 * vy) + (0.25 * vz); 
    float SpeedB = (-0.35 * vx) + (-0.35 * vy) + (0.25 * vz);
    float SpeedC = (0.35 * vx) + (-0.35 * vy) + (0.25 * vz);
    float SpeedD = (0.35 * vx) + (0.35 * vy) + (0.25 * vz);

    Serial.print("A: "); Serial.print(SpeedA);
    Serial.print(" B: "); Serial.print(SpeedB);
    Serial.print(" C: "); Serial.print(SpeedC);
    Serial.print(" D: "); Serial.println(SpeedD);

    // ========= Mengendalikan Motor ========
    controlMotor(AmotorR, AmotorL, SpeedA);
    controlMotor(BmotorR, BmotorL, SpeedB);
    controlMotor(CmotorR, CmotorL, SpeedC);
    controlMotor(DmotorR, DmotorL, SpeedD);
}
// ========= FUNGSI GERAKIN MOTOR DARI HOLONOMIC =======
void controlMotor(int motorR, int motorL, float speed) {
    int pwmValue = abs(speed) * 100;

    if (speed > 0) {
        analogWrite(motorR, pwmValue);
        analogWrite(motorL, 0);
    } else if (speed < 0) {
        analogWrite(motorR, 0);
        analogWrite(motorL, pwmValue);
    } else {
        analogWrite(motorR, 0);
        analogWrite(motorL, 0);
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("hai");
    pinMode(AmotorR, OUTPUT);
    pinMode(AmotorL, OUTPUT);
    pinMode(BmotorR, OUTPUT);
    pinMode(BmotorL, OUTPUT);
    pinMode(CmotorR, OUTPUT);
    pinMode(CmotorL, OUTPUT);
    pinMode(DmotorR, OUTPUT);
    pinMode(DmotorL, OUTPUT);
    pinMode(PinEnable, OUTPUT);
    pinMode(emergency, INPUT);
}

void loop() {
    // =========== Gerakan XYZ ============
    float x = 0;   
    float y = 1;
    float z = 0;
    holonomic(x, y, z);

    // ========= Tombol Emergency =========
    if (digitalRead(emergency) == LOW) {
        digitalWrite(PinEnable, LOW);
        analogWrite(AmotorR, 0);
        analogWrite(BmotorR, 0);
        analogWrite(CmotorR, 0);
        analogWrite(DmotorR, 0);
        analogWrite(AmotorL, 0);
        analogWrite(BmotorL, 0);
        analogWrite(CmotorL, 0);
        analogWrite(DmotorL, 0);
    } else {
        digitalWrite(PinEnable, HIGH);
    }
    // ====================================
}
