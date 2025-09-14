
typedef struct Vertex {
	Vec4f pos;
	Vec2f uv;
	Vec3f normal;

	Vec3f bary_coord;

	// perspective correction terms
	float inv_w;
	Vec2f uv_over_w;
	Vec3f normal_over_w;
} Vertex;

void triangle_calculate_bary_coords(float x, float y, Triangle* tri) {

	Vec3f result;

	Vec4f A = tri->A.pos;
	Vec4f B = tri->B.pos;
	Vec4f C = tri->C.pos;

	result.x = (A.x*(C.y-A.y)+(y-A.y)*(C.x-A.x)-x*(C.y-A.y))
			/((B.y-A.y)*(C.x-A.x)-(B.x-A.x)*(C.y-A.y));

	result.y = ((y-A.y) - alpha*(B.y-A.y))/(C.y-A.y);
	result.z = 1 - alpha - beta;

	return result;
}

Vertex vertex_create(Vec3f pos, Vec2f* uv, Vec3f* normal){
	Vertex v = {0};
	v.pos.x = pos->x;
	v.pos.y = pos->y;
	v.pos.z = pos->z;
	v.pos.w = 1.0f;

	if(uv != NULL) v.uv = *uv;
	if(normal != NULL) v.normal = *normal;
	return v;
}


void vertex_prep_perspective_correct_terms(Vertex* vertex) {
	//TODO
	return;
}

