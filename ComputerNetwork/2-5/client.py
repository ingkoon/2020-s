from socket import *
from pyowm import OWM

serverName = '127.0.0.1'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

user_input = input('날씨를 알고싶은 지역을 입력하세요: ')
clientSocket.send(user_input.encode())

w = clientSocket.recv(2048).decode()
print('%s\'s weather is %s' %(user_input, w))
clientSocket.close()
