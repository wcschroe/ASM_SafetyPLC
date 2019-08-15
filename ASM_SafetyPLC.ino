//Outputs
#define contactorEnable A5
#define EMO_OUT_0 4
#define EMO_OUT_1 5
#define Door_SW1_OUT 7
	// external door switch exicitaion....#define Door_SW2_OUT, OUTPUT);
//Inputs
#define EMO_IN_0 A0
#define EMO_IN_1 A1
#define Door_SW1_IN A2
#define TMP_CNTL_ALARM 2

bool safe = false;

void pinSetup() {
	//Outputs
	pinMode(contactorEnable, OUTPUT);
	pinMode(EMO_OUT_0, OUTPUT);
	pinMode(EMO_OUT_1, OUTPUT);
	pinMode(Door_SW1_OUT, OUTPUT);
	// external door switch exicitaion....pinMode(Door_SW2_OUT, OUTPUT);

	
	//Inputs
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

	//to be addded internal and external door switches
	//to be added else for switch open error trapping
	//good to scan and store all switch states for error output to user to know which switches are in fault   (amybe in bit set to one int?)

	return safe;
}

void setup() {
	pinSetup();
} 

void loop() {
	if (safeCheck()) digitalWrite(contactorEnable, HIGH);
	else digitalWrite(contactorEnable, LOW);
}
