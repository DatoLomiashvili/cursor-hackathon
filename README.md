# Morphosis - 4D Julia Set Fractal Renderer 🌌

This is a 3D fractal rendering application that generates and displays 4D Julia sets using OpenGL.

## 🎯 Hackathon Task Overview

Welcome to the **Cursor Reverse Engineering Challenge**! 

This task simulates a real-world scenario where you're given a legacy codebase that has fallen into disrepair. Your mission is to understand the codebase and revive the algorithm, identify and fix issues, optimize performance, and potentially add new features.


## 🏆 Success Criteria (Tiered System)

You must demonstrate deep code understanding and create comprehensive documentation for each tier achieved.

### Tier 1: Make It Launch 🚀
**Objective**: Get the code compiling and running successfully
- Fix compilation errors and runtime failures
- Ensure the basic functionale works
- Document all issues found and fixes applied
- Create code documentation explaining the core algorithms

### Tier 2: Optimize Performance ⚡️
**Objective**: Improve code efficiency and maintainability
- Identify and resolve performance bottlenecks
- Clean up code inconsistencies and technical debt
- Implement optimizations while preserving functionality
- Document optimization decisions and their impact

### Tier 3: Add Features ✨
**Objective**: Extend functionality with new capabilities
- ✅ **Interactive Color Schemes**: Six beautiful color themes accessible via number keys
- ✅ **Rendering Mode Toggle**: Switch between wireframe and solid rendering
- ✅ **Rotation Control**: Pause/unpause automatic rotation for detailed examination  
- ✅ **Zoom Controls**: Smooth zoom in/out with +/- keys
- ✅ **Reset Functionality**: Instant reset to default view settings
- Dynamic rendering? Variations and new types? Deep zooms? Scan-line algo and raytracing?
- Add user interface improvements or configuration options
- Enhance the mathematical algorithms
- Document new features and their implementation

## 🎯 Participant Goals

1. **Fix the Code**: Identify and resolve all issues preventing successful execution
2. **Understand the Logic**: Demonstrate comprehension of the algorithms
3. **Create Documentation**: Produce comprehensive documentation of:
   - Code structure and algorithms
   - Issues found and solutions implemented
   - Optimization decisions and their rationale
   - Any new features added

## 🛠 Getting Started

### Prerequisites
- C compiler (GCC/Clang recommended)
- OpenGL development libraries
- GLFW library
- OpenSSL for matrix hashing
- Build system (Make)

## ⚡ Performance Features

This implementation includes comprehensive performance optimizations that significantly improve fractal generation speed and efficiency. 

**For detailed technical information**: See [Performance Optimizations](docs/commits/02-performance-optimizations.md)

## 🔍 Common Challenges You'll Encounter

As you work through this codebase, you may encounter several types of issues:

- Build System Configuration
- OpenGL Context Setup
- Mathematical Precision
- Memory Management
- Performance Bottlenecks

Remember: The core algorithms are mathematically sound - focus on implementation and optimization!

## 🚀 BUILD AND RUN

### Install Dependencies:
```bash
brew install glfw glew cglm pkg-config openssl
```

### Build (Optimized):
```bash
make clean && make
```

The build system includes comprehensive optimizations for maximum performance.

### Usage:
```bash
# Use default parameters
./morphosis -d

# Custom Julia set parameters
./morphosis <step_size> <q.x> <q.y> <q.z> <q.w>
# Example: ./morphosis 0.1 -0.7 0.27015 0 0

# Read from matrix file
./morphosis -m <matrix_file.mat>

# Read from poem file
./morphosis -p <poem_file>
```

### Controls:
- **ESC**: Exit the application
- **S**: Save and export the fractal as an OBJ file

### Interactive Controls:
- **1-6**: Change color schemes (Golden, Cyan-Green, Purple-Magenta, Red, Blue, Yellow)
- **W**: Toggle between wireframe and solid rendering
- **SPACE**: Pause/unpause automatic rotation
- **+ / -**: Zoom in/out (use = key for +)
- **R**: Reset view (zoom, rotation, color, wireframe mode)

### Example Commands:
```bash
# Classic Julia set
echo "100" | ./morphosis 0.05 -0.8 0.156 0 0

# Spiral patterns
echo "150" | ./morphosis 0.08 -0.7 0.27015 0 0

# Default parameters
./morphosis -d
```

## 🏗 TECHNICAL ARCHITECTURE

### Core Components:
1. **Julia Set Mathematics** (`sample_julia.c`, `lib_complex.c`)
   - 4D quaternion-based Julia set calculation
   - Configurable iteration limits and threshold values

2. **Point Cloud Generation** (`point_cloud.c`, `build_fractal.c`)
   - 3D grid sampling of 4D Julia set
   - Marching cubes polygonization algorithm

3. **OpenGL Rendering** (`gl_*.c` files)
   - Real-time 3D visualization
   - Shader-based rendering pipeline
   - Interactive camera controls

4. **File I/O** (`matrix_*.c`, `write_obj.c`)
   - Matrix-based parameter input
   - OBJ file export for 3D printing/modeling
   - SHA256-based coordinate generation

### File Structure:
```
├── srcs/           # Source code
├── includes/       # Header files
├── shaders/        # GLSL shader files
├── libft/          # Custom library headers
├── docs/           # Documentation and commit history
└── Makefile        # Build configuration
```

## 📋 Documentation & Development History

### Recent Updates
- [Performance Optimizations v2.0](docs/commits/02-performance-optimizations.md) - Comprehensive performance improvements
- [Restoration Fixes v1.0](docs/commits/01-restoration-fixes.md) - Initial codebase restoration and fixes

### Technical Reference
- [TECHNICAL_REFERENCE.md](TECHNICAL_REFERENCE.md) - Complete technical documentation and algorithms
- [CHANGELOG.md](CHANGELOG.md) - Chronological index of all changes

## 📋 Submission Requirements

For each tier you complete, submit:

1. **Working Code**: The fixed/optimized/enhanced codebase
2. **Documentation**:
   - Code comments and README updates
   - Technical documentation explaining algorithms
   - Change log documenting all modifications
   - Performance analysis (for Tier 2+)
3. **Demonstration**: Screenshots/videos of the working application
4. **Process Documentation**: Description of your debugging process and problem-solving approach

## 🏅 Winner Selection Criteria

Winners will be selected based on:

1. **Code Quality**: Clean, well-documented, and maintainable solutions
2. **Technical Depth**: Demonstrated understanding of algorithms and optimizations
3. **Documentation Excellence**: Comprehensive and clear documentation
4. **Innovation**: Creative solutions and feature additions (Tier 3)
5. **Efficiency**: Performance improvements and optimization quality (Tier 2+)

## 💡 Tips for Success

1. **Start Small**: Understand what you are working with, begin with compilation issues before tackling optimizations
2. **Document As You Go**: Keep detailed notes of problems and solutions
3. **Test Frequently**: Run the application after each major change
4. **Read the Code**: Understand the algorithms before making changes
5. **Version Control**: Use git to track your changes and revert if needed

**Good luck!** 🌌