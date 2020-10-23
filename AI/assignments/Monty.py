from random import *
import sys
import io
sys.stdout = io.TextIOWrapper(sys.stdout.detach(), encoding = 'utf-8')
sys.stderr = io.TextIOWrapper(sys.stderr.detach(), encoding = 'utf-8')

class Monty:
    def __init__(self):
        self.car = 0
        self.user = 0
        self.doors = []
        self.winCnt = 0

    def assign_Car(self):
        self.car = randrange(3)
        self.user = randrange(3)
        self.doors = [1,2,3]

        for i in range(len(self.doors)):
            if i == self.car:
                self.doors[i] = "car"
            else:
                continue

    def choice(self):
        print("1차 선택")
        for i in range(len(self.doors)):
            if self.doors[i] != "car":
                continue
            elif self.doors[i] == "selected":
                continue
            else:
                print("하나의 문 개방")
                self.doors[i] = "open"
                break

    def change(self):
        for i in range(len(self.doors)):
            if self.doors[i] != "open" and i != self.user:
                print("문 변경")
                self.fin = i
            else:
                continue

    def Notchange(self):
        self.fin = self.user

    def check_win(self):
        if self.fin == self.car:
            print("승리")
            self.winCnt = self.winCnt + 1

changeUser = Monty()

for i in range(100):
    changeUser.assign_Car()
    changeUser.choice()
    changeUser.change()
    changeUser.check_win()
print("총 승리 횟수 %d" %changeUser.winCnt)
'''nonChangeUser = Monty()


for i in range(100):
    nonChangeUser.assign_Car()
    nonChangeUser.choice()
    nonChangeUser.Notchange()
    nonChangeUser.check_win()


print("문을 변경하지 않았을 시, 총 승리 횟수 %d" %nonChangeUser.winCnt)'''
