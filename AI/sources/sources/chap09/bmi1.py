import matplotlib.pylab as plt
from sklearn import linear_model

# 선형 회귀 모델을 생성한다. 
reg = linear_model.LinearRegression()

# 데이터는 파이썬의 리스트로 만들어도 되고 아니면 넘파이의 배열로 만들어도 됨
X = [[0], [1], [2]]		# 2차원으로 만들어야 함
y = [3, 3.5, 5.5]		# y = x + 3

# 학습을 시킨다. 
reg.fit(X, y)	