#컴네 2-4
#20151167 이인재
#서버 소스코드
from socket import *

#서버의 포트번호 지정
serverPort = 12000
#UDP 소켓생성
serverSocket = socket(AF_INET, SOCK_DGRAM)
#서버의 주소와 포트 바인딩
serverSocket.bind(('localhost', serverPort))

#소문자 입력을 위한 안내
print("The server is ready to receive")

while 1:
    #소켓을 통해 클라이언트가 보내는 메시지와 클라이이너트의 주소를 갖게 된다
    message, clientAddress = serverSocket.recvfrom(2048)
    #클라이언트가 보낸 메세지를 대문자로 바꿔준다.
    modifiedMessage = message.upper()
    #소켓을 통해 다시 변환시킨 문자들을 클라이언트의 주소로 전송
    serverSocket.sendto(modifiedMessage, clientAddress)
