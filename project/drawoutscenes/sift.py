import numpy as np
import cv2
from matplotlib import pyplot as plt

imgname1 = 'E:/other/gakki101.jpg'
imgname2 = 'E:/other/gakki102.jpg'

rtsp_str = 'D:\\code\\drawoutscene\\build\\test\\00142.m2ts'
cap = cv2.VideoCapture(rtsp_str)
h = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
w = cap.get(cv2.CAP_PROP_FRAME_WIDTH)

th = int(h/4);
tw = int(w/4);

n = 257

sift = cv2.xfeatures2d.SIFT_create()

# FLANN 参数设计
FLANN_INDEX_KDTREE = 0
index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 1)
search_params = dict(checks=50)
flann = cv2.FlannBasedMatcher(index_params,search_params)

# img1 = cv2.imread(imgname1)
cap.set(cv2.CAP_PROP_POS_FRAMES, n)
ret, img1 = cap.read()
img1 = cv2.resize(img1, (tw, th))   
gray1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY) #灰度处理图像
kp1, des1 = sift.detectAndCompute(img1,None)#des是描述子

# img2 = cv2.imread(imgname2)
cap.set(cv2.CAP_PROP_POS_FRAMES, n+1)
ret, img2 = cap.read()
img2 = cv2.resize(img2, (tw, th))   
gray2 = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
kp2, des2 = sift.detectAndCompute(img2,None)

# hmerge = np.hstack((gray1, gray2)) #水平拼接
# cv2.imshow("gray", hmerge) #拼接显示为gray
# cv2.waitKey(0)

img3 = cv2.drawKeypoints(img1,kp1,img1,color=(255,0,255))
img4 = cv2.drawKeypoints(img2,kp2,img2,color=(255,0,255))

hmerge = np.hstack((img3, img4)) #水平拼接
cv2.imshow("point", hmerge) #拼接显示为gray
matches = flann.knnMatch(des1,des2,k=2)
matchesMask = [[0,0] for i in range(len(matches))]
# print(matches)
# print(matchesMask)

good = []
for m,n in matches:
    if m.distance < 0.4*n.distance:
        good.append([m])

print(len(good), len(matches), len(kp1), len(kp2))
img5 = cv2.drawMatchesKnn(img1,kp1,img2,kp2,good,None,flags=2)
cv2.imshow("FLANN", img5)
cv2.waitKey(0)
cv2.destroyAllWindows()