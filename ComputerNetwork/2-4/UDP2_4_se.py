#컴네 2-4
#서버 소스코드
from socket import *

serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('localhost', serverPort))

print("The server is ready to receive")

while 1:
    #소켓을 통해 클라이언트가 보내는 메시지와 클라이이너트의 주소를 갖게 된다
    message, clientAddress = serverSocket.recvfrom(2048)
    #클라이언트가 보낸 메세지를 대문자로 바꿔준다.
    modifiedMessage = message.upper()
    #소켓을 통해 다시 변환시킨 문자들을 클라이언트의 주소로 전송
    serverSocket.sendto(modifiedMessage, clientAddress)
