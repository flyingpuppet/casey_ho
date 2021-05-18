import cv2
import sys
import matplotlib.pyplot as plt
import os
import pdb
import numpy as np
# from wrapper import ClassifierWrapper
os.environ["KMP_DUPLICATE_LIB_OK"]="TRUE"

class FrameReader(object):
    def __init__(self, video_path):
        self._cap = cv2.VideoCapture(video_path)
        self._backend = 'op'

    def jumpto(self, frameindex):
        self._cap.set(cv2.CAP_PROP_POS_FRAMES, frameindex)

    def read(self, interval = 1):
        while True:
            rt, frame = self._cap.read()
            interval -= 1
            if interval == 0:
                return rt, frame

    def get(self, frameindex):
        self.jumpto(frameindex)
        return self.read()

    def totalframe(self):
        return int(self._cap.get(cv2.CAP_PROP_FRAME_COUNT))

    def fps(self):
        return self._cap.get(cv2.CAP_PROP_FPS)

    def size(self):
        return int(self._cap.get(cv2.CAP_PROP_FRAME_WIDTH)), int(self._cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

def pre_img(img):
    return np.array(cv2.resize(img,(224,224))/255, np.float32)

def cal_static(self, frameimg2, pixdiff=20, diffratio=0.01):
    bbox1  = self._detections[-1].to_tlbr()
    patch1 = self._detections[-1].patch

    patch2 = frameimg2[bbox1[1]:bbox1[3], bbox1[0]:bbox1[2], :]

    sub_frame = cv2.absdiff(patch1, patch2)

    kerne = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))

    frame_2 = cv2.erode(sub_frame, kerne)

    frame_2 = cv2.dilate(frame_2, kerne)

    count = np.sum(frame_2 > pixdiff)

    totalpixel = (bbox1[3] - bbox1[1])*(bbox1[2] - bbox1[0])*3
    ratio = float(count) / totalpixel

    if ratio > diffratio:
        print('count={}, ratio={}'.format(count, ratio))

    return True

def count_fluc(arr):
    length = arr.size
    count = 0
    for i in range(1,length-1):
        if arr[i] != arr[i-1] and arr[i-1] == arr[i+1]:
            count += 1
    return count

cls_list = ['animals','buildings','food','landscapes','others','persons']


def main(video_path):
    # savepath = video_path+'_result.avi'
    reader = FrameReader(video_path)
    fps = reader.fps()
    # fourcc = cv2.VideoWriter_fourcc('M', 'P', '4', '2')
    w,h = reader.size()
    # videoWriter = cv2.VideoWriter(savepath, fourcc, fps/3, (w,h))
    totalframe = reader.totalframe()
    # modelpath = "D:/project/my_codebase/ckpt/mobilenetv3-10-best.pth"
    # model = ClassifierWrapper(modelpath, gpu_id='0')
    interval = 1
    
    cv2.namedWindow('test', cv2.WINDOW_NORMAL)
    cv2.resizeWindow('test', 800, 800)
    x = np.arange(0,totalframe)
    y = np.zeros(totalframe)
    for idx in range(int(totalframe)):
        print(fps, w, h)
        if idx % interval != 0:
            continue
        img1 = reader.get(idx)[-1]
        if img1 is None:
            continue
        pre = pre_img(img1)
        # result = model.infer(pre)
        # cidx = np.argmax(result)
        # y[idx] = cidx
        # c = cls_list[cidx]
        # cv2.putText(img1,c,(10, 530), cv2.FONT_HERSHEY_SIMPLEX, 5, (0, 0, 255), 2)
        # videoWriter.write(img1)
        # print(str(idx) + '/' + str(totalframe) + '   ' + str(result) + '   ' + str(c))
        cv2.imshow('test',img1)
        cv2.waitKey(20)
    # videoWriter.release()
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.set_title(video_path.split('/')[-1])
    plt.xlabel('frame')
    plt.ylabel('class')
    ax1.scatter(x,y,s=1)
    plt.savefig(video_path+".jpg")
    print(count_fluc(y))


# 绘制像素点统计图
def main2(video_path):
    reader = FrameReader(video_path)
    totalframe = reader.totalframe()
    x = np.arange(0,totalframe)
    y = np.zeros(totalframe)
    # arr = np.load('k.npy')
    fluc_pix = []
    cv2.namedWindow('test', cv2.WINDOW_NORMAL)
    cv2.resizeWindow('test', 800, 800)
    for idx in range(1, int(totalframe)):
        img1 = reader.get(idx-1)[-1]
        img2 = reader.get(idx)[-1]
        if img1 is None or img2 is None:
            print('raed frame' + str(idx) + 'fail!')
            continue
        pre1 = cv2.resize(img1,(224,224))
        pre2 = cv2.resize(img2,(224,224))
        sub = cv2.absdiff(pre1, pre2)
        gray = cv2.cvtColor(sub, cv2.COLOR_BGR2GRAY)
        thresh = cv2.threshold(gray,20,255,cv2.THRESH_BINARY)[1]
        kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
        erode = cv2.erode(sub, kernel)
        dilate = cv2.dilate(erode, kernel)

        cv2.imshow('test',dilate)
        cv2.waitKey(20)
        pix_count = int(dilate.sum()/255)
        y[idx] = pix_count
        print(str(idx) + '/' + str(totalframe) + '   sum:' + str(pix_count))
        if idx < totalframe:
            fluc_pix.append(thresh)
    fig = plt.figure()
    ax1 = fig.add_subplot(111)
    ax1.set_title(video_path.split('/')[-1])
    plt.xlabel('frame')
    plt.ylabel('diffsum')
    ax1.scatter(x,y,s=1)
    plt.savefig(video_path+"_flus.jpg")
    np.save('pixsum.npy',fluc_pix)


main2('D:\\code\\drawoutscene\\build\\test\\00142.m2ts')