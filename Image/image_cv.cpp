//
// Created by Florent on 14/12/2018.
//

#include "image_cv.h"
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <glm/common.hpp>

ImageCV::ImageCV(uint32_t hauteur, uint32_t largeur) :
		BaseImage(hauteur, largeur),
		pixels(hauteur, largeur, type) {}

void ImageCV::setSize(uint32_t hauteur, uint32_t largeur) {
	pixels.create(hauteur, largeur, ImageCV::type);
	ImageCV::hauteur = hauteur;
	ImageCV::largeur = largeur;
}

bool ImageCV::save(const std::string &name) {
	if (this->pixels.empty()) {
		std::stringstream exptn("Exception at ");
		exptn << __LINE__ << " in " << __FILE__ << ": not initialized. Make sure to use the not default constructor or use the setSize method.\n";
		throw std::runtime_error(exptn.str());
	}
	return cv::imwrite(name, this->pixels);
}

void ImageCV::setPixel(uint32_t x, uint32_t y, const glm::vec3 &pixel) {
	if (this->pixels.empty())
		throw std::runtime_error("Exception: not initialized. Make sure to use the not default constructor or use the setSize method.\n");

	this->pixels.at<cv::Vec4b>(cv::Point(x, y)).val[0] = static_cast<unsigned char>(glm::clamp(pixel.z * 255.0f, 0.0f, 255.0f));
	this->pixels.at<cv::Vec4b>(cv::Point(x, y)).val[1] = static_cast<unsigned char>(glm::clamp(pixel.y * 255.0f, 0.0f, 255.0f));
	this->pixels.at<cv::Vec4b>(cv::Point(x, y)).val[2] = static_cast<unsigned char>(glm::clamp(pixel.x * 255.0f, 0.0f, 255.0f));
	this->pixels.at<cv::Vec4b>(cv::Point(x, y)).val[3] = 255;
}
