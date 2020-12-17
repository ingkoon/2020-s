#20151167 이인재
#상태를 정의하기 위한 클래스
class State:
    #객체생성 함수
    def __init__(self, board, goal, moves=0):
        #현재의 보드상태
        self.board = board
        #움직임의 횟수
        self.moves = moves
        #목표상태
        self.goal = goal

    #새로운 상태를 반환하는 함수
    def get_new_board(self, i1, i2, moves):
        new_board = self.board[:]
        #i1과 i2를 교환하여 새로운 상태를 반환
        new_board[i1], new_board[i2] = new_board[i2], new_board[i1]
        #결과 반환
        return State(new_board, self.goal, moves)

    #board객체를 출력하기 위하는 함수
    def __str__(self):
        return str(self.board[:4]) + "\n" +\
        str(self.board[4:8]) + "\n" + \
        str(self.board[8:12]) + "\n" +\
        str(self.board[12:]) + "\n" +\
        "------------------------------"

    #자식 노드를 확장하여서 리스트에 저장 하여서 반환하기 위한 함수
    #기존의 형태에서 하나의 크기를 늘려주는 것으로 퍼즐을 생성하였다.
    #움직임 횟수가 매개변수로 삽입된다
    def expand(self, moves):
        #자식노드들이 삽입될 예정
        result = []
        #0의 위치 탐색 후 위치 반환
        i = self.board.index(0)
        #0 1 2 3 중이 아니라면
        if not i in [0, 1, 2, 3]:
            #up 연산 수행 후, 새로운 상태 생성 후 result 리스트에 저장
            result.append(self.get_new_board(i, i-4, moves))
        if not i in [0, 4, 8, 12]:
            #LEFT연산 수행 후, 새로운 상태 생성 후 result 리스트에 저장
            result.append(self.get_new_board(i, i-1, moves))
        if not i in [3,7,11,15]:
            #Down 연산 수행 후, 새로운 상태 생성 후 result 리스트에 저장
            result.append(self.get_new_board(i, i+1, moves))
        if not i in [12,13,14,15]:
            #Right연산 수행 후, 새로운 상태 생성 후 result 리스트에 저장
            result.append(self.get_new_board(i, i+4, moves))
        return result


#초기 퍼즐의 상태
puzzle = [1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 0,
        13,14,15, 12]

#목표 퍼즐의 상태
goal = [1, 2, 3, 4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,0]


#상태객체를 저장하기 위한 큐 생성
open_queue = []
#시작상태를 배치하기위해  puzzle과 goal을 매개변수로 객체 생성
open_queue.append(State(puzzle, goal))

#반복되는 위치 이동에 대한 검사를 위한 배열 선언
closed_queue = []
moves = 0
#open_queue리스트가 0이 아닐경우
while len(open_queue) != 0:
    #open_queue의 전단 삭제
    current = open_queue.pop(0)
    #pop한 값 출력
    print(current)
    print(current.moves);
    #현재 보드가 목표 보드와 같다면 게임 종료
    if current.board == goal:
        print("finish this game")
        print("20151167 이인재")
        break
    #전역 변수 moves를 하나 증가시킨다.
    moves = current.moves + 1
    #표현한 상태는 closed_queue에 넣는다
    closed_queue.append(current)
    #moves를 이용하여 상태확장
    for state in current.expand(moves):
        #closed_queue에 에 있는 것들이라면 노드를 버린다.
        if(state in closed_queue) or (state in open_queue):
            continue
        else:
            #아닐 경우 자식노드 큐은 queue에 삽입
            open_queue.append(state)
