#include "image.h"
#include "camera.h"
#include "objet.h"
#include "sphere.hpp"
#include "triangle.h"
#include "plan.hpp"
#include "phong.hpp"

int main() {
	const unsigned int h = 480 * 2;
	const unsigned int l = 640 * 2;
	Camera myCamera;
	Scene scene;
	Image myImage(h, l);
	Sphere sphere(new Phong(glm::highp_dvec3(0.1, 0.2, 0.1), glm::highp_dvec3(0.6, 0.0, 0.0), 128.0, 1.0), glm::highp_dvec3(-2.5, -0.2, 50.0), 1);
	Sphere secSpher(new Phong(glm::highp_dvec3(0.2f, 0.0f, 0.0f), glm::highp_dvec3(0.0f, 0.5f, 0.392f), 128.0f, 0.0f),
					glm::highp_dvec3(2.5f, -1.7f, 50.0f), 1);
	Triangle triangle(new Phong(glm::highp_dvec3(0.2f, 0.2f, 0.0f), glm::highp_dvec3(1.0f, 1.0f, 1.0f), 128.0f, 0.25f),
					  glm::highp_dvec3(1.7f, -2.0f, 100.0f),
					  glm::highp_dvec3(-2.7f, -2.0f, 100.0f), glm::highp_dvec3(-0.7f, 3.0f, 100.0f));
	Plan background(new Phong(glm::highp_dvec3(0.f, 0.f, 0.f), glm::highp_dvec3(1.0f, 1.0f, 1.0f), 128.0f, 1.0f),
					glm::highp_dvec3(0.0f, 0.0f, 300.0f),
					glm::highp_dvec3(0.0f, 0.0f, -1.0f));
	Plan rooftop(new Phong(glm::highp_dvec3(0.2f, 0.2f, 0.0f), glm::highp_dvec3(0.5f, 0.0f, 0.6f), 128.f, 0.3f), glm::highp_dvec3(0.0f, 10.0f, 0.0f),
				 glm::highp_dvec3(0.0f, -1.0f, 0.0f));
	Plan left(new Phong(glm::highp_dvec3(0.2f, 0.0f, 0.2f), glm::highp_dvec3(0.0f, 0.6f, 0.0f), 128.f, 0.25f), glm::highp_dvec3(10.0f, 0.0f, 0.0f),
			  glm::highp_dvec3(-1.0f, 0.0f, 0.0f));
	Plan right(new Phong(glm::highp_dvec3(0.0f, 0.2f, 0.2f), glm::highp_dvec3(0.6f, 0.0f, 0.0f), 128.0f, 0.6f), glm::highp_dvec3(-10.0f, 0.0f, 0.0f),
			   glm::highp_dvec3(1.0f, 0.0f, 0.0f));
	Plan floor(new Phong(glm::highp_dvec3(0.2f, 0.2f, 0.2f), glm::highp_dvec3(1.0f, 1.0f, 1.0f), 128.f, 0.4f), glm::highp_dvec3(0.0f, -10.0f, 0.0f),
			   glm::highp_dvec3(0.0f, 1.0f, 0.0f));
	Plan closedBox(new Phong(glm::highp_dvec3(0.0f, 0.0f, 0.0f), glm::highp_dvec3(1.0f, 1.0f, 1.0f), 128.0f, 0.35f),
				   glm::highp_dvec3(0.0f, 0.0f, -10.0f),
				   glm::highp_dvec3(0.0f, 0.0f, 1.0f));
	Light light(glm::highp_dvec3(1.0f, 4.0f, 4.0f), glm::highp_dvec3(1.0f, 1.0f, 1.0f));
	scene.addLight(&light);
	scene.addObjet(&sphere);
	scene.addObjet(&secSpher);
	//scene.addObjet(&triangle);
	scene.addObjet(&rooftop);
	scene.addObjet(&left);
	scene.addObjet(&floor);
	scene.addObjet(&right);
	scene.addObjet(&closedBox);
	scene.addObjet(&background);
	myCamera.Calculer_image(myImage, scene, 6);

	myImage.Save("out.png");

	return EXIT_SUCCESS;
}
