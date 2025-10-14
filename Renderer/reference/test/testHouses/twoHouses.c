#include "test/myhouse.h"
#include "test/twoHousesShaders.h"

const unsigned int resolutionX = 1920;
const unsigned int resolutionY = 1080;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* twoHouseWindow = glfwCreateWindow(resolutionX, resolutionY, "MyHouse2", NULL, NULL);
    if (twoHouseWindow == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(twoHouseWindow);
    glfwSetFramebufferSizeCallback(twoHouseWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    // setup ends



    unsigned int firstVertexShader = glCreateShader(GL_VERTEX_SHADER);   // assigns id for the vertex shader
    glShaderSource(firstVertexShader, 1, &firstVertexShaderSource, NULL);     // figures out where and what the shader is
    glCompileShader(firstVertexShader);                                  // compiles the shader
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(firstVertexShader, GL_COMPILE_STATUS, &success);       //asks if vertextShader's compile status is a success (1)
    if (!success)
    {
        glGetShaderInfoLog(firstVertexShader, 512, NULL, infoLog);       
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);   //prints error log
    }

    // fragment shader
    unsigned int firstFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(firstFragmentShader, 1, &firstFragmentShaderSource, NULL);
    glCompileShader(firstFragmentShader);
    // check for shader compile errors
    glGetShaderiv(firstFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(firstFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }

    unsigned int secondVertexShader = glCreateShader(GL_VERTEX_SHADER);   // assigns id for the vertex shader
    glShaderSource(secondVertexShader, 1, &secondVertexShaderSource, NULL);     // figures out where and what the shader is
    glCompileShader(secondVertexShader);                                  // compiles the shader
    // check for shader compile errorse

    glGetShaderiv(secondVertexShader, GL_COMPILE_STATUS, &success);       //asks if vertextShader's compile status is a success (1)
    if (!success)
    {
        glGetShaderInfoLog(secondVertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);   //prints error log
    }


    // fragment shader
    unsigned int secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(secondFragmentShader, 1, &secondFragmentShaderSource, NULL);
    glCompileShader(secondFragmentShader);
    // check for shader compile errors
    glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(secondFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }




    // link shaders
    unsigned int houseShaderProgram1 = glCreateProgram(); // shader program = multiple shaders linked
    glAttachShader(houseShaderProgram1, firstVertexShader);    // attach both
    glAttachShader(houseShaderProgram1, firstFragmentShader);
    glLinkProgram(houseShaderProgram1);                   // and link them
    // check for linking errors
    glGetProgramiv(houseShaderProgram1, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(houseShaderProgram1, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
    }
    glDeleteShader(firstVertexShader);
    glDeleteShader(firstFragmentShader); // don't need them anymore after being attached

    // link shaders
    unsigned int houseShaderProgram2 = glCreateProgram(); // shader program = multiple shaders linked
    glAttachShader(houseShaderProgram2, secondVertexShader);    // attach both
    glAttachShader(houseShaderProgram2, secondFragmentShader);
    glLinkProgram(houseShaderProgram2);                   // and link them
    // check for linking errors
    glGetProgramiv(houseShaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(houseShaderProgram2, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
    }


    glDeleteShader(firstVertexShader);
    glDeleteShader(firstFragmentShader); // don't need them anymore after being attached
    glDeleteShader(secondVertexShader);
    glDeleteShader(secondFragmentShader);

    float firstVertices[] = {                    //actual points to be rendered
     0.0f,  0.75f, 0.0f,  // tip
     0.5f,  0.25f, 0.0f,  // tri base R
    -0.5f,  0.25f, 0.0f,  // tri base L
     0.5f, -0.5f, 0.0f,  // bottom R
    -0.5f, -0.5f, 0.0f,  // bottom L
    };
    unsigned int firstIndices[] = {  // note that we start from 0
        0, 1, 2, // roof
        1, 2, 3, // room rightx
        2, 3, 4  // room lefts
    };

    float secondVertices[] = {                    //actual points to be rendered
     0.0f,  -0.75f, 0.0f,  // tip
     0.5f,  -0.25f, 0.0f,  // tri base R
    -0.5f,  -0.25f, 0.0f,  // tri base L
     0.5f,   0.5f, 0.0f,  // bottom R
    -0.5f,   0.5f, 0.0f,  // bottom L
    };
    unsigned int secondIndices[] = {  // note that we start from 0
        0, 1, 2, // roof
        1, 2, 3, // room rightx
        2, 3, 4  // room lefts
    };


// set up BOTH arrays and BOTH vertex buffers
    unsigned int houseVertexArrays[2]; 
    unsigned int houseVertexBuffers[2];
    unsigned int houseElementBuffers[2];
    //unsigned int houseElementBuffer;
    glGenVertexArrays(2, houseVertexArrays);    // create the array and buffers
    glGenBuffers(2, houseVertexBuffers);
    glGenBuffers(2, houseElementBuffers);
    

    //glGenBuffers(1, &houseElementBuffer);
//

// FIRST HOUSE
    glBindVertexArray(houseVertexArrays[0]);        //bind the array

    glBindBuffer(GL_ARRAY_BUFFER, houseVertexBuffers[0]);                                   //bind the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);    // give info about the array to the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseElementBuffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(firstIndices), firstIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);       // set up vertex attributes and enable them
    glEnableVertexAttribArray(0);
    
//
//  SECOND HOUSE
    glBindVertexArray(houseVertexArrays[1]);        //bind the array

    glBindBuffer(GL_ARRAY_BUFFER, houseVertexBuffers[1]);                                   //bind the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);    // give info about the array to the buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseElementBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(secondIndices), secondIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);       // set up vertex attributes and enable them, same attributes
    glEnableVertexAttribArray(0);
//

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseElementBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(firstIndices), firstIndices, GL_STATIC_DRAW);


    //glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds
    //glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

    while (!glfwWindowShouldClose(twoHouseWindow)) {
        firstVertices[0] += 0.001f;
        secondVertices[3] += 0.01f;

        glBindBuffer(GL_ARRAY_BUFFER, houseVertexBuffers[0]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(firstVertices), firstVertices);

        glBindBuffer(GL_ARRAY_BUFFER, houseVertexBuffers[1]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(secondVertices), secondVertices);

        processInput(twoHouseWindow); // process any input 

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
        glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only

        glUseProgram(houseShaderProgram1);       // use the shader program

        glBindVertexArray(houseVertexArrays[0]);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glUseProgram(houseShaderProgram2);
        glBindVertexArray(houseVertexArrays[1]);

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(houseVertexArray);     // bind the buffer in case a different one got bound at some point

        //glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(twoHouseWindow);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, houseVertexArrays);
    glDeleteBuffers(1, houseVertexBuffers);
    //glDeleteBuffers(1, &houseElementBuffer);
    glDeleteProgram(houseShaderProgram1);

    glfwTerminate();
    return 0;


}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

