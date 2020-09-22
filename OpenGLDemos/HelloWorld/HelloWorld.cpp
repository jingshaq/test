#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#define GL_PRINT(S) printf("%s\n",#S)

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//将该窗口作为当前线程的主上下文
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册回调函数，这里是窗口大小改变时候调用framebuffer_size_callback，该函数还可以注册其他相关硬件的回调函数

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))//初始化glad库，只要用glad库都这么写，没什么可说的，glfwGetProcAddress这个函数返回指定的OpenGL或OpenGL ES核心或扩展函数的地址，如果它被当前上下文所支持的话。
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))//不阻塞，循环会一直执行
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);//交换缓冲区,这里用了双缓冲技术,用两个内存区域来保存数据,分为前缓冲区和后缓冲区,前缓冲区用于展示屏幕上的内容,而后缓冲区就用来绘制,然后每一帧开始的时候,将两个缓冲区交换,这样后缓冲区又可以画新的内容
		glfwPollEvents();//轮询事件（如: 鼠标键盘事件）
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	GL_PRINT("Window Resize!");
}