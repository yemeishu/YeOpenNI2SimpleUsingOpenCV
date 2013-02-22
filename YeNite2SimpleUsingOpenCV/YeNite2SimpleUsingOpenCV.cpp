// YeNite2SimpleUsingOpenCV.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

// ����NiTEͷ�ļ�
#include <NiTE.h>

// using namespace
using namespace std;
using namespace nite;

int main( int argc, char** argv )
{
	// ��ʼ��NiTE����
	NiTE::initialize();

	// ����HandTracker������
	HandTracker mHandTracker;
	mHandTracker.create();

	// �趨����̽�⣨GESTURE_WAVE��GESTURE_CLICK��GESTURE_HAND_RAISE��
	mHandTracker.startGestureDetection( GESTURE_WAVE );
	mHandTracker.startGestureDetection( GESTURE_CLICK );
	//mHandTracker.startGestureDetection( GESTURE_HAND_RAISE );

	while(true)
	{
		// ��ȡ֡��Ϣ
		HandTrackerFrameRef mHandFrame;
		mHandTracker.readFrame( &mHandFrame );

		// ��������֡��Ϣ���з������ҵ����ϵ�����
		const Array<GestureData>& aGestures = mHandFrame.getGestures();

		for( int i = 0; i < aGestures.getSize(); ++ i )
		{
			const GestureData& rGesture = aGestures[i];

			// ���ҵ������ƽ��������жϣ����������
			cout << "Detect gesture ";
			switch( rGesture.getType() )
			{
			case GESTURE_WAVE:
				cout << "ҡ������---��wave����";
				break;

			case GESTURE_CLICK:
				cout << "ǰ�Ʋ��ջ�����---��click��";
				break;

			case GESTURE_HAND_RAISE:
				cout << "��������---��hand raise��";
				break;
			}

			// �õ���������Ϣ�л������˵�ǰ���Ƶ�����λ��
			const Point3f& rPos = rGesture.getCurrentPosition();
			cout << " ����λ��Ϊ�� ��" << rPos.x << ", " << rPos.y << ", " << rPos.z << ")" << endl;

			// �Լ�����״̬�����״̬�ͽ���״̬
			if( rGesture.isComplete() )
				cout << "  �������";
			if( rGesture.isInProgress() )
				cout << "  �������ڽ���";

			cout << endl;
		}
	}

	// �ر�HandTracker����
	mHandTracker.destroy();

	// �ر�NITE����
	NiTE::shutdown();

	return 0;
}

#pragma region ����̽���ʶ��
// ����NiTEͷ�ļ�
//#include <NiTE.h>
//
//// using namespace
//using namespace std;
//using namespace nite;
//
//int main( int argc, char** argv )
//{
//	// ��ʼ��NiTE����
//	NiTE::initialize();
//
//	// ����UserTracker������
//	UserTracker mUserTracker;
//	mUserTracker.create();
//
//	while(true)
//	{
//		// ��ȡ֡��Ϣ
//		UserTrackerFrameRef mUserFrame;
//		mUserTracker.readFrame( &mUserFrame);
//
//		// ͨ��֡��Ϣ������û�����UserData
//		const Array<UserData>& aUsers = mUserFrame.getUsers();
//
//		for( int i = 0; i < aUsers.getSize(); ++ i )
//		{
//			const UserData& rUser = aUsers[i];
//			const UserId& uID = rUser.getId();
//
//			if( rUser.isNew() )
//			{
//				cout << "User " << uID << " found." << endl;
//
//				// Ϊÿһ�����û���������̽��
//				cout << "Start pose detection " << uID<< endl;
//
//				// ̽��uID����������
//				mUserTracker.startPoseDetection( uID, POSE_PSI );
//				mUserTracker.startPoseDetection( uID, POSE_CROSSED_HANDS );
//			}
//			else if( rUser.isLost() )
//			{
//				cout << "User " << uID << " lost." << endl;
//			}
//			else
//			{
//				// ��ȡ�û��ġ�POSI_PSI��������״̬
//				const PoseData& rPosePSI = rUser.getPose( POSE_PSI );
//
//				// �����ˡ�POSI_PSI��ʱ��
//				if( rPosePSI.isEntered() )
//					cout << " ��ʼ---Ͷ������(PSI pose)" << endl;
//
//				if( rPosePSI.isHeld() )
//					cout << " ����---Ͷ������(PSI pose)" << endl;
//
//				// �������ˡ�POSI_PSI����˫�ַ���ʱ��
//				if( rPosePSI.isExited() )
//					cout << "ֹͣ---Ͷ������(PSI pose)" << endl;
//
//				// ͬ���Ķ�ȡ��POSE_CROSSED_HANDS��������״̬
//				const PoseData& rPCH = rUser.getPose( POSE_CROSSED_HANDS );
//
//				if( rPCH.isEntered() )
//					cout << " ��ʼ---˫�ֱ���(Cross Hand pose)" << endl;
//
//				if( rPCH.isHeld() )
//					cout << " ����---˫�ֱ���(Cross Hand pose)" << endl;
//
//				if( rPCH.isExited() )
//					cout << " ֹͣ---˫�ֱ���(Cross Hand pose)" << endl;
//			}
//		}
//	}
//
//	// �ر�UserTracker����
//	mUserTracker.destroy();
//
//	// �ر�NITE����
//	NiTE::shutdown();
//
//	return 0;
//}
#pragma endregion ����̽���ʶ��

