#include <CmdMessenger.h>  // CmdMessenger
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=106,201
AudioPlaySerialflashRaw  playFlashRaw2;  //xy=114,281
AudioMixer4              mixLeft;         //xy=439,206
AudioMixer4              mixRight;         //xy=443,268
AudioOutputI2S           i2s1;           //xy=691,248
AudioConnection          patchCord1(playFlashRaw1, 0, mixLeft, 0);
AudioConnection          patchCord2(playFlashRaw1, 0, mixRight, 0);
AudioConnection          patchCord3(playFlashRaw2, 0, mixLeft, 1);
AudioConnection          patchCord4(playFlashRaw2, 0, mixRight, 1);
AudioConnection          patchCord5(mixLeft, 0, i2s1, 0);
AudioConnection          patchCord6(mixRight, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=100,317
// GUItool: end automatically generated code



//Program Objects
CmdMessenger cmdMessenger = CmdMessenger(Serial);

// This is the list of recognized commands.  
// In order to receive, attach a callback function to these events
enum
{
  kCommandList         , // Command to request list of available commands
  kSetLed              , // Command to request led to be set in specific state  
  kSetLedBrightness    , // Command to request led to be set in to specific brightness  
  kStatus              , // Command to request led status
};

// Callbacks define on which received commands we take action
void attachCommandCallbacks()
{
  // Attach callback methods
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kCommandList, OnCommandList);
  cmdMessenger.attach(kSetSawVolume, OnSetSawVolume);
  cmdMessenger.attach(kSetRingVolume, OnSetRingVolume);
  cmdMessenger.attach(kStatus, OnStatus);
}

// Called when a received command has no attached function
void OnUnknownCommand()
{
  Serial.println("This command is unknown!");
  ShowCommands();
}

// Callback function that shows a list of commands
void OnCommandList()
{
  ShowCommands();
}

// Callback function that sets led on or off
void OnSetLed()
{
  // Read led state argument, expects 0 or 1 and interprets as false or true 
  ledState = cmdMessenger.readBoolArg(); 
  ShowLedState();  
}

void OnStatus()
{
  // Send back status that describes the led state
  ShowLedState();  
}

// Callback function that sets led on or off
void OnSetLedBrightness()
{
  // Read led brightness argument, expects value between 0 to 255
  ledBrightness = cmdMessenger.readInt16Arg();  
  // Set led brightness
  SetBrightness();  
  // Show Led state
  ShowLedState();  
}

void ShowLedState() 
{
  Serial.print("Led status: ");
  Serial.println(ledState?"on":"off");
  Serial.print("Led brightness: ");
  Serial.println(ledBrightness);
}


void setup() {
 // Listen on serial connection for messages from the PC
  Serial.begin(115200);
  Serial1.begin(9600);
  delay(100); 
  Serial.println("Started!");
  
  // Adds newline to every command
  cmdMessenger.printLfCr();   

  // Attach my application's user-defined callback methods
  attachCommandCallbacks();
  ShowCommands();
// Audio Setup
AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(7);
  SPI.setSCK(14);
  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  delay(1000);
  
}

void loop() {
   cmdMessenger.feedinSerialData();
  // put your main code here, to run repeatedly:

}
