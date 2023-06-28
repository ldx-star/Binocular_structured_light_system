//
// Created by liangdaxin on 23-6-28.
//

#include "utils.h"

void utils::im_read(const std::vector<std::string>& img_fileNames, std::vector<cv::Mat>& imgs, int color_model) {
    cv::Mat img;

    for (auto fileName: img_fileNames) {
        img = cv::imread(fileName,color_model);
        if(img.data == nullptr){
            std::cout << "棋盘格读取错误"<<std::endl;
            exit(1);
        }
        imgs.emplace_back(img);
    }
}

void utils::detectCenters(const cv::Mat &img, std::vector<cv::Point2f> &point2fs, const cv::Size& patSize,bool show) {
    //转为灰度图
    cv::Mat img_gray;
    cv::cvtColor(img,img_gray,cv::COLOR_BGR2GRAY);
    //检测
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(img_gray,circles,cv::HOUGH_GRADIENT,1,15);


    if(1){
        std::cout<<"圆心提取失败"<<std::endl;
        exit(1);
    }
    if(show){
        cv::drawChessboardCorners(img,patSize,point2fs,true);
        cv::namedWindow("Board",cv::WINDOW_NORMAL);
        cv::resizeWindow("Board",img.size()/3);
        cv::imshow("Board",img);
        cv::waitKey();
    }

}