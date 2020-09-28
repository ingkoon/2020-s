#컴네 2-4
#20151167 이인재
from socket import *

#서버이름과 포트번호 설정
serverName = 'localhost'
serverPort = 12000

#UDP소켓 생성
clientSocket = socket(AF_INET, SOCK_DGRAM)

#소문자 메세지를 입력받도록 안내
message = input('input loewrcase sentence: ')

#클라이언트 소켓을 통해 메세지를 서버에 전송
clientSocket.sendto(message.encode(),(serverName, serverPort))

#서버가 보낸 메세지와 서버주소를 받아들이기 위한 변수
modifiedMessage, serverAddress = clientSocket.recvfrom(2048)

#서버로 부터 전송받은 메세지 출력
print(modifiedMessage.decode())

#클라이언트 소켓 종료
clientSocket.close()
