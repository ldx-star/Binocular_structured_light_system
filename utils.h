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
    static bool detectCorners(const cv::Mat& img_L,const cv::Mat& img_R, std::vector<cv::Point2f>& cornersL_xy ,std::vector<cv::Point2f>& cornersR_xy, const cv::Size& patSize,bool show = true);
    static bool makedir(const std::string& path);
    static std::string extract_num(const std::string& str);
    static bool is_includeNum(const std::string& line);
};


#endif //BINOCULAR_STRUCTURED_LIGHT_SYSTEM_UTILS_H
