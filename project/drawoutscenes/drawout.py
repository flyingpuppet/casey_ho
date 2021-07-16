
#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import cv2 as cv
import time
import numpy as np
import matplotlib.pyplot as plt
import logging
import os
import math
import uuid


def get_log():
    # 在控制台输出
    # acars存储日志

    # 创建一个logger
    logger = logging.getLogger()
    logger.handlers.clear()  # 清除logger,避免多个文件引用重复打印log
    logger.setLevel(logging.INFO)
    """定义一个函数，回调logger实例"""
    # log_path = os.path.dirname(sys.path[0])
    # print(log_path)

    # 创建一个handler，用于写入日志文件
    # log_path = os.path.dirname(os.path.dirname(sys.path[0]))+"/Logs/" # 指定文件输出路径，注意logs是个文件夹，一定要加上/，不然会导致输出路径错误，把logs变成文件名的一部分了
    #  curPath = os.path.abspath(os.path.dirname(__file__))
    # log_path = 'D:\\code\\drawoutscene\\build\\test\\00142.log'
    


    # nowTime = time.strftime('%Y-%m-%d')
    # logname = log_path + 'acars-' + nowTime + '.log'  # 指定输出的日志文件名
   
    logname = 'D:\\output\\scenes.log'

    fp = open(logname, 'a')
    # 直接打开一个文件，如果文件不存在则创建文件
    fp.close()

    fh = logging.FileHandler(logname, encoding='utf-8')  # 指定utf-8格式编码，避免输出的日志文本乱码
    fh.setLevel(logging.INFO)

    # 创建一个handler，用于将日志输出到控制台
    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)

    # 定义handler的输出格式
    formatter = logging.Formatter('%(asctime)s - %(filename)s[line:%(lineno)d] - %(levelname)s: %(message)s')

    fh.setFormatter(formatter)
    ch.setFormatter(formatter)

    # 给logger添加handler
    logger.addHandler(fh)
    logger.addHandler(ch)
    return logger
 
 
def knnDetect(last_img, img, sift, flann):
    if sift is None:
        return 0
    if flann is None:
        return 0
    if img is None:
        return 0
    if last_img is None:
        return 0
    #siff--------------
    match = 0
    knn = 0
    kpcount = 0
    kp1, des1 = sift.detectAndCompute(last_img,None)#des是描述子
    kp2, des2 = sift.detectAndCompute(img,None)#des是描述子
    # print( kp1, des1, kp2, des2)
    # print("----------------------------------------------")
    # print(n, len(kp1),len(kp2))
    
    # log.debug("knn debug----kp1：%d, kp2:%d", len(kp1), len(kp2))

    x = len(kp1)
    y = len(kp2)

    max = x if x > y else y
    min = x if x < y else y

    if max == 0:
        return 0

    if float((min / max)) < 0.2:
        return 100


    if(len(kp1)>5 and len(kp2)>5):
        matches = flann.knnMatch(des1,des2,k=2)
    # matchesMask = [[0,0] for i in range(len(matches))]
    # print(matches)
    # print(matchesMask)
        kpcount = len(kp1) if(len(kp1)>len(kp2)) else len(kp2)

        # good=[]
        for m,n in matches:
            if m.distance < 0.4*n.distance:
                # good.append([m])
                knn+=1
        if(kpcount > 0):
            
            # log.debug('%d, %d, %d, %d, %d', knn, len(matches), len(kp1), len(kp2), int(knn/kpcount*1000))            
            match = int(knn/kpcount*1000)

        # if knn> 0:
        #     img5 = cv.drawMatchesKnn(last_img,kp1,img,kp2,good,None,flags=2)
        #     cv.imshow("knn",img5)

    return match

