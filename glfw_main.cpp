#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define GLFW_INCLUDE_ES3
#define GLFW_INCLUDE_GLEXT
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

#include "game_math.h"

#define ARRAYSIZE(array) (sizeof(array)/sizeof(array[0]))

static const GLuint WIDTH = 800;
static const GLuint HEIGHT = 600;
static const GLchar* vertex_shader_source = R"FOO(
#version 300 es
layout(location = 0) in vec3 position;
uniform mat4 model_transform;
uniform mat4 view_transform;
uniform mat4 projection_transform;
void main() {
   vec4 model_position = model_transform * vec4(position, 1.0);
   gl_Position = projection_transform * view_transform * model_position;
}
)FOO";

static const GLchar* fragment_shader_source = R"FOO(
#version 300 es
precision mediump float;
out vec4 FragColor;
void main() {
   FragColor = vec4(0.8, 0.0, 0.0, 1.0);
}
)FOO";

//
// Static triangle data
//
static const GLfloat triangle_vertices[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
};
static const unsigned int triangle_indices[] = {
    0, 1, 2, 3,
};

//
// Static cube data
//
static const GLfloat cube_vertices[] = {
    // bottom square
    -1.0f, -1.0f, -1.0f, // (0) front left
    -1.0f, -1.0f,  1.0f, // (1) back left
     1.0f, -1.0f,  1.0f, // (2) back right
     1.0f, -1.0f, -1.0f, // (3) front right
    // top square
    -1.0f,  1.0f, -1.0f, // (4) front left
    -1.0f,  1.0f,  1.0f, // (5) back left
     1.0f,  1.0f,  1.0f, // (6) back right
     1.0f,  1.0f, -1.0f, // (7) front right
};
static const unsigned int cube_indices[] = {
    // bottom square
    0, 1, 2, 0, 2, 3,
    // top square
    4, 5, 6, 4, 6, 7,
    // back square
    1, 6, 5, 1, 2, 6,
    // right square
//    3, 7, 6, 3, 6, 2,
    // some dummy fillers
//    0, 0, 0, 0, 0, 0
};

static GLfloat identity_transform[] = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

GLint common_get_shader_program(const char *vertex_shader_source, const char *fragment_shader_source) {
    enum Consts {INFOLOG_LEN = 512};
    GLchar infoLog[INFOLOG_LEN];
    GLint fragment_shader;
    GLint shader_program;
    GLint success;
    GLint vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
    }

    /* Link shaders */
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, INFOLOG_LEN, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}

void GL_APIENTRY debugproc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam) {
}

int main(void) {
    GLuint shader_program, vbo[2];
    GLint pos;
    GLFWwindow* window;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR);
    //glDebugMessageCallbackKHR(debugproc, NULL);

    shader_program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    pos = glGetAttribLocation(shader_program, "position");

    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(pos);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
//    glBindBuffer(GL_INDEX_ARRAY_BUFFER, &vbo[1]);
//    glBindBuffer(GL_INDEX_ARRAY_BUFFER, 0);

    int quit = 0;
    while (!quit && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            quit = 1;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);

        // Create the 3D projection transform
        float near = 0.15f;
        float far = 10.0f;
        float aspect = (float)WIDTH / (float)HEIGHT;
        float A = near;
        float B = near * aspect;
        float C = (far + near) / (far - near);
        float D = 2 * far * near / (far - near);
        GLfloat projection_transform[] = {
            A,    0.0f,  0.0f, 0.0f,
            0.0f, B,     0.0f, 0.0f,
            0.0f, 0.0f,  C,    D,
            0.0f, 0.0f, -1.0f, 0.0f,
        };
        GLint projection_mat_loc = glGetUniformLocation(shader_program, "projection_transform");
        assert(projection_mat_loc != -1);
        glUniformMatrix4fv(projection_mat_loc, 1, GL_TRUE, projection_transform);

        // Create the model transform
        GLfloat model_transform[] = {
            0.5f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.5f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
        GLint model_mat_loc = glGetUniformLocation(shader_program, "model_transform");
        assert(model_mat_loc != -1);
        glUniformMatrix4fv(model_mat_loc, 1, GL_TRUE, model_transform);

        // Create the camera transform
        GLint view_mat_loc = glGetUniformLocation(shader_program, "view_transform");
        assert(view_mat_loc != -1);
        glUniformMatrix4fv(view_mat_loc, 1, GL_TRUE, identity_transform);

        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, triangle_indices);
        glDrawElements(GL_TRIANGLES, ARRAYSIZE(cube_indices), GL_UNSIGNED_INT, cube_indices);
        glfwSwapBuffers(window);
    }
    glDeleteBuffers(2, vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}
