//
// Created by liangdaxin on 23-6-28.
//

#include "Camera.h"
#include "utils.h"
#include "types.h"
#include <opencv2/opencv.hpp>
#include <fstream>

void Camera::Camera_Calibrate() {
    std::vector<std::vector<cv::Point3f>> all_corners_xyz;//所有图片角点的世界坐标
    std::vector<cv::Point3f> corners_xyz;//所有角点的世界坐标
    //角点世界坐标
    for(int i = 0; i < patSize_.height;i++){
        for(int j = 0; j < patSize_.width;j++){
            cv::Point3f point3f;
            point3f.x = j * Board_square_;
            point3f.y = i * Board_square_;
            point3f.z = 0;
            corners_xyz.emplace_back(point3f);
        }
    }

    std::vector<std::vector<cv::Point2f>> all_cornersL_xy;//所有左相机图像的圆心像素坐标
    std::vector<std::vector<cv::Point2f>> all_cornersR_xy;//所有右相机图像的圆心像素坐标

    /*=================左右相机标定===============*/
    std::cout << "===============左右相机标定============" << std::endl;
    std::vector<std::string> img_fileNames_L;
    cv::glob(board_imagePath_ + "/L/*.bmp", img_fileNames_L);
    std::vector<std::string> img_fileNames_R;
    cv::glob(board_imagePath_ + "/R/*.bmp", img_fileNames_R);
    //读取图片
    std::vector<cv::Mat> imgs_L;
    utils::im_read(img_fileNames_L, imgs_L, 1);
    std::vector<cv::Mat> imgs_R;
    utils::im_read(img_fileNames_R, imgs_R, 1);

    //角点检测
    std::cout << "开始角点检测" << std::endl;
    bool show = false;
    for(int i = 0; i < img_counts_;i++){
        std::vector<cv::Point2f> cornersL_xy;//左相机角点像素坐标
        std::vector<cv::Point2f> cornersR_xy;//右相机角点像素坐标
        cv::Mat img_L = imgs_L[i];
        cv::Mat img_R = imgs_R[i];
        bool find = utils::detectCorners(img_L,img_R,cornersL_xy,cornersR_xy,patSize_,show);
        if(find){
            all_cornersL_xy.emplace_back(cornersL_xy);
            all_cornersR_xy.emplace_back(cornersR_xy);
            //每张图都需要世界坐标
            all_corners_xyz.emplace_back(corners_xyz);
        }else{
            if(show){
                cv::Mat imgshow;
                cv::hconcat(img_L, img_R, imgshow);
                cv::namedWindow("Board", cv::WINDOW_NORMAL);
                cv::resizeWindow("Board", imgshow.size() / 3);
                cv::imshow("Board", imgshow);
                cv::waitKey();
            }

        }

    }
    std::cout << "角点检测完成" << std::endl;

    //相机标定
    std::cout << "开始标定左相机" << std::endl;
    error_L_ = cv::calibrateCamera(all_corners_xyz, // 世界坐标
                        all_cornersL_xy, // 像素坐标
                        cv::Size(imgSize_.width*2,imgSize_.height), // 图像尺寸
                        M_L_, //内参
                        D_L_, //畸变系数
                        rotation_L_,        //旋转矩阵
                        translation_L_        //平移矩阵
                        );
    std::cout << "左相机标定完成" << std::endl;

    //相机标定
    std::cout << "开始标定右相机" << std::endl;
    error_R_ = cv::calibrateCamera(all_corners_xyz, // 世界坐标
                                   all_cornersR_xy, // 像素坐标
                                   imgSize_, // 图像尺寸
                                   M_R_, //内参
                                   D_R_, //畸变系数
                                   rotation_R_,        //旋转矩阵
                                   translation_R_        //平移矩阵
    );
    std::cout << "右相机标定完成" << std::endl;

    //立体标定
    std::cout << "===============立体标定============" << std::endl;
    error_LR_ = cv::stereoCalibrate(all_corners_xyz,
                                    all_cornersL_xy,
                                    all_cornersR_xy,
                                    M_L_,D_L_,
                                    M_R_,D_R_,
                                    imgSize_,
                                    R_,
                                    T_,
                                    E_,
                                    F_,
                                    cv::CALIB_FIX_INTRINSIC,
                                    cv::TermCriteria(cv::TermCriteria::COUNT+cv::TermCriteria::EPS, 100, 1e-6)
                                    );
    std::cout << "立体标定完成" << std::endl;
    std::cout <<  std::endl;
}

