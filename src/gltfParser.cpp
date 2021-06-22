#include "gltfParser.hpp"
#include <json.hpp>

#include <fstream>

namespace gltf {

std::optional<GLTFData> Parse(const std::string &path) {
  std::ifstream file(path.c_str());
  nlohmann::json gltfSource;
  file >> gltfSource;

  auto scenes_json = gltfSource["scenes"];
  if (!scenes_json.is_array()) {
    return {};
  }

  for (const auto &scene_entry : scenes_json) {
  }
}

} // namespace gltf
