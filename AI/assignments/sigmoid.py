import numpy as np
from sklearn.datasets import load_iris
from sklearn.linear_model import Perceptron
from sklearn.metrics import accuracy_score

iris = load_iris()
#아이리스 데이터셋을 가져온다

x =  iris.data[:,(0,1)]
#아이리스 데이터의 0,1번째 값만을 채택하여 배열 재구성

y = (iris.target == 0).astype(np.int)
# (0 = setosa, 1 = versicolor, 2 = virginica)의 값을 정수로 변환시킨다.

percep = Perceptron(random_state=32)
# 퍼셉트론을 percep 변수에 할당

percep.fit(x,y)
# 데이터를 바탕으로 훈련 진행

Y_pred = percep.predict(x)
# x데이터셋을 예측모델에 삽입
print("Y data")
print(y)
print("\n\nprediced Y data")
print(Y_pred)
# Y와 예측된 Y를 출력

print("\n\ntotal testdata count: %d, error count: %d" %(len(y),(y != Y_pred).sum()))
# 예측된 결과값과의 차이가 얼마큼 나는지 비교

print("accuracy score is %d", accuracy_score(y,Y_pred))
# 정확도를 계산하여 출력
