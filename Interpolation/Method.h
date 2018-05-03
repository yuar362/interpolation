#ifndef _METHOD_H_
#define _METHOD_H_

#include <map>
#include <vector>
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IMethod
{
public:
	virtual void calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_) = 0;
	virtual ~IMethod() {}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StepMetod : public IMethod
{
public:
	void calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_) override;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LinearMethod : public IMethod
{
public:
	void calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_) override;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class QuadraticMethod : public IMethod
{
public:
	void calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_) override;
};
#endif // !_METHOD_H_

