#20151167 이인재
#기상 알림프로그램 클라이언트

#기상 상태 관리를 위한 pyowm, 통신을 위한 Socket 라이브러리 import
from socket import *

#연결을 위한 주소 및 포트번호 선언
serverName = '127.0.0.1'
serverPort = 12000

#서버 포트번호 지정후 TCP 클라이언트 소켓 생성 및 연결
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

#사용자로부터 지역 입력
user_input = input('날씨를 알고싶은 지역을 입력하세요: ')
#입력받은 데이터를 서버로 전달
clientSocket.send(user_input.encode())

#서버로 부터 날씨 데이터 전달받음
w = clientSocket.recv(2048).decode()
#입력받은 날씨 데이터를 출력
print('%s\'s weather is %s' %(user_input, w))
#소켓 통신 종료
clientSocket.close()
