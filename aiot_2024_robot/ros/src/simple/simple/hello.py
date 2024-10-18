import rclpy
from rclpy.node import Node

def print_hello():
    print("hello, ros2! nice to meet you!")
    print("this is simlink")

def main():
    rclpy.init()
    node = Node("hello")
    node.create_timer(1, print_hello)

    rclpy.spin(node)

if __name__ == "__main__":
    main()