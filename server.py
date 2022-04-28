import serial
import pymysql
import db
import time

#set a port number&baud rate

PORT='COM3'
BaudRate = 9600

ARD= serial.Serial(PORT,BaudRate)
conn = db.count_db()


while(1):
    now = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
    now_list = now.split(' ')
    line = ARD.readline()
    line = line.decode('utf-8')
    if 'name' in line :
        name_list = line.split(' ')
        print(name_list[0])
        name_list[1] = name_list[1].strip()
        print(name_list[1])
    if 'count' in line:
        count_list = line.split(' ')
        print(count_list[0])
        count_list[1] = count_list[1].strip()
        print(count_list[1])
        conn.insert_traffic_count(name_list[1],count_list[1],now_list[0], now_list[1])
