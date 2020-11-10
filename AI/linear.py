import numpy as np
import matplotlib.pyplot as plt

X = np.array([0.0, 1.0, 2.0])
Y = np.array([3.0, 3.5, 5.5])

W = 0 #기울기
b = 0 #절편

lrate = 0.01 #학습률
epochs = 1000 #반복횟수

n = float(len(X)) # 입력데이터의 개수

#경사하강법
for i in range(epochs):
  y_pred = W*X + b #예측값
  dW = (2/n) * sum(X * (y_pred - Y))
  db = (2/n) * sum(y_pred - Y)
  W = W - lrate * dW #기울기 수정
  b = b - lrate * db #절편수정

print ( W, b)
y_pred = W*X + b

plt.scatter(X,Y)

plt.plot([min(X), max(X)], [min(y_pred), max(y_pred)], color = 'red')
plt.show()
