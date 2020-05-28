#include "Summa_Time.h"

///////// Time Settings
unsigned long SWT_timeNow = 0;
unsigned long SWT_timeLast = 0;
//Time start Settings:
int SWT_startingHour = 15;
// set your starting hour here, not below at int hour. This ensures accurate daily correction of time
int SWT_seconds = 0;
int SWT_minutes = 25;
int SWT_hours = SWT_startingHour;
int SWT_days = 0;

//Accuracy settings
int SWT_dailyErrorFast = 0; // set the average number of milliseconds your microcontroller's time is fast on a daily basis
int SWT_dailyErrorBehind = 0; // set the average number of milliseconds your microcontroller's time is behind on a daily basis
int SWT_correctedToday = 1; // do not change this variable, one means that the time has already been corrected today for the error in your boards crystal. This is true for the first day because you just set the time when you uploaded the sketch.


void Summa_Time_Calculate(){
  // put your main code here, to run repeatedly:
  SWT_timeNow = millis()/1000; // the number of milliseconds that have passed since boot
  SWT_seconds = SWT_timeNow - SWT_timeLast;
  //the number of seconds that have passed since the last time 60 seconds was reached.
  if (SWT_seconds == 60) {
    SWT_timeLast = SWT_timeNow;
    SWT_minutes = SWT_minutes + 1; 
  }
  //if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.
  if (SWT_minutes == 60){
    SWT_minutes = 0;
    SWT_hours = SWT_hours + 1; 
  }
  // if one hour has passed, start counting minutes from zero and add one hour to the clock
  if (SWT_hours == 24){
    SWT_hours = 0;
    SWT_days = SWT_days + 1;
  }
  //if 24 hours have passed, add one day
  if (SWT_hours ==(24 - SWT_startingHour) && SWT_correctedToday == 0){
    delay(SWT_dailyErrorFast*1000);
    SWT_seconds = SWT_seconds + SWT_dailyErrorBehind;
    SWT_correctedToday = 1; 
  }
  //every time 24 hours have passed since the initial starting time and it has not been reset this day before, add milliseconds or delay the program with some milliseconds.
  //Change these varialbes according to the error of your board.
  // The only way to find out how far off your boards internal clock is, is by uploading this sketch at exactly the same time as the real time, letting it run for a few days
  // and then determining how many seconds slow/fast your boards internal clock is on a daily average. (24 hours).
  if (SWT_hours == 24 - SWT_startingHour + 2) {
    SWT_correctedToday = 0; 
  }
  //let the sketch know that a new day has started for what concerns correction, if this line was not here the arduiono // would continue to correct for an entire hour that is 24 - startingHour.

}

String Summa_Time_Get() {
  String _time = "";
  _time+= String(SWT_hours);
  _time+= ",";
  _time+= String(SWT_minutes);
  _time+= ",";
  _time+= String(SWT_seconds);
  return _time;
}