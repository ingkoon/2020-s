#컴네 2-4
from socket import *

serverName = 'localhost'
serverPort = 12000

clientSocket = socket(AF_INET, SOCK_DGRAM)

#소문자 메세지를 입력받도록 안내
message = input('input loewrcase sentence: ')

#클라이언트 소켓을 통해 메세지를 서버에 전송
clientSocket.sendto(message.encode(),(serverName, serverPort))

#서버가 보낸 메세지와 서버주소를 받아들이기 위한 변수
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)
print(modifiedMessage.decode())

clientSocket.close()
