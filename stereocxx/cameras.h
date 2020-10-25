#pragma once
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <chrono>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class Cameras {
public:
	Cameras(std::vector<int> sources = {},
		unsigned width = 1280,
		unsigned height = 1024,
		unsigned fps = 60,
		int mode = 0);
	~Cameras();

	bool capture();
	bool capture_black();

	cv::VideoCapture& cam(size_t no);
	cv::Mat& frame(size_t no);
	size_t size() const;
	void set_prop(int prop_id, double value);

	void loop(size_t no);
private:
	//void loop(size_t no);

	size_t _size;
	std::vector<std::thread> _threads;
	std::mutex _cond_mutex;
	std::condition_variable _cond;
	std::vector<cv::VideoCapture> _cams;
	std::vector<cv::Mat> _frames;
	std::vector<bool> _status;
	std::chrono::high_resolution_clock _clock;
};