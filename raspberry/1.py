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
 
            curs.execute("""INSERT INTO test_table (ddate, zone, temp) VALUES (%s,%s,%s)""",
                (datetime.datetime.now().strftime('%Y-%m-%d %H:%M'), ZONE, 36))
            db.commit()
 
        except KeyboardInterrupt:
                break
 
port.close()
db.close()
