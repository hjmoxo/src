- 2024.10.25

ROS graph는 로봇내에서 메세지, 신호 등 교환이 일어나고 
이런 메세지, 신호들이 연결된 하나의 네트워크를 의미.

node란 특정 임무를 수행하는 로봇의 작은 구성(모듈)들 중 하나.
topic, service, action, parameter등을 통해 다른 node와 정보 및 신호를 주고받음.
executable(c++이나 python으로 작성된 실행 가능한 프로그램) 은 한개 이상의 node를 포함할 수 있다. 

ros2 run 명령어는 패키지내 존재하는 executable을 실행한다.
ros2 run <패키지 이름> <실행 프로그램 이름>
ros2 node list를 통해 현재 실행중인 node의 이름을 볼 수 있음 

Remapping이란 node 이름, node가 갖는 topic이름, service 이름등의 특성들을 사용자가 설정하는 값으로 변환 할 수 있는 기능.
ex: ros2 run turtlesim turtlesim_node --ros-args --remap __node:my_turtle
이라고 명령어를 사용하면 turtlesim 대신 my_turtle이라는 이름으로 지정 가능. 3

ros2 node info <node 이름>
을 사용해서 node의 정보를 확인 가능. 

Topic
로봇 내부의 데이터와 신호들이 오가는데 이 정보들을 message로 만들어서 
topic이라는 공간을 통해 message를 발행하고 구독한다. 

ros2 topic list 를 통해 현재 존재하는 모든 topic 이름들을 나열 
ros2 topic list-t를 입력하면 message의 type도 출력해줌 

- 2024.10.29

ros2 topic echo <topic 이름>
topic에서 발행되는 메세지를 확인 가능
ex. ros2 topic echo /turtle1/cmd_vel

일대다, 다대일, 다대다 통신이 가능하기 때문에 
rots2 topic info /turtle1/cmd_vel
Publisher count: 발행자 수 
Subscription count: 구독자 수

node 속에는 발행자와 구독자가 있는데 정상적으로 데이터를 주고 받으려면 
같은 message type을 사용해야 한다.
ex. geometry_msgs/msg/Twist
geometry_msgs패키지 안에 msg 중에 Twist라는 type이 있다. 

topic에 message를 임의로 발행. publish
ros2 topic pub <topic 이름><message 타입> '<message 내용(데이터)>'

topic이 1초당 몇번 publish되는지 알 수 있음
ros2 topic hz <topic 이름>

Service란?
요청(call) 그리고 응답(response)형태로 이루어진 node간 통신 방식

node1에서 service client(고객)는 요청사항을 request message를 생성해서 
service server(식당)에 요청(request)한다.
server는 이를 받아서 처리하고 client가 요청한 서비스가 어떻게 처리됬는지 
응답(response)형태로 고객에게 알려준다.

ros2 service list
를 사용해서 /turtlesim 과 /teleop_turtle node 에서 제공되는 service들의 이름을 볼 수 있음

ros service에도 내가 무엇을 요청하려는지 잘 정리해서 보내야 한다.
이렇게 정해진 형태를 service type이라고 한다.
service별로 정의된 type을 어떻게 알 수 있을까?
ros2 service type <서비스 이름>
ex. ros2 service type /clear
std_srvs/srv/Empty
std_srvs패키지에 srv라는 폴더 안에 있는 Empty라는 service type을 사용함.
Empty 는 요청할때 아무 데이터도 넣지 않고 그냥 요청만 하면 됨.
또한 응답 데이터도 없음.

ros2 service list -t 
는 service의 이름들과 해당 service의 type들도 같이 표시해줌 

특정 srvice type을 갖는 service들을 찾아줌
ros2 service find std_srvs/srv/Empty
결과 /clear
/reset

특정 service type의 구조(request와 response정보)를 보여준다.
ros2 interface show (turtlesim/srv/Spawn)
출력
request 내용(필요한 구조)
---
response 내용(반환되는 값)

ros2 service call <요청하고자 하는 서비스 이름><해당 서비스의 타입><서비스 타입의 request 구조>
ros2 service call /clear std_srvs/srv/Empty
위 같은 경우 Empty는 아무것도 작성할 필요가 없으니깐 서비스 타입의 request구조를 비워둠 

parameter는 node의 설정 값
interger, float, boolen, string, list같은 형식을 가짐

ros2 param list

특정 parameter의 현재 설정 값을 보여줌
ros2 param get <관심 노드 이름><알고자하는 parameter 이름>

