//
// Created by liangdaxin on 23-6-28.
//

#include "Camera.h"
#include "utils.h"
#include "types.h"
#include <opencv2/opencv.hpp>

void Camera::Camera_Calibrate() {
    /*=================左相机标定===============*/
    std::cout << "===============左相机标定============" << std::endl;
    std::vector<std::string> img_fileNames;
    cv::glob(board_imagePath_ + "/L/*.bmp", img_fileNames);
    //读取图片
    std::vector<cv::Mat> imgs;
    utils::im_read(img_fileNames, imgs, 1);

    //圆心检测
    std::cout << "开始圆心检测" << std::endl;
    cv::Size patSize;
    patSize = cv::Size(Board_col_, Board_row_); // 标定板 col * row
    for(auto img:imgs){
        std::vector<cv::Point2f> centers_xy;//圆心像素坐标
        utils::detectCenters(img,centers_xy,patSize,true);
        all_centersL_xy_.emplace_back(centers_xy);
    }
    std::cout << "圆形检测完成" << std::endl;

    //相机标定
    std::cout << "开始标定左相机" << std::endl;




    //右相机标定
}

void Camera::load_params() {

}

void Camera::Stereo_Calibrate() {

}


