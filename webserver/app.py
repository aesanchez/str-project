from flask import Flask, render_template                                        
from flask_socketio import SocketIO, emit
from threading import Thread                             
import time
import eventlet
eventlet.monkey_patch()
import serial
ser = serial.Serial('/dev/ttyACM0', 115200)                                                                

app = Flask(__name__)
app.debug = True                                                         
app.config['SECRET_KEY'] = 'secret!'                                            
socketio = SocketIO(app)                                                        
thread = None                                                                   

def background_thread():                                                   
	while True:
		time.sleep(0.001)
		serial_line = ser.readline()
		if(len(serial_line) < 9):
			break
		sensor1 = serial_line[:4]
		sensor2 = serial_line[5:-2]
		print(sensor1 + "/" + sensor2)
		socketio.emit('value', {'value1': (float(sensor1)*10),
		'value2': (float(sensor2)*10)})                   

@app.route('/')                                                                 
def index():
	global thread
	if thread is None:
		thread = Thread(target=background_thread)
		thread.start()                                                     
	return render_template('index.html')

@socketio.on('parametros')
def handle_parametros(json, methods=['GET', 'POST']):
	print("Segundos", json['segundos'])
	print("Threshold", json['threshold'])
	ser.write(b'S')
	ser.write([int(json['segundos'])])
	ser.write(b'T')
	ser.write([int(json['threshold'])])

if __name__ == '__main__': 
	socketio.run(app)