ros2 param dump 는 특정 node가 갖는 parameter의 설정 값을 보여주고 필요하면 저장
ros2 param dump <node 이름> 
만약 저장하고 싶으면 ros2 param dump <node 이름><parameter 파일이름.yaml>

저장한 parameter를 불러옴
ros2 param load <node 이름><불러오고자 하는 parameter file경로 또는 이름>

ros2 run 를 실행할때 원하는 parameter로 설정
ros2 run <package 이름><executable 이름> --ros-args --params-file <parameter 파일 이름>
ex. ros2 run turtlesim turtlesim_node --ros-args --params-file turtlesim.yaml
이란 
turtlesim 이란 패키지에 있는 turtlesim_node를 실행할 executable을 실행할건데
>>executable은 c++혹은 python으로 작성된 실행 가능한 프로그램)<< 기억해두자! 
turtlesim.yaml이라는 parameter값들로 node의 parameter들을 설정해줘 라는 뜻

action은 topic이나 service처럼 ros2에서 사용되는 통신 방법중 하나 
goal(목표로 하는 행위), feedback(행위가 이루어지는 동안 피드백), result(결과)로 구성됨

action은 service와 topic을 갖추고 있다.
(goal에 대한 Goal Service, result에 대한 Result Service)(feedback을 주는 Feedback Topic)
service랑 유사하지만 차이점!
service랑은 다르게 action은 중간에 취소 가능하고 goal을 위해 어떤 행위를 취하는 동안 
그에 대한 피드백을 말해줌

Action은 client-server구조를 사용함.
"Action Client" node는 "Action Server" node로 goal 을 보내고 
Action Server는 이를 받아 행동을 수행하면서 피드백을 보내고 결과적으로 행위가 잘 이루어 졌는지 결괄르 반환

action server에서 취소하는 행위를 "abort"라고 부름.
result 이전에 새로운 goal이 들어올 경우 이전의 goal을 abort하게 됨.

ros2 node info /turtlesim 을 사용해 
subscriber(구독자), publisher(발행자), service, action server, actioin client를 출력
ex. Atcion Servers 
/turtle1/rotate_absolute : turtlesim/action/RotateAbsolute
/turtlesim node는 /turtle1/rotate_absolute라는 action을 제공함.

action은 topic이나 service처럼 ros2에서 사용되는 통신 방법중 하나 
goal(목표로 하는 행위), feedback(행위가 이루어지는 동안 피드백), result(결과)로 구성됨

action은 service와 topic을 갖추고 있다.
(goal에 대한 Goal Service, result에 대한 Result Service)(feedback을 주는 Feedback Topic)
service랑 유사하지만 차이점!
service랑은 다르게 action은 중간에 취소 가능하고 goal을 위해 어떤 행위를 취하는 동안 
그에 대한 피드백을 말해줌

Action은 client-server구조를 사용함.
"Action Client" node는 "Action Server" node로 goal 을 보내고 
Action Server는 이를 받아 행동을 수행하면서 피드백을 보내고 결과적으로 행위가 잘 이루어 졌는지 결괄르 반환

action server에서 취소하는 행위를 "abort"라고 부름.
result 이전에 새로운 goal이 들어올 경우 이전의 goal을 abort하게 됨.

ros2 node info /turtlesim 을 사용해 
subscriber(구독자), publisher(발행자), service, action server, actioin client를 출력
ex. Atcion Servers 
/turtle1/rotate_absolute : turtlesim/action/RotateAbsolute
/turtlesim node는 /turtle1/rotate_absolute라는 action을 제공함.
ex. Action Clients
/turtle1/rotate_absolute: turtlesim/action/RotateAbsolute
turtle1_/rotate_absolute로 action goal을 보냄.

ros graph에 존재하는 모든 action을 알려줌
ros2 actioin list (-t) type까지 표시 

action에 대한 요약된 정보들 출력
ros2 action info 

action은 command나 code를 통해 요청하기 전에 정보가 필요한데, 
이를 알아낼 수 있는 명령어 action type의 구조를 알려줌
ros2 interface show (turtlesim/action/RotateAbsolute)

action을 요청
ros2 action send_goal <action 이름><action type><action 구조에 맞는 값>
ex. ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theate: 1.57}"
"/turtle1/roate_absolute"의 이름을 갖는 action은 "turtlesim/action/RotateAbsolure"라는 type을 갖고 
goal 방향 theate는 1.57radian 으로 하겠다. 라는 뜻!


