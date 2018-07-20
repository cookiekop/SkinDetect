#include <iostream>

#include <opencv2/opencv.hpp>

using namespace std;

cv::Mat DetectSkin(cv::Mat img){
    /*
        R>95 AND G>40 B>20 AND MAX(R,G,B)-MIN(R,G,B)>15 AND ABS(R-G)>15 AND R>G AND R>B
            OR
        R>220 AND G>210 AND B>170 AND ABS(R-G)<=15 AND R>B AND G>B
    */
    cv::Mat detect = img.clone();
    detect.setTo(0);
    if (img.empty() || img.channels() != 3)
    {
        cout << "image error!" << endl;
        return detect;
    }

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            uchar *p_detect = detect.ptr<uchar>(i, j);
            uchar *p_img = img.ptr<uchar>(i, j);
            if ((p_img[2] > 95 && p_img[1]>40 && p_img[0] > 20 &&
                 (MAX(p_img[0], MAX(p_img[1], p_img[2])) - MIN(p_img[0], MIN(p_img[1], p_img[2])) > 15) &&
                 abs(p_img[2] - p_img[1]) > 15 && p_img[2] > p_img[1] && p_img[1] > p_img[0]) ||
                (p_img[2] > 200 && p_img[1] > 210 && p_img[0] > 170 && abs(p_img[2] - p_img[1]) <= 15 &&
                 p_img[2] > p_img[0] &&  p_img[1] > p_img[0]))
            {
                p_detect[0] = p_img[0];
                p_detect[1] = p_img[1];
                p_detect[2] = p_img[2];
            }


        }

    }
    return detect;
}

int main() {
    cv::Mat black, white, yellow;
    black = cv::imread("./black.jpg");
    white = cv::imread("./white.jpg");
    yellow = cv::imread("./yellow.jpg");

    cv::Mat black_out, white_out, yellow_out;
    black_out = DetectSkin(black);
    white_out = DetectSkin(white);
    yellow_out = DetectSkin(yellow);
    cv::imshow("black", black_out);
    cv::imshow("white", white_out);
    cv::imshow("yellow", yellow_out);

    cv::waitKey(0);
    return 0;
}