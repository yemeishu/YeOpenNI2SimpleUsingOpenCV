// YeNite2SimpleUsingOpenCV.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

	// OpenCV ͷ�ļ�
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <OpenNI.h>
#include <NiTE.h>

using namespace std;
using namespace openni;
using namespace nite;

//int main( int argc, char **argv )
//{
//	// ��ʼ��OpenNI
//	OpenNI::initialize();
//
//	// ��Kinect�豸
//	Device  mDevice;
//	mDevice.open( ANY_DEVICE );
//
//	// �������������
//	VideoStream mDepthStream;
//	mDepthStream.create( mDevice, SENSOR_DEPTH );
//
//	// ����VideoModeģʽ
//	VideoMode mDepthMode;
//	mDepthMode.setResolution( 640, 480 );
//	mDepthMode.setFps( 30 );
//	mDepthMode.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
//	mDepthStream.setVideoMode(mDepthMode);
//
//	// ͬ�������ò�ɫ������
//	VideoStream mColorStream;
//	mColorStream.create( mDevice, SENSOR_COLOR );
//	// ����VideoModeģʽ
//	VideoMode mColorMode;
//	mColorMode.setResolution( 640, 480 );
//	mColorMode.setFps( 30 );
//	mColorMode.setPixelFormat( PIXEL_FORMAT_RGB888 );
//	mColorStream.setVideoMode( mColorMode);
//
//	// �������ͼ��ӳ�䵽��ɫͼ��
//	mDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );
//
//	// Ϊ�˵õ��������ݣ��ȳ�ʼ��NiTE
//	NiTE::initialize();
//
//	// ����HandTracker������
//	HandTracker mHandTracker;
//	mHandTracker.create(&mDevice);
//
//	// �趨����̽�⣨GESTURE_WAVE��GESTURE_CLICK��GESTURE_HAND_RAISE��
//	mHandTracker.startGestureDetection( GESTURE_WAVE );
//	mHandTracker.startGestureDetection( GESTURE_CLICK );
//	//mHandTracker.startGestureDetection( GESTURE_HAND_RAISE );
//
//	mHandTracker.setSmoothingFactor(0.1f);
//
//	// �������ͼ����ʾ
//	cv::namedWindow("Depth Image", CV_WINDOW_AUTOSIZE);
//
//	// ������ɫͼ����ʾ
//	cv::namedWindow( "Hand Image",  CV_WINDOW_AUTOSIZE );
//
//	// ������ʼ���󣬿�ʼ��ȡ����������Ͳ�ɫ������
//	mDepthStream.start();
//	mColorStream.start();
//
//	// ���������ֵ
//	int iMaxDepth = mDepthStream.getMaxPixelValue();
//
//	while( true )
//	{
//		// ����OpenCV����Mat��������ʾ��ɫ����ͼ��
//		cv::Mat cImageBGR;
//
//		// ��ȡ�������֡��Ϣ��
//		VideoFrameRef mDepthFrame;
//		mDepthStream.readFrame(&mDepthFrame);
//
//		// ��ȡ��ɫ����֡��Ϣ��
//		VideoFrameRef mColorFrame;
//		mColorStream.readFrame( &mColorFrame );
//
//
//		//���������ת����OpenCV��ʽ
//		const cv::Mat mImageDepth( mDepthFrame.getHeight(), mDepthFrame.getWidth(), CV_16UC1, (void*)mDepthFrame.getData());
//		// Ϊ�������ͼ����ʾ�ĸ�������һЩ����CV_16UC1 ==> CV_8U��ʽ
//		cv::Mat mScaledDepth;
//		mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );
//
//		// ����ɫ������ת��ΪOpenCV��ʽ���ǵø�ʽ�ǣ�CV_8UC3����R\G\B��
//		const cv::Mat mImageRGB( mColorFrame.getHeight(), mColorFrame.getWidth(),
//			CV_8UC3, (void*)mColorFrame.getData() );
//
//		// RGB ==> BGR
//		cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
//
//		// ��ȡ֡��Ϣ
//		HandTrackerFrameRef mHandFrame;
//		mHandTracker.readFrame( &mHandFrame );
//
//		// ��������֡��Ϣ���з������ҵ����ϵ�����
//		const nite::Array<GestureData>& aGestures = mHandFrame.getGestures();
//
//		for( int i = 0; i < aGestures.getSize(); ++ i )
//		{
//			const GestureData& rGesture = aGestures[i];
//
//			// �õ���������Ϣ�л������˵�ǰ���Ƶ�����λ��
//			const Point3f& rPos = rGesture.getCurrentPosition();
//			cout << " ����λ��Ϊ�� ��" << rPos.x << ", " << rPos.y << ", " << rPos.z << ")" << endl;
//
//			// �õ�����ʶ��󣬿�ʼ�ֲ�����
//			HandId mHandID;
//			mHandTracker.startHandTracking( rPos, &mHandID );
//			cout << "ȷ������λ�ã���ʼ�ֲ�����" << endl;
//
//		}
//
//		const nite::Array<HandData>& aHands = mHandFrame.getHands();
//		
//		for( int i = 0; i < aHands.getSize(); ++ i )
//		{
//			const HandData& rHand = aHands[i];
//			
//			if( rHand.isNew() )
//				cout << " Start tracking";
//			
//			else if( rHand.isLost() )
//				cout << " Lost";
//
//			// ȷ���ֲ��Ƿ����ڸ���״̬
//			if( rHand.isTracking() )
//			{
//				// �õ���������
//				const Point3f& rPos = rHand.getPosition();
//				cout << " at " << rPos.x << ", " << rPos.y << ", " << rPos.z;
//
//				cv::Point2f aPoint;
//				mHandTracker.convertHandCoordinatesToDepth(rPos.x, rPos.y, rPos.z, &aPoint.x, &aPoint.y);
//				// ����������ӳ�䵽��ɫͼ������ͼ����
//				cv::circle( cImageBGR, aPoint, 3, cv::Scalar( 0, 0, 255 ), 4 );
//				cv::circle( mScaledDepth, aPoint, 3, cv::Scalar(0, 0, 255), 4);
//
//				// �ڲ�ɫͼ���л����ֵ�������
//				cv::Point2f ctlPoint, ctrPoint, cdlPoint, cdrPoint;
//				ctlPoint.x = aPoint.x - 100;
//				ctlPoint.y = aPoint.y - 100;
//
//				ctrPoint.x = aPoint.x - 100;
//				ctrPoint.y = aPoint.y + 100;
//
//				cdlPoint.x = aPoint.x + 100;
//				cdlPoint.y = aPoint.y - 100;
//
//				cdrPoint.x = aPoint.x + 100;
//				cdrPoint.y = aPoint.y + 100;
//
//				cv::line( cImageBGR, ctlPoint, ctrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( cImageBGR, ctlPoint, cdlPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( cImageBGR, cdlPoint, cdrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( cImageBGR, ctrPoint, cdrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//
//				// �����ͼ���л����ֵ�������
//				cv::Point2f mtlPoint, mtrPoint, mdlPoint, mdrPoint;
//				mtlPoint.x = aPoint.x - 100;
//				mtlPoint.y = aPoint.y - 100;
//
//				mtrPoint.x = aPoint.x - 100;
//				mtrPoint.y = aPoint.y + 100;
//
//				mdlPoint.x = aPoint.x + 100;
//				mdlPoint.y = aPoint.y - 100;
//
//				mdrPoint.x = aPoint.x + 100;
//				mdrPoint.y = aPoint.y + 100;
//
//				cv::line( mScaledDepth, mtlPoint, mtrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( mScaledDepth, mtlPoint, mdlPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( mScaledDepth, mdlPoint, mdrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//				cv::line( mScaledDepth, mtrPoint, mdrPoint, cv::Scalar( 255, 0, 0 ), 3 );
//			}
//		}
//
//		// ��ʾͼ��
//		cv::imshow( "Depth Image", mScaledDepth );
//		cv::imshow( "Hand Image", cImageBGR );
//
//		// ������q���˳�ѭ��
//		if( cv::waitKey( 1 ) == 'q' )
//			break;
//	}
//
//	// �������ֲ�������
//	mHandTracker.destroy();
//
//	// ���ٲ�ɫ�����������������
//	mColorStream.destroy();
//	mDepthStream.destroy();
//
//	// �ر�Kinect�豸
//	mDevice.close();
//
//	// �ر�NITE��OpenNI����
//	NiTE::shutdown();
//	OpenNI::shutdown();
//
//	return 0;
//}
//#pragma region �ڲ�ɫͼ������ʾ��������ͼ��
int main( int argc, char **argv )
{
	// ��ʼ��OpenNI
	OpenNI::initialize();

	// ��Kinect�豸
	Device  mDevice;
	mDevice.open( ANY_DEVICE );

	// �������������
	VideoStream mDepthStream;
	mDepthStream.create( mDevice, SENSOR_DEPTH );

	// ����VideoModeģʽ
	VideoMode mDepthMode;
	mDepthMode.setResolution( 640, 480 );
	mDepthMode.setFps( 30 );
	mDepthMode.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
	mDepthStream.setVideoMode(mDepthMode);

	// ͬ�������ò�ɫ������
	VideoStream mColorStream;
	mColorStream.create( mDevice, SENSOR_COLOR );
	// ����VideoModeģʽ
	VideoMode mColorMode;
	mColorMode.setResolution( 640, 480 );
	mColorMode.setFps( 30 );
	mColorMode.setPixelFormat( PIXEL_FORMAT_RGB888 );
	mColorStream.setVideoMode( mColorMode);

	// �������ͼ��ӳ�䵽��ɫͼ��
	mDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );

	// Ϊ�˵õ��������ݣ��ȳ�ʼ��NiTE
	NiTE::initialize();

	// �����û�������
	UserTracker mUserTracker;
	mUserTracker.create( &mDevice );

	// Control the smoothing factor of the skeleton joints. Factor should be between 0 (no smoothing at all) and 1 (no movement at all)
	mUserTracker.setSkeletonSmoothingFactor( 0.1f );

	// ����User��ɫͼ����ʾ
	cv::namedWindow( "User Image",  CV_WINDOW_AUTOSIZE );

	// ������ʼ���󣬿�ʼ��ȡ����������Ͳ�ɫ������
	mDepthStream.start();
	mColorStream.start();

	while( true )
	{
		// ����OpenCV����Mat��������ʾ��ɫ����ͼ��
		cv::Mat cImageBGR;

		// ��ȡ�������֡��Ϣ��
		VideoFrameRef mColorFrame;
		mColorStream.readFrame( &mColorFrame );

		// ����ɫ������ת��ΪOpenCV��ʽ���ǵø�ʽ�ǣ�CV_8UC3����R\G\B��
		const cv::Mat mImageRGB( mColorFrame.getHeight(), mColorFrame.getWidth(),
			CV_8UC3, (void*)mColorFrame.getData() );

		// RGB ==> BGR
		cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );

		// ��ȡUser�û�����֡��Ϣ��
		UserTrackerFrameRef  mUserFrame;
		mUserTracker.readFrame( &mUserFrame );

		// �õ�Users��Ϣ
		const nite::Array<UserData>& aUsers = mUserFrame.getUsers();
		for( int i = 0; i < aUsers.getSize(); ++ i )
		{
			const UserData& rUser = aUsers[i];

			// ����û�״̬
			if( rUser.isNew() )
			{
				// ��ʼ�Ը��û��Ĺ�������
				mUserTracker.startSkeletonTracking( rUser.getId() );
			}

			if( rUser.isVisible() )
			{
				// �õ��û���������
				const Skeleton& rSkeleton = rUser.getSkeleton();

				// ������״̬�Ƿ�Ϊ������״̬��
				if( rSkeleton.getState() == SKELETON_TRACKED )
				{
					// �õ�15��������������
					SkeletonJoint aJoints[15];
					aJoints[ 0] = rSkeleton.getJoint( JOINT_HEAD );
					aJoints[ 1] = rSkeleton.getJoint( JOINT_NECK );
					aJoints[ 2] = rSkeleton.getJoint( JOINT_LEFT_SHOULDER );
					aJoints[ 3] = rSkeleton.getJoint( JOINT_RIGHT_SHOULDER );
					aJoints[ 4] = rSkeleton.getJoint( JOINT_LEFT_ELBOW );
					aJoints[ 5] = rSkeleton.getJoint( JOINT_RIGHT_ELBOW );
					aJoints[ 6] = rSkeleton.getJoint( JOINT_LEFT_HAND );
					aJoints[ 7] = rSkeleton.getJoint( JOINT_RIGHT_HAND );
					aJoints[ 8] = rSkeleton.getJoint( JOINT_TORSO );
					aJoints[ 9] = rSkeleton.getJoint( JOINT_LEFT_HIP );
					aJoints[10] = rSkeleton.getJoint( JOINT_RIGHT_HIP );
					aJoints[11] = rSkeleton.getJoint( JOINT_LEFT_KNEE );
					aJoints[12] = rSkeleton.getJoint( JOINT_RIGHT_KNEE );
					aJoints[13] = rSkeleton.getJoint( JOINT_LEFT_FOOT );
					aJoints[14] = rSkeleton.getJoint( JOINT_RIGHT_FOOT );

					// ����������ת��Ϊ��������¹���λ�ã���������������
					cv::Point2f aPoint[15];
					for( int  s = 0; s < 15; ++ s )
					{
						const Point3f& rPos = aJoints[s].getPosition();
						mUserTracker.convertJointCoordinatesToDepth( 
							rPos.x, rPos.y, rPos.z,
							&(aPoint[s].x), &(aPoint[s].y) );
					}

					// �ڲ�ɫͼ���л����������������
					cv::line( cImageBGR, aPoint[ 0], aPoint[ 1], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 1], aPoint[ 2], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 1], aPoint[ 3], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 2], aPoint[ 4], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 3], aPoint[ 5], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 4], aPoint[ 6], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 5], aPoint[ 7], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 1], aPoint[ 8], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 8], aPoint[ 9], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 8], aPoint[10], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[ 9], aPoint[11], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[10], aPoint[12], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[11], aPoint[13], cv::Scalar( 255, 0, 0 ), 3 );
					cv::line( cImageBGR, aPoint[12], aPoint[14], cv::Scalar( 255, 0, 0 ), 3 );

					// ͬ�����ڲ�ɫͼ���й���λ���ϻ���Բ��
					for( int  s = 0; s < 15; ++ s )
					{
						if( aJoints[s].getPositionConfidence() > 0.5 )
							cv::circle( cImageBGR, aPoint[s], 3, cv::Scalar( 0, 0, 255 ), 2 );
						else
							cv::circle( cImageBGR, aPoint[s], 3, cv::Scalar( 0, 255, 0 ), 2 );
					}
				}
			}
		}

		// ��ʾͼ��
		cv::imshow( "User Image", cImageBGR );

		// ������q���˳�ѭ��
		if( cv::waitKey( 1 ) == 'q' )
			break;
	}

	// ������User������
	mUserTracker.destroy();

	// ���ٲ�ɫ�����������������
	mColorStream.destroy();
	mDepthStream.destroy();

	// �ر�Kinect�豸
	mDevice.close();

	// �ر�NITE��OpenNI����
	NiTE::shutdown();
	OpenNI::shutdown();

	return 0;
}
#pragma endregion �ڲ�ɫͼ������ʾ��������ͼ��


	#pragma region �򵥵������������

