
#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import cv2 as cv
import threading
import time
import numpy as np
import matplotlib.pyplot as plt
 
 
class Producer(threading.Thread):
    def __init__(self,str_rtsp):
        super(Producer, self).__init__()
        self.str_rtsp = str_rtsp
        #通过cv2中的类获取视频流操作对象cap  
        self.cap = cv.VideoCapture(self.str_rtsp)
        #调用cv2方法获取cap的视频帧（帧：每秒多少张图片）  
        fps = self.cap.get(cv.CAP_PROP_FPS)
        print(fps)
        #获取cap视频流的每帧大小  
        size = (int(self.cap.get(cv.CAP_PROP_FRAME_WIDTH)), int(self.cap.get(cv.CAP_PROP_FRAME_HEIGHT)))
        print(size)
        # #定义编码格式mpge-4  
        # fourcc = cv.VideoWriter_fourcc('M', 'P', '4', '2')
        # #定义视频文件输入对象  
        # self.outVideo = cv.VideoWriter('saveDir.avi',fourcc,fps,size)
        cv.namedWindow("cap video",0)

    def run(self):
        print('in producer')
        while True:
            ret,image = self.cap.read()
            if (ret == True):
                cv.imshow('cap video',image)
                # self.outVideo.write(image)
                if cv.waitKey(1) & 0xFF == ord('q'):
                    # self.outVideo.release()
                    self.cap.release()
                    cv.destroyAllWindows()
                    break
                    # continue
 
 
def knnDetect(last_img, img, sift, flann):
    if sift is None:
        return 0
    if flann is None:
        return 0
    if img is Nome:
        return 0
    if last_img is None:
        return 0
    #siff--------------
    match = 0
    knn = 0
    kp1, des1 = sift.detectAndCompute(last_ori_gray_img,None)#des是描述子
    kp2, des2 = sift.detectAndCompute(ori_gray_img,None)#des是描述子
    # kp1, des1 = sift.detectAndCompute(last_gray_img,None)#des是描述子
    # kp2, des2 = sift.detectAndCompute(gray_img,None)#des是描述子
    # kp3, des3 = sift.detectAndCompute(last_2_gray_img,None)#des是描述子
    # print( kp1, des1, kp2, des2)
    # print("----------------------------------------------")
    # print(n, len(kp1),len(kp2))
    
    if(len(kp1)>10 and len(kp2)>10):
        matches = flann.knnMatch(des1,des2,k=2)
    # matchesMask = [[0,0] for i in range(len(matches))]
    # print(matches)
    # print(matchesMask)
        kpcount = len(kp1) if(len(kp1)>len(kp2)) else len(kp2)

        good = []
        for m,n in matches:
            if m.distance < 0.4*n.distance:
                good.append([m])
                knn+=1
        if(kpcount > 0):
            print(len(good), knn, len(matches), len(kp1), len(kp2), int(knn/kpcount*1000))            
            match = int(knn/kpcount*1000)

    return match

