#ifndef MODEL_H
#define MODEL_H

#include <cstdlib>
#include <cstdio>

#include "opengl_macro.h"
#include "image.h"

using namespace std;

int load_texture(const char *filename) {
	// create Storage Space For The Texture
	image *img;										
	// texture id
	unsigned int texture = 0;
	// loads The Bitmap Specified By filename
	img = load_bmp(filename);									

	// load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (img != NULL && img->pixels != NULL) {
		// create texture
		gl_gen_textures(1, &texture);									
		// typical Texture Generation Using Data From The Bitmap
		gl_bind_textures(GL_TEXTURE_2D, texture);
		gl_text_image_2d(GL_TEXTURE_2D, 0, 3, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
		gl_text_parameter_i(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		gl_text_parameter_i(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		delete img;
		img = NULL;
	}
	return texture;
}

class model {
public:
	struct mesh {
		int material_index;
		int no_triangles;
		int *triangle_indices;
	};

    struct no_materials {
		float ambient[4];
		float diffuse[4];
		float specular[4];
		float emissive[4];
		float shininess;
		int texture;
		char *texture_filename;
	};

	struct triangle {
		float vertex_normals[3][3];
		float m_s[3], m_t[3];
		int vertex_indices[3];
	};

	struct vertex {
		char bone_id;	// for skeletal animation
		float location[3];
	};

public:
	model() {
		no_meshes = 0;
		meshes = NULL;
		no_materials = 0;
		materials = NULL;
		no_triangles = 0;
		triangles = NULL;
		no_vertices = 0;
		vertices = NULL;
	}

	virtual ~model() {
		int i;
		for (i = 0; i < no_meshes; ++i) {
			delete[] meshes[i].triangle_indices;
		}
		for ( i = 0; i < no_materials; i++ ) {
			delete[] materials[i].texture_filename;
		}

		no_meshes = 0;
		if (meshes != NULL) {
			delete[] meshes;
			meshes = NULL;
		}

		no_materials = 0;
		if (materials != NULL) {
			delete[] materials;
			materials = NULL;
		}

		no_triangles = 0;
		if (triangles != NULL) {
			delete[] triangles;
			triangles = NULL;
		}

		no_vertices = 0;
		if (vertices != NULL) {
			delete[] vertices;
			vertices = NULL;
		}
	}
		
	virtual bool load_model(const char *filename) = 0;
	void draw();
	void reload_textures() {
		for (int i = 0; i < no_materials; ++i) {
			if (strlen(materials[i].texture_filename) > 0 ) {
				materials[i].texture = load_texture(materials[i].texture_filename);
			} else {
				materials[i].texture = 0;
			}
		}
	}

protected:
	int no_meshes;
	mesh *meshes;

	int no_materials;
	material *materials;

	int no_triangles;
	triangle *triangles;

	int no_vertices;
	vertex *vertices;
};

#endif // ndef MODEL_H
