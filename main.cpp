//
// Created by liangdaxin on 23-6-28.
//
#include "Camera.h"
#include "types.h"
#include <opencv2/opencv.hpp>

void phase_shifting_and_gray_code(const Config& config){
    Camera camera = Camera();
    camera.Board_col_ = config.Board_col;
    camera.Board_row_ = config.Board_row;
    camera.Board_square_ = config.Board_square;
    camera.cameraL_param_path_ = config.cameraL_param_path;
    camera.cameraR_param_path_ = config.cameraR_param_path;
    camera.board_imagePath_ = config.board_imagePath;
    //相机标定
    if(config.is_calibrate){
        //进行标定
        camera.Camera_Calibrate();

    }else{
        //加载相机参数
        camera.load_params();

    }

}

void test(){
    cv::Mat img = cv::imread("../img_1.png",0);

    std::vector<cv::Point2f> points;
    cv::SimpleBlobDetector::Params params;
    params.
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    bool find = cv::findCirclesGrid(img,cv::Size(5,4) , points);
    cv::imshow("Detected Circles", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
int main(){
    test();
    Config config;
    config.Board_row = 9;
    config.Board_col = 11;
    config.Board_square = 1;
    config.board_imagePath = "../calib_imgs";
    phase_shifting_and_gray_code(config);

    return 0;
}