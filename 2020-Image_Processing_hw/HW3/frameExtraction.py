import cv2
def get_images_from_video(video_name, time_F):
    video_images = []
    vc = cv2.VideoCapture(video_name)
    c = 1
    
    if vc.isOpened(): #判斷是否開啟影片
        rval, video_frame = vc.read()
    else:
        rval = False

    while rval:   #擷取視頻至結束
        rval, video_frame = vc.read()
        
        if(c % time_F == 0): #每隔幾幀進行擷取
            video_images.append(video_frame)     
        c = c + 1
    vc.release()
    
    return video_images

time_F = 2 #time_F越小，取樣張數越多
video_name = '3.mp4' #影片名稱
video_images = get_images_from_video(video_name, time_F) #讀取影片並轉成圖片


for i in range(0, len(video_images)): #顯示出所有擷取之圖片
    savepath = 'img/{}.png'.format(i)
    cv2.imwrite(savepath, video_images[i])
