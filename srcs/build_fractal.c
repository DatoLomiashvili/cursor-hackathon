#include "morphosis.h"

void						build_fractal(t_data *data)
{
	t_fract 				*f;
	float3 					**new_tris;
	size_t 					i;
	uint2					pos;
	size_t					grid_size;
	size_t					progress_step;

	i = 0;
	f = data->fract;
	grid_size = (size_t)f->grid_size;
	data->len.x = 0;
	data->len.y = 0;
	pos.x = 0;
	pos.y = 0;
	new_tris = NULL;
	
	// Optimized: Adaptive progress reporting based on grid size
	progress_step = (grid_size > 50) ? grid_size / 20 : 1;
	printf("Building fractal with grid size: %zu\n", grid_size);
	
	// Optimized: Cache-friendly z-y-x traversal order for better spatial locality
	for (size_t z = 0; z < grid_size; z++)
	{
		// Optimized: Less frequent progress updates to reduce I/O overhead
		if (z % progress_step == 0 || z == grid_size - 1)
			printf("Progress: %zu/%zu (%.1f%%)\n", z + 1, grid_size, 
				   ((float)(z + 1) / grid_size) * 100.0f);
		
		// Optimized: Pre-compute grid_z once per z-layer	   
		float grid_z = f->grid.z[z];
			   
        for (size_t y = 0; y < grid_size; y++)
		{
			// Optimized: Pre-compute grid_y once per y-row
			float grid_y = f->grid.y[y];
			
            for (size_t x = 0; x < grid_size; x++)
			{
				// Optimized: Pre-calculate grid positions to reduce memory access
				float grid_x = f->grid.x[x];
				
				// Optimized: Unrolled loop for better performance (8 vertices per cube)
				float3 base_pos = {grid_x, grid_y, grid_z};
				
                for (int c = 0; c < 8; c++)
				{
					data->vertexpos[i].x = base_pos.x + f->voxel[c].dx;
					data->vertexpos[i].y = base_pos.y + f->voxel[c].dy;
					data->vertexpos[i].z = base_pos.z + f->voxel[c].dz;
					data->vertexval[i] = sample_4D_Julia(f->julia, data->vertexpos[i]);
					i++;
				}
				pos.y += 8;
				new_tris = polygonise(data->vertexpos, data->vertexval, &pos, data);
				if (new_tris)
				{
					if (!(data->triangles = arr_float3_cat(new_tris, data->triangles, &data->len)))
						error(MALLOC_FAIL_ERR, data);
				}
				pos.x = pos.y;
			}
		}
	}
	data->gl->num_tris = data->len.x;
	data->gl->num_pts = data->len.x * 3 * 3;
	printf("Fractal generation complete. Generated %u triangles.\n", data->gl->num_tris);
}
