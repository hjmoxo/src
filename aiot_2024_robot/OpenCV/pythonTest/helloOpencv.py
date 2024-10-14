import cv2

def main():
    path = "/home/test/Desktop/OpenCV/cppTest/build"
    img = cv2.imread(path +"/lena.bmp")
    cv2.imshow("image", img)
    cv2.waitKey(0)

if __name__ == "__main__":
    main()