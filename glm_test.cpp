
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char *argv[]) {
    glm::vec4 myVector(1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 Identity = glm::mat4(1.0f);
    std::cout << "Identity:" << std::endl << glm::to_string(Identity) << std::endl;
    glm::vec4 transVector = Identity * myVector;
    std::cout << "Transformed:" << std::endl << glm::to_string(transVector) << std::endl;

    glm::mat4 Scale = glm::scale(Identity, glm::vec3(2.0f, 2.0f, 2.0f));
    std::cout << "Scale:" << std::endl << glm::to_string(Scale) << std::endl;
    transVector = Scale * myVector;
    std::cout << "Transformed:" << std::endl << glm::to_string(transVector) << std::endl;

    glm::mat4 Camera = glm::lookAt(
        glm::vec3(0.0f, 1.0f, -5.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    std::cout << "Camera:" << std::endl << glm::to_string(Camera) << std::endl;

    glm::mat4 Projection = glm::perspective(
        glm::radians(45.0f),
        (float)WIDTH / (float)HEIGHT,
        0.1f, 100.0f);
    std::cout << "Projection:" << std::endl << glm::to_string(Projection) << std::endl;
}
