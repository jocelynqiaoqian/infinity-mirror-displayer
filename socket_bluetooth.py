import socket
import time
import RPi.GPIO as GPIO
import os
import datetime

bd_addr = "98:D3:31:40:08:51" #the address from the Arduino sensor
port = 1
connected = 0
sock = socket.socket (socket.AF_BLUETOOTH,socket.SOCK_STREAM, socket.BTPROTO_RFCOMM)
sock.connect((bd_addr,port))

data = ""
data_result =""
rpm = 0
trash = ""

GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT, initial=GPIO.LOW)

def readdata(length):
    length = length + 1
    global data
    global data_result
    data_len = 0
    temp = ""

    while not '\r' in data:    # so there are still some data in the buffer
        temp= sock.recv(max(length-data_len,1))
        print temp
        data= data + temp
        print data
        data_len= data_len + len(temp)
        print data_len
    data_result = data.replace('\r', '')
    data_result = data_result.replace('\n', '')
    print data_result
    data = ""

def emptysocket():
    sock.settimeout(0)
    try:
        trash = sock.recv(1024)
        print "trash is "
        print trash
        print "end"
        sock.settimeout(None)
    except :       
        print "no data in the buffer"
        sock.settimeout(None)

try:
    time.sleep(3)
    sock.send("1")
    print "finish"

    readdata(5)

    print data_result
    print "why"
    if data_result == 'test1':
        print "why"
        GPIO.output(4,True)
        print "motor"
        
    emptysocket()

    readdata(6)
    print data_result

    if data_result == "test2":   
        print "you are fast enough"
        os.system('omxplayer /home/pi/project/start.wav&')
    
    time.sleep(10)
    emptysocket()
    sock.send("2")
    
    os.system('omxplayer /home/pi/project/start.wav&')
    time.sleep(10)
    
    time.sleep(10)
    hour = datetime.datetime.now().strftime("%H")
    miniute = datetime.datetime.now().strftime("%M")
    second = datetime.datetime.now().strftime("%S")
    sock.send("3" + hour + miniute + second)
    second_history = second

    while 1:
        second = datetime.datetime.now().strftime("%S")
        print "now"
        print second
        print "history"
        print second_history
        if second_history != second:
            second_history = second
            print "come in"
            sock.send("3")
        

except KeyboardInterrupt:
    print "clean"
    emptysocket()
    GPIO.output(4,False)
    GPIO.cleanup()
    exit(0)
 

    
        
            

 






    