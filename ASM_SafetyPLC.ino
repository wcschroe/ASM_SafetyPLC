//Outputs
#define contactorEnable A5
#define EMO_OUT_0 4
#define EMO_OUT_1 5
#define Door_SW1_OUT 7
#define Door_SW2_OUT 6
	// external door switch exicitaion....#define Door_SW2_OUT, OUTPUT);
//Inputs
#define EMO_IN_0 A0
#define EMO_IN_1 A1
#define Door_SW1_IN A2
#define Door_SW2_IN A3
#define Main_Controller_ON 2

bool safe = false;
unsigned long wiringCheckInterval = 10000;

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

void digitalWriteOutputs(uint8_t val) {
	digitalWrite(EMO_OUT_0, val);
	digitalWrite(EMO_OUT_1, val);
	digitalWrite(Door_SW1_OUT, val);
	digitalWrite(Door_SW2_OUT, val);
}

void pinSetup() {
	//Outputs
	pinMode(contactorEnable, OUTPUT);
	pinMode(EMO_OUT_0, OUTPUT);
	pinMode(EMO_OUT_1, OUTPUT);
	pinMode(Door_SW1_OUT, OUTPUT);
	pinMode(Door_SW2_OUT, OUTPUT);

	
	//Inputs
	pinMode(EMO_IN_0, INPUT);
	pinMode(EMO_IN_1, INPUT);
	pinMode(Door_SW1_IN, INPUT);
	pinMode(Door_SW2_IN, INPUT);
	pinMode(Main_Controller_ON, INPUT);

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
	else return false;
}

void wiringCheck() {

}

void setup() {
	pinSetup();
} 

void loop() {
	if (safeCheck()) digitalWrite(contactorEnable, HIGH);
	else {
		digitalWrite(contactorEnable, LOW);
		while (true) safeCheck();
	}
}
