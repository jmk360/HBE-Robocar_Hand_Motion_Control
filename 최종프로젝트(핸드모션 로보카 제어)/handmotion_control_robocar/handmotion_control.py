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
            baudrate=115200, # baudrate=115200
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,)
        self.rx_frames = []
        self.thread_run = True
        self.dist = 0
        self.receive_thread = threading.Timer(1, self.serial_threading)
        self.receive_thread.start()
    
    def serial_threading(self):
        print("car driver receive thread start. PORT:" + self.serial_port.port)
        while self.thread_run:
            try:
                # for c in self.serial_port.read():
                #     self.rx_frames.append(chr(c))
                #     if c == 13:
                #         self.serial_command_receive(''.join(self.rx_frames))
                #         del self.rx_frames[:]
                #     elif len(self.rx_frames) > 100:
                #         del self.rx_frames[:]
                for c in self.serial_port.read():
                    print(c, type(c))
                    self.dist = c
            except Exception as e:
                print("Error occurred. Exiting Program: " + str(e))
                self.serial_port.close()
                self.thread_run = False
        print("serial receive threading terminated.")
    
    def serial_command_receive(self, rx_frame):
        print(rx_frame)

    def serial_command_send(self, tx_frame):
        if not self.thread_run: return
        try:
            print("OUT: " + tx_frame + "=>")
            self.serial_port.write(tx_frame.encode())
        except Exception as e:
            print("send fail.\n" + str(e))

sen = ioe_cardriver('COM3') # 로보카와 연결했을때 장치 관리자에서 COM포트번호 확인하기

# 카메라 열기
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print('Camera open failed!')
    sys.exit()

w = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
h = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
w2 = w // 2
h2 = h // 2

ret, frame = cap.read()

if not ret:
    print('Frame read failed!')
    sys.exit()

frame = cv2.flip(frame, 1)  # 좌우 대칭
gray1 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
gray1 = cv2.resize(gray1, (w2, h2), interpolation=cv2.INTER_AREA)

# 매 프레임에 대해 옵티컬플로우 계산
while True:
    ret, frame = cap.read()

    if not ret:
        print('Frame read failed!')
        break

    frame = cv2.flip(frame, 1)  # 좌우 대칭
    gray2 = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray2 = cv2.resize(gray2, (w2, h2), interpolation=cv2.INTER_AREA)

    # 밀집 옵티컬플로우 계산
    flow = cv2.calcOpticalFlowFarneback(gray1, gray2, None, 0.5, 3, 15, 3, 5, 1.1, 0)
    vx, vy = flow[..., 0], flow[..., 1]
    mag, ang = cv2.cartToPolar(vx, vy)

    '''
    # 움직임 벡터 시각화
    hsv = np.zeros((h2, w2, 3), dtype=np.uint8)
    hsv[..., 0] = ang*180/np.pi/2
    hsv[..., 1] = 255
    hsv[..., 2] = cv2.normalize(mag, None, 0, 255, cv2.NORM_MINMAX)
    bgr = cv2.cvtColor(hsv, cv2.COLOR_HSV2BGR)
    cv2.imshow('flow', bgr)
    '''

    # 움직임이 충분히 큰 영역 선택
    motion_mask = np.zeros((h2, w2), dtype=np.uint8)
    motion_mask[mag > 2.0] = 255

    mx = cv2.mean(vx, mask=motion_mask)[0]
    my = cv2.mean(vy, mask=motion_mask)[0]
    m_mag = math.sqrt(mx*mx + my*my)

    if m_mag > 4.0:
        m_ang = math.atan2(my, mx) * 180 / math.pi
        m_ang += 180

        pt1 = (100, 100)

        if m_ang >= 45 and m_ang < 135:
            pt2 = (100, 30)
            sen.serial_command_send('y')
        elif m_ang >= 135 and m_ang < 225:
            pt2 = (170, 100)
            sen.serial_command_send('g')
        elif m_ang >= 225 and m_ang < 315:
            pt2 = (100, 170)
            sen.serial_command_send('b')
        else:
            pt2 = (30, 100)
            sen.serial_command_send('j')

        cv2.arrowedLine(frame, pt1, pt2, (0, 0, 255),
                        7, cv2.LINE_AA, tipLength=0.7)
    else: # 아무 반응이 없어도 atmega128에 'x'를 보내주어서 atmega128이 돌도록 만들어 줌.
        sen.serial_command_send('x')
    # else: # 아무 반응이 없다고 한다면 전방, 후방 led끄고 정지하는 코드
    #     sen.serial_command_send('s')

    # 로보카의 psd센서로 부터 받은 거리정보를 영상에 출력
    cv2.putText(frame, str(sen.dist) + 'cm', (450, 80), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 0, 0), 2)
    if sen.dist < 35: # 로보카의 psd센서로 부터의 거리정보가 35cm미만이면 위험, 충돌주의를 영상에 출력
        cv2.putText(frame, "DANGER!", (140, 200), cv2.FONT_HERSHEY_SIMPLEX, 3, (0, 0, 255), 4)
        cv2.putText(frame, "CAUTION-COLLISION", (10, 300), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 255), 3)
        sen.serial_command_send('s')

    # 결과 영상 화면 출력
    # cv2.namedWindow('frame', cv2.WINDOW_NORMAL)
    # cv2.setWindowProperty('frame', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    cv2.imshow('frame', frame)
    #cv2.imshow('motion_mask', motion_mask)

    if cv2.waitKey(1) == 27:
        break

    # 현재 프레임을 이전 프레임으로 복사
    gray1 = gray2

cap.release()
cv2.destroyAllWindows()
