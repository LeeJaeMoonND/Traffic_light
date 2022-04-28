import pymysql

class count_db:
    def __init__(self):
        self.conn = pymysql.connect(host = '127.0.0.1',
                           user = 'root',
                           password = '1234',
                           db = 'traffic_count',
                           charset = 'utf8')
        self.cur = self.conn.cursor()

    def insert_traffic_count(self, name, count, date, time):
        
        self.cur.execute("INSERT INTO traffic_count VALUES('{0}',{1}, '{2}', '{3}')".format(name, count, date, time))
        self.conn.commit()
