//
// Created by Florent on 14/12/2018.
//

#include "image_cv.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <glm/common.hpp>

ImageCV::ImageCV(uint32_t hauteur, uint32_t largeur) :
		BaseImage(hauteur, largeur),
		pixels(hauteur, largeur, type),
		initialized(true) {}

void ImageCV::setSize(uint32_t hauteur, uint32_t largeur) {
	pixels.create(hauteur, largeur, ImageCV::type);
	ImageCV::hauteur = hauteur;
	ImageCV::largeur = largeur;
	ImageCV::initialized = true;
}

bool ImageCV::save(const std::string& name) {
	if (!this->initialized)
		throw std::runtime_error("Exception : not initialized. Make sure to use the not default constructor or use the setSize method.\n");
	cv::Mat hsv;
	std::vector<cv::Mat> channels;

	cv::cvtColor(this->pixels, hsv, cv::ColorConversionCodes::COLOR_BGR2HSV_FULL);

	cv::split(hsv, channels);
	cv::equalizeHist(channels.at(2), channels.at(2));
	cv::merge(channels, hsv);

	cv::cvtColor(hsv, this->pixels, cv::ColorConversionCodes::COLOR_HSV2BGR_FULL);

	return cv::imwrite(name, this->pixels);
}

void ImageCV::setPixel(uint32_t x, uint32_t y, const glm::vec3& pixel) {
	if (!this->initialized)
		throw std::runtime_error("Exception: not initialized. Make sure to use the not default constructor or use the setSize method.\n");

	this->pixels.at<cv::Vec4f>(cv::Point(x, y)).val[0] = pixel.z;
	this->pixels.at<cv::Vec4f>(cv::Point(x, y)).val[1] = pixel.y;
	this->pixels.at<cv::Vec4f>(cv::Point(x, y)).val[2] = pixel.x;
	this->pixels.at<cv::Vec4f>(cv::Point(x, y)).val[3] = 1.0f;
}
