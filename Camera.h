//
// Created by liangdaxin on 23-6-28.
//

#ifndef BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H
#define BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H

#include <iostream>
#include <opencv2/opencv.hpp>

class Camera {
public:
    std::vector<std::vector<cv::Point2f>> all_centersL_xy_;//所有左相机图像的圆心像素坐标
    std::vector<std::vector<cv::Point2f>> all_centersR_xy_;//所有右相机图像的圆心像素坐标

    cv::Size imgSize;       // 图像大小 1280x720
    cv::Size patSize;       // 棋盘格 cols x rows
    double squareSize;  // 方格尺寸 5.f
    cv::Mat M_L, M_R;       // 内参矩阵(左/右)
    cv::Mat D_L, D_R;       // 畸变系数(左/右)
    std::vector<cv::Mat> rvecs_L, rvecs_R;  // 旋转矩阵(左/右)
    std::vector<cv::Mat> tvecs_L, tvecs_R;  // 平移矩阵(左/右)
    double error_L = 0., error_R = 0.; // 标定误差(单目)

    cv::Mat R, T;          // 旋转矩阵（R）+矩阵（T）
    cv::Mat E, F;          // 本质矩阵（）
    double error_LR = 0.;  // 标定误差（双目）

public:
    std::string board_imagePath_;
    int Board_row_; // 棋盘格行数
    int Board_col_; // 棋盘格列数
    float Board_square_; // 单个棋盘格的大小
    std::string cameraL_param_path_; // 左相机参数路径
    std::string cameraR_param_path_; // 右相机参数路径
public:
    Camera() = default;
    ~Camera() = default;
    //相机标定
    void Camera_Calibrate();
    //立体标定
    void Stereo_Calibrate();

    //加载相机参数
    void load_params();
};


#endif //BINOCULAR_STRUCTURED_LIGHT_SYSTEM_CAMERA_H
