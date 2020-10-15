#20151167 이인재

import numpy as np
import matplotlib.pyplot as plt

#EstimateRTT
def isEstimatedRTT(list, a):

    #EstimatedRTT를 저장할 배열
    Estimate = []
    #이전 EstimatedRTT의 값
    result = 100

    # 반복문을 통한 EstimatedRTT값 계산
    for i in list:
        result = (1-a) * result + a * i
        #계산된 값 배열에 저장
        Estimate.append(round(result,2))

    #배열 출력
    print(Estimate)
    plt.plot(list, marker = 'o', label = 'Sample')
    plt.plot(Estimate, marker = 'o', label = 'EstimatedRTT')
    plt.show()
    return Estimate

#20151167 이인재
#DevRTT
def isDevRTT(EstimatedRTT, SampltRTT, b):
    #DevRTT를 저장할 배열
    Dev = []
    #이전 DevRTT의 값
    result = 5
    #반복문을 통한 DevRTT의 값 계산
    for Es, Sa in zip(EstimatedRTT,SampleRTT):
        result = (1-b) * result + b *abs(Sa - Es)
        #배열에 계산된 값 저장
        Dev.append(round(result,2))
    #출력
    print("\n")
    print("DevRTT의 값")
    print(Dev)
    return Dev

# 20151167 이인재
#TCP TimeInterval
def isTimeoutInterval(EstimatedRTT, DevRTT):
    # TimeoutInterval 배열 선언
    Ti = []
    #반복문을 통한 TimeoutInterval 계산
    for Es, Dev in zip(EstimatedRTT, DevRTT):
        result = Es + Dev * 4
        #계산된 값 추가
        Ti.append(round(result,2))
    print("\n")
    print("Timeout Interval의 값")
    print(Ti)
    return Ti

SampleRTT = [106, 120, 140, 90, 115]
a = 0.125

EstimatedRTT = isEstimatedRTT(SampleRTT, a)
b = 0.25
DevRTT = isDevRTT(EstimatedRTT, SampleRTT, b)

TimeoutInterval = isTimeoutInterval(EstimatedRTT, DevRTT)