if __name__ == '__main__':
    print('run program')
    # rtsp_str='rtmp://live.hkstv.hk.lxdns.com/live/hks'

    rtsp_str = 'D:\\code\\drawoutscene\\build\\test\\00142.m2ts'
    # producer = Producer(rtsp_str)
    # producer.start()    

    sift = cv.xfeatures2d.SIFT_create()

    # FLANN 参数设计
    FLANN_INDEX_KDTREE = 0
    index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 8)
    search_params = dict(checks=50)
    flann = cv.FlannBasedMatcher(index_params,search_params)

    cap = cv.VideoCapture(rtsp_str)
    
    fps = cap.get(cv.CAP_PROP_FPS)
    totalframe = int(cap.get(cv.CAP_PROP_FRAME_COUNT))
    h = cap.get(cv.CAP_PROP_FRAME_HEIGHT)
    w = cap.get(cv.CAP_PROP_FRAME_WIDTH)
    
    th = int(h/4);
    tw = int(w/4);
    pixelCount = th*tw
    print(fps, totalframe , h, w)


    img = last_2_gray_img = last_gray_img = gray_img = diff_img = erodeImg = dilateImge = diff_2_img =  diff_m_img =None
    scenechanged = 0;
    n = 0
    ss = 0
    ss_2 = 0
    diff = 0
    kernel = cv.getStructuringElement(cv.MORPH_RECT,(3, 3))

    count = totalframe
    count = totalframe if totalframe<count else count 
    x = np.arange(0,count+1)
    y = np.zeros(count+1)
    y2 = np.zeros(count+1)
    ym = np.zeros(count+1)
    yn = np.zeros(count+1)


    last_hist = hist = diff_hist = None
    
    lastmean = last_stddev = last_vaira = diff_stddev = 0
    last_ori_gray_img =  ori_gray_img = None
    while(n < totalframe):
        # read original image
        ret, img = cap.read()        
        if not ret:
            n += 1
            continue
    
        # resize to the quarter of the original image
        resize_img = cv.resize(img, (tw, th))        

        cv.imshow("video", resize_img)

        # gray image 
        ori_gray_img = cv.cvtColor(resize_img, cv.COLOR_BGRA2GRAY)
        gray_img = ori_gray_img
        # gray_img = cv.medianBlur(gray_img, 5)
        # gray_img = cv.GaussianBlur(gray_img, (15,15), 0) #高斯模糊

        # histogram equalize
        # gray_img = cv.equalizeHist(gray_img)
        # clahe = cv.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
        # gray_img = clahe.apply(gray_img)

        cv.imshow("eqH", gray_img)

        # caculate & compare the histogram, need the rgb image
        # hist = cv.calcHist(gray_img, [0], None, [256], [0, 256])
        # # cv.normalize(hist, hist, 0, 255*0.9,cv.NORM_MINMAX)
        # hist = np.float32(hist)
    
        
        #caculate mean & sd
        # (mean, stddev) = cv.meanStdDev(gray_img)
        # varia = stddev / mean

        
        if(last_gray_img is None):
            pass
        # elif(last_2_gray_img is None):
        #     # scenechanged = 1
        #     pass
        elif(last_ori_gray_img is None):
            pass
        else:
            #sift
            ratio = knnDetect(last_gray_img, gray_img, sift, flann)
            y[n] = ratio

            # calculate pixel difference of three image
            diff_img = cv.absdiff(last_gray_img, gray_img)          
            diff_img = cv.erode(diff_img, kernel)
            diff_img = cv.dilate(diff_img, kernel)           

            # diff_2_img = cv.absdiff(last_gray_img, last_2_gray_img)                
            # diff_2_img = cv.erode(diff_2_img, kernel)
            # diff_2_img = cv.dilate(diff_2_img, kernel)            

            # diff_m_img = cv.absdiff(diff_img, diff_2_img)      

            ret, diff_img = cv.threshold(diff_img, 32, 255, cv.THRESH_BINARY)

            # print("diff threshold value %s"%ret)
            # ret, diff_2_img = cv.threshold(diff_2_img, 0, 255, cv.THRESH_BINARY | cv.THRESH_OTSU )
            # print("diff2 threshold value %s"%ret)
            # ret, diff_m_img = cv.threshold(diff_m_img, 0, 255, cv.THRESH_BINARY)

            # ss = int(diff_img.sum()/pixelCount)
            # ss_2 = int(diff_2_img.sum()/pixelCount)
            # diff = abs(ss-ss_2)

            diff = int(diff_img.sum()/pixelCount)

            if n >= count:
                break

            # diff_hist = cv.compareHist(hist, last_hist, cv.HISTCMP_BHATTACHARYYA)
            # diff_stddev = int(abs(stddev - last_stddev))

            

            y[n] = diff            
            y2[n] = diff_stddev
            ym[n] = diff_hist             

            # cv.imshow("diff", diff_img)
            # cv.imshow("diff2", diff_2_img)
            # cv.imshow("diffm", diff_m_img)

        # last_2_gray_img = last_gray_img
        last_gray_img = gray_img
        last_ori_gray_img = ori_gray_img
        last_hist = hist
        last_stddev = stddev

        if(diff_stddev > 2 ):            
            scenechanged =1;
        
        if(scenechanged == 1):
            # print("diff", n, diff_stddev)         
            # cv.imwrite("D:\\code\\drawoutscene\\build\\test\\"+"00142_"+str(n-1)+"_"+str(diff_stddev)+".png", img, [cv.IMWRITE_PNG_COMPRESSION, 9])
            scenechanged = 0  

        # time.sleep(1/fps)
        
        n += 1

        if cv.waitKey(1) & 0xFF == ord('q'):
            break


    cv.normalize(y, y, 0, 100,cv.NORM_MINMAX)
    cv.normalize(y2, y2, 0, 100,cv.NORM_MINMAX)
    cv.normalize(ym, ym, 0, 100,cv.NORM_MINMAX)
    cv.normalize(yn, yn, 0, 100,cv.NORM_MINMAX)

    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.set_title("pixel diff")
    plt.xlabel('frame')
    plt.ylabel('diffsum')
    ax1.scatter(x,y,s=1,c='r')
    # ax1.scatter(x,y2,s=1,c='g')
    # ax1.scatter(x,ym,s=1,c='b')
    ax1.scatter(x,yn,s=1,c='m')

    # ax2 = fig.add_subplot(132)
    # ax2.set_title("SD diff")
    # plt.xlabel('frame')
    # plt.ylabel('diffsum')
    # ax2.scatter(x,y2,s=1,c='g')

    # ax3 = fig.add_subplot(133)
    # ax3.set_title("hist diff")
    # plt.xlabel('frame')
    # plt.ylabel('diffsum')
    # ax3.scatter(x,ym,s=1,c='b')

    plt.savefig(rtsp_str+".jpg")


    # cv.waitKey(20)
