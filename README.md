# 计算机视觉 Compute Vision

本目录下为计算机视觉相关的一些项目源码。源码采用C++编写，运行在VS2017版本，OpenCV 4.3版本。

各源码及其功能如下（源码均可编译运行、提供图片的所属路径可能稍许修改）:
   
#### RGB_split.cpp ---------> RGB分量提取
#### Pic_processing --------> 滤波（平均、高斯、中值）、边缘检测算子（sobel、canny）
#### Rice_evaluation -------> Rice Evaluation（大津算法、形态学[开运算]去噪、图像分割、轮廓提取、性能评价RSME）
#### Video_Porc ------------> 运动检测和光流估计
#### -- MotionDetectionBasedOnBackgroundExtraction.cpp -->基于背景提取的运动检测
#### -- OpticalFlowEstimation.cpp -->光流估计 角点检测

