import mysql.connector
import mysql.connector.plugins

mydb = mysql.connector.connect(
  host='localhost',
  user='SDB',
  password='BrokenFragment'
)

cursorObject = mydb.cursor()
print(mydb)