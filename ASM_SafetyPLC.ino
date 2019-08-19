//Outputs
#define contactorEnable A5
#define EMO_OUT_0 4
#define EMO_OUT_1 5
#define Door_SW1_OUT 6
#define Door_SW2_OUT 7
//Inputs
#define EMO_IN_0 A0
#define EMO_IN_1 A1
#define Door_SW1_IN A2
#define Door_SW2_IN A3
#define Main_Controller_ON 2

bool safe = false;

uint16_t INPUTPINS[] = { 
	EMO_IN_0, 
	EMO_IN_1, 
	Door_SW1_IN, 
	Door_SW2_IN,
	Main_Controller_ON
};

uint16_t OUTPUTPINS[] = { 
	EMO_OUT_0, 
	EMO_OUT_1, 
	Door_SW1_OUT, 
	Door_SW2_OUT 
};

int numInputs = sizeof(INPUTPINS) / sizeof(INPUTPINS[0]);
int numOutputs = sizeof(OUTPUTPINS) / sizeof(OUTPUTPINS[0]);

void SHUTDOWN(int errorPin) {
	digitalWrite(contactorEnable, LOW);
	digitalWriteOutputs(LOW);
	while (true) {
		digitalWrite(OUTPUTPINS[errorPin], HIGH);
		delay(1000);
		digitalWrite(OUTPUTPINS[errorPin], LOW);
		delay(1000);
	}
}

void digitalWriteOutputs(uint8_t val) {
	for (int i = 0; i < numOutputs; i++) digitalWrite(OUTPUTPINS[i], val);
}

void pinSetup() {
	//Outputs
	for (int i = 0; i < numOutputs; i++) pinMode(OUTPUTPINS[i], OUTPUT);
	
	//Inputs
	for (int i = 0; i < numInputs; i++) pinMode(INPUTPINS[i], INPUT);

	digitalWriteOutputs(HIGH);
}

bool safeCheck() {
	safe = true;
	for(int i = 0; i < numInputs; i++) {
		safe &= (digitalRead(INPUTPINS[i]) == HIGH);
		if (!safe) SHUTDOWN(i);
	}
	return true;
}

bool wiringCheck() {
	for(int i = 0; i < numOutputs; i++) {
		digitalWrite(OUTPUTPINS[i], LOW);
		delay(100);
		if (digitalRead(INPUTPINS[i]) != LOW) SHUTDOWN(i);
		digitalWrite(OUTPUTPINS[i], HIGH);
	}
}

void setup() {
	pinSetup();
	wiringCheck();
	digitalWrite(contactorEnable, HIGH);
} 

void loop() {
	safeCheck();
}
