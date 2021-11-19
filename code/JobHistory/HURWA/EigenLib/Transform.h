#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "../CoordinateSystemManager/CoordinateSystem.h"
#include <Eigen/Geometry>

class Transform {
public:
	static Eigen::Quaterniond angleAxisToQuaternion(__in Eigen::AngleAxisd& _rotateVec);
	static Eigen::AngleAxisd quaternionToAngleAxis(__in Eigen::Quaterniond& _quaternion);
	static Eigen::Matrix3d angleAxisToMatrix(__in Eigen::AngleAxisd& _rotateVec);
	static Eigen::AngleAxisd matrixToAngleAxis(__in Eigen::Matrix3d& _matrix);
	static Eigen::Matrix3d quaternionToMatrix(__in Eigen::Quaterniond& _quaternion);
	static Eigen::Quaterniond matrixToQuaternion(__in Eigen::Matrix3d& _matrix);
	static Eigen::Vector3d matrixToEulerAngle(__in Eigen::Matrix3d& _matrix);
	static Eigen::Matrix3d eulerAngleToMatrix(__in Eigen::Vector3d& _eulerAngle);
	static Eigen::Isometry3d coordinateToIsometry(__in CoordinateSystem& _coordinate);
	static CoordinateSystem IsometryToCoordinate(__in Eigen::Isometry3d& _matrix);
	static Eigen::Isometry3d matrixBufferToIsometry3d(__in double* _buffer);
	static void isometry3dToMatrixBuffer(__in Eigen::Isometry3d& _matrix, __out double _matrixBuffer[16]);
};

#endif //_TRANSFORM_H