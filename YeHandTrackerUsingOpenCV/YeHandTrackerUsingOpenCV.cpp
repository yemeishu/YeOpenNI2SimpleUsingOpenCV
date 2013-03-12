// YeHandTrackerUsingOpenCV.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

// ����NiTE.hͷ�ļ�
#include <NiTE.h>

// ����OpenCVͷ�ļ�
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

const unsigned int XRES = 640;
const unsigned int YRES = 480;

const float DEPTH_SCALE_FACTOR = 255./4096.;

const unsigned int BIN_THRESH_OFFSET = 5;

const unsigned int ROI_OFFSET = 70;

const unsigned int MEDIAN_BLUR_K = 5;

const double GRASPING_THRESH = 0.9;

// colors
const Scalar COLOR_BLUE        = Scalar(240,40,0);
const Scalar COLOR_DARK_GREEN  = Scalar(0, 128, 0);
const Scalar COLOR_LIGHT_GREEN = Scalar(0,255,0);
const Scalar COLOR_YELLOW      = Scalar(0,128,200);
const Scalar COLOR_RED         = Scalar(0,0,255);

// conversion from cvConvexityDefect
struct ConvexityDefect
{
	Point start;
	Point end;
	Point depth_point;
	float depth;
};

// Thanks to Jose Manuel Cabrera for part of this C++ wrapper function
void findConvexityDefects(vector<Point>& contour, vector<int>& hull, vector<ConvexityDefect>& convexDefects)
{
	if(hull.size() > 0 && contour.size() > 0)
	{
		CvSeq* contourPoints;
		CvSeq* defects;
		CvMemStorage* storage;
		CvMemStorage* strDefects;
		CvMemStorage* contourStr;
		CvConvexityDefect *defectArray = 0;

		strDefects = cvCreateMemStorage();
		defects = cvCreateSeq( CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq),sizeof(CvPoint), strDefects );

		contourStr = cvCreateMemStorage();
		contourPoints = cvCreateSeq(CV_SEQ_KIND_GENERIC|CV_32SC2, sizeof(CvSeq), sizeof(CvPoint), contourStr);
		for(int i = 0; i < (int)contour.size(); i++) {
			CvPoint cp = {contour[i].x,  contour[i].y};
			cvSeqPush(contourPoints, &cp);
		}

		int count = (int) hull.size();
		int* hullK = (int*) malloc(count*sizeof(int));
		for(int i = 0; i < count; i++) { hullK[i] = hull.at(i); }
		CvMat hullMat = cvMat(1, count, CV_32SC1, hullK);

		// calculate convexity defects
		storage = cvCreateMemStorage(0);
		defects = cvConvexityDefects(contourPoints, &hullMat, storage);
		defectArray = (CvConvexityDefect*)malloc(sizeof(CvConvexityDefect)*defects->total);
		cvCvtSeqToArray(defects, defectArray, CV_WHOLE_SEQ);

		for(int i = 0; i<defects->total; i++){
			ConvexityDefect def;
			def.start       = Point(defectArray[i].start->x, defectArray[i].start->y);
			def.end         = Point(defectArray[i].end->x, defectArray[i].end->y);
			def.depth_point = Point(defectArray[i].depth_point->x, defectArray[i].depth_point->y);
			def.depth       = defectArray[i].depth;
			convexDefects.push_back(def);
		}

		// release memory
		cvReleaseMemStorage(&contourStr);
		cvReleaseMemStorage(&strDefects);
		cvReleaseMemStorage(&storage);

	}
}

