#define contactorEnable A5
#define EMO_OUT_0 4
#define EMO_OUT_1 5
#define Door_SW1_OUT 7

#define EMO_IN_0 A0
#define EMO_IN_1 A1
#define Door_SW1_IN A2
#define TMP_CNTL_ALARM 2

bool safe = false;

void pinSetup() {
	pinMode(contactorEnable, OUTPUT);
	pinMode(EMO_OUT_0, OUTPUT);
	pinMode(EMO_OUT_1, OUTPUT);
	pinMode(Door_SW1_OUT, OUTPUT);

	pinMode(EMO_IN_0, INPUT);
	pinMode(EMO_IN_1, INPUT);
	pinMode(Door_SW1_IN, INPUT);
	pinMode(TMP_CNTL_ALARM, INPUT);
}

void digitalWriteOutputs(uint8_t val) {
	digitalWrite(EMO_OUT_0, val);
	digitalWrite(EMO_OUT_1, val);
	digitalWrite(Door_SW1_OUT, val);
}

bool safeCheck() {
	if (digitalRead(TMP_CNTL_ALARM) == HIGH) digitalWriteOutputs(HIGH);
	else digitalWriteOutputs(LOW);

	safe = 
	(digitalRead(EMO_IN_0) == HIGH)
	&&
	(digitalRead(EMO_IN_1) == HIGH);

	return safe;
}

void setup() {
	pinSetup();
} 

void loop() {
	if (safeCheck()) digitalWrite(contactorEnable, HIGH);
	else digitalWrite(contactorEnable, LOW);
}
