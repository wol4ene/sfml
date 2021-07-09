#include "game_map.h"

using std::cout;
using std::endl;
GameMap::GameMap(const std::string& map_json_file,
                 const std::string& tile_atlas)
    : _map_parser{map_json_file},
      _map_renderer{tile_atlas,
                    _map_parser.get_tile_layers().size()}
    {}

void
GameMap::draw(sf::RenderTarget &target,
              sf::RenderStates states) const
{
    target.draw(_map_renderer, states);
}

void
GameMap::update()
{
    auto layers = _map_parser.get_tile_layers();
    auto map_info = _map_parser.get_map_info();
    auto tile_sets = _map_parser.get_tile_sets();

    for (uint32_t i = 0; i < layers.size(); i++) {
        _map_renderer.load(i,
                           map_info.num_tiles_x,
                           map_info.num_tiles_y,
                           map_info.tile_height_pixels,
                           map_info.tile_width_pixels,
                           tile_sets[0].num_tiles_x,
                           layers[i].tile_ids);
    }
}

void
GameMap::dump_map_info()
{
	auto game_map = _map_parser.get_map_info();
	printf("h: %d, w: %d, th: %d, tw: %d\n",
			game_map.num_tiles_y,
			game_map.num_tiles_x,
			game_map.tile_height_pixels,
			game_map.tile_width_pixels);
}

void
GameMap::dump_tile_layers()
{
	auto tile_layers = _map_parser.get_tile_layers();
	for (const auto& x : tile_layers) {
		printf("tile layer name=%s, id=%d, h=%d w=%d\n",
			  x.name.c_str(), x.id, x.num_tiles_y, x.num_tiles_x);

		for (const auto& p : x.properties) {
			printf("\tproperty name=%s, type=%s val=",
					p.name.c_str(), p.type.c_str());
			if (p.type == "string") { printf("%s\n", p.sval.c_str()); }
			if (p.type == "int") { printf("%u\n", p.uval); }
			if (p.type == "bool") { printf("%d\n", p.bval); }
		}   
	}  
}

void
GameMap::dump_object_layers()
{
	auto object_layers = _map_parser.get_object_layers();
	for (const auto& x : object_layers) {
		printf("obj layer name=%s id=%d\n", x.name.c_str(), x.id);
		for (const auto& o : x.objects) {
			printf("\tobj name=%s, type='%s' id=%d, h=%d, w=%d, tlx=%d, tly=%d\n",
				   o.name.c_str(), o.type.c_str(), o.id, o.height_pixels, o.width_pixels,
				   o.top_left_x, o.top_left_y);
			for (const auto& p : o.properties) {
				printf("\t\tproperties name=%s, type=%s, val= ",
						p.name.c_str(), p.type.c_str());
				if (p.type == "string") { printf("%s\n", p.sval.c_str()); }
				if (p.type == "int") { printf("%u\n", p.uval); }
				if (p.type == "bool") { printf("%d\n", p.bval); }
			}
		}
	}
}

void
GameMap::dump_tile_sets()
{
	auto tile_sets = _map_parser.get_tile_sets();
	cout << "tileset size: " <<  tile_sets.size() << endl;
	for (const auto& x : tile_sets) {
		printf("name %s, columns %d firstgid %d, imh %d imw %d margin %d ",
				x.name.c_str(), x.num_tiles_x, x.firstgid,
                x.imageheight_pixels, x.imagewidth_pixels, x.margin);
		printf("spacing %d tilecount %d tileheight %d tilewidth %d\n",
				x.spacing, x.tilecount, x.tileheight, x.tilewidth);
	}
}
