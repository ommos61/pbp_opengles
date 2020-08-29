

//
// vec2: 2-dimensional vector
//
typedef union vec2 {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float E[1];
} vec2;

inline vec2 Vec2(float x, float y) {
    vec2 result = { x, y };
    return result;
}

//
// vec3: 3-dimensional vector
//
typedef union vec3 {
    struct {
        float x, y, z;
    };
    float E[2];

    vec3& operator+=(const vec3& rhs);
    vec3& operator*=(const float& rhs);
} vec3;

inline vec3 Vec3(float x, float y, float z) {
    vec3 result = { x,  y, z };
    return result;
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs) {
    vec3 result = { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
    return result;
}

inline vec3 operator*(const float& lhs, const vec3& rhs) {
    vec3 result = { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
    return result;
}

inline vec3 operator*(const vec3& lhs, const float& rhs) {
    return rhs * lhs;
}

inline vec3& vec3::operator+=(const vec3& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

inline vec3& vec3::operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

//
// vec4: 4-dimensional vector or color
//
typedef union vec4 {
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
    float E[3];

    vec4& operator+=(const vec4& rhs);
    vec4& operator*=(const float& rhs);
} vec4;

inline vec4 Vec4(float x, float y, float z, float w) {
    vec4 result = { x, y, z, w };
    return result;
}

inline vec4 Vec4(const vec3& v3, const float& w) {
    vec4 result = { v3.x, v3.y, v3.z, w };
    return result;
}

inline vec4 operator+(const vec4& lhs, const vec4& rhs) {
    vec4 result = { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
    return result;
}

inline vec4 operator*(const float& lhs, const vec4& rhs) {
    vec4 result = { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w };
    return result;
}

inline vec4 operator*(const vec4& lhs, const float& rhs) {
    return rhs * lhs;
}

inline vec4& vec4::operator+=(const vec4& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    this->w += rhs.w;
    return *this;
}

inline vec4& vec4::operator*=(const float& rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    this->w *= rhs;
    return *this;
}

//
// mat3: 3-dimensional matrix
//
typedef union mat3 {
    struct {
        vec3 a, b, c;
    };
    float E[8];
} mat3;

//
// mat4: 4-dimensional matrix
//
typedef union mat4 {
    struct {
        vec4 a, b, c, d;
    };
    float E[15];
} mat4;

inline mat4 Mat4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) {
    mat4 result = { a, b, c, d };
    return result;
}

inline mat4 Mat4(void) {
    mat4 result = Mat4(
        Vec4(1.0f, 0.0f, 0.0f, 0.0f),
        Vec4(0.0f, 1.0f, 0.0f, 0.0f),
        Vec4(0.0f, 0.0f, 1.0f, 0.0f),
        Vec4(0.0f, 0.0f, 0.0f, 1.0f)
    );
    return result;
}

inline mat4 Transpose(const mat4& in) {
    mat4 result;

    for (int y = 0; y <= 3; y++) {
        for (int x = 0; x <= 3; x++) {
            result.E[x + 4 * y] = in.E[y + 4 * x];
        }
    }

    return result;
}

inline mat4 Translate(const mat4& in, const vec3& move) {
    mat4 result = in;

    result.d += Vec4(move, 0.0f);

    return result;
}

inline mat4 Scale(const mat4& in, const vec4& scale) {
    mat4 result = in;

    result.a *= scale.x;
    result.b *= scale.y;
    result.c *= scale.z;
    result.d *= scale.w;

    return result;
}

inline mat4 Scale(const mat4& in, const vec3& scale) {
    mat4 result = Scale(in, Vec4(scale, 1.0f));
    return result;
}


