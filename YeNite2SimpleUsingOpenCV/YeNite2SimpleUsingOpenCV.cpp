// YeNite2SimpleUsingOpenCV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

// 载入NiTE头文件
#include <NiTE.h>

// using namespace
using namespace std;
using namespace nite;

int main( int argc, char** argv )
{
	// 初始化NiTE环境
	NiTE::initialize();

	// 创建HandTracker跟踪器
	HandTracker mHandTracker;
	mHandTracker.create();

	// 设定手势探测（GESTURE_WAVE、GESTURE_CLICK和GESTURE_HAND_RAISE）
	mHandTracker.startGestureDetection( GESTURE_WAVE );
	mHandTracker.startGestureDetection( GESTURE_CLICK );
	//mHandTracker.startGestureDetection( GESTURE_HAND_RAISE );

	while(true)
	{
		// 读取帧信息
		HandTrackerFrameRef mHandFrame;
		mHandTracker.readFrame( &mHandFrame );

		// 整个界面帧信息进行分析，找到符合的手势
		const Array<GestureData>& aGestures = mHandFrame.getGestures();

		for( int i = 0; i < aGestures.getSize(); ++ i )
		{
			const GestureData& rGesture = aGestures[i];

			// 对找到的手势进行类型判断，并输出类型
			cout << "Detect gesture ";
			switch( rGesture.getType() )
			{
			case GESTURE_WAVE:
				cout << "摇手手势---“wave”：";
				break;

			case GESTURE_CLICK:
				cout << "前推并收回手势---“click”";
				break;

			case GESTURE_HAND_RAISE:
				cout << "举起手势---“hand raise”";
				break;
			}

			// 得到的手势信息中还包含了当前手势的坐标位置
			const Point3f& rPos = rGesture.getCurrentPosition();
			cout << " 手势位置为： （" << rPos.x << ", " << rPos.y << ", " << rPos.z << ")" << endl;

			// 以及手势状态，完成状态和进行状态
			if( rGesture.isComplete() )
				cout << "  手势完成";
			if( rGesture.isInProgress() )
				cout << "  手势正在进行";

			cout << endl;
		}
	}

	// 关闭HandTracker跟踪
	mHandTracker.destroy();

	// 关闭NITE环境
	NiTE::shutdown();

	return 0;
}

#pragma region 姿势探测和识别
// 载入NiTE头文件
//#include <NiTE.h>
//
//// using namespace
//using namespace std;
//using namespace nite;
//
//int main( int argc, char** argv )
//{
//	// 初始化NiTE环境
//	NiTE::initialize();
//
//	// 创建UserTracker跟踪器
//	UserTracker mUserTracker;
//	mUserTracker.create();
//
//	while(true)
//	{
//		// 读取帧信息
//		UserTrackerFrameRef mUserFrame;
//		mUserTracker.readFrame( &mUserFrame);
//
//		// 通过帧信息，获得用户数据UserData
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
//				// 为每一个新用户进行姿势探测
//				cout << "Start pose detection " << uID<< endl;
//
//				// 探测uID的两种姿势
//				mUserTracker.startPoseDetection( uID, POSE_PSI );
//				mUserTracker.startPoseDetection( uID, POSE_CROSSED_HANDS );
//			}
//			else if( rUser.isLost() )
//			{
//				cout << "User " << uID << " lost." << endl;
//			}
//			else
//			{
//				// 读取用户的“POSI_PSI”的姿势状态
//				const PoseData& rPosePSI = rUser.getPose( POSE_PSI );
//
//				// 当做了“POSI_PSI”时：
//				if( rPosePSI.isEntered() )
//					cout << " 开始---投降姿势(PSI pose)" << endl;
//
//				if( rPosePSI.isHeld() )
//					cout << " 保持---投降姿势(PSI pose)" << endl;
//
//				// 当做完了“POSI_PSI”后，双手放下时：
//				if( rPosePSI.isExited() )
//					cout << "停止---投降姿势(PSI pose)" << endl;
//
//				// 同样的读取“POSE_CROSSED_HANDS”的姿势状态
//				const PoseData& rPCH = rUser.getPose( POSE_CROSSED_HANDS );
//
//				if( rPCH.isEntered() )
//					cout << " 开始---双手抱胸(Cross Hand pose)" << endl;
//
//				if( rPCH.isHeld() )
//					cout << " 保持---双手抱胸(Cross Hand pose)" << endl;
//
//				if( rPCH.isExited() )
//					cout << " 停止---双手抱胸(Cross Hand pose)" << endl;
//			}
//		}
//	}
//
//	// 关闭UserTracker跟踪
//	mUserTracker.destroy();
//
//	// 关闭NITE环境
//	NiTE::shutdown();
//
//	return 0;
//}
#pragma endregion 姿势探测和识别

