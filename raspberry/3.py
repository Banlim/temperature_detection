import serial
import pymysql
import datetime
import random
 
port = serial.Serial("/dev/ttyACM0", "9600")
 
db = pymysql.connect("localhost", "gonggam", "1234", "phpmyadmin")
curs = db.cursor()
 
ZONE = "HOUSE"
print 'Start Monitor'
 

while True:

        try:
            std = random.randint(1000, 9000)
            flag = False
            print(flag)
            data = port.readline()
            print("test")
            print(data)
            temp = float(data)
            if(temp > 38.0): 
                flag = True
            curs.execute("""INSERT INTO gonggam (date, name,id,phone,temperature,flag) VALUES (%s,%s,%s,%s,%s,%s)""",
                (datetime.datetime.now().strftime('%Y-%m-%d %H:%M'), "test",std,"010-1234-1234",data,flag))
            db.commit()
        except KeyboardInterrupt:
                break
 
port.close()
db.close()
