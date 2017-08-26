#include "VoxelWorld.h"
#include <tuple>

VoxelWorld::VoxelWorld(int size[3], float *vals){
	for (auto i = 0; i < size[0]; i++) {
		for (auto j = 0; j < size[1]; j++) {
			for (auto k = 0; k < size[2]; k++) {
				VertexInstanced vox;
				vox.offset[0] = i;
				vox.offset[1] = j;
				vox.offset[2] = k;
				
				vox.color = vals[i*size[1] * size[2] + j*size[2] + k];
				
				vox.color!=0.0?world.push_back(vox):0;
			}
		}
	}
}
std::vector<VertexInstanced> VoxelWorld::getData(std::tuple<double, double, double> plane, double side) {
	std::vector<VertexInstanced> res;

	for (auto vox : world) {
		if (side*(vox.offset[0] * std::get<0>(plane) + vox.offset[1] * std::get<1>(plane) + vox.offset[2] * std::get<2>(plane)) >= 0) res.push_back(vox);
	}

	return res;
}
