- 2024.10.25

ROS graph는 로봇내에서 메세지, 신호 등 교환이 일어나고 
이런 메세지, 신호들이 연결된 하나의 네트워크를 의미.

node란 특정 임무를 수행하는 로봇의 작은 구성(모듈)들 중 하나.
topic, service, action, parameter등을 통해 다른 node와 정보 및 신호를 주고받음.
executable(c++이나 python으로 작성된 실행 가능한 프로그램) 은 한개 이상의 node를 포함할 수 있다. 

ros2 run 명령어는 패키지내 존재하는 executable을 실행한다.
ros2 run <패키지 이름> <실행 프로그램 이름>
ros2 node list를 통해 현재 실행중인 node의 이름을 볼 수 있음 

Remapping이란 node 이름, node가 갖는 topic이름, service 이름등의 특성들을 
사용자가 설정하는 값으로 변환 할 수 있는 기능.
ex: ros2 run turtlesim turtlesim_node --ros-args --remap __node:my_turtle
이라고 명령어를 사용하면 turtlesim 대신 my_turtle이라는 이름으로 지정 가능. 

ros2 node info <node 이름>
을 사용해서 node의 정보를 확인 가능. 

Topic
로봇 내부의 데이터와 신호들이 오가는데 이 정보들을 message로 만들어서 
topic이라는 공간을 통해 message를 발행하고 구독한다. 

ros2 topic list 를 통해 현재 존재하는 모든 topic 이름들을 나열 
ros2 topic list-t를 입력하면 message의 type도 출력해줌 