  import processing.serial.*;

  Serial myPort;
  float value1 = 0;
  float value2 = 0;

  void setup () {
    // set the window size:
    size(900, 550);
    
    println(Serial.list());
    // Open whatever port is the one you're using.
    myPort = new Serial(this, Serial.list()[0], 115200);
    delay(100);
    myPort.bufferUntil('\n');
  }

  void draw () {
    background(50);
    stroke(50);
    fill(50,50,200);
    rect(100, (height - 50) - value1*(height - 50), 300, value1*(height - 50));
    fill(50,200,50);
    rect(500, (height - 50) - value2*(height - 50), 300, value2*(height - 50));
    stroke(150,150,150);
    line(0, height-50, width, height-50);
    fill(255,255,255);
    textAlign(CENTER, CENTER);
    textSize(25);
    text("Sensor #1", 100, height - 50, 300, 50);
    text("Sensor #2", 500, height - 50, 300, 50);
  }

  void serialEvent (Serial myPort) {
    String str = myPort.readStringUntil('\n');
    if(str == null) return;
    String[] values = split(str, '/');
    value1 = float(values[0]);
    value2 = float(values[1]);
  }
