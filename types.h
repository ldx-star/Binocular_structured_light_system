//
// Created by liangdaxin on 23-6-28.
//

#ifndef BINOCULAR_STRUCTURED_LIGHT_SYSTEM_TYPES_H
#define BINOCULAR_STRUCTURED_LIGHT_SYSTEM_TYPES_H
#include <iostream>

struct Config{
public:
    bool is_calibrate = true;//是否需要进行相机标定，如果有相机参数则不需要标定
    std::string camera_param_file;// 相机参数文件
    std::string board_imagePath;// 棋盘格路径
    int Board_row; // 棋盘行数
    int Board_col; // 棋盘列数
    int img_row; // 图像行数
    int img_col; // 图像列数
    float Board_square; // 单个棋盘格的大小
    int img_counts; //图片数量
    std::string camera_param_path; // 相机参数路径
    std::string params_fileName; // 参数文件名


};
//struct Point3f{
//public:
//    float x;
//    float y;
//    float z;
//public:
//    Point3f() = default;
//};
//
//struct Point2f{
//public:
//    float x;
//    float y;
//public:
//    Point2f() = default;
//};

#endif //BINOCULAR_STRUCTURED_LIGHT_SYSTEM_TYPES_H
