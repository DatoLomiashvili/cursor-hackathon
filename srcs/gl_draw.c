#include "morphosis.h"

void 						run_graphics(t_gl *gl, float3 max, float3 min)
{
	gl_scale_tris(gl, max, min);

	init_gl(gl);
	createVAO(gl);
	createVBO(gl, gl->num_pts * sizeof(float), (GLfloat *)gl->tris);

	makeShaderProgram(gl);
	gl_set_attrib_ptr(gl, "pos", 3,3, 0);
	gl_calc_transforms(gl);
	gl_render(gl);

	terminate_gl(gl);
}

void							gl_render(t_gl *gl)
{
	float 					time;
	float					delta;
	float 					old_time;

	old_time = 0;
	while (!glfwWindowShouldClose(gl->window))
	{
		processInput(gl->window, gl);

		// Set polygon mode based on wireframe setting
		if (gl->wireframe_mode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glClearColor(0.05f, 0.05f, 0.1f, 1.0f); // Slightly better background
		glClear(GL_COLOR_BUFFER_BIT);

		time = (float)glfwGetTime();
		delta = (time - old_time);
		
		// Apply rotation only if not paused
		if (!gl->rotation_paused)
		{
			glm_mat4_identity(gl->matrix->model_mat);
			glm_rotate(gl->matrix->model_mat, (0.25f * delta * glm_rad(180.0f)), gl->matrix->up);
			glUniformMatrix4fv(gl->matrix->model, 1, GL_FALSE, (float *)gl->matrix->model_mat);
			glm_rotate(gl->matrix->view_mat, (0.25f * delta * glm_rad(180.0f)), gl->matrix->up);
			glUniformMatrix4fv(gl->matrix->view, 1, GL_FALSE, (float *)gl->matrix->view_mat);
		}
		old_time = time;
		
		// Apply zoom by adjusting field of view
		float fov = 45.0f / gl->zoom_level; // Inverse relationship for intuitive zoom
		// Clamp FOV to reasonable range (5 to 120 degrees)
		if (fov < 5.0f) fov = 5.0f;
		if (fov > 120.0f) fov = 120.0f;
		
		mat4 zoom_proj;
		glm_perspective(glm_rad(fov), (float)SRC_WIDTH / (float)SRC_HEIGHT, 1.0f, 10.0f, zoom_proj);
		GLuint projection = glGetUniformLocation(gl->shaderProgram, "proj");
		glUniformMatrix4fv(projection, 1, GL_FALSE, (float *)zoom_proj);
		
		// Apply current color scheme
		apply_color_scheme(gl);

		glDrawArrays(GL_TRIANGLES, 0, gl->num_pts);

		glfwSwapBuffers(gl->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
