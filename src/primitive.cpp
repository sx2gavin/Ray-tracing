#include "primitive.hpp"
#include "polyroots.hpp"

Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}

Cube::~Cube()
{
}

NonhierSphere::~NonhierSphere()
{
}

void NonhierSphere::rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img) 
{
	// std::cerr << "p_world is " << p_world << std::endl;
	// std::cerr << "eye is " << eye << std::endl;
	// std::cerr << "m_pos is " << m_pos << std::endl;
	// std::cerr << "m_radius is " << m_radius << std::endl;

	double a = (p_world - eye).dot(p_world - eye);
	double b = 2 * (p_world - eye).dot(eye - m_pos);
	double c = (eye - m_pos).dot(eye - m_pos) - m_radius * m_radius;
	double roots[2]; 
	// std::cerr << "a is " << a << std::endl;
	// std::cerr << "b is " << b << std::endl;
	// std::cerr << "c is " << c << std::endl;
	
	if (quadraticRoots(a, b, c, roots) >= 1) {	
		std::cerr << "drawing the sphere" << std::endl;
		(*img)(p_screen[0], p_screen[1], 0) = m_material->getDiffuseColor().R();
		(*img)(p_screen[0], p_screen[1], 1) = m_material->getDiffuseColor().G();
		(*img)(p_screen[0], p_screen[1], 2) = m_material->getDiffuseColor().B();
	}
}

NonhierBox::NonhierBox(const Point3D& pos, double size)
: m_pos(pos), m_size(size)
{
	for (double x = m_pos[0]; x <= m_pos[0] + size; x += size) {
		for (double y = m_pos[1]; y <= m_pos[1] + size; y += size) {
			for (double z = m_pos[2]; z <= m_pos[2] + size; z += size) {
				m_verts.push_back(Point3D(x, y, z));
			}
		}
	}

	for ( std::vector<Point3D>::const_iterator I = m_verts.begin(); I != m_verts.end(); ++I) {
		std::cerr << *I << std::endl;
	}
	
	m_faces.resize(6);
	for (int i = 0; i < 6; i++) {
		m_faces[i].resize(4);
	}
	
	m_faces[0][0] = 0;
	m_faces[0][1] = 1;
	m_faces[0][2] = 3;
	m_faces[0][3] = 2;

	m_faces[1][0] = 0;
	m_faces[1][1] = 2;
	m_faces[1][2] = 6;
	m_faces[1][3] = 4;
		
	m_faces[2][0] = 0;
	m_faces[2][1] = 1;
	m_faces[2][2] = 5;
	m_faces[2][3] = 4;

	m_faces[3][0] = 7;
	m_faces[3][1] = 3;
	m_faces[3][2] = 2;
	m_faces[3][3] = 6;

	m_faces[4][0] = 7;
	m_faces[4][1] = 3;
	m_faces[4][2] = 1;
	m_faces[4][3] = 5;

	m_faces[5][0] = 7;
	m_faces[5][1] = 6;
	m_faces[5][2] = 4;
	m_faces[5][3] = 5;
}

NonhierBox::~NonhierBox()
{
}

void NonhierBox::rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img)
{
	
	// std::cerr << " NohierBox ray tracer called" << std::endl;
	Point3D p0;
	Point3D p1;
	Point3D p2;
	Vector3D n;
	float num;
	float den;
	float x1;
	float x2;
	float x3;
	float r1;
	float y1;
	float y2;
	float y3;
	float r2;
	float z1;
	float z2;
	float z3;
	float r3;
	float d ;
	float d1;
	float d2;
	float d3;
	float beta;
	float gamma;
	float t;
		
	for (std::vector< std::vector<int> >::const_iterator I = m_faces.begin(); I != m_faces.end(); ++I) {
		for (std::vector<int>::const_iterator J = I->begin(); J != I->end() - 2; ++J) {
			// std::cerr << "point 1" << std::endl;
			p0 = m_verts[(*I)[0]];
			// std::cerr << "*(J + 1) = " << *(J + 1) << std::endl;
			p1 = m_verts[*(J + 1)];
			// std::cerr << "*(J + 2) = " << *(J + 2) << std::endl;
			p2 = m_verts[*(J + 2)];
			// std::cerr << "point 2" << std::endl;
			// p1 = m_verts[(*I)[1]];
			// p2 = m_verts[(*I)[2]];

			n = (p1 - p0).cross(p2 - p0);
			//num = - n.dot(eye - p0);

			// std::cerr << "n = " << n << std::endl;
			den = n.dot(p_world - eye);

			// std::cerr << "den = " << den << std::endl;
			// if the ray doesn't hit the plane represented by the triangle.
			if (den == 0) break;
			// std::cerr<< "point 3" << std::endl;

			x1 = p1[0] - p0[0];
			x2 = p2[0] - p0[0];
			x3 = p_world[0] - eye[0];
			r1 = eye[0] - p0[0];

			y1 = p1[1] - p0[1];
			y2 = p2[1] - p0[1];
			y3 = p_world[1] - eye[1];
			r2 = eye[1] - p0[1];

			z1 = p1[2] - p0[2];
			z2 = p2[2] - p0[2];
			z3 = p_world[2] - eye[2];
			r3 = eye[2] - p0[2];

			d = det(x1, x2, x3, y1, y2, y3, z1, z2, z3);
			d1 = det(r1, x2, x3, r2, y2, y3, r3, z2, z3);
			d2 = det(x1, r1, x3, y1, r2, y3, z1, r3, z3);
			d3= det(x1, x2, r1, y1, y2, r2, z1, z2, r3);

			beta = d1 / d;
			gamma = d2 / d;
			t = d3 / d;

			// std::cerr << "beta = " << beta << ", gamma = " << gamma << ", t = " << t << std::endl;

			if ( beta >= 0 && gamma >= 0 && (beta + gamma) <= 1) {
				// the ray hits the triangle. 
				(*img)(p_screen[0], p_screen[1], 0) = m_material->getDiffuseColor().R();
				(*img)(p_screen[0], p_screen[1], 1) = m_material->getDiffuseColor().G();
				(*img)(p_screen[0], p_screen[1], 2) = m_material->getDiffuseColor().B();
			}
		}
	}
}
