#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;

namespace gltf {

enum class ComponentType {
  Byte = 5120,
  UnsignedByte = 5121,
  Short = 5122,
  UnsignedShort = 5123,
  UnsignedInt = 5125,
  Float = 5126,
};

enum class Type {
  Scalar,
  Vec2,
  Vec3,
  Vec4,
  Mat2,
  Mat3,
  Mat4,
};

enum class TargetType {
  ArrayBuffer = 34962,
  ElementBuffer = 34963,
};

struct Float3 {
  // TODO;
};
using Scale = Float3;
using Translation = Float3;
struct Mat4 {};
struct Quaternion {
  // TODO
};
struct Scene {
  std::vector<u32> node_handles;
  std::optional<std::string> name;
  // TODO: extensions and extras
};

struct Node {
  std::optional<u32> mesh_handle;
  // NOTE: these do have default values, not sure if those should be used or
  // just optional since the lack of all of them would just produce the identity
  // matrix. Which is what the result of constructing a matrix from the defaults
  // would be.
  std::optional<Scale> scale;
  std::optional<Translation> translation;
  std::optional<Quaternion> rotation;
  std::optional<Mat4> transform;

  std::optional<u64> camera_handle;
  std::optional<std::vector<u64>> child_handles;
  std::optional<u64> skin_index;
  std::optional<std::vector<f32>> weights;
  std::optional<std::string> name;
  // TODO: extensions and extras
};

struct Mesh {
  struct Primitives {
    struct Attribute {
      std::string name;
      u32 index;
    };
    std::vector<Attribute> attributes;
    std::vector<u32> indices_handle;
  };
  std::vector<Primitives> primitives;
  std::optional<std::vector<f32>> weights;
  std::optional<std::string> name;
};

// TODO: If the data is just kept in memory, then allot of this could just be
// string_views and slices. Or the parsed data could be converted to a better
// format.
class GLTFData {

  struct Buffer {
    u64 byte_length;
    std::optional<std::string> uri;
    std::optional<std::string> name;
  };

  struct BufferView {
    u64 buffer_index;
    u64 byte_offset = 0;
    u64 byte_length;
    std::optional<u64> byte_stride;
    std::optional<std::string> name;
    std::optional<TargetType> target;
  };

  struct Acessor {
    std::optional<u64> buffer_view_handle;
    u64 byte_offset = 0;
    ComponentType component_type;
    bool normalized = false;
    u64 count;
    Type type;
    std::optional<std::vector<f32>> max;
    std::optional<std::vector<f32>> min;
    std::optional<std::string> name;
  };

  struct Asset {
    std::string version;
    std::optional<std::string> copyright;
    std::optional<std::string> generator;
    std::optional<std::string> min_version;
    std::optional<std::string> extensions;
    std::optional<std::string> extras;
  };

  std::vector<Node> _meshes;
  std::vector<Buffer> _buffers;
  std::vector<BufferView> _buffer_views;
};

std::optional<GLTFData> Parse(const std::string &path);

} // namespace gltf
