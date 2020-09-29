#TCP
#20151167 이인재
from socket import *

#서버이름, 포트번호 선언
serverName = 'servername'
serverPort = 12000

#TCP소켓 생성
clientSocket = socket(AF_INET, SOCK_STREAM)
#서버이름과 서버 포트를 통한 소켓 연결
clientSocket.connect((serverName, serverPort))

#문자가 입력받을 수 있도록 input 함수 사용
sentence = raw_input('input lowercase sentence:')
#소켓을 통해 서버로 문장 전송
clientSocket.send(sentence)
#수정된 문장을 서버로부터 전송받음
modifiedSentence = clientSocket.recv(1024)

#수정된 문장을 출력
print("From Server: ", modifiedSentence)

#소켓 연결 종료
clientSocket.close()
