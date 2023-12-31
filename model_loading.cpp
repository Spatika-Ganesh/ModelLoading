#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>
#include <sstream>
#include <iomanip>



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* RESOURCE_FOLDER = "C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\"; 

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(2*SCR_WIDTH, 2*SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    // 
    Shader ourShader("C:\\Users\\home\\Documents\\OpenGL\\learning_Projects\\ModelLoading\\model_loading.vs", "C:\\Users\\home\\Documents\\OpenGL\\learning_Projects\\ModelLoading\\model_loading.fs");

    // load models
    // -----------
    // C:\\Users\\home\\Documents\\OpenGL\\resources
    vector<Model> models;
    //Model ourModel("C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\cara_000001.obj");
        //cyborg\\cyborg.obj");
        //frame_obj\\cara_000001.obj");
   const string pathS = "C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\cara_";
    vector<string> pathsOfModel;
    string s, pathStr;
    for (int j = 1; j< 282; j++) {

        stringstream ss;
        ss << setw(6) << setfill('0') << j;
        s = ss.str();
        pathStr = pathS + s + ".obj";
        cout << pathStr;
        pathsOfModel.push_back(pathStr);
        models.push_back(Model(pathStr, false, RESOURCE_FOLDER));
    }
    
    cout << "Model vector loaded" << endl;
    // draw in wireframe;
    // 
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Model ourModel;
    //Model ourModel("C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\cara_000015.obj");
    int i = 0;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        
        if (i == 281) {
            i = 0;
        }
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
                
        pathStr = pathsOfModel.at(i);

        //if (models.size() == 9) {
            ourModel = models.at(i);
        //}
        //else {
          //  ourModel = Model(pathStr, false, RESOURCE_FOLDER);
          //  models.push_back(ourModel);
       // }

        if (deltaTime > 2.0f) {
            cout << "CHANGED: " << i << endl;
            cout << "Current Frame:: " << currentFrame << endl;
            cout << "Delta Time:: " << deltaTime << endl;
            cout << "Last Frame:: " << lastFrame << endl;

            i++;

            lastFrame = currentFrame;
        }

        //     input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f,1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         
        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        view = glm::scale(view, glm::vec3(30.0f, 30.0f,30.0f));
        view = glm::translate(view, glm::vec3(0.0f, -1.0f, -1.0f));
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -1.0f)); // translate it down so it's at the center of the scene
        
        //model = glm::translate(model, glm::vec3(-1.0f, -1.0f, -0.5f)); // translate it down so it's at the center of the scene
        /*model = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 3.0f, 0.0f));
            */
        model = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 2.0f, 0.0f));
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
