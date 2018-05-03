#include "Interpolation.h"
#include "Method.h"

#include <stdexcept>
#include <fstream>
#include<assert.h>

std::shared_ptr<IMethod> Interpolation::createMethod(MehthodEnum method_)
{
	switch (method_)
	{
		case STEP:
		{
			return std::shared_ptr<IMethod>(new StepMetod());
		}
		case LINEAR:
		{
			return std::shared_ptr<IMethod>(new LinearMethod());
		}
		case QUADRATIÑ:
		{
			return std::shared_ptr<IMethod>(new QuadraticMethod());
		}
		default:
			return nullptr;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Interpolation::Interpolation() : m_method(createMethod(LINEAR))
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Interpolation::Interpolation(MehthodEnum method_) : m_method(createMethod(method_))
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interpolation::readReferencePoints(const std::string & file_name_)
{
	std::ifstream fin;
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fin.open(file_name_);
	size_t points_count;
	float x, y;
	fin >> points_count;
	m_reference_points.clear();
	for (size_t i = 0; i < points_count; ++i)
	{
		fin >> x >> y;
		m_reference_points.insert(std::make_pair(x, y));
	}
	fin.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interpolation::readPoints(const std::string & file_name_)
{
	std::ifstream fin;
	fin.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fin.open(file_name_);
	size_t points_count;
	float x;
	fin >> points_count;
	m_points_x.clear();
	m_points_x.reserve(points_count);
	for (size_t i = 0; i < points_count; ++i)
	{
		fin >> x;
		m_points_x.push_back(x);
	}
	fin.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interpolation::calculate()
{
	assert(m_method);
	if (!m_points_x.size())
	{
		throw(std::logic_error("There are no points coordinates!"));
	}
	if (m_reference_points.empty())
	{
		throw(std::logic_error("There are no reference points!"));
	}

	m_points_y.clear();
	m_points_y.reserve(m_points_x.size());
	m_method->calculate(m_reference_points, m_points_x, m_points_y);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interpolation::writeData(const std::string & file_name_) const
{
	size_t y_points_count = m_points_y.size();
	if (!y_points_count || y_points_count != m_points_x.size())
	{
		throw(std::logic_error("There is no interpolation!"));
	}

	std::ofstream fout;
	fout.exceptions(std::ofstream::failbit | std::ofstream::badbit);
	fout.open(file_name_);
	fout << y_points_count << std::endl;
	
	for (size_t i = 0; i < y_points_count; ++i)
	{
		fout << m_points_x[i] << ' ' << m_points_y[i] << std::endl;
	}
	fout.close();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Interpolation::setMethod(MehthodEnum method_)
{
	m_method = createMethod(method_);
}
