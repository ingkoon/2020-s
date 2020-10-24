from random import *
#난수 발생을 위한 라이브러리 import
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.detach(), encoding = 'utf-8')
sys.stderr = io.TextIOWrapper(sys.stderr.detach(), encoding = 'utf-8')

class Monty:
    def __init__(self):
        self.winCnt = 0
    #성공 count를 위한 변수 선언

    def assign_Car(self):
        self.car = randrange(3)
        self.user = randrange(3)
        self.doors = [1,2,3]
    #배열 선언 및 차가 있는 위치와 사용자가 선택한 번호를 난수로 선언

    def open(self):
        for i in range(len(self.doors)):
            if i == self.car:
                continue
            #open할 문의 위치가 차가 있는 위치와 같을 경우 통과
            elif i == self.user:
                continue
            #open할 문의 위치가 사용자가 선택한 위치와 같을 경우 통과
            else:
                self.doors[i] = "open"
                break
            #사용자가 선택한부분과 차가 들어있는 부분을 제외한 나머지 하나를 open한다.

    def change(self):
        for i in range(len(self.doors)):
            if self.doors[i] != "open" and i != self.user:
                self.fin = i
            else:
                continue
    # open한 부분과 사용자가 선택한 부분을 제외한 문을 최종선택하도록 변경하는 change함수

    def Notchange(self):
        self.fin = self.user
    #처음선택을 마지막 선택으로 하는 Notchange

    def check_win(self):
        if self.fin == self.car:
            self.winCnt = self.winCnt + 1
    # fin을 위치를 통해 승리했는가의 여부를 검사

changeUser = Monty()
#바꾼 상황에 대한 객체 생성
for i in range(10000):
    changeUser.assign_Car()
    changeUser.open()
    changeUser.change()
    changeUser.check_win()
#보다 더 정확한 결과를 위한 반복문 선언

nonChangeUser = Monty()
#바꾸지 않은 상태에 대한 객체 생성
for i in range(10000):
    nonChangeUser.assign_Car()
    nonChangeUser.open()
    nonChangeUser.Notchange()
    nonChangeUser.check_win()
#보다 더 정확한 결과를 위한 반복문 선언

print("문을 변경 했을 시, 총 승리 횟수 %d" %changeUser.winCnt)
print("문을 변경하지 않았을 시, 총 승리 횟수 %d" %nonChangeUser.winCnt)