#pragma region ����OpenCV���м򵥵�NIteʶ��
//// ����NiTE.hͷ�ļ�
//#include <NiTE.h>
//
//// ����OpenCVͷ�ļ�
//#include "opencv2/opencv.hpp"
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//
//using namespace std;
//using namespace cv;
//
//int main( int argc, char** argv )
//{
//
//	// ��ʼ��NITE
//	nite::NiTE::initialize();
//
//	// ����Hand������
//	nite::HandTracker* mHandTracker = new nite::HandTracker;
//	mHandTracker->create();
//
//	// ����OpenCVͼ�񴰿�
//	namedWindow( "Hand Image",  CV_WINDOW_AUTOSIZE );
//
//	// ѭ����ȡ��������Ϣ��������HandFrameRef��
//	nite::HandTrackerFrameRef mHandFrame;
//
//	// ��ʼ����̽��
//	mHandTracker->startGestureDetection(nite::GESTURE_CLICK);
//	mHandTracker->startGestureDetection(nite::GESTURE_WAVE);
//	mHandTracker->startGestureDetection(nite::GESTURE_HAND_RAISE);
//
//	while( true )
//	{
//		// ��ȡFrame��Ϣ
//		nite::Status rc = mHandTracker->readFrame(&mHandFrame);
//		if (rc != nite::STATUS_OK)
//		{
//			cout << "GetNextData failed" << endl;
//			return 0;
//		}
//
//		// ��ȡ��λ���ֵĿ�����Ϣ����ȡ��ʱһ���ж��ٸ�����
//		const nite::Array<nite::GestureData>& gestures = mHandFrame.getGestures();
//		for (int i = 0; i < gestures.getSize(); ++i)
//		{
//			// ����ȡ����������ȷ�����
//			if (gestures[i].isComplete())
//			{
//				// �Ϳ�ʼ��λ��ʱ���Ƶ�����
//				const nite::Point3f& position = gestures[i].getCurrentPosition();
//				cout << "Gesture " << gestures[i].getType() << " at" << position.x << "," << position.y <<"," << position.z;
//
//				// nite::HandId newId ===>typedef short int HandId;
//				nite::HandId newId;
//				// ��ʼ���ٸ���Ч���Ƶ��������꣬��ȷ�����ֵ�Id��
//				// ����ԭ��Ϊ��NITE_API NiteStatus niteStartHandTracking(NiteHandTrackerHandle, const NitePoint3f*, NiteHandId* pNewHandId);
//				mHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
//			}
//		}
//
//		// ��ȡ��λ�֡�
//		const nite::Array<nite::HandData>& hands= mHandFrame.getHands();
//		for (int i = 0; i < hands.getSize(); ++i)
//		{
//			const nite::HandData& user = hands[i];
//
//			if (!user.isTracking())
//			{
//				cout << "Lost hand %d\n" << user.getId();
//				nite::HandId id = user.getId();
//			}
//			else
//			{
//				if (user.isNew())
//				{
//					cout << "Found hand %d\n" << user.getId();
//				}
//				else
//				{
//					cout << "Hand ID:" << hands[i].getId()
//						<<hands[i].getPosition().x << "," 
//						<< hands[i].getPosition().y << ","
//						<< hands[i].getPosition().z << endl;
//					float x, y;
//
//					// ����������ת��ӳ�䵽���������
//					mHandTracker->convertHandCoordinatesToDepth(hands[i].getPosition().x, hands[i].getPosition().y,
//						hands[i].getPosition().z, &x, &y);
//
//					// ���������ת����OpenCV��ʽ
//					const cv::Mat mHandDepth( mHandFrame.getDepthFrame().getHeight(), mHandFrame.getDepthFrame().getWidth(), CV_16UC1, 
//						(void*)mHandFrame.getDepthFrame().getData());
//
//					// Ϊ�������ͼ����ʾ�ĸ�������һЩ����CV_16UC1 ==> CV_8U��ʽ
//					cv::Mat mScaledHandDepth;
//					mHandDepth.convertTo( mScaledHandDepth, CV_8U, 255.0 / 10000 );
//
//					// ��ȡ������Ϊ���ģ�200*200��С��ͼ��
//					cv::Mat mHandsizeDepth = mScaledHandDepth(Rect(x - 100, y -100 , 200, 200));
//
//					// ��ʾ�ֵ�ͼ��
//					cv::imshow( "Hand Image", mHandsizeDepth );
//				}
//			}
//
//		}
//		// ��ֹ��ݼ�
//		if( cv::waitKey(1) == 'q')
//			break;
//	}
//
//	// �ر�Frame
//	mHandFrame.release();
//
//	// �رո�����
//	mHandTracker->destroy();
//
//	// �ر�NITE����
//	nite::NiTE::shutdown();
//
//	return 0;		
//}
#pragma endregion ����OpenCV���м򵥵�NIteʶ��

