#include <iostream>
#include "glad.h"
#include "imgui_impl_glfw.h"
#include "GLFW/glfw3.h"
#include <sstream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_images.h"



void FrameResizingCallback(GLFWwindow* window,int width,int height)
{

    glViewport(0,0,width,height);
}


void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
GLenum severity, GLsizei length,
const GLchar *msg, const void *data)
{
std::string _source;
std::string _type;
std::string _severity;


switch (source) {
case GL_DEBUG_SOURCE_API:
_source = "API";
break;

case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
_source = "WINDOW SYSTEM";
break;

case GL_DEBUG_SOURCE_SHADER_COMPILER:
_source = "SHADER COMPILER";
break;

case GL_DEBUG_SOURCE_THIRD_PARTY:
_source = "THIRD PARTY";
break;

case GL_DEBUG_SOURCE_APPLICATION:
_source = "APPLICATION";
break;

case GL_DEBUG_SOURCE_OTHER:
_source = "UNKNOWN";
break;

default:
_source = "UNKNOWN";
break;
}

switch (type) {
case GL_DEBUG_TYPE_ERROR:
_type = "ERROR";
break;

case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
_type = "DEPRECATED BEHAVIOR";
break;

case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
_type = "UDEFINED BEHAVIOR";
break;

case GL_DEBUG_TYPE_PORTABILITY:
_type = "PORTABILITY";
break;

case GL_DEBUG_TYPE_PERFORMANCE:
_type = "PERFORMANCE";
break;

case GL_DEBUG_TYPE_OTHER:
_type = "OTHER";
break;

case GL_DEBUG_TYPE_MARKER:
_type = "MARKER";
break;

default:
_type = "UNKNOWN";
break;
}

switch (severity) {
case GL_DEBUG_SEVERITY_HIGH:
_severity = "HIGH";
break;

case GL_DEBUG_SEVERITY_MEDIUM:
_severity = "MEDIUM";
break;

case GL_DEBUG_SEVERITY_LOW:
_severity = "LOW";
break;

case GL_DEBUG_SEVERITY_NOTIFICATION:
_severity = "NOTIFICATION";
break;

default:
_severity = "UNKNOWN";
break;
}
char* _type2 = _type.data();
char* _severity2 = _severity.data();
char* _source2 = _source.data();

printf("%d: %s of %s severity, raised from %s: %s\n",
id, _type2, _severity2, _source2, msg);
}

// During init, enable debug output

float quadVertices[] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f
};


int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920,1080,"V2 Yahooo",NULL,NULL);






    if (window == NULL)
    {

        std::cout << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to create GLAD" << std::endl;
        return -1;
    }




    const char* VertexShaderGrassSourceCSTR = "#version 330 core\n"
                                              "\n"
                                              "\n"
                                              "layout (location = 0)  in vec3 aPos;\n"
                                              "layout (location = 1) in vec2 aTexCoord;\n"
                                              "out vec2  TexCoord;\n"
                                              "void main() {\n"
                                              "    gl_Position = vec4(aPos, 1.0);\n"
                                              "    TexCoord = aTexCoord;\n"
                                              "}";
    unsigned int VertexShaderGrass;
    VertexShaderGrass = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderGrass,1,&VertexShaderGrassSourceCSTR,NULL);
    glCompileShader(VertexShaderGrass);


    const char* FragmentShaderSourceCSTRGrass = "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "in vec2 TexCoord;\n"
                                                "uniform sampler2D Texture;\n"
                                                "void main() {\n"
                                                "    FragColor = vec4(1.0f,1.0f,1.0f,1.0f);\n"
                                                "\n"
                                                "}";
    unsigned int FragmentShaderGrass;
    FragmentShaderGrass = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(FragmentShaderGrass,1,&FragmentShaderSourceCSTRGrass,NULL);
    glCompileShader(FragmentShaderGrass);


    //Basically Creates the shader program the shader program attaches all fragment and vertex shaders and is what makes it work all shaders attached to a program when used will be executed

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    unsigned int ShaderProgramGrass;
    ShaderProgramGrass= glCreateProgram();
    glAttachShader(ShaderProgramGrass,VertexShaderGrass);
    glAttachShader(ShaderProgramGrass,FragmentShaderGrass);
    glLinkProgram(ShaderProgramGrass);

    glDeleteShader(VertexShaderGrass);
    glDeleteShader(FragmentShaderGrass);



    unsigned int VAOQuad;
    unsigned int VBOQuad;
    glGenVertexArrays(1,&VAOQuad);
    glGenVertexArrays(1,&VBOQuad);
    glBindVertexArray(VAOQuad);
    glBindBuffer(GL_ARRAY_BUFFER,VBOQuad);

    glBufferData(GL_ARRAY_BUFFER,sizeof(quadVertices),quadVertices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,2 ,GL_FLOAT,GL_FALSE,4 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,2 ,GL_FLOAT,GL_FALSE,4 * sizeof(float),(void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);




    while (!glfwWindowShouldClose(window))
    {

        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);


        glDebugMessageCallback(GLDebugMessageCallback, NULL);

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.529, 0.808, 0.922,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);




        glUseProgram(ShaderProgramGrass);
        glBindBuffer(GL_ARRAY_BUFFER,VBOQuad);
        glBindVertexArray(VAOQuad);

        glDrawArrays(GL_TRIANGLES,0,6);





        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}