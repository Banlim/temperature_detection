import serial
import pymysql
import datetime
import random
import json
import requests
from collections import OrderedDict
 
port = serial.Serial("/dev/ttyACM0", "9600")
 
db = pymysql.connect("localhost", "gonggam", "1234", "phpmyadmin")
curs = db.cursor()
 
ZONE = "HOUSE"
print 'Start Monitor'
 
file_data = OrderedDict()

while True:

        try:
            std = random.randint(1, 5)
            flag = False
            data = port.readline()
            print(data)
            temp = float(data)
            if(temp > 38.0): 
                flag = True
            #curs.execute("""INSERT INTO gonggam (date, name,id,phone,temperature,flag) VALUES (%s,%s,%s,%s,%s,%s)""",
                #(datetime.datetime.now().strftime('%Y-%m-%d %H:%M'), data.split(',')[0],data.split(',')[1],data.split(',')[2],data.split(',')[3],flag))
            #db.commit()
            file_data["date"] = datetime.datetime.now().strftime('%Y-%m-%d %H:%M')
            file_data["building"]= std
            file_data["temperature"] = float(data)
            file_data["flag"] = flag
            
            #print(json.dumps(file_data,indent=4))
            
            with open('./test.json', 'w') as make_file:
                json.dump(file_data,make_file,indent=4)
            #r = requests.post('http://localhost/process.php', file_data).text
            #print(r)
            
        except KeyboardInterrupt:
                break
 
port.close()
db.close()
