#ifndef GLOBALMOTIONESTIMATION_HPP
#define GLOBALMOTIONESTIMATION_HPP

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include <io.h>
#include <math.h>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>

#include <GMEParameter.hpp>
#include <FlowFile.hpp>
#include <InputFilePath.hpp>


void calculateRatio(const std::string preIMGPath, const std::string curIMGPath,
                    float &hRatio, float &wRatio);
float defineMinority(cv::Mat &STGS);
void showMask(cv::Mat data);
void geneuratePosition(cv::Mat &pos, int h, int w, bool rowflag);

/*class GlobalMotionEstimation:
        calculate motionvector from input path and get the GME parameters
        Initiated with the rootPath and a ratio for downsampling*/
class GlobalMotionEstimation {
public:
  friend class GMEParameter;
  friend class GMEParameter2;
  friend class GMEParameter6;

  GlobalMotionEstimation(const std::string s, const int r = 1);
  ~GlobalMotionEstimation();

  void calculateParameter();

  std::vector<cv::Mat> parameter;
  std::vector<cv::Mat> mask;

private:
  int initial();
  void calculateMotionVector(const int i);
  std::shared_ptr<GMEParameter> checkRatio(const int i);

  InputFilePath *inputIMG;
  InputFilePath *inputFlow;
  std::shared_ptr<FlowFile> flow;
  std::shared_ptr<GMEParameter> GMEModel;

  size_t nbframes;
  int height = 0, width = 0, ratio;
  std::string rootPath;
  cv::Mat xPos, yPos;
};

#endif