# Morphosis Technical Reference

## Algorithm Overview

Morphosis is a 4D Julia Set fractal renderer that generates 3D visualizations of quaternion-based fractals using the marching cubes algorithm.

## Mathematical Foundation

### 4D Julia Sets
Julia sets are defined by the iterative formula: `z = z² + c`

In 4D quaternion space:
- `z = (x, y, z, w)` - 4D point being tested
- `c = (cx, cy, cz, cw)` - 4D constant defining the specific Julia set
- Iteration continues until |z| > threshold or max_iterations reached

### Quaternion Mathematics
Quaternions extend complex numbers to 4 dimensions:
- `q = w + xi + yj + zk`
- Multiplication: `(a + bi + cj + dk)(e + fi + gj + hk)`
- Implemented in `lib_complex.c`

### Marching Cubes Algorithm
Converts scalar field to triangular mesh:
1. Sample 4D Julia set on 3D grid
2. For each cube, determine surface configuration
3. Generate triangles based on lookup table
4. Interpolate vertex positions for smooth surfaces

## Core Functions

### Julia Set Sampling (`sample_julia.c`)
```c
float sample_4D_Julia(t_julia *julia, float3 pos)
```
- Evaluates Julia set at 3D position (4th dimension set to 0)
- Returns distance/value for marching cubes
- Uses quaternion arithmetic for iteration

### Point Cloud Generation (`point_cloud.c`)
```c
void calculate_point_cloud(t_data *data)
```
- Creates 3D sampling grid
- Calls Julia set evaluation for each point
- Stores scalar values for polygonization

### Polygonization (`polygonisation.c`)
```c
float3 **polygonise(float3 *v_pos, float *v_val, uint2 *pos, t_data *data)
```
- Implements marching cubes algorithm
- Generates triangle mesh from scalar field
- Uses lookup tables for cube configurations

## OpenGL Rendering Pipeline

### Initialization (`gl_init.c`)
- Sets up OpenGL context
- Loads and compiles shaders
- Creates vertex buffer objects

### Rendering Loop (`gl_draw.c`)
- Clears framebuffer
- Applies transformations
- Renders triangle mesh
- Handles user input

### Shaders
**Vertex Shader** (`shaders/vertex.shader`):
```glsl
#version 330 core
in vec3 pos;
uniform mat4 model, view, proj;
void main() {
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}
```

**Fragment Shader** (`shaders/fragment.shader`):
```glsl
#version 330 core
out vec4 color;
void main() {
    color = vec4(0.878f, 0.761f, 0.176f, 1.0f);
}
```

## File Formats

### Matrix Files (.mat)
Binary format containing:
- 6x6 integer matrix
- Converted to parameters via SHA256 hash
- Used with `-m` flag

### Poem Files
Text format for artistic parameter input:
- Parsed character by character
- Converted to binary representation
- Hash-based coordinate generation

### OBJ Export
Standard 3D model format:
- Vertex positions (`v x y z`)
- Face definitions (`f v1 v2 v3`)
- Compatible with 3D modeling software

## Performance Characteristics

### Grid Resolution
Controlled by `step_size` parameter:
- Smaller values = higher resolution, longer computation
- Typical range: 0.01 to 0.5
- Grid dimensions: `2.0 / step_size` per axis

### Memory Usage
- Point cloud: `(2/step_size)³ * 12 bytes` (position + value)
- Triangle mesh: Variable based on fractal complexity
- Typical: 1-100MB for standard parameters

### Computation Complexity
- Julia set evaluation: O(iterations * grid_points)
- Marching cubes: O(grid_cubes)
- Total: O(n³) where n = 2/step_size

## Parameter Tuning Guide

### Classic Julia Sets
```bash
# Complex branching structure
./morphosis 0.05 -0.8 0.156 0 0

./morphosis 0.08 -0.7 0.27015 0 0

./morphosis 0.1 -0.4 0.6 0 0
```

### Step Size Guidelines
- `0.01-0.03`: High detail, slow rendering
- `0.05-0.1`: Balanced quality/performance  
- `0.2-0.5`: Fast preview, lower detail

### Iteration Count
- `50-100`: Basic structure visible
- `100-200`: Good detail for most sets
- `500+`: Maximum detail, slow computation

## Troubleshooting Guide

### Common Issues
1. **Empty output**: Check step_size (too large) or iterations (too small)
2. **Memory errors**: Reduce grid resolution
3. **Slow performance**: Increase step_size or reduce iterations
4. **Missing triangles**: Verify marching cubes threshold

### Debug Configuration
Add to Makefile for debugging:
```makefile
FLAGS = -g -O0 -Wall -DDEBUG
```

## Data Structures

### Core Types (`structures.h`)
```c
typedef struct {
    float x, y, z;
} float3;

typedef struct {
    uint x, y;
} uint2;

typedef struct {
    float4 c;           // Julia set constant
    int max_iter;       // Maximum iterations
    float threshold;    // Escape threshold
} t_julia;
```

### Grid Organization
- **Point Cloud**: 3D array of scalar values sampled from Julia set
- **Vertex Buffer**: 8 vertices per cube (marching cubes requirement)
- **Triangle Mesh**: Generated triangles stored as `float3` arrays

### Memory Layout
```
Grid Point: [position(x,y,z)] -> [julia_value(float)]
Cube: [8_vertices] -> [triangle_list]
Final: [all_triangles] -> [OpenGL_buffer]
```

## Algorithm Flow

### 1. Initialization
1. Parse command line parameters
2. Initialize Julia set constants
3. Set up 3D sampling grid
4. Initialize OpenGL context

### 2. Computation Phase
1. **Grid Sampling**: For each 3D grid point, evaluate Julia set
2. **Polygonization**: Apply marching cubes to generate triangles
3. **Buffer Creation**: Transfer triangle data to OpenGL buffers

### 3. Rendering Loop
1. **Clear buffers**
2. **Apply transformations** (model, view, projection matrices)
3. **Render triangles** using vertex/fragment shaders
4. **Handle input** (ESC to exit, S to save)
5. **Swap buffers** and repeat

