#include <opencv2/opencv.hpp>
#include <opencv2/core/opengl.hpp>
#include <GL/glut.h>
#include "cvlibs.h"

void on_opengl(void* userdata);
using namespace cv;

int main(void)
{
	VideoCapture video("./jpg/img%03d.jpg");
	int w = video.get(CV_CAP_PROP_FRAME_WIDTH);
	int h = video.get(CV_CAP_PROP_FRAME_HEIGHT);
	int n = video.get(CV_CAP_PROP_FRAME_COUNT);

	namedWindow("window", CV_WINDOW_OPENGL);
	resizeWindow("window", w, h);

	Mat frame;
	ogl::Texture2D tex;

	setOpenGlDrawCallback("window", on_opengl, &tex);
	glEnable(GL_TEXTURE_2D);

	for(int i =0; i<n && waitKey(30); i++)
	{
		video >> frame;
		tex.copyFrom(frame);
		updateWindow("window");
	}

	return 0;
}

void on_opengl(void* userdata)
{
	ogl::Texture2D* pTex = static_cast<ogl::Texture2D*>(userdata);
	if (pTex->empty())
		return;

	pTex->bind();

	glLoadIdentity();

	double x = +1.0;
	double y = -1.0;
	glColor3d(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-x, -y);
	glTexCoord2d(1.0, 0.0); glVertex2d(+x, -y);
	glTexCoord2d(1.0, 1.0); glVertex2d(+x, +y);
	glTexCoord2d(0.0, 1.0); glVertex2d(-x, +y);
	glEnd();
}