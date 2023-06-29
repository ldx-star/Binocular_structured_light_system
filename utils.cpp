//
// Created by liangdaxin on 23-6-28.
//

#include "utils.h"
#include <filesystem>

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

bool utils::detectCorners(const cv::Mat &img_L, const cv::Mat &img_R, std::vector<cv::Point2f> &cornersL_xy,
                          std::vector<cv::Point2f> &cornersR_xy, const cv::Size &patSize, bool show) {

    //转为灰度图
    cv::Mat img_gray_L,img_gray_R;

    cv::cvtColor(img_L,img_gray_L,cv::COLOR_BGR2GRAY);
    cv::cvtColor(img_R,img_gray_R,cv::COLOR_BGR2GRAY);
    //角点检测
    bool findL = cv::findChessboardCorners(img_gray_L,patSize,cornersL_xy,cv::CALIB_CB_ASYMMETRIC_GRID | cv::CALIB_CB_FILTER_QUADS);
    bool findR = cv::findChessboardCorners(img_gray_R,patSize,cornersR_xy,cv::CALIB_CB_ASYMMETRIC_GRID | cv::CALIB_CB_FILTER_QUADS);
    //精检测
    if(findL && findR) {
        cv::cornerSubPix(img_gray_L, cornersL_xy, cv::Size(11, 11), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 300, 0.01));
        cv::cornerSubPix(img_gray_R, cornersR_xy, cv::Size(11, 11), cv::Size(-1, -1),
                         cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 300, 0.01));

        if (show) {
            cv::drawChessboardCorners(img_L, patSize, cornersL_xy, true);
            cv::drawChessboardCorners(img_R, patSize, cornersR_xy, true);
            cv::Mat imgshow;
            cv::hconcat(img_L, img_R, imgshow);
            cv::namedWindow("Board", cv::WINDOW_NORMAL);
            cv::resizeWindow("Board", imgshow.size() / 3);
            cv::imshow("Board", imgshow);
            cv::waitKey();
        }
        return true;
    }
    return false;
}

bool utils::makedir(const std::string &path) {
    if(std::filesystem::is_directory(path)){
        std::cout << "文件已存在"<< std::endl;
    }else{
        std::filesystem::create_directories(path);
        if(std::filesystem::is_directory(path)){
            std::cout<<"创建成功"<<std::endl;
        }else{
            std::cout<<"创建失败"<<std::endl;
            return false;
        }
    }
    return true;
}

std::string utils::extract_num(const std::string &str) {
    std::string data;
    for(auto e : str){
        if(e >= '0' && e <= '9'|| e == '.' || e == '-' || e == 'e' ){
            data += e;
        }
    }
    return data;
}

bool utils::is_includeNum(const std::string& line) {
    for (const auto &e: line)
        if (e >= '0' && e <= '9') {
            return true;
        }
    return false;
}