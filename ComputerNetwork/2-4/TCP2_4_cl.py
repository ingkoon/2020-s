#TCP
#20151167 이인재
from socket import *

#서버이름, 포트번호 선언
serverName = '127.0.0.1'
serverPort = 12000

#TCP소켓 생성
clientSocket = socket(AF_INET, SOCK_STREAM)
#서버이름과 서버 포트를 통한 소켓 연결
clientSocket.connect((serverName, serverPort))

#문자가 입력받을 수 있도록 input 함수 사용
sentence = input('input lowercase sentence:')
#소켓을 통해 서버로 문장 전송, 전송과정에서 바이트 스트림 형태로 인코딩 수행
clientSocket.send(sentence.encode())
#수정된 문장을 서버로부터 전송받음
modifiedSentence = clientSocket.recv(2048)

#수정된 문장을 출력
print("From Server: ", modifiedSentence)

#소켓 연결 종료
clientSocket.close()