#pragma region 利用OpenCV进行简单的NIte识别
//// 载入NiTE.h头文件
//#include <NiTE.h>
//
//// 载入OpenCV头文件
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
//	// 初始化NITE
//	nite::NiTE::initialize();
//
//	// 创建Hand跟踪器
//	nite::HandTracker* mHandTracker = new nite::HandTracker;
//	mHandTracker->create();
//
//	// 创建OpenCV图像窗口
//	namedWindow( "Hand Image",  CV_WINDOW_AUTOSIZE );
//
//	// 循环读取数据流信息并保存在HandFrameRef中
//	nite::HandTrackerFrameRef mHandFrame;
//
//	// 开始手势探测
//	mHandTracker->startGestureDetection(nite::GESTURE_CLICK);
//	mHandTracker->startGestureDetection(nite::GESTURE_WAVE);
//	mHandTracker->startGestureDetection(nite::GESTURE_HAND_RAISE);
//
//	while( true )
//	{
//		// 读取Frame信息
//		nite::Status rc = mHandTracker->readFrame(&mHandFrame);
//		if (rc != nite::STATUS_OK)
//		{
//			cout << "GetNextData failed" << endl;
//			return 0;
//		}
//
//		// 获取定位的手的快照信息，读取此时一共有多少个手势
//		const nite::Array<nite::GestureData>& gestures = mHandFrame.getGestures();
//		for (int i = 0; i < gestures.getSize(); ++i)
//		{
//			// 当获取的手势是正确完成了
//			if (gestures[i].isComplete())
//			{
//				// 就开始定位此时手势的坐标
//				const nite::Point3f& position = gestures[i].getCurrentPosition();
//				cout << "Gesture " << gestures[i].getType() << " at" << position.x << "," << position.y <<"," << position.z;
//
//				// nite::HandId newId ===>typedef short int HandId;
//				nite::HandId newId;
//				// 开始跟踪该有效手势的手心坐标，并确定该手的Id。
//				// 函数原型为：NITE_API NiteStatus niteStartHandTracking(NiteHandTrackerHandle, const NitePoint3f*, NiteHandId* pNewHandId);
//				mHandTracker->startHandTracking(gestures[i].getCurrentPosition(), &newId);
//			}
//		}
//
//		// 获取定位手。
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
//					// 将手心坐标转换映射到深度坐标中
//					mHandTracker->convertHandCoordinatesToDepth(hands[i].getPosition().x, hands[i].getPosition().y,
//						hands[i].getPosition().z, &x, &y);
//
//					// 将深度数据转换成OpenCV格式
//					const cv::Mat mHandDepth( mHandFrame.getDepthFrame().getHeight(), mHandFrame.getDepthFrame().getWidth(), CV_16UC1, 
//						(void*)mHandFrame.getDepthFrame().getData());
//
//					// 为了让深度图像显示的更加明显一些，将CV_16UC1 ==> CV_8U格式
//					cv::Mat mScaledHandDepth;
//					mHandDepth.convertTo( mScaledHandDepth, CV_8U, 255.0 / 10000 );
//
//					// 提取以手心为中心，200*200大小的图像
//					cv::Mat mHandsizeDepth = mScaledHandDepth(Rect(x - 100, y -100 , 200, 200));
//
//					// 显示手的图像
//					cv::imshow( "Hand Image", mHandsizeDepth );
//				}
//			}
//
//		}
//		// 终止快捷键
//		if( cv::waitKey(1) == 'q')
//			break;
//	}
//
//	// 关闭Frame
//	mHandFrame.release();
//
//	// 关闭跟踪器
//	mHandTracker->destroy();
//
//	// 关闭NITE环境
//	nite::NiTE::shutdown();
//
//	return 0;		
//}
#pragma endregion 利用OpenCV进行简单的NIte识别

