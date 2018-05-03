#ifndef _INTERPOLATION_H_
#define _INTERPOLATION_H_

#include "MethodEnum.h"

#include <memory>
#include <string>
#include <map>
#include <vector>

class IMethod;

class Interpolation
{
	std::shared_ptr<IMethod> m_method;	 
	std::map<float, float> m_reference_points;
	std::vector<float> m_points_x;
	std::vector<float> m_points_y;
private:
	std::shared_ptr<IMethod> createMethod(MehthodEnum method_);
public:
	Interpolation();
	Interpolation(MehthodEnum method_);
	void readReferencePoints(const std::string& file_name_);
	void readPoints(const std::string& file_name_);
	void calculate();
	void writeData(const std::string& file_name_) const;
	void setMethod(MehthodEnum method_);
};


#endif // !_INTERPOLATION_H_

