//Outputs
#define contactorEnable A5
#define EMO_OUT_0 4
#define EMO_OUT_1 5
#define Door_SW1_OUT 6
#define Door_SW2_OUT 7
	// external door switch exicitaion....#define Door_SW2_OUT, OUTPUT);
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
	Door_SW2_IN
};

uint16_t OUTPUTPINS[] = { 
	EMO_OUT_0, 
	EMO_OUT_1, 
	Door_SW1_OUT, 
	Door_SW2_OUT 
};

int numInputs = sizeof(INPUTPINS) / sizeof(INPUTPINS[0]);
int numOutputs = sizeof(OUTPUTPINS) / sizeof(OUTPUTPINS[0]);

void SHUTDOWN() {
	while (true) {
		digitalWrite(contactorEnable, LOW);
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
	safe = 
	(digitalRead(EMO_IN_0) == HIGH) // EMO Up
	&&
	(digitalRead(EMO_IN_1) == HIGH) // EMO Up
	&&
	(digitalRead(Door_SW1_IN) == HIGH) // Panel Door Closed
	&&
	(digitalRead(Door_SW2_IN) == HIGH) // Test Site Door Closed
	&&
	(digitalRead(Main_Controller_ON) == HIGH); // Main Controller has no conditional errors

	//to be added else for switch open error trapping
	//good to scan and store all switch states for error output to user to know which switches are in fault   (amybe in bit set to one int?)

	if (safe) return true;
	else SHUTDOWN();
}

bool wiringCheck() {
	for(int i = 0; i < numOutputs; i++) {
		digitalWrite(OUTPUTPINS[i], LOW);
		delay(100);
		if (digitalRead(INPUTPINS[i]) != LOW) SHUTDOWN();
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
