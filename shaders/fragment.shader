#version 330 core

uniform vec3            fractal_color;
out vec4                color;

void                    main()
{
    color = vec4(fractal_color, 1.0f);
}