import serial
import pymysql
import datetime
 
port = serial.Serial("/dev/ttyACM0", "9600")
 
db = pymysql.connect("localhost", "gonggam", "1234", "phpmyadmin")
curs = db.cursor()
 
ZONE = "HOUSE"
print 'Start Monitor'
 
while True:
        try:
            data = port.readline()
 
            print("House temp/humi is ")
            print(data)  
 
            curs.execute("""INSERT INTO temp (date, temp) VALUES (%s,%s)""",
                (datetime.datetime.now().strftime('%Y-%m-%d %H:%M'), data))
            db.commit()
 
        except KeyboardInterrupt:
                break
 
port.close()
db.close()
