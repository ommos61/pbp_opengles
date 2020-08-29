
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "game_math.h"

#define EPSILON 0.00001
#define FC(a, b) ((a < (b + EPSILON)) && (a > (b - EPSILON)))

static void print(const vec2& a) {
    fprintf(stdout, "vec2 = { %f, %f }\n", a.x, a.y);
}

static void print(const vec3& a) {
    fprintf(stdout, "vec3 = { %f, %f, %f }\n", a.x, a.y, a.z);
}

static void print(const vec4& a) {
    fprintf(stdout, "vec4 = { %f, %f, %f, %f }\n", a.x, a.y, a.z, a.w);
}

static void print(const mat4& a) {
    fprintf(stdout, "mat4 = {\n");
    fprintf(stdout, "  { %f, %f, %f, %f },\n", a.a.x, a.a.y, a.a.z, a.a.w);
    fprintf(stdout, "  { %f, %f, %f, %f },\n", a.b.x, a.b.y, a.b.z, a.b.w);
    fprintf(stdout, "  { %f, %f, %f, %f },\n", a.c.x, a.c.y, a.c.z, a.c.w);
    fprintf(stdout, "  { %f, %f, %f, %f }\n", a.d.x, a.d.y, a.d.z, a.d.w);
    fprintf(stdout, "}\n");
}

static bool operator==(const mat4& a, const mat4& b) {
    bool result = true;

    for (int y = 0; y <= 3; y++) {
        for (int x = 0; x <= 3; x++) {
            if (! FC(a.E[x + 4 * y], b.E[x + 4 * y])) {
                result = false;
                break;
            }
        }
    }

    return result;
}

static int test_vec3_constructors(void) {
    int result = 0;

    vec3 a = Vec3(1.0f, 2.0f, 3.0f);
    assert((a.x == 1.0f) && (a.y == 2.0f) && (a.z == 3.0f));

    return result;
}

static int test_vec3_operators(void) {
    int result = 0;

    // operator+
    vec3 a = Vec3(1.0f, 2.0f, 3.0f);
    vec3 b = Vec3(4.0f, 5.0f, 6.0f);
    vec3 c = a + b;
    assert(FC(c.x, 5.0f) && FC(c.y, 7.0f) && FC(c.z, 9.0f));
    vec3 d = b + a;
    assert(FC(d.x, 5.0f) && FC(d.y, 7.0f) && FC(d.z, 9.0f));

    // operator*
    float m = 10.0f;
    vec3 e = m * a;
    assert(FC(e.x, 10.0f) && FC(e.y, 20.0f) && FC(e.z, 30.0f));
    vec3 f = a * m;
    assert(FC(f.x, 10.0f) && FC(f.y, 20.0f) && FC(f.z, 30.0f));

    // operator+=
    a += b;
    assert(FC(a.x, 5.0f) && FC(a.y, 7.0f) && FC(a.z, 9.0f));
    a = Vec3(1.0f, 2.0f, 3.0f);

    // operator*=
    a *= 10.0f;
    assert(FC(a.x, 10.0f) && FC(a.y, 20.0f) && FC(a.z, 30.0f));

    return result;
}

static int test_vec4_constructors(void) {
    int result = 0;

    vec4 a = Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    assert((a.x == 1.0f) && (a.y == 2.0f) && (a.z == 3.0f) && (a.w == 4.0f));

    vec3 b3 = Vec3(5.0f, 6.0f, 7.0f);
    vec4 b = Vec4(b3, 8.0f);
    assert((b.x == 5.0f) && (b.y == 6.0f) && (b.z == 7.0f) && (b.w == 8.0f));

    return result;
}

static int test_vec4_operators(void) {
    int result = 0;

    // operator+
    vec4 a = Vec4(1.0f, 2.0f, 3.0f, 4.0f);
    vec4 b = Vec4(5.0f, 6.0f, 7.0f, 8.0f);
    vec4 c = a + b;
    assert(FC(c.x, 6.0f) && FC(c.y, 8.0f) && FC(c.z, 10.0f) && FC(c.w, 12.0f));
    vec4 d = b + a;
    assert(FC(d.x, 6.0f) && FC(d.y, 8.0f) && FC(d.z, 10.0f) && FC(d.w, 12.0f));

    // operator*

    // operator+=

    // operator*=

    return result;
}

static int test_mat4_constructors(void) {
    int result = 0;

    return result;
}

static int test_mat4_operators(void) {
    int result = 0;

    mat4 m1 = Mat4();
    mat4 m2 = Scale(m1, Vec4(2.0f, 3.0f, 4.0f, 5.0f));
    mat4 m3 = Translate(m2, Vec3(10.0f, 20.0f, 30.0f));
    mat4 m4 = Transpose(m3);
//    print(m3);
//    print(m4);
    assert(m4 == Mat4(Vec4(2.0f, 0.0f, 0.0f, 10.0f), Vec4(0.0f, 3.0f, 0.0f, 20.0f),
                      Vec4(0.0f, 0.0f, 4.0f, 30.0f), Vec4(0.0f, 0.0f, 0.0f, 5.0f)));

    return result;
}

extern int main(int argc, char *argv[]) {
    int result = 0;

    result |= test_vec3_constructors();

    result |= test_vec3_operators();

    result |= test_vec4_constructors();

    result |= test_vec4_operators();

    result |= test_mat4_constructors();

    result |= test_mat4_operators();

    if (result != 0) {
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