/// ��ʼ��NITE
	//nite::NiTE::initialize();

	//// ����User������
	//nite::UserTracker* mUserTracker = new nite::UserTracker;
	//mUserTracker->create();

	//// ����OpenCVͼ�񴰿�
	//namedWindow( "Skeleton Image",  CV_WINDOW_AUTOSIZE );

	//// ѭ����ȡ��������Ϣ��������HandFrameRef��
	//nite::UserTrackerFrameRef mUserFrame;

	//while( true )
	//{
	//	// ��ȡFrame��Ϣ
	//	nite::Status rc = mUserTracker->readFrame(&mUserFrame);
	//	if (rc != nite::STATUS_OK)
	//	{
	//		cout << "GetNextData failed" << endl;
	//		return 0;
	//	}

	//	// ���������ת����OpenCV��ʽ
	//	const cv::Mat mHandDepth( mUserFrame.getDepthFrame().getHeight(), mUserFrame.getDepthFrame().getWidth(), CV_16UC1, 
	//		(void*)mUserFrame.getDepthFrame().getData());

	//	// Ϊ�������ͼ����ʾ�ĸ�������һЩ����CV_16UC1 ==> CV_8U��ʽ
	//	cv::Mat mScaledHandDepth, thresholdDepth;
	//	mHandDepth.convertTo( mScaledHandDepth, CV_8U, 255.0 / 10000 );

	//	// ��ֵ������Ϊ����ʾЧ������
	//	cv::threshold(mScaledHandDepth, thresholdDepth, 50, 255, 0);

	//	// ��User Frame��Ϣ�л�ȡUser��Ϣ
	//	const nite::Array<nite::UserData>& aUsers = mUserFrame.getUsers();

	//	// Frame��User�ĸ���
	//	for( int i = 0; i < aUsers.getSize(); ++ i )
	//	{
	//		const nite::UserData& rUser = aUsers[i];

	//		// ����User�û�������Kinect��ǰ�����жϲ���ʾ
	//		if( rUser.isNew() )
	//		{
	//			cout << "New User [" << rUser.getId() << "] found." << endl;

	//			// ��ʼ�����������
	//			mUserTracker->startSkeletonTracking( rUser.getId() );
	//		}

	//		// ��ȡ��������
	//		const nite::Skeleton& rSkeleton = rUser.getSkeleton();
	//		if( rSkeleton.getState() == nite::SKELETON_TRACKED )
	//		{
	//			// ֻ�õ�ǰ8������������
	//			for(int i = 0; i < 8; i++)
	//			{
	//				// �õ���������
	//				const nite::SkeletonJoint& skeletonJoint
	//					= rSkeleton.getJoint((nite::JointType)i);
	//				const nite::Point3f& position = skeletonJoint.getPosition();

	//				float depth_x, depth_y;

	//				// ������������ӳ�䵽���������
	//				mUserTracker->convertJointCoordinatesToDepth(position.x, position.y, position.z, &depth_x, &depth_y);

	//				cv::Point point((int)depth_x, (int)depth_y);

	//				// ����ȡ�����ͼ�������Ӧ����������¸�ֵΪ255.�������ͼ������ʾ�����������㡣
	//				thresholdDepth.at<uchar>(point) = 255;
	//			}
	//			
	//			// ��ʾͼ��
	//			cv::imshow( "Skeleton Image", thresholdDepth );
	//		}

	//	}
	//	
	//	// ��ֹ��ݼ�
	//	if( cv::waitKey(1) == 'q')
	//		break;
	//}

	//// �ر�Frame
	//mUserFrame.release();

	//// �رո�����
	//mUserTracker->destroy();

	//// �ر�NITE����
	//nite::NiTE::shutdown();

	//return 0;		
	#pragma endregion �򵥵������������