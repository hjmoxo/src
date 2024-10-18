from setuptools import find_packages, setup

package_name = 'simple'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='test',
    maintainer_email='cjp8042000@gmail.com',
    description='simple demo',
    license='Apache 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
             "hello = simple.hello:main",
             "hello_class = simple.hello_class:main",   # 명령어 = 패키지.실행파일 이름
             "hello_sub = simple.hello_sub:main",
             "hello_pub = simple.hello_pub:main",
             "time_pub = simple.time_pub:main"
        ],
    },
)
