#include <iostream>
#include <string>
#include <vector>

#include "detector.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
	Detector* detector = new Detector;
	string xml_path = "D:\\Disk\\new weight\\last.xml";
	//string xml_path = "C:/Users/db245/Downloads/openvino_yolov5-master/openvino_yolov5-master/yolov5s.xml";
	detector->init(xml_path);
	Mat src=imread("D:\\Disk\\yolov5\\datasets\\coco128\\images\\train\\1.bmp");
	vector<Detector::Object> detected_objects;

	auto start = chrono::high_resolution_clock::now();
	detector->process_frame(src, detected_objects);
	for (int i = 0; i < detected_objects.size(); ++i) {
		int xmin = detected_objects[i].rect.x;
		int ymin = detected_objects[i].rect.y;
		int width = detected_objects[i].rect.width;
		int height = detected_objects[i].rect.height;
		Rect rect(xmin, ymin, width, height);
		cv::rectangle(src, rect, Scalar(255, 0, 0), 1, LINE_8, 0);
		cout << "is: " << detected_objects[i].name << endl;
		putText(src, detected_objects[i].name,
			cv::Point(xmin, ymin - 10),
			cv::FONT_HERSHEY_SIMPLEX,
			0.5,
			cv::Scalar(0, 0, 0));
	}
	auto end = chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	cout << "use " << diff.count() << " s" << endl;
	putText(src, "" + to_string(diff.count()),
		cv::Point(5, 20),
		cv::FONT_HERSHEY_SIMPLEX,
		0.5,
		cv::Scalar(255, 0, 0));
	resize(src, src, Size(src.cols/2, src.rows/2 ));
	imshow("cap", src);
	waitKey(0);

	return 0;
}
