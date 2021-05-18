import matplotlib.pyplot as plt
import numpy as np 
import cv2 as cv


filepath = "D:\\code\\drawoutscene\\build\\test\\00142_1974_4.png"

rtsp_str = 'D:\\code\\drawoutscene\\build\\test\\00142.m2ts'
    # producer = Producer(rtsp_str)
    # producer.start()    

cap = cv.VideoCapture(rtsp_str)
hist = last_hist = diff = None
n = 0
count = 4004
x = np.arange(0, count+1)
y = np.zeros(count+1)
while(1):
    # cap.set(cv.CAP_PROP_POS_FRAMES, 2456)
    ret, img = cap.read()

    # img = cv.imread(filepath)
    img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

    hist = cv.calcHist([img], [0], None, [256], [0,256])      

    h, w = img.shape
    print(h, w)

    # if n > 200:
    #     break

    # print(hist)
    print(n, hist.shape, hist.sum())

    cv.normalize(hist, hist, 0, 255*0.9,cv.NORM_MINMAX)
    cv.normalize(last_hist, last_hist, 0, 255*0.9,cv.NORM_MINMAX)

    hist = np.float32(hist)
    # last_hist = np.float32(last_hist)

    # hist = hist.convertTo(hist, cv.CV_32F);
    # last_hist = last_hist.convertTo(last_hist, cv.CV_32F);
    # hist_rgb.convertTo(hist_temp, CV_32F);
    if(not last_hist is None):
        diff = cv.compareHist(hist, last_hist, cv.HISTCMP_BHATTACHARYYA)
        y[n]=  diff
        print(diff)
    


    last_hist = hist.copy()

    if(n >= count):
        break

    n+=1

    cv.waitKey(0)



plt.title("frame "+str(n)) 
plt.xlabel("x axis caption") 
plt.ylabel("y axis caption") 
plt.scatter(x, y, s=0.5)
# plt.plot(hist)
# plt.xlim([0,255]) 
plt.show()

    # plt.hist(img.ravel(),256,[0,256])
    # plt.show()

   