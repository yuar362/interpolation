#include "Method.h"

#include <stdexcept>

void StepMetod::calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_)
{
	for (const auto& x : points_x_)
	{
		auto it = reference_points_.lower_bound(x);
		if (it == reference_points_.begin())
		{
			points_y_.push_back(it->second);
		}
		else if (it == reference_points_.end())
		{
			points_y_.push_back((--it)->second);
		}
		else
		{
			auto prev = it;
			--prev;
			if (x < (prev->first + it->first) * 0.5)
				points_y_.push_back(prev->second);
			else
				points_y_.push_back(it->second);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LinearMethod::calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_)
{
	if (reference_points_.size() < 2)
	{
		throw(std::logic_error("more reference points are needed!"));
	}

	for (const auto& x : points_x_)
	{
		auto it = reference_points_.lower_bound(x);
		auto prev = it;
		if (it == reference_points_.begin())
		{
			++it;
		}
		else if (it == reference_points_.end())
		{
			--it;
			prev = it;
			--prev;
		}
		else
		{
			--prev;
		}
		
		float y = prev->second + (it->second - prev->second) * (x - prev->first) / (it->first - prev->first);
		points_y_.push_back(y);
	}	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void QuadraticMethod::calculate(const std::map<float, float>& reference_points_, const std::vector<float>& points_x_, std::vector<float>& points_y_)
{
	if (reference_points_.size() < 3)
	{
		throw(std::logic_error("more reference points are needed!"));
	}

	for (const auto& x : points_x_)
	{
		auto it = reference_points_.lower_bound(x);
		auto prev = it;
		auto prev_prev = prev;
		if (it == reference_points_.end())
		{
			--it;
			--(--prev);
			--(--(--prev_prev));
		}
		else if (it == reference_points_.begin())
		{
			++(++it);
			++prev;
		}
		else
		{
			--prev;
			--prev_prev;
			if (prev == reference_points_.begin())
			{
				++it;
				++prev;
			}
			else
			{
				--prev_prev;
			}
		}
		
		float dx0 = x - prev_prev->first;
		float dx1 = x - prev->first;
		float dx2 = x - it->first;
		float dx21 = it->first - prev->first;
		float dx20 = it->first - prev_prev->first;
		float dx10 = prev->first - prev_prev->first;
		
		float y = prev_prev->second * dx1 * dx2 / dx20 / dx10 - prev->second * dx0 * dx2 / dx10 / dx21 + it->second * dx2 *dx1 / dx21 / dx20;
		points_y_.push_back(y);
	}
}
