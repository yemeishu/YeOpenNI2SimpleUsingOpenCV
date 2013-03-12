// YeNite2SimpleUsingOpenCV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

	// OpenCV 头文件
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
//	// 初始化OpenNI
//	OpenNI::initialize();
//
//	// 打开Kinect设备
//	Device  mDevice;
//	mDevice.open( ANY_DEVICE );
//
//	// 创建深度数据流
//	VideoStream mDepthStream;
//	mDepthStream.create( mDevice, SENSOR_DEPTH );
//
//	// 设置VideoMode模式
//	VideoMode mDepthMode;
//	mDepthMode.setResolution( 640, 480 );
//	mDepthMode.setFps( 30 );
//	mDepthMode.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
//	mDepthStream.setVideoMode(mDepthMode);
//
//	// 同样的设置彩色数据流
//	VideoStream mColorStream;
//	mColorStream.create( mDevice, SENSOR_COLOR );
//	// 设置VideoMode模式
//	VideoMode mColorMode;
//	mColorMode.setResolution( 640, 480 );
//	mColorMode.setFps( 30 );
//	mColorMode.setPixelFormat( PIXEL_FORMAT_RGB888 );
//	mColorStream.setVideoMode( mColorMode);
//
//	// 设置深度图像映射到彩色图像
//	mDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );
//
//	// 为了得到骨骼数据，先初始化NiTE
//	NiTE::initialize();
//
//	// 创建HandTracker跟踪器
//	HandTracker mHandTracker;
//	mHandTracker.create(&mDevice);
//
//	// 设定手势探测（GESTURE_WAVE、GESTURE_CLICK和GESTURE_HAND_RAISE）
//	mHandTracker.startGestureDetection( GESTURE_WAVE );
//	mHandTracker.startGestureDetection( GESTURE_CLICK );
//	//mHandTracker.startGestureDetection( GESTURE_HAND_RAISE );
//
//	mHandTracker.setSmoothingFactor(0.1f);
//
//	// 创建深度图像显示
//	cv::namedWindow("Depth Image", CV_WINDOW_AUTOSIZE);
//
//	// 创建彩色图像显示
//	cv::namedWindow( "Hand Image",  CV_WINDOW_AUTOSIZE );
//
//	// 环境初始化后，开始获取深度数据流和彩色数据流
//	mDepthStream.start();
//	mColorStream.start();
//
//	// 获得最大深度值
//	int iMaxDepth = mDepthStream.getMaxPixelValue();
//
//	while( true )
//	{
//		// 创建OpenCV：：Mat，用于显示彩色数据图像
//		cv::Mat cImageBGR;
//
//		// 读取深度数据帧信息流
//		VideoFrameRef mDepthFrame;
//		mDepthStream.readFrame(&mDepthFrame);
//
//		// 读取彩色数据帧信息流
//		VideoFrameRef mColorFrame;
//		mColorStream.readFrame( &mColorFrame );
//
//
//		//将深度数据转换成OpenCV格式
//		const cv::Mat mImageDepth( mDepthFrame.getHeight(), mDepthFrame.getWidth(), CV_16UC1, (void*)mDepthFrame.getData());
//		// 为了让深度图像显示的更加明显一些，将CV_16UC1 ==> CV_8U格式
//		cv::Mat mScaledDepth;
//		mImageDepth.convertTo( mScaledDepth, CV_8U, 255.0 / iMaxDepth );
//
//		// 将彩色数据流转换为OpenCV格式，记得格式是：CV_8UC3（含R\G\B）
//		const cv::Mat mImageRGB( mColorFrame.getHeight(), mColorFrame.getWidth(),
//			CV_8UC3, (void*)mColorFrame.getData() );
//
//		// RGB ==> BGR
//		cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );
//
//		// 读取帧信息
//		HandTrackerFrameRef mHandFrame;
//		mHandTracker.readFrame( &mHandFrame );
//
//		// 整个界面帧信息进行分析，找到符合的手势
//		const nite::Array<GestureData>& aGestures = mHandFrame.getGestures();
//
//		for( int i = 0; i < aGestures.getSize(); ++ i )
//		{
//			const GestureData& rGesture = aGestures[i];
//
//			// 得到的手势信息中还包含了当前手势的坐标位置
//			const Point3f& rPos = rGesture.getCurrentPosition();
//			cout << " 手势位置为： （" << rPos.x << ", " << rPos.y << ", " << rPos.z << ")" << endl;
//
//			// 得到手势识别后，开始手部跟踪
//			HandId mHandID;
//			mHandTracker.startHandTracking( rPos, &mHandID );
//			cout << "确定手势位置，开始手部跟踪" << endl;
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
//			// 确定手部是否属于跟踪状态
//			if( rHand.isTracking() )
//			{
//				// 得到手心坐标
//				const Point3f& rPos = rHand.getPosition();
//				cout << " at " << rPos.x << ", " << rPos.y << ", " << rPos.z;
//
//				cv::Point2f aPoint;
//				mHandTracker.convertHandCoordinatesToDepth(rPos.x, rPos.y, rPos.z, &aPoint.x, &aPoint.y);
//				// 将手心坐标映射到彩色图像和深度图像中
//				cv::circle( cImageBGR, aPoint, 3, cv::Scalar( 0, 0, 255 ), 4 );
//				cv::circle( mScaledDepth, aPoint, 3, cv::Scalar(0, 0, 255), 4);
//
//				// 在彩色图像中画出手的轮廓边
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
//				// 在深度图像中画出手的轮廓边
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
//		// 显示图像
//		cv::imshow( "Depth Image", mScaledDepth );
//		cv::imshow( "Hand Image", cImageBGR );
//
//		// 按键“q”退出循环
//		if( cv::waitKey( 1 ) == 'q' )
//			break;
//	}
//
//	// 先销毁手部跟踪器
//	mHandTracker.destroy();
//
//	// 销毁彩色数据流和深度数据流
//	mColorStream.destroy();
//	mDepthStream.destroy();
//
//	// 关闭Kinect设备
//	mDevice.close();
//
//	// 关闭NITE和OpenNI环境
//	NiTE::shutdown();
//	OpenNI::shutdown();
//
//	return 0;
//}
//#pragma region 在彩色图像中显示骨骼坐标图像
int main( int argc, char **argv )
{
	// 初始化OpenNI
	OpenNI::initialize();

	// 打开Kinect设备
	Device  mDevice;
	mDevice.open( ANY_DEVICE );

	// 创建深度数据流
	VideoStream mDepthStream;
	mDepthStream.create( mDevice, SENSOR_DEPTH );

	// 设置VideoMode模式
	VideoMode mDepthMode;
	mDepthMode.setResolution( 640, 480 );
	mDepthMode.setFps( 30 );
	mDepthMode.setPixelFormat( PIXEL_FORMAT_DEPTH_1_MM );
	mDepthStream.setVideoMode(mDepthMode);

	// 同样的设置彩色数据流
	VideoStream mColorStream;
	mColorStream.create( mDevice, SENSOR_COLOR );
	// 设置VideoMode模式
	VideoMode mColorMode;
	mColorMode.setResolution( 640, 480 );
	mColorMode.setFps( 30 );
	mColorMode.setPixelFormat( PIXEL_FORMAT_RGB888 );
	mColorStream.setVideoMode( mColorMode);

	// 设置深度图像映射到彩色图像
	mDevice.setImageRegistrationMode( IMAGE_REGISTRATION_DEPTH_TO_COLOR );

	// 为了得到骨骼数据，先初始化NiTE
	NiTE::initialize();

	// 创建用户跟踪器
	UserTracker mUserTracker;
	mUserTracker.create( &mDevice );

	// Control the smoothing factor of the skeleton joints. Factor should be between 0 (no smoothing at all) and 1 (no movement at all)
	mUserTracker.setSkeletonSmoothingFactor( 0.1f );

	// 创建User彩色图像显示
	cv::namedWindow( "User Image",  CV_WINDOW_AUTOSIZE );

	// 环境初始化后，开始获取深度数据流和彩色数据流
	mDepthStream.start();
	mColorStream.start();

	while( true )
	{
		// 创建OpenCV：：Mat，用于显示彩色数据图像
		cv::Mat cImageBGR;

		// 读取深度数据帧信息流
		VideoFrameRef mColorFrame;
		mColorStream.readFrame( &mColorFrame );

		// 将彩色数据流转换为OpenCV格式，记得格式是：CV_8UC3（含R\G\B）
		const cv::Mat mImageRGB( mColorFrame.getHeight(), mColorFrame.getWidth(),
			CV_8UC3, (void*)mColorFrame.getData() );

		// RGB ==> BGR
		cv::cvtColor( mImageRGB, cImageBGR, CV_RGB2BGR );

		// 读取User用户数据帧信息流
		UserTrackerFrameRef  mUserFrame;
		mUserTracker.readFrame( &mUserFrame );

		// 得到Users信息
		const nite::Array<UserData>& aUsers = mUserFrame.getUsers();
		for( int i = 0; i < aUsers.getSize(); ++ i )
		{
			const UserData& rUser = aUsers[i];

			// 检查用户状态
			if( rUser.isNew() )
			{
				// 开始对该用户的骨骼跟踪
				mUserTracker.startSkeletonTracking( rUser.getId() );
			}

			if( rUser.isVisible() )
			{
				// 得到用户骨骼数据
				const Skeleton& rSkeleton = rUser.getSkeleton();

				// 检查骨骼状态是否为“跟踪状态”
				if( rSkeleton.getState() == SKELETON_TRACKED )
				{
					// 得到15个骨骼数据数字
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

					// 将骨骼坐标转换为深度坐标下骨骼位置，并保存在数组中
					cv::Point2f aPoint[15];
					for( int  s = 0; s < 15; ++ s )
					{
						const Point3f& rPos = aJoints[s].getPosition();
						mUserTracker.convertJointCoordinatesToDepth( 
							rPos.x, rPos.y, rPos.z,
							&(aPoint[s].x), &(aPoint[s].y) );
					}

					// 在彩色图像中画出骨骼间的连接线
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

					// 同样的在彩色图像中骨骼位置上画“圆”
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

		// 显示图像
		cv::imshow( "User Image", cImageBGR );

		// 按键“q”退出循环
		if( cv::waitKey( 1 ) == 'q' )
			break;
	}

	// 先销毁User跟踪器
	mUserTracker.destroy();

	// 销毁彩色数据流和深度数据流
	mColorStream.destroy();
	mDepthStream.destroy();

	// 关闭Kinect设备
	mDevice.close();

	// 关闭NITE和OpenNI环境
	NiTE::shutdown();
	OpenNI::shutdown();

	return 0;
}
#pragma endregion 在彩色图像中显示骨骼坐标图像


	#pragma region 简单的人体骨骼跟踪

/// 初始化NITE
	//nite::NiTE::initialize();

	//// 创建User跟踪器
	//nite::UserTracker* mUserTracker = new nite::UserTracker;
	//mUserTracker->create();

	//// 创建OpenCV图像窗口
	//namedWindow( "Skeleton Image",  CV_WINDOW_AUTOSIZE );

	//// 循环读取数据流信息并保存在HandFrameRef中
	//nite::UserTrackerFrameRef mUserFrame;

	//while( true )
	//{
	//	// 读取Frame信息
	//	nite::Status rc = mUserTracker->readFrame(&mUserFrame);
	//	if (rc != nite::STATUS_OK)
	//	{
	//		cout << "GetNextData failed" << endl;
	//		return 0;
	//	}

	//	// 将深度数据转换成OpenCV格式
	//	const cv::Mat mHandDepth( mUserFrame.getDepthFrame().getHeight(), mUserFrame.getDepthFrame().getWidth(), CV_16UC1, 
	//		(void*)mUserFrame.getDepthFrame().getData());

	//	// 为了让深度图像显示的更加明显一些，将CV_16UC1 ==> CV_8U格式
	//	cv::Mat mScaledHandDepth, thresholdDepth;
	//	mHandDepth.convertTo( mScaledHandDepth, CV_8U, 255.0 / 10000 );

	//	// 二值化处理，为了显示效果明显
	//	cv::threshold(mScaledHandDepth, thresholdDepth, 50, 255, 0);

	//	// 从User Frame信息中获取User信息
	//	const nite::Array<nite::UserData>& aUsers = mUserFrame.getUsers();

	//	// Frame中User的个数
	//	for( int i = 0; i < aUsers.getSize(); ++ i )
	//	{
	//		const nite::UserData& rUser = aUsers[i];

	//		// 当有User用户出现在Kinect面前，则判断并显示
	//		if( rUser.isNew() )
	//		{
	//			cout << "New User [" << rUser.getId() << "] found." << endl;

	//			// 开始人体骨骼跟踪
	//			mUserTracker->startSkeletonTracking( rUser.getId() );
	//		}

	//		// 获取骨骼坐标
	//		const nite::Skeleton& rSkeleton = rUser.getSkeleton();
	//		if( rSkeleton.getState() == nite::SKELETON_TRACKED )
	//		{
	//			// 只得到前8个骨骼点坐标
	//			for(int i = 0; i < 8; i++)
	//			{
	//				// 得到骨骼坐标
	//				const nite::SkeletonJoint& skeletonJoint
	//					= rSkeleton.getJoint((nite::JointType)i);
	//				const nite::Point3f& position = skeletonJoint.getPosition();

	//				float depth_x, depth_y;

	//				// 将骨骼点坐标映射到深度坐标中
	//				mUserTracker->convertJointCoordinatesToDepth(position.x, position.y, position.z, &depth_x, &depth_y);

	//				cv::Point point((int)depth_x, (int)depth_y);

	//				// 将获取的深度图像中相对应的坐标点重新赋值为255.即在深度图像中显示出各个骨骼点。
	//				thresholdDepth.at<uchar>(point) = 255;
	//			}
	//			
	//			// 显示图像
	//			cv::imshow( "Skeleton Image", thresholdDepth );
	//		}

	//	}
	//	
	//	// 终止快捷键
	//	if( cv::waitKey(1) == 'q')
	//		break;
	//}

	//// 关闭Frame
	//mUserFrame.release();

	//// 关闭跟踪器
	//mUserTracker->destroy();

	//// 关闭NITE环境
	//nite::NiTE::shutdown();

	//return 0;		
	#pragma endregion 简单的人体骨骼跟踪