int main(int argc, char** argv)
{
	// ��ʼ��NITE
	nite::NiTE::initialize();

	// ����Hand������
	nite::HandTracker* mHandTracker = new nite::HandTracker;
	mHandTracker->create();
		
	Mat depthShow(YRES, XRES, CV_8UC1);
	Mat handDebug;

	// �����ͼ����ȡ���ֵ�������С
	Rect roi;
	roi.width  = ROI_OFFSET*2;
	roi.height = ROI_OFFSET*2;

	namedWindow("depthFrame", CV_WINDOW_AUTOSIZE);

	// ѭ����ȡ��������Ϣ��������HandFrameRef��
	nite::HandTrackerFrameRef mHandFrame;

	// ��ʼ����̽��
	mHandTracker->startGestureDetection(nite::GESTURE_CLICK);

	int key = 0;
	while(key != 27 && key != 'q')
	{

		// ��ȡFrame��Ϣ
		nite::Status rc = mHandTracker->readFrame(&mHandFrame);
		if (rc != nite::STATUS_OK)
		{
			cout << "GetNextData failed" << endl;
			return 0;
		}

		// ���������ת����OpenCV��ʽ
		const cv::Mat depthRaw( mHandFrame.getDepthFrame().getHeight(), mHandFrame.getDepthFrame().getWidth(), CV_16UC1, 
			(void*)mHandFrame.getDepthFrame().getData());
		/*memcpy(depthRaw.data, mHandFrame.getDepthFrame().getData(), XRES*YRES*2);*/
		depthRaw.convertTo(depthShow, CV_8U, DEPTH_SCALE_FACTOR);

		// ��ȡ��λ���ֵĿ�����Ϣ����ȡ��ʱһ���ж��ٸ�����
		const nite::Array<nite::GestureData>& gestures = mHandFrame.getGestures();
		for (int i = 0; i < gestures.getSize(); ++i)
		{
			// ����ȡ����������ȷ�����
			if (gestures[i].isComplete())
			{
				// �Ϳ�ʼ��λ��ʱ���Ƶ�����
				const nite::Point3f& position = gestures[i].getCurrentPosition();
				cout << "Gesture " << gestures[i].getType() << " at" << position.x << "," << position.y <<"," << position.z;

				// nite::HandId newId ===>typedef short int HandId;
				nite::HandId newId;
				// ��ʼ���ٸ���Ч���Ƶ��������꣬��ȷ�����ֵ�Id��
				// ����ԭ��Ϊ��NITE_API NiteStatus niteStartHandTracking(NiteHandTrackerHandle, const NitePoint3f*, NiteHandId* pNewHandId);
				mHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
			}
		}

		// ��ȡ��λ�֡�
		const nite::Array<nite::HandData>& hands= mHandFrame.getHands();
		for (int i = 0; i < hands.getSize(); ++i)
		{
			const nite::HandData& user = hands[i];

			if (!user.isTracking())
			{
				cout << "Lost hand %d\n" << user.getId();
				nite::HandId id = user.getId();
			}
			else
			{
				if (user.isNew())
				{
					cout << "Found hand %d\n" << user.getId();
				}
				else
				{

					float x, y;

					// ����������ת��ӳ�䵽���������
					mHandTracker->convertHandCoordinatesToDepth(hands[i].getPosition().x, hands[i].getPosition().y,
						hands[i].getPosition().z, &x, &y);
					float handDepth = hands[i].getPosition().z * DEPTH_SCALE_FACTOR;
					roi.x = x - ROI_OFFSET;
					roi.y = y - ROI_OFFSET;
					// �����ͼ������ȡ�ֵ�����ͼ��
					Mat handCpy(depthShow, roi);
					Mat handMat = handCpy.clone();
					// binary threshold
					handMat = (handMat > (handDepth - BIN_THRESH_OFFSET)) & (handMat < (handDepth + BIN_THRESH_OFFSET));

					// ƽ������
					medianBlur(handMat, handMat, MEDIAN_BLUR_K);

					// create debug image of thresholded hand and cvt to RGB so hints show in color
					handDebug = handMat.clone();
					cvtColor(handDebug, handDebug, CV_GRAY2RGB);

					// ��ȡ�ֵ�����
					std::vector< std::vector<Point> > contours;
					findContours(handMat, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

					if (contours.size()) {
						for (int i = 0; i < contours.size(); i++) {
							vector<Point> contour = contours[i];
							Mat contourMat = Mat(contour);
							double cArea = contourArea(contourMat);

							if(cArea > 2000) 
							{
								// ����õ�������������
								Scalar center = mean(contourMat);
								Point centerPoint = Point(center.val[0], center.val[1]);

								// ͨ��������˹-�տ��㷨�õ�һ�������ߣ����Ƶ�������
								vector<Point> approxCurve;
								approxPolyDP(contourMat, approxCurve, 10, true);

								// ��������
								vector< vector<Point> > debugContourV;
								debugContourV.push_back(approxCurve);
								drawContours(handDebug, debugContourV, 0, COLOR_DARK_GREEN, 3);

								// �����������͹����
								vector<int> hull;
								convexHull(Mat(approxCurve), hull, false, false);

								// ����͹����
								for(int j = 0; j < hull.size(); j++)
								{
									int index = hull[j];
									circle(handDebug, approxCurve[index], 3, COLOR_YELLOW, 2);
								}

								// ����͹ȱ��
								vector<ConvexityDefect> convexDefects;
								findConvexityDefects(approxCurve, hull, convexDefects);

								for(int j = 0; j < convexDefects.size(); j++)
								{
									circle(handDebug, convexDefects[j].depth_point, 3, COLOR_BLUE, 2);

								}

								// ����������͹����ȱ�ݵȵ�����ȷ��ָ��ȵ����꣬������
								vector<Point> hullPoints;
								for(int k = 0; k < hull.size(); k++)
								{
									int curveIndex = hull[k];
									Point p = approxCurve[curveIndex];
									hullPoints.push_back(p);
								}

								double hullArea  = contourArea(Mat(hullPoints));
								double curveArea = contourArea(Mat(approxCurve));
								double handRatio = curveArea/hullArea;

								if(handRatio > GRASPING_THRESH)
									circle(handDebug, centerPoint, 5, COLOR_LIGHT_GREEN, 5);
								else
									circle(handDebug, centerPoint, 5, COLOR_RED, 5);

								// ��ʾ���
								imshow("hand", handDebug);
							}
						} 
					}
				}
			}
		}

		imshow("depthFrame", depthShow);
		key = waitKey(10);
	}

	// �ر�Frame
	mHandFrame.release();

	// �رո�����
	mHandTracker->destroy();

	// �ر�NITE����
	nite::NiTE::shutdown();

	return 0;
}