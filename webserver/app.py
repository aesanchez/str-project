from flask import Flask, render_template                                        
from flask_socketio import SocketIO, emit
from threading import Thread                             
import time   
import eventlet
eventlet.monkey_patch()                                                                

app = Flask(__name__)
app.debug = True                                                         
app.config['SECRET_KEY'] = 'secret!'                                            
socketio = SocketIO(app)                                                        
thread = None                                                                   

def background_thread():
	i = 0                                                        
	while True:
		time.sleep(0.05)                                            
		socketio.emit('value', {'value': i%10})
		i = i + 1                       

@app.route('/')                                                                 
def index():
	global thread
	if thread is None:
		thread = Thread(target=background_thread)
		thread.start()                                                             
	return render_template('index.html')        

if __name__ == '__main__': 
	socketio.run(app)	