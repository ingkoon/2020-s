#20151167 이인재
#기상 알림프로그램 서버

#기상 상태 관리를 위한 pyowm, 통신을 위한 Socket 라이브러리 import
from socket import *
from pyowm import OWM

#API KEY를 받아 변수에 저장
API_KEY = '1b394ff862cea8bb6c434072d2cd7c41'

#API 관리 권한 임가
owm = OWM(API_KEY)
mgr = owm.weather_manager()

#서버 포트번호 지정후 TCP서버 소켓 생성 및 바인딩
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('127.0.0.1',serverPort))
serverSocket.listen(1)

print('server waiting...')

while True:
    #클라이언트로부터 입력 받아들임
    connection, addr = serverSocket.accept()
    #입력 값을 변수에 할당
    loc = connection.recv(2048).decode()
    #해당 저장값을 기상 API에 인수로 전달
    obs = mgr.weather_at_place(loc)

    #날씨 데이터 변수에 할당
    w = obs.weather

    #다시 클라이언트로 현재 해당 국가의 기상현황 전달
    connection.send(w.status.encode())
