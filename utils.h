//
// Created by liangdaxin on 23-6-28.
//

#ifndef BINOCULAR_STRUCTURED_LIGHT_SYSTEM_UTILS_H
#define BINOCULAR_STRUCTURED_LIGHT_SYSTEM_UTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class utils {
public:
    static void im_read(const std::vector<std::string>& img_fileNames, std::vector<cv::Mat>& imgs, int color_model = 1);
    static void detectCenters(const cv::Mat& img, std::vector<cv::Point2f>& point2fs , const cv::Size& patSize,bool show = true);
};


#endif //BINOCULAR_STRUCTURED_LIGHT_SYSTEM_UTILS_H
