# 8주차 -1
## 네트워크 계층
* 개요
  * 라우팅 프로토콜: 라우터로부터 경로를 결정하는 것
  * IP 프로토 콜
  * ICMP 프로토 콜

* 데이터 평면에 초점을 두고 네트워크 계층의 서비스 원리 이해
  * 네트워크 계층 서비스 모델
  * 포워딩과 라우팅
  * 라우터 동작 방식
  * 일반적인 포워딩

## 네트워크 계층
* 송신 호스트에서 수신 호스트로 패킷 전달
  * 송신호스트는 트랜스포트 계층에서 세그먼트를 받아 데이터그램을 캡슐화
  * 수신 호스트는 데이터 그램에서 세그먼트를 추출하여 트랜스포트 계층에 전달

* 모든 호스트와 라우터에 네트워크 계층 프로토콜 내장

* 라우터는 입력 링크의 IP 데이터그램의 헤더필드를 조사하여 출력 링크로 전달(포워딩)

## 네트워크 계층의 주요기능
* 포워딩
  * 라우터에 입력 링크에 도착한 패킷을 적절한 출력 링크로 이동

* 라우팅
  * 출발지에서 목적지까지 경로를 결정
  * 라우팅 알고리즘

## 데이터평면, 제어 평면
* 데이터 평면
  * 로컬 라우터 당(per-router)의 기능
  * 라우터 입력포트에 도착한 데이터그램을 라우터의 어느 출력 포트로 포워딩 할 것인가를 결정
  * 포워딩 함수

* 제어 평면
  * 네트워크 범위 로직
  * 데이터그램이 종단 간의 출발지에서 목적지까지 어떤 경로의 라우터를 거쳐 라우팅 될 것인가를 결정
  * 2가지 제어 평면 방식
    * 전통적인 라우팅 알고리즘 라우터들 내부에서 구현
    * SDN(Software-Defined Network) 원격 서버들 안에서 구현


## 전통적인 접근 방식
  * 각각의 모든 라우터 안의 개별 라우팅 알고리즘이 제어 평면에서 상호작용

## SDN접근방식
  * 논리적인 제어기가 로컬 제어 에이전트(local control agent, CA)와 상호작용

## 제공 가능한 네트워크서비스 모델
* 개별 패킷(데이터그램)을 위한 네트워크서비스
  * 보장된 전달
  * 특정 지연 시간 이내의 보장된 전달
* 패킷 흐름(flow)을 위한 서비스
  * 순서화된 패킷 전달
  * 보장된 최소 대역폭
  * 보장된 패킷 간 간격
    * 두개의 패킷 전송 사이의 송신자간의 시간 간격 수신자에서의 시간간격과 같음
   **다만 인터넷에서 실질적으로 어떤 부분에 대해서든 보장하지 않는다**

## 라우터
* 입출력의 기능에 있어서 특화되어 있다
* 라우팅 알고리즘/프로토콜(RIP, OSPF, BGP), 포워딩의 주요 기능을 수행한다.

## 입력포트 기능
* 기존 방식은 IP주소를 통한 입력 (destination-based)
* 일반화된 포워딩

## 목적지 기반 포워딩
  * 32비트 IP 주소
    * 40억개 이상의 주소
    * 만약 라우터 포워딩 테이블이 목적지 주소마다 하나의 엔트리를 갖는다면 아주 큰 테이블이 필요

  * 최장 프리픽스 대응
    * 가장 긴 프리픽스 엔트리를 찾아서 해당 링크 인터페이스로 패킷을 전달
      * 복수의 링크와 일치할 경우, 보다 더 긴 링크에 매칭된다.

## 스위칭 구조
* 입력 버퍼의 패킷을 적당한 출력 버퍼로 이동

* 스위칭 속도: 페킷들이 입력에서 출력으로 전달되는 속도
  * 입력/출력 라인 속도의 배수로 측정
  * N개 입력: 라인속도의 N배 스위칭 속도가 바람직
  * 메모리, 버스, 크로스바의 형태가 있다.

* 메모리를 통한 스위칭
  * 1세대 라우터
* 버스를 통한 스위칭
  * 버스 충돌로 인한 스위칭 속도 제한, 32Gbps까지 지원
* 크로스바 스위치
  * 앞서 설명한 스위칭보다 더 빠른 속도 지원(60Gbps)

## 입력포트 큐잉
* 오버플로우로 인한 입력버퍼에 큐잉 지연 및 패킷 손실발생가능성
* HOL 블로킹
  * 큐의 앞 부분에서 데이터그램이 다른 패킷을 전달하는 것을 방해

## 출력 포트
* 스위칭 구조가 패킷의 전송속도가 빠를 경우 버퍼링 필요
  * 패킷손실 발생 가능성 존재
* 데이터그램들을 선택하여 전송하는 스케줄링 규칙 필요
  * 우선순위 기반 스케줄링

## 버퍼링 용량
* 버퍼링 용량 규칙
  * 버퍼의 용량은 링크 용량(C)과 전형적인 RTT(250msec)값의 곱
  * c = 10Gbps link, B = 0.25 x 10 Gbps = 2.5 Gbit용량의 버퍼 필요
* 최근의 이론
  * 대용량의 TCP 흐름이 링크를 지나갈 때 버퍼링 용량

## 패킷 스케줄링 메커니즘
* 스케줄링
  * 링크로 전송을 위해 큐에 있는 패킷을 선택하는 방식
* FIFO 스케줄링
  * 큐에 도착한 순서대로 전송
  * 큐가 가득찬 경우 패킷 폐기 정책 필요
    * 꼬리 폐기: 도착한 패킷 폐기
    * 우선순위: 우선순위에 기반하여 폐기/제거
    * 무작위 방식: 무작위로 폐기/제거

## 우선순위 스케줄링 정책
* 대기중인 큐에서 높은 우선순위의 패킷을 전송
* 서로다른 우선순위를 갖는 다중 클래스들
  * 클래스는 마킹이나 IP출발지/목적지, 포트번호등의 헤더 정보에 기반하여 구분

## 라운드 로빈 정책

## WFQ 스케줄링 정책
* 라운드 로빈의 일반화된  개념
  * 각 클래스 별로 순서대로 패킷을 전송
  * 서비스시간에 가중치를 부여하여 각 서비스마다 시간이 다르도록 설정하여 라운드 로빈과 차이를 둠

## 인터넷 네트워크 계층 구성 요소
* 경로를 구성하는 라우터
* 메시지 표현, 패킷 핸들링, 주소를 위한 IP프로토콜
* 에러 기록 및 라우터 신호를 다루기 위한 ICMP프로토콜

## 메시지 형식
* 옵션 헤더를 사용하지 않을 경우 20byte의 헤더
* 32bit의 출발, 목적 IP주소
* 헤더를 통해 라우터에서 경로 설정

## IP단편화
* 링크계층에 전달할 수있는 최대 크기 MTU
  * 링크 계층 프로토콜 마다 다르다.
* 4000byte 다이어그램, MTU = 1500 bytes
  * length = 1500, ID = x, fragflag = 1, offset = 0(1480bytes in data field)
  * length = 1500, ID = x, fragflag = 1, offset = 185(1480/8)
  * length = 1040, ID = x, fragflag = 0, offset = 370(2960/8)
