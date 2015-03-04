#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
}

int Mesh::rayTracing(Point3D eye, Point3D p_world, Colour ambient, std::list<Light*> lights, pixel& p)
{
	int retVal = 0; 
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
		
	for (std::vector<Mesh::Face>::const_iterator I = m_faces.begin(); I != m_faces.end(); ++I) {
		for (Face::const_iterator J = I->begin(); J != I->end() - 2; ++J) {

			p0 = m_verts[(*I)[0]];
			// p1 = m_verts[(*I)[1]];
			// p2 = m_verts[(*I)[2]];
			p1 = m_verts[*(J + 1)];
			p2 = m_verts[*(J + 2)];

			n = (p1 - p0).cross(p2 - p0);
			//num = - n.dot(eye - p0);

			// std::cerr << "n = " << n << std::endl;
			den = n.dot(p_world - eye);

			// std::cerr << "den = " << den << std::endl;
			// if the ray doesn't hit the plane represented by the triangle.
			if (den == 0) break;

			x1 = p1[0] - p0[0];
			x2 = p2[0] - p0[0];
			x3 = - p_world[0] + eye[0];
			r1 = eye[0] - p0[0];

			y1 = p1[1] - p0[1];
			y2 = p2[1] - p0[1];
			y3 = - p_world[1] + eye[1];
			r2 = eye[1] - p0[1];

			z1 = p1[2] - p0[2];
			z2 = p2[2] - p0[2];
			z3 = - p_world[2] + eye[2];
			r3 = eye[2] - p0[2];

			d = det(x1, x2, x3, y1, y2, y3, z1, z2, z3);
			d1 = det(r1, x2, x3, r2, y2, y3, r3, z2, z3);
			d2 = det(x1, r1, x3, y1, r2, y3, z1, r3, z3);
			d3= det(x1, x2, r1, y1, y2, r2, z1, z2, r3);

			beta = d1 / d;
			gamma = d2 / d;
			t = d3 / d;

			// std::cerr << "beta = " << beta << ", gamma = " << gamma << ", t = " << t << std::endl;

			if ( beta >= 0 && gamma >= 0 && (beta + gamma) <= 1 && t > 0) {
				// the ray hits the triangle. 
				retVal = 1;
				if ( p.z_buffer == 0 || p.z_buffer > t ) {
					p.z_buffer = t;
					p.color = Colour(m_material->getDiffuseColor().R(), m_material->getDiffuseColor().G(),  m_material->getDiffuseColor().B());
				}
				// (*img)(p_screen[0], p_screen[1], 0) = m_material->getDiffuseColor().R();
				// (*img)(p_screen[0], p_screen[1], 1) = m_material->getDiffuseColor().G();
				// (*img)(p_screen[0], p_screen[1], 2) = m_material->getDiffuseColor().B();
				break;
			}
		}		
	}
	return retVal;
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
	std::cerr << "mesh({";
	for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
		if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
		std::cerr << *I;
	}
	std::cerr << "},\n\n     {";

	for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
		if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
		std::cerr << "[";
		for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
			if (J != I->begin()) std::cerr << ", ";
			std::cerr << *J;
		}
		std::cerr << "]";
	}
	std::cerr << "});" << std::endl;
	return out;
}

