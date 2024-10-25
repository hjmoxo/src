#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp" // 표준 메세지 형식을 사용하기 위한 헤더파일

/* publish(출판)할때 string data type을 사용하기 위해서 사용 
  - publish란 
  데이터를 생성하거나 전송하고 싶은 노드를 주제로 메시지를 publish하고 
  그 주제를 구독하는 다른 노드들이 해당 메시지를 받을 수 있습니다. */

using namespace std::chrono_literals; //  std::chrono_literals 이거 입력하는 수고 없애기 위해


class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0) // rclcpp::Node 에서 상속받은 MinimalPublisher 라는 노드 클래스
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);  
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }
  /* 
  - ros2에서 제공하는 create_publisher이라는 함수를 사용. 
  <std::msg::String> 이라는 타입 명시, 
  "topic"이라는 이름으로 메세지 큐의 크기는 10(topic이 가질 수 있는 메세지의 최대 개수는 10)
  을 사용하는 publisher이라는 객체 

  - timer는 보통 주기적으로 어떤 함수를 실행하고 싶을때 사용. 
  500ms마다 실행(0.5초마다 실행) 
  std::bind는 함수와 인수를 연결해서 std::bind로 설정한 대로 함수를 호출
  & 이건 주소값을 의미 
  MinimalPublisher 클래스에 정의된 timer_callback 멤버 함수
  this는 현재 MinimalPublisher 자기 자신을 가리킴. 
  인자가 필요하기 때문에 현재 객체와 timer_callback을 연결. 
  요약: 현재 객체의 timer_callback 함수를 타이머와 연결해서 타이머가 작동할때마다 
  this(MinimalPublisher)의 timer_callback이 호출됨 
  */


private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();   
    // auto 자동으로 타입 지정 message를 std_msgs::msg::String() 타입으로 지정
    message.data = "Hello, world! " + std::to_string(count_++);
    // std_msgs::msg::String()에는 data라는 필드가 있고 문자열을 저장함. to_string은 숫자를 string으로 형변환
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    /* 
    RCLCPP_INFO는 ros2의 매크로 정보를 출력함 INFO는 일반적인 정보 메세지를 나타냄.
    this현재 노드(MiniamlPublisher가 상속"받은" >노드< 클래스) 에서 get_logger()함수를 가져옴. 
    get_logger를 통해 해당 노드의 상태나 정보를 남길 수 있음. 
    '%s'는 C스타일에서 문자열을 삽입할 위치를 나타냄. 
    message.data는 std::string타입으로 c_str 메소드를 사용해서 c 스타일 문자열(const char*)로 변환.
    RCLCPP_INFO 는 printf를 사용. 즉 c 스타일을 요구함. 그래서 c_str를 사용해서 형변환이 필요.
    그러나, RCLCPP_INFO_STREAM를 사용한다면 형 변환 없이 
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing: " << message.data) 로 사용 가능.
    RCLCPP_INFO 랑 RCLCPP_INFO_STREAM는 동일한 출력 결과를 가지지만 문자열 처리 방식에만 차이점이 있음.
    만약 RCLCPP_INFO를 사용하지 않는다면 형 변환 필요x 
    로그를 사용하지 않을거면 std::string 형식으로 해도 됨 
    */
    publisher_->publish(message); 
    /*
    - 미리 정의해둔 publisher_ 이라는 객체를 통해 publish라는 함수를 사용.
  publish(message)는 message는 발행할 메세지 객체. 해당 메세지를 토픽에 전달. 
  publisher_ -> publish(message)는 publisher_ 객체를 통해 미리 정의된 메세지(message)를 지정된 토픽으로 발행.
  발행된 메세지는 이 토픽을 구독하고 있는 다른 노드들이 받을 수 있음.

  - 토픽이란?
  ros2에서 노드가넹 메세지를 비동기적으로 주고받기 위한 통신 채널. 
  ros는 퍼블리셔-서브스크라이버 통신 모델을 기반으로 동작하며, 토픽은 그 핵심역할.
  퍼블리셔(Publisher)은 토픽에 메세지를 발행하는 노드. 다른 노드들이 데이터를 받을 수 있도록 함.
  서브스크라이버(Subscriber)는 토픽을 구독하는 노드. 해당 토픽에 Publisher가 발행한 메세지를 수신.
  토픽(Topic)은 Publisher랑 Subscriber간에 메세지를 교환하기 위한 채널. 
  각 토픽은 고유한 이름을 가지며 같은 이름을 가진 퍼블리셔랑 서브스라이버는 메세지를 주고받을 수 있음.

  - 토픽의 주요 특징
  1. 비동기 통신: 퍼블리셔는 서브스크라이버가 언제 메세지를 받는지 신경 쓰지 않고 메세지를 보내고 끝냄. 
  서브스크리라이버는 토픽에서 메세지를 받을 준비가 되어있을 때 메세지를 처리함.
  2. 1 또는 N : 
  통신: 하나의 퍼블리셔가 여러 스브스크라이버에 메세지를 보내거나, 
  여러 퍼블리셔가 하나의 토픽에 메세지를 발행하여 여러 스크라이버가 메세지를 받음
  동적인 노드 연결: ros에서 퍼블리셔와 서브스크라이버가 독립적으로 실행.
  서로 직접 연결되지 않고 중간의 토픽을 통해 간접적으로 메세지를 주고받음.
    */
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
  /*
  timer_ : 타이머를 나타내는 포인터.
  rclcpp::TimerBase::SharedPtr은 타이머 객체를 가르키는 포인터. 
  ros2에서 일정한 시간 간격마다 콜백 함수를 호출할때 사용.

  publisher_ : 퍼블리셔를 나타내는 포인터 
  rclcpp::Publisher< >::SharedPtr은 ros2의 퍼블리셔 객체를 가르키는 포인터.
  <std_msgs::msg::String>타입의 메세지를 발행. 이를 통해서 토픽에 문자열 메세지를 발행할 수 있음.

  count_ : 카운터를 나타내는 변수. 
  size_t는 양의 정수를 저장하는 데이터 타입.
  */

};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}

/*
rclcpp::init(argc, argv)는 ros2를 노드를 초기화 하는 함수.
rclcpp::spin은 노드를 실행하는 함수. spin은 루프를 돌며 노드가 계속해서 메세지를 수신하도록 함.
std::make_shared()는 <MinimalPublisher>클래스의 인스턴스를 포인터로 생성. 
노드를 정의한 클래스(MinimalPublisher)를 실행. 
rclcpp::shutdown은 ros2를 종료하는 함수. 
*/
