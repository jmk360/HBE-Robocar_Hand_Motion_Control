# ATmega128 UART 송수신 테스트

---

* ATmega128에서 1초 주기로 30, 31, ... 40의 데이터를 반복해서 Hostpc로 송신
* Hostpc는 ATmega128에서 송신한 데이터를 수신하여 실시간 웹캠 영상에다가 수신 받은 데이터를 출력
* Hostpc에 수신된 데이터가 35 미만이면 실시간 웹캠영상에 "DANGER! CAUTION-COLLISION" 문구를 출력

---

![ATmega128 송수신 테스트](https://user-images.githubusercontent.com/64933820/145941908-acdb9c7c-29da-44f7-adf7-557b29a895eb.png)
