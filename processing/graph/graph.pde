  import processing.serial.*;

  Serial myPort;
  float value1 = 0;
  float value2 = 0;

  void setup () {
    // set the window size:
    size(275, 300);
    
    println(Serial.list());
    // Open whatever port is the one you're using.
    myPort = new Serial(this, Serial.list()[0], 115200);
    delay(100);
    myPort.bufferUntil('\n');
  }

  void draw () {
    background(0);
    fill(0,0,255);
    rect(25, height - value1*height, 100, value1*height);
    fill(0,255,0);
    rect(150, height - value2*height, 100, value2*height);
  }

  void serialEvent (Serial myPort) {
    String str = myPort.readStringUntil('\n');
    if(str == null) return;
    String[] values = split(str, '/');
    value1 = float(values[0]);
    value2 = float(values[1]);
  }