def pixeldiff(last_img, img):

    if img is None:
        return 0
    if last_img is None:
        return 0
    # calculate pixel difference of three image
    diff_img = cv.absdiff(last_img, img)          
    diff_img = cv.erode(diff_img, kernel)
    diff_img = cv.dilate(diff_img, kernel)           

    # diff_2_img = cv.absdiff(last_gray_img, last_2_gray_img)                
    # diff_2_img = cv.erode(diff_2_img, kernel)
    # diff_2_img = cv.dilate(diff_2_img, kernel)            

    # diff_m_img = cv.absdiff(diff_img, diff_2_img)      

    ret, diff_img = cv.threshold(diff_img, 10, 255, cv.THRESH_BINARY)
    # cv.imshow("diff_img",diff_img)
    h, w = img.shape
    diff = diff_img.sum()/(h*w)
    diff = int(math.sqrt(diff)*1600)
    
    return diff

def drawoutScenes(filename, outputpath = "D:\\output_1\\"):

    # sift = cv.xfeatures2d.SIFT_create()

    

    # FLANN 参数设计
    # FLANN_INDEX_KDTREE = 0
    # index_params = dict(algorithm = FLANN_INDEX_KDTREE, trees = 8)
    # search_params = dict(checks=50)
    # flann = cv.FlannBasedMatcher(index_params,search_params)

    cap = cv.VideoCapture(filename)

    if not cap.isOpened():
        log.info(filename + " is not a media file!")
        return 0
    
    fps = cap.get(cv.CAP_PROP_FPS)
    totalframe = int(cap.get(cv.CAP_PROP_FRAME_COUNT))
    h = cap.get(cv.CAP_PROP_FRAME_HEIGHT)
    w = cap.get(cv.CAP_PROP_FRAME_WIDTH)

    if(fps < 0 or totalframe < 0 or h < 0 or w < 0):
        return 0
    
    th = int(h/4);
    tw = int(w/4);

    if(th < 224) or (tw < 224):
        th = 270
        tw = 480


    # pixelCount = th*tw
    print(fps, totalframe , h, w)


    img = last_gray_img = gray_img = None


    # kernel = cv.getStructuringElement(cv.MORPH_RECT,(3, 3))

    count = totalframe
    count = totalframe if totalframe<count else count 
    x = np.arange(0,count+1)
    y = np.zeros(count+1)
    y2 = np.zeros(count+1)
    ym = np.zeros(count+1)
    yn = np.zeros(count+1)
    
    last_stddev  = diff_stddev = 0

    scenechanged = 0;
    n = 0
    imagecount = 0
    start = end = 0
    start = time.time()

    imageindex = 0
    imagecontinues = 0
    imagestart = 0
    while(n < totalframe):
        # read original image
        ret, img = cap.read()        
        if not ret:
            n += 1
            continue
    
        # resize to the quarter of the original image
        resize_img = cv.resize(img, (tw, th))        

        # cv.imshow("video", resize_img)

        # gray image 
        gray_img = cv.cvtColor(resize_img, cv.COLOR_BGRA2GRAY)
        # gray_img = ori_gray_img

        # caculate mean & sd
        (mean, stddev) = cv.meanStdDev(gray_img)



        # cv.imshow("eqH", gray_img)

        
        if(last_gray_img is None):
            scenechanged = 1
        else:

            diff_stddev = int(abs(stddev - last_stddev))
            y2[n] = diff_stddev
            

            if n >= count:
                break

            if(diff_stddev > 0 ):
                log.debug("frame-----------------------------------------------  "+str(n))
                if(imagecontinues == 0):
                    imagecontinues = 1
                    imagecount += 1
                    imagestart = n
                    imageindex = n  
                    scenechanged = 1                  
                else:
 
                    if(n-imageindex == 1):
                        imageindex = n
                    else:
                        imagecontinues = 0

                # print("imagestart :", imagestart, "iamgeindex :", imageindex, "imagecontinues: ",imagecontinues)
               
                # ratio = knnDetect(last_gray_img, gray_img, sift, flann)
                # ratio = 0
                # yn[n] = ratio*25
                
                # if (ratio > 0 and ratio < 200):
                #     log.debug("-------------------------------------------------------------------------------------------")
                #     log.debug("%d, %s-%d, %d, %d",imagecount,"frame", n, diff, ratio)
                #     imagecount += 1
                #     scenechanged = 1

        last_gray_img = gray_img
        last_stddev = stddev
        
        
        if(scenechanged == 1):
        #     # print("diff", n, diff_stddev)    
            uuname = uuid.uuid1().hex
            outputfilename = outputpath+uuname+".png"     
            cv.imwrite(outputfilename, resize_img, [cv.IMWRITE_PNG_COMPRESSION, 9])
            scenechanged = 0  

        # time.sleep(1/fps)
        
        n += 1

    end = time.time()
    return imagecount

    # log.info("total time : %d, imagecount: %d",(end-start, imagecount)

    # cv.normalize(y, y, 0, 100,cv.NORM_MINMAX)
    # cv.normalize(y2, y2, 0, 100,cv.NORM_MINMAX)
    # cv.normalize(ym, ym, 0, 100,cv.NORM_MINMAX)
    # cv.normalize(yn, yn, 0, 100,cv.NORM_MINMAX)

    # fig = plt.figure()
    # ax1 = fig.add_subplot(111)
    # ax1.set_title("pixel diff")
    # plt.xlabel('frame')
    # plt.ylabel('diffsum')
    # ax1.scatter(x,y,s=1,c='r')
    # ax1.scatter(x,y2,s=1,c='g')
    # ax1.scatter(x,ym,s=1,c='m')
    # ax1.scatter(x,yn,s=1,c='b')

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

    # plt.savefig(rtsp_str+".jpg")
    

