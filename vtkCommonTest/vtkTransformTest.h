#pragma once
class vtkTransformTest
{
public:
	vtkTransformTest(void);
	~vtkTransformTest(void);

	static const double pt[3];
	static const double translate[3];
	static const double rx;
	static const double ry;
	static const double rz;

	static bool Run(bool on);
};

