#include "morphosis.h"

void 						framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
    glViewport(0, 0, width, height);
}

void 						processInput(GLFWwindow *window, t_gl *gl)
{
	static int key_states[GLFW_KEY_LAST] = {0}; // Track key states to prevent repeat
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		gl->export = 1;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	// Color scheme changes (1-6 keys)
	for (int i = GLFW_KEY_1; i <= GLFW_KEY_6; i++)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS && !key_states[i])
		{
			gl->color_scheme = i - GLFW_KEY_1;
			key_states[i] = 1;
		}
		else if (glfwGetKey(window, i) == GLFW_RELEASE)
			key_states[i] = 0;
	}
	
	// Wireframe toggle (W key)
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !key_states[GLFW_KEY_W])
	{
		gl->wireframe_mode = !gl->wireframe_mode;
		key_states[GLFW_KEY_W] = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
		key_states[GLFW_KEY_W] = 0;
	
	// Pause rotation (SPACE key)
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !key_states[GLFW_KEY_SPACE])
	{
		gl->rotation_paused = !gl->rotation_paused;
		key_states[GLFW_KEY_SPACE] = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		key_states[GLFW_KEY_SPACE] = 0;
	
	// Zoom controls (+ and - keys)
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) // + key
		gl->zoom_level *= 1.02f;
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) // - key
		gl->zoom_level *= 0.98f;
	
	// Clamp zoom level (reasonable range for FOV-based zoom)
	if (gl->zoom_level < 0.2f) gl->zoom_level = 0.2f;
	if (gl->zoom_level > 8.0f) gl->zoom_level = 8.0f;
	
	// Reset view (R key)
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !key_states[GLFW_KEY_R])
	{
		gl->zoom_level = 1.0f;
		gl->rotation_paused = 0;
		gl->color_scheme = 0;
		gl->wireframe_mode = 1;
		key_states[GLFW_KEY_R] = 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
		key_states[GLFW_KEY_R] = 0;
}

void 						init_gl(t_gl *gl)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_STENCIL_BITS, 8);

	gl->window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "Morphosis", NULL, NULL);
	glfwMakeContextCurrent(gl->window);
	glewExperimental = GL_TRUE;
	glewInit();
	if (!gl->window)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		exit (1);
	}
	glfwSetFramebufferSizeCallback(gl->window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
}

void						get_color_scheme(int scheme, float *r, float *g, float *b)
{
	static float colors[6][3] = {
		{0.878f, 0.761f, 0.176f}, // Original golden
		{0.176f, 0.878f, 0.761f}, // Cyan-green
		{0.761f, 0.176f, 0.878f}, // Purple-magenta
		{0.878f, 0.176f, 0.176f}, // Red
		{0.176f, 0.176f, 0.878f}, // Blue
		{0.878f, 0.878f, 0.176f}  // Yellow
	};
	
	int index = scheme % 6; // Ensure valid range
	*r = colors[index][0];
	*g = colors[index][1];
	*b = colors[index][2];
}

void						apply_color_scheme(t_gl *gl)
{
	float r, g, b;
	get_color_scheme(gl->color_scheme, &r, &g, &b);
	glUniform3f(gl->color_uniform, r, g, b);
}

void 						terminate_gl(t_gl *gl)
{
	glDeleteVertexArrays(1, &gl->vao);
	glDeleteBuffers(1, &gl->vbo);
	glDeleteProgram(gl->shaderProgram);
	glfwTerminate();
}