void Camera::save_params() {
    std::cout << "=========保存参数===========" << std::endl;

    utils::makedir(camera_param_path_);

    std::fstream file;
    file.open(camera_param_path_ + "/" + camera_param_file_,std::ios::out);

    if(file.is_open()){
        file<<"M_L:\n";
        file<<M_L_<<std::endl;

        file<<"M_R:\n";
        file<<M_R_<<std::endl;

        file<<"D_L:\n";
        file<<D_L_<<std::endl;

        file<<"D_R:\n";
        file<<D_R_<<std::endl;

        file<<"R:\n";
        file<<R_<<std::endl;

        file<<"T:\n";
        file<<T_<<std::endl;

        file<<"E:\n";
        file<<E_<<std::endl;

        file<<"F:\n";
        file<<F_<<std::endl;

        file<<"error_L:\n";
        file<<error_L_<<std::endl;

        file<<"error_R:\n";
        file<<error_R_<<std::endl;

        file<<"error_LR:\n";
        file<<error_LR_<<std::endl;
    }


    file.close();

    std::cout << "save params success" << std::endl;


}

void Camera::load_params() {
    std::cout << "=========加载参数===========" << std::endl;

    std::fstream file;
    file.open(camera_param_path_ +"/"+ camera_param_file_,std::ios::in);
    if(!file.is_open()){
        std::cout<< camera_param_file_ +  "打开失败"<<std::endl;
    }

    std::string title;
    std::string data;
    std::string line;
    std::vector<double>numbers;

    while(!file.eof()){
        std::getline(file,line);
        if(utils::is_includeNum(line)){
            data = line;
        }else{
            if(!numbers.empty()){
                if(title == "M_L:"){
                    cv::Mat mat(3,3,CV_64F,numbers.data());
                    M_L_ = mat.clone();
                }else if(title == "M_R:"){
                    cv::Mat mat(3,3,CV_64F,numbers.data());
                    M_R_ = mat.clone();
                }else if(title == "D_L:"){
                    cv::Mat mat(1,5,CV_64F,numbers.data());
                    D_L_ = mat.clone();
                }else if(title == "D_R:"){
                    cv::Mat mat(1,5,CV_64F,numbers.data());
                    D_R_ = mat.clone();
                }else if(title == "R:"){
                    cv::Mat mat(3,3,CV_64F,numbers.data());
                    R_ = mat.clone();
                }else if(title == "T:"){
                    cv::Mat mat(3,1,CV_64F,numbers.data());
                    T_ = mat.clone();
                }else if(title == "E:"){
                    cv::Mat mat(3,3,CV_64F,numbers.data());
                    E_ = mat.clone();
                }else if(title == "F:"){
                    cv::Mat mat(3,3,CV_64F,numbers.data());
                    F_ = mat.clone();
                }else if(title == "error_L:") {
                    error_L_ = numbers[0];
                }else if(title == "error_R:") {
                    error_R_ = numbers[0];
                }else if(title == "error_LR:") {
                    error_LR_ = numbers[0];
                }
            }
            title = line;
            numbers.clear();
            continue;
        }
        std::istringstream iss(data); // 使用字符串流读取输入
        std::string word;
        while (iss >> word) {
            // 尝试将每个字符串转换为数值
            std::istringstream wordIss(word);

            std::string num = utils::extract_num(word);
            double number = std::stod(num);
            numbers.emplace_back(number);
        }
    }
    file.close();
    std::cout<<"============参数加载完成==========="<<std::endl;
}

void Camera::printInfo() {
    std::cout << "==========打印参数=================";
    std::cout<< std::endl;

    std::cout<< "左相机内参：" << std::endl;
    std::cout<< M_L_ << std::endl;
    std::cout<< "右相机内参：" << std::endl;
    std::cout<< M_R_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "左相机畸变系数：" << std::endl;
    std::cout<< D_L_ << std::endl;
    std::cout<< "右相机畸变系数：" << std::endl;
    std::cout<< D_R_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "左相机重投影误差：" << std::endl;
    std::cout<< error_L_ << std::endl;
    std::cout<< "右相机重投影误差：" << std::endl;
    std::cout<< error_R_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "旋转矩阵：" << std::endl;
    std::cout<< R_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "平移矩阵：" << std::endl;
    std::cout<< T_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "本质矩阵：" << std::endl;
    std::cout<< E_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "基础矩阵：" << std::endl;
    std::cout<< F_ << std::endl;

    std::cout<< std::endl;

    std::cout<< "立体标定重投影误差：" << std::endl;
    std::cout<< error_LR_ << std::endl;

}

