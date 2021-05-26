import sys
import math
import numpy as np
import cv2
import time, serial, threading

# uart 통신 클래스
class ioe_cardriver:
    def __init__(self, comport):
        self.comm = comport
        self.serial_port = serial.Serial(
            port=self.comm,
            baudrate=9600, # 9600보레이트
            bytesize=serial.EIGHTBITS, # 데이터비트는 8비트 사용
            parity=serial.PARITY_NONE, # 패리티비트는 사용하지 않음
            stopbits=serial.STOPBITS_ONE,) # 스탑비트는 1비트 사용
        self.rx_frames = []
        self.thread_run = True
        self.dist = 0
        self.receive_thread = threading.Timer(1, self.serial_threading)
        self.receive_thread.start()
    
    def serial_threading(self):
        print("host pc receive thread start. PORT:" + self.serial_port.port)
        while self.thread_run:
            try:
                for c in self.serial_port.read(): # 데이터를 수신받아 옴
                    self.serial_command_receive(c)
                    self.dist = c
            except Exception as e:
                print("Error occurred. Exiting Program: " + str(e))
                self.serial_port.close()
                self.thread_run = False
        print("serial receive threading terminated.")
    
    def serial_command_receive(self, rx_frame):
        print(rx_frame)

    def serial_command_send(self, tx_frame): # 데이터를 송신 함
        if not self.thread_run: return
        try:
            print("OUT: " + tx_frame + "=>")
            self.serial_port.write(tx_frame.encode())
        except Exception as e:
            print("send fail.\n" + str(e))

sen = ioe_cardriver('COM4') # 로보카와 연결했을때 장치 관리자에서 COM포트번호 확인하기

# 카메라 열기
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print('Camera open failed!')
    sys.exit()

while True:
    ret, frame = cap.read()

    if not ret:
        print('Frame read failed!')
        break

    # atmega128로 부터 받아온 데이터를 영상에 출력
    cv2.putText(frame, str(sen.dist) + 'cm', (450, 80), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 0, 0), 2)
    if sen.dist < 35: # 수신 받은 데이터가 35 미만이면 다음 문자열을 영상에 출력
        cv2.putText(frame, "DANGER!", (140, 200), cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 0, 255), 4)
        cv2.putText(frame, "CAUTION-COLLISION", (10, 300), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)

    # 결과 영상 화면 출력

    # cv2.namedWindow('frame', cv2.WINDOW_NORMAL) # 영상을 전체화면으로 해주는 부분
    # cv2.setWindowProperty('frame', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN) # 영상을 전체화면으로 해주는 부분
    cv2.imshow('frame', frame)

    if cv2.waitKey(1) == 27:
        break

cap.release()
cv2.destroyAllWindows()
