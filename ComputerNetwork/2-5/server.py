#20151167 이인재

#기상 알림프로그램 서버
from socket import *
from pyowm import OWM

API_KEY = '1b394ff862cea8bb6c434072d2cd7c41'
owm = OWM(API_KEY)
manager = owm.weather_manager()
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('127.0.0.1',serverPort))
serverSocket.listen(1)

print('server waiting...')

while True:
    connection, addr = serverSocket.accept()

    loc = connection.recv(2048).decode()
    obs = manager.weather_at_places(loc,'accurate')
    w = obs.get_weather()

    connction.send(w.get_status())

    serverSocket.close()
