#include <fmt/core.h>

#include <focus.hpp>
#include <string>

int main(int argc, char **argv) {
  if (argc < 2) {
    fmt::print("Usage: gltf <gltf-file>\n");
    return 0;
  }
  std::string path(argv[1]);
  fmt::print("gltf-file path: {}", path);
  focus::Init(focus::RendererAPI::OpenGL);
  return 0;
}
