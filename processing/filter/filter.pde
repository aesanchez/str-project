int size = 200;
float[] wave;
float[] filtered1;
float[] filtered2;
float[] buffer1;
float[] buffer2;
int buffer_size1 = 1;
int buffer_size2 = 1;
float graph_canvas_height = 500;
float button_canvas_height = 60;
String button1 = "";
String button2 = "";
int button_selection = 0;
boolean overButton1 = false;
boolean overButton2 = false;
boolean overReset = false;

void setup() {
	wave = new float[size];
	filtered1 = new float[size];
	filtered2 = new float[size];
	
	button1 = str(buffer_size1);
	button2 = str(buffer_size2);

	for(int i = 0; i < size; i++){
		wave[i] = random(1);
	}
	//poner un piso
	int param = 10;
	for(int i = 1; i < param; i++){
		wave[size-i] = 0;
	}
	//poner un techo
	for(int i = param; i < param*2; i++){
		wave[size-i] = 1;
	}

	generate_filtered_waves();
	size(900, 560);
  	textSize(15);
}

void draw() {	
	background(0);
	draw_graphs();
	draw_buttons();
}

void draw_graphs(){
	fill(0,255,0);
	float w = 1.0 * width/size;
	float h_act = graph_canvas_height/3;
	for(int i = 0; i < size; i++){
		float h = h_act * wave[i];
		rect(i*w,h_act - h,w,h);
	} 
	for(int i = 0; i < size; i++){
		float h = h_act * filtered1[i];
		rect(i*w,h_act * 2 - h,w,h);
	} 
	for(int i = 0; i < size; i++){
		float h = h_act * filtered2[i];
		rect(i*w,h_act * 3 - h,w,h);
	}
	stroke(255);
	line(0, graph_canvas_height/3 * 1, width, graph_canvas_height/3 * 1);
	line(0, graph_canvas_height/3 * 2, width, graph_canvas_height/3 * 2);
	line(0, graph_canvas_height/3 * 3, width, graph_canvas_height/3 * 3);
	stroke(0);
}

void draw_buttons(){
	//bg
	fill(75,75,75);
	rect(0, graph_canvas_height, width, button_canvas_height);
	//button1
	fill(255,255,255);
	textAlign(LEFT, CENTER);
	text("Buffer #1", 10, graph_canvas_height, 70, button_canvas_height);
	if(button_selection == 1)
    	stroke(0,255,0);
	fill(255,255,255);
	rect(90,graph_canvas_height + 15,40,30);
	stroke(0);
	fill(0,0,0);
	textAlign(CENTER, CENTER);
	text(button1, 90, graph_canvas_height + 15, 40, 27);

	//button2
	fill(255,255,255);
	textAlign(LEFT, CENTER);
	text("Buffer #2", 10+140, graph_canvas_height, 70, button_canvas_height);
	if(button_selection == 2)
    	stroke(0,255,0);
	fill(255,255,255);
	rect(90+140,graph_canvas_height + 15,40,30);
	stroke(0);
	fill(0,0,0);
	textAlign(CENTER, CENTER);
	text(button2, 90+140, graph_canvas_height + 15, 40, 27);
}

void keyPressed() {
  if(button_selection == 0){
    return;
  }
  if(keyCode == ENTER){
	try {
		buffer_size1 = Integer.parseInt(button1);
	} catch (Exception e) {
		buffer_size1 = 1;
	}
	try{
		buffer_size2 = Integer.parseInt(button2);
	} catch (Exception e) {
		buffer_size2 = 1;
	}		
	generate_filtered_waves();
	return;
  }
  if(button_selection == 1){
    if (keyCode == BACKSPACE) {
    if (button1.length() > 0) {
      button1 = button1.substring(0, button1.length()-1);
    }
  } else if (keyCode == DELETE) {
    button1 = "";
  } else if (keyCode != SHIFT && keyCode != CONTROL && keyCode != ALT) {
    button1 = button1 + key;
  }
  }
  if(button_selection == 2){
    if (keyCode == BACKSPACE) {
    if (button2.length() > 0) {
      button2 = button2.substring(0, button2.length()-1);
    }
  } else if (keyCode == DELETE) {
    button2 = "";
  } else if (keyCode != SHIFT && keyCode != CONTROL && keyCode != ALT) {
    button2 = button2 + key;
  }
  }
  
}

void mouseMoved() { 
  checkButtons(); 
}
  
void mouseDragged() {
  checkButtons(); 
}

void mousePressed(){
  if(overButton1){
    button_selection = 1;
  }else if(overButton2){
    button_selection = 2;
  }else{
    button_selection = 0;
  }
}

void checkButtons() {
  if (mouseX > 90 && mouseX < 90+40 && mouseY > graph_canvas_height + 15 && mouseY < graph_canvas_height + 15 + 30) {
    overButton1 = true;   
  } else {
    overButton1 = false;
  }
  if (mouseX > 90+140 && mouseX < 90+140+40 && mouseY > graph_canvas_height + 15 && mouseY < graph_canvas_height + 15 + 30) {
    overButton2 = true;   
  } else {
    overButton2 = false;
  }
}

void generate_filtered_waves(){	
	buffer1 = new float[buffer_size1];
	buffer2 = new float[buffer_size2];
	for(int i = 0; i < buffer_size1; i++){
		buffer1[i] = 0;
	}
	for(int i = 0; i < buffer_size2; i++){
		buffer2[i] = 0;
	}
	//filter
	for(int i = 0; i < size; i++){
		 //shift de buffers
		 for(int j = 0; j < buffer_size1-1; j++){
			 buffer1[j] = buffer1[j+1]; 
		 }
		 for(int j = 0; j < buffer_size2-1; j++){
			 buffer2[j] = buffer2[j+1]; 
		 }
		 
		 //calcular el valor filtrado
		 buffer1[buffer_size1 - 1] = wave[i];
		 float aux = 0;
		 for(int j = 0; j < buffer_size1; j++){
				 aux += buffer1[j];
		 }
		 aux = aux / buffer_size1;
		 filtered1[i] = aux;
		 
		 //calcular el valor filtrado
		 buffer2[buffer_size2 - 1] = wave[i];
		 aux = 0;
		 for(int j = 0; j < buffer_size2; j++){
				 aux += buffer2[j];
		 }
		 aux = aux / buffer_size2;
		 filtered2[i] = aux;
	}
	//endfilter
}