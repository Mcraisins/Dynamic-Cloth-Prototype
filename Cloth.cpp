#include "Cloth.h"

Cloth::Cloth()
{
	this->vao_vertices.clear();
	this->veo_indices.clear();
	this->indexed_faces.clear();

	this->ori_positions.clear();
	this->ori_normals.clear();
	this->ori_texcoords.clear();

	this->masses.clear();
	this->springs.clear();
}

void Cloth::build()
{
	this->vao_vertices.clear();
	this->veo_indices.clear();
	this->indexed_faces.clear();

	this->ori_positions.clear();
	this->ori_normals.clear();
	this->ori_texcoords.clear();

	if(!built)
	{
		for(int i = 0; i < height; i++)
			for(int j = 0; j < width; j++)
			{
				masses.push_back(Mass(startpos.x + float(j) * float(spacing), startpos.y, startpos.z + float(i) * float(spacing), mass, dampcon, false));
			}

		std::vector<Dir> dirs = { CR, DW };
		for(int i = 0; i < masses.size(); i++)
		{
			for(Dir d : dirs)
				if(-1 < To(i, d) && To(i, d) < masses.size())
					springs.push_back(Spring(&masses[i], &masses[To(i, d)], springcon, dampcon, glm::distance(masses[i].pos, masses[To(i, d)].pos)));
		}
	}

	for(int i = 0; i < masses.size(); i++)
		ori_positions.push_back(masses[i].pos);
	for(int i : fixed)
		masses[i].fixed = true;

	for(int i = 0; i < width-1; i++)
	{
		for(int j = 0; j < height-1; j++)
		{
			Face_Index face_idx;
			for(int k = 0; k < 3; k++) {
				if(k == 0)
					face_idx.vertex[k].pos_idx = j * width + i + 1;
				if(k == 1)
					face_idx.vertex[k].pos_idx = (j + 1) * width + i + 1;
				if(k == 2)
					face_idx.vertex[k].pos_idx = (j + 1) * width + i;

				face_idx.vertex[k].texcoord_idx = -1;
				face_idx.vertex[k].normal_idx = -1;
			}
			indexed_faces.push_back(face_idx);

			for(int k = 0; k < 3; k++) {
				if(k == 0)
					face_idx.vertex[k].pos_idx = j * width + i;
				if(k == 1)
					face_idx.vertex[k].pos_idx = j * width + i + 1; 
				if(k == 2)
					face_idx.vertex[k].pos_idx = (j+1) * width + i;

				face_idx.vertex[k].texcoord_idx = -1;
				face_idx.vertex[k].normal_idx = -1;
			}
			indexed_faces.push_back(face_idx);

			
		}
	}

	// Retrieve data from index and assign to vao and veo
	for(int i = 0; i < indexed_faces.size(); i++) {
		Face_Index cur_idx_face = indexed_faces[i];
		// If no normal: recalculate for them
		glm::vec3 v0 = ori_positions[cur_idx_face.vertex[0].pos_idx];
		glm::vec3 v1 = ori_positions[cur_idx_face.vertex[1].pos_idx];
		glm::vec3 v2 = ori_positions[cur_idx_face.vertex[2].pos_idx];
		glm::vec3 new_normal = glm::cross(v1 - v0, v2 - v0);

		for(int j = 0; j < 3; j++) {
			Vertex cur_vertex;
			Vertex_Index cur_idx_vertex = cur_idx_face.vertex[j];
			if(cur_idx_vertex.pos_idx >= 0) {
				cur_vertex.Position = ori_positions[cur_idx_vertex.pos_idx];
			}
			cur_vertex.Normal = new_normal;
			vao_vertices.push_back(cur_vertex);
			veo_indices.push_back(i * 3 + j);
		}
	}

	obj_name = "cloth";
	calculate_center();

	m_obj_type = OBJ_TRIANGLES;
	m_render_type = RENDER_TRIANGLES;
	built = true;
}

void Cloth::update(float delta)
{
	if(!built) return;

	for(int i = 0; i < masses.size(); i++)
		masses[i].force = glm::vec3(0, gravity*masses[i].mass*delta, 0);
	for(int i = 0; i < springs.size(); i++) springs[i].update();
	for(int i = 0; i < masses.size(); i++) masses[i].update(delta, verlet);

	build();
};

int Cloth::To(int i, Dir d)
{
	switch(d)
	{
	case UR: return i - width + 1;
	case UP: return i - width;
	case UL: return i - width - 1;
	case CR: return i + 1;
	case CL: return i - 1;
	case DR: return i + width + 1;
	case DW: return i + width;
	case DL: return i + width - 1;
	}
}