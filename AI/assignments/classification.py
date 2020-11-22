user_input = int(input())

num1 = 0
num2 = 1
temp = 0
su = []
for i in range(user_input):
    temp = num1 + num2
    num1 = num2
    num2 = temp
    if temp > user_input:
        break;
    else:
        su.append(temp)

print(su)
