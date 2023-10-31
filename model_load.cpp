//#include <iostream>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <learnopengl/model.h>
//
//// Global variables for GLFW
//GLFWwindow* window;
//int screenWidth = 800;
//int screenHeight = 600;
//
//void errorCallback(int error, const char* description) {
//    std::cerr << "GLFW Error: " << description << std::endl;
//}
//
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) {
//        std::cerr << "Failed to initialize GLFW" << std::endl;
//        return -1;
//    }
//
//    // Set error callback
//    glfwSetErrorCallback(errorCallback);
//
//    // Create a GLFW window
//    window = glfwCreateWindow(screenWidth, screenHeight, "Model Loading with Assimp", NULL, NULL);
//    if (!window) {
//        std::cerr << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // Make the OpenGL context current
//    glfwMakeContextCurrent(window);
//
//    // Initialize Glad
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::cerr << "Failed to initialize Glad" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // Load the 3D model with Assimp
//    Shader ourShader("C:\\Users\\home\\Documents\\OpenGL\\learning_Projects\\ModelLoading\\1.model_loading.vs", "C:\\Users\\home\\Documents\\OpenGL\\learning_Projects\\ModelLoading\\1.model_loading.fs");
//    //const char *pathS = "C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\cara_000001.obj";
//    Model ourModel("C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\backpack\\backpack.obj");
//    // Set up rendering here
//    // You will need to write rendering code to render the 3D model using OpenGL and apply materials
//    // This involves setting up shaders, textures, material properties, and rendering the mesh
//
//    // Main rendering loop
//    while (!glfwWindowShouldClose(window)) {
//        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Render the 3D model with materials here
//        glfwMakeContextCurrent(window);
//
//        ourModel.Draw(ourShader);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Clean up and terminate GLFW
//    glfwTerminate();
//
//    return 0;
//}
