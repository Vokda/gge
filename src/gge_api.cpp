#include "gge_api.hpp"
#include "core.hpp"
#include <memory>
#include "texter.hpp"
#include <vector>
using namespace std;

GGE_API::GGE_API(Core& core):
	_core(core)
{}

const string GGE_API::hello()
{
	return "GGE API says hello!";
}

size_t GGE_API::create_text(const string& text, int x, int y)
{
	auto texter = _core.get_texter();
	return texter->create_text(text, {x, y});
}

size_t GGE_API::create_text(
		const string& text, 
		vector<int> color,
		vector<int> size,
		int milliseconds
		)
{
	auto texter = _core.get_texter();
	vector<Uint8> casted_v(color.begin(), color.end());
	SDL_Color c = {casted_v[0], casted_v[1], casted_v[2], casted_v[3]};

	// position
	SDL_Rect s = {size[0], size[1], size[2], size[3]};

	return texter->create_text(
			text, 
			c,
			s,
			milliseconds
			);
}
