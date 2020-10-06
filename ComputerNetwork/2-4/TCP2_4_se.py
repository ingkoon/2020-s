#TCP서버
#20151167
from socket import *

#포트번호 설정
serverPort = 12000

#TCP소켓 생성
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('127.0.0.1',serverPort))
serverSocket.listen(1)

print('The server is ready to receive')

while True:
    #서버소켓으로 연결
    connectionSocket, addr = serverSocket.accept()

    #클라이언트로부터 입력 대기
    sentence = connectionSocket.recv(2048)
    #입력받은 문장을 대문자로 변경
    capitalizedSentence = sentence.upper()
    #대문자로 변경한 문장을 다시 클라이언트로 전달
    connectionSocket.send(capitalizedSentence)
    #소켓 연결 종료
    connectionSocket.close()
