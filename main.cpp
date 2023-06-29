//
// Created by liangdaxin on 23-6-28.
//
#include "Camera.h"
#include "types.h"
#include <opencv2/opencv.hpp>

void phase_shifting_and_gray_code(const Config& config){
    Camera camera = Camera();
    camera.img_counts_ = config.img_counts;
    camera.patSize_= cv::Size(config.Board_col,config.Board_row) ;
    camera.imgSize_ = cv::Size(config.img_col,config.img_row);
    camera.Board_square_ = config.Board_square;
    camera.camera_param_path_ = config.camera_param_path;
    camera.board_imagePath_ = config.board_imagePath;
    camera.camera_param_file_ = config.camera_param_file;
    //相机标定
    if(config.is_calibrate){
        //进行标定
        camera.Camera_Calibrate();
        //保存参数信息
        camera.save_params();
    }else{
        //加载相机参数
        camera.load_params();
    }
    //打印参数信息
    camera.printInfo();


}

void test(){
    std::string input = "The number is 123.45";
    std::istringstream iss(input); // 使用字符串流读取输入

    std::string word;
    while (iss >> word) {
        // 尝试将每个字符串转换为数值
        std::istringstream wordIss(word);
        double number;
        if (wordIss >> number) {
            std::cout << "提取到的数值: " << number << std::endl;
        }
    }
}
int main(){
    //test();
    Config config;
    config.is_calibrate = false;
    config.img_counts = 12;
    config.img_col = 2256; //pix
    config.img_row = 2048;
    config.Board_row = 8;
    config.Board_col = 11;
    config.Board_square = 15; // 毫米
    config.board_imagePath = "../calib_imgs";
    config.camera_param_path = "../calib_params";
    config.camera_param_file = "params.txt";
    phase_shifting_and_gray_code(config);

    return 0;
}