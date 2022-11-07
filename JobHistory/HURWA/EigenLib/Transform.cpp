#include "Transform.h"

/************************************************************************/
/* 函数功能：角轴（旋转向量）转四元数
/* 函数参数：角轴（旋转向量）
/* 函数返回：四元数
/* 函数说明：角轴与四元数转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时02分
/************************************************************************/
Eigen::Quaterniond Transform::angleAxisToQuaternion(__in Eigen::AngleAxisd& _rotateVec)
{
    return Eigen::Quaterniond(_rotateVec);
}

/************************************************************************/
/* 函数功能：四元数转角轴（旋转向量）
/* 函数参数：四元数
/* 函数返回：角轴（旋转向量）
/* 函数说明：四元数与角轴转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时04分
/************************************************************************/
Eigen::AngleAxisd Transform::quaternionToAngleAxis(__in Eigen::Quaterniond& _quaternion)
{
    return Eigen::AngleAxisd(_quaternion);
}

/************************************************************************/
/* 函数功能：角轴（旋转向量）转旋转矩阵
/* 函数参数：角轴（旋转向量）
/* 函数返回：旋转矩阵
/* 函数说明：角轴（旋转向量）与旋转矩阵转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时05分
/************************************************************************/
Eigen::Matrix3d Transform::angleAxisToMatrix(__in Eigen::AngleAxisd& _rotateVec)
{
    return _rotateVec.toRotationMatrix();
}

/************************************************************************/
/* 函数功能：旋转矩阵转角轴（旋转向量）
/* 函数参数：旋转矩阵
/* 函数返回：角轴（旋转向量）
/* 函数说明：旋转矩阵与角轴（旋转向量）转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时18分
/************************************************************************/
Eigen::AngleAxisd Transform::matrixToAngleAxis(__in Eigen::Matrix3d& _matrix)
{
    return Eigen::AngleAxisd(_matrix);
}

/************************************************************************/
/* 函数功能：四元数转旋转矩阵
/* 函数参数：四元数
/* 函数返回：旋转矩阵
/* 函数说明：四元数与旋转矩阵转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时20分
/************************************************************************/
Eigen::Matrix3d Transform::quaternionToMatrix(__in Eigen::Quaterniond& _quaternion)
{
    return  Eigen::Matrix3d(_quaternion);
}

/************************************************************************/
/* 函数功能：旋转矩阵转四元数
/* 函数参数：旋转矩阵
/* 函数返回：四元数
/* 函数说明：旋转矩阵与四元数转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时21分
/************************************************************************/
Eigen::Quaterniond Transform::matrixToQuaternion(__in Eigen::Matrix3d& _matrix)
{
    return Eigen::Quaterniond(_matrix);
}

/************************************************************************/
/* 函数功能：旋转矩阵转欧拉角
/* 函数参数：旋转矩阵
/* 函数返回：欧拉角
/* 函数说明：旋转矩阵与欧拉角转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时38分
/************************************************************************/
Eigen::Vector3d Transform::matrixToEulerAngle(__in Eigen::Matrix3d& _matrix)
{
	return _matrix.eulerAngles(0, 1, 2);
}

/************************************************************************/
/* 函数功能：欧拉角转旋转矩阵
/* 函数参数：欧拉角
/* 函数返回：旋转矩阵
/* 函数说明：欧拉角与旋转矩阵转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 12时40分
/************************************************************************/
Eigen::Matrix3d Transform::eulerAngleToMatrix(__in Eigen::Vector3d& _eulerAngle)
{
	auto axisX = Eigen::AngleAxisd(_eulerAngle[0], Eigen::Vector3d::UnitX());
	auto axisY = Eigen::AngleAxisd(_eulerAngle[1], Eigen::Vector3d::UnitY());
	auto axisZ = Eigen::AngleAxisd(_eulerAngle[2], Eigen::Vector3d::UnitZ());
	return Eigen::Matrix3d(axisX * axisY * axisZ);
}

/************************************************************************/
/* 函数功能：坐标系转欧式变换矩阵
/* 函数参数：坐标系
/* 函数返回：欧式变换矩阵
/* 函数说明：坐标系与欧式变换矩阵转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 13时32分
/************************************************************************/
Eigen::Isometry3d Transform::coordinateToIsometry(__in CoordinateSystem& _coordinate)
{
	Eigen::Isometry3d matrix = Eigen::Isometry3d::Identity();
	for (int i = 0; i < 3; ++i) {
		matrix(i, 0) = _coordinate.getAxisX()[i];
		matrix(i, 1) = _coordinate.getAxisY()[i];
		matrix(i, 2) = _coordinate.getAxisZ()[i];
	}
	matrix.pretranslate(_coordinate.getOrigin());
	return matrix;
}

/************************************************************************/
/* 函数功能：欧式变换矩阵转坐标系
/* 函数参数：欧式变换矩阵
/* 函数返回：坐标系
/* 函数说明：欧式变换矩阵与坐标系转换可逆
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月23日 13时36分
/************************************************************************/
CoordinateSystem Transform::IsometryToCoordinate(Eigen::Isometry3d& _matrix)
{
	Eigen::Vector3d origin(_matrix(0, 3), _matrix(1, 3), _matrix(2, 3));
	Eigen::Vector3d axisX(_matrix(0, 0), _matrix(1, 0), _matrix(2, 0));
	Eigen::Vector3d axisY(_matrix(0, 1), _matrix(1, 1), _matrix(2, 1));
	Eigen::Vector3d axisZ(_matrix(0, 2), _matrix(1, 2), _matrix(2, 2));
	return CoordinateSystem(origin, axisX, axisY, axisZ);
}

/************************************************************************/
/* 函数功能：矩阵数组转欧式变换矩阵
/* 函数参数：矩阵数组
/* 函数返回：欧式变换矩阵
/* 函数说明：数组长度16个double
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月27日 15时11分
/************************************************************************/
Eigen::Isometry3d Transform::matrixBufferToIsometry3d(__in double* _buffer)
{
	Eigen::Isometry3d matrix;
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			matrix(i, j) = _buffer[index++];
		}
	}
	return matrix;
}

/************************************************************************/
/* 函数功能：欧式变换矩阵转矩阵数组
/* 函数参数：欧式变换矩阵, 矩阵数组
/* 函数返回：void
/* 函数说明：void
/* 编 写 人：刘鹏春
/* 编写时间：2021年09月27日 15时18分
/************************************************************************/
void Transform::isometry3dToMatrixBuffer(__in Eigen::Isometry3d& _matrix, __out double _buffer[16])
{
	memset(_buffer, 0, sizeof(_buffer));
	int index = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			_buffer[index++] = _matrix(i, j);
		}
	}
}
