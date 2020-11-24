import matplotlib.pyplot as plt
from sklearn.svm import SVC


classifier = SVC(kernel = 'linear')
#선형 분류모델 할당

training_points = [[1, 2], [1, 5], [2, 2], [7, 5], [9, 4], [8, 2]]
#훈련용 데이터 선언

labels = [1, 1, 1, 0, 0, 0]
#Y값 선언

classifier.fit(training_points, labels)
# 훈련 시작

a = 0
b = 0
#입력을 위한 두개의 변수 선언

cnt = 0
#클래스 분류를 위한 변수 선언

class1 = []
class2 = []
Y1 = []
Y2 = []
#출력을 위한 클래스 선언

a, b = map(int, input("plz input two integer ex)1 1, if you want stop this program plz input 0 0").split())
#입력을 두개의 변수로 받아들일 수 있도록 선언

while True:

    training_points.append([a, b])
    #훈련 데이터셋에 사용자 입력값 추가

    tmp = classifier.predict([[a, b]])
    #예측된 값, 0인지 1인지에 대한 값을 받아온다.
    
    labels.append(tmp[0])
    #예측된 값을 Y에 추가한다.
    classifier.fit(training_points,labels)
    #추가된 데이터와 Y를 통해 학습을 수행한다.

    for i, j in training_points:
        if labels[cnt] == 0:
            class1.append(i)
            Y1.append(j)
        elif labels[cnt] == 1:
            class2.append(i)
            Y2.append(j)
        cnt += 1
    #반복문을 통해 클래스에 데이터 추가

    plt.scatter(class1, Y1, c = 'red', s = 10, label = 'class1')
    plt.scatter(class2, Y2, s = 10, label = 'class2')
    plt.legend(loc = 'upper right')
    #각각의 그래프를 표시하고 legend함수를 통해 클래스간의 분류 수행
    plt.show()

    a, b = map(int, input("plz input two integer ex)1 1, if you want stop this program plz input 0 0").split())
    #입력을 다시 받아들이고 위의 과정을 반복한다.

    if a == 0 and b == 0:
        print("thank you for your watching:)")
    #a b의 값이 각각 0이 들어왔을 때 프로그램을 종료한다.

    cnt = 0
    #cnt의 값 초기화
