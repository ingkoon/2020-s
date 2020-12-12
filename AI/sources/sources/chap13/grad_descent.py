x = 20
learning_rate = 0.01
max_iterations = 100

# 손실 함수를 람다식으로 정의한다.
loss_func = lambda x: (0.33*x)**3 + (50*x)**2 - 100*x -30
 
# 그래디언트를 람다식으로 정의한다. 손실 함수의 1차 미분값이다.

gradient = lambda x: (0.99*x)**2 + 100 * x - 100

# 그래디언트 강하법
for i in range(max_iterations):
    x = x - learning_rate * gradient(x)
    print("lossFuncVal(", x, ")=", loss_func(x))

print("MinValue = ", x)