def readfdictfromfile(filename):
    fdict = {}
    f = open(filename, 'r', encoding='utf-8')
    foperations = f.readlines()

    
    for foper in foperations:
    # for fileopstr in fileoperations:
        fop = foper.split('\t')
        fname = fop[0]
        op = fop[3]

        fname = fname.strip()
        op = op.strip()
        fdict[fname] = op
    
    f.close()

    return fdict


def writefdictofile(dict, file):
    f = open(file, 'w', encoding='utf-8')
    for key, value in dict.items():
        f.write(key +"\t\t\t"+ value+'\n')
    f.close()

if __name__ == '__main__':

    # rtsp_str = 'D:\\code\\drawoutscene\\build\\test\\00142.m2ts'
    # rtsp_str = 'D:\\迅雷下载\\[电影天堂www.dytt89.com]冒牌大保镖-2021_HD国语中字.mp4'
    start = time.time()
    log = get_log()
    rootpath = "D:\\food\\"

    dictfilename = "D:\\output_1\\files-1.txt"

    # filedict = readfdictfromfile(dictfilename)

    # rootpath = "D:\\BaiduNetdiskDownload\\视频任务组_20170922_2313\\"

    dirfiles = os.walk(rootpath)
    
    
    for dirfile in dirfiles:
        (path, dirs, files) = dirfile
        for file in files:
            imagecount = 0
            filepathname = os.path.join(path, file)
            # if filedict[filepathname] == '1':
            #     log.info(filepathname+ " is analysed!")
            #     continue
            # print(filepathname)
            filestart = time.time()
            log.info(filepathname+"-------- analysed start")  
            try:           
                imagecount = drawoutScenes(filepathname)
                pass
            except Exception as e:
                log.error(e)
                # writefdictofile(filedict, dictfilename)    
            # filedict[filepathname] = '1'    
            log.info(filepathname+"-------- analysed end")
            fileend = time.time()
            log.info(filepathname+" total time: %f, imagecount: %d", fileend-filestart, imagecount)
    end = time.time()
    log.info("all files total time: "+str(end-start))
    
    

    


    # cv.waitKey(20)
