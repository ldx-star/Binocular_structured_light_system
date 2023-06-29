//
// Created by liangdaxin on 23-6-28.
//

#ifndef BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H
#define BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H

#include <iostream>
#include <opencv2/opencv.hpp>

class Camera {
public:
    int img_counts_; //图片数量
    std::string board_imagePath_; // 棋盘格图像路径
    std::string camera_param_path_; // 参数路径
    std::string camera_param_file_; // 参数文件

    cv::Size patSize_;       // 棋盘格 cols x rows
    cv::Size imgSize_;       // 图像 cols x rows
    float Board_square_; // 单个棋盘格的大小


    cv::Mat M_L_, M_R_;       // 内参矩阵(左/右)
    cv::Mat D_L_, D_R_;       // 畸变系数(左/右)
    std::vector<cv::Mat> rotation_L_, rotation_R_;  // 旋转矩阵(左/右)
    std::vector<cv::Mat> translation_L_, translation_R_;  // 平移矩阵(左/右)

    double error_L_, error_R_; // 左/右相机重投影误差
    double error_LR_; // 立体标定重投影误差

    cv::Mat R_, T_;          // 旋转矩阵，平移矩阵
    cv::Mat E_, F_;          // 本质矩阵，基础矩阵

public:
    Camera() = default;
    ~Camera() = default;
    //相机标定
    void Camera_Calibrate();
    //打印标定信息
    void printInfo();
    //保存参数
    void save_params();
    //加载相机参数
    void load_params();
};


#endif //BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H
