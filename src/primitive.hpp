#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include <vector>
#include "algebra.hpp"
#include "material.hpp"
#include "image.hpp"

class Primitive {
	public:
		virtual ~Primitive();
		void setMaterial(Material* m)
		{
			m_material = m;
		}

		virtual void rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img) = 0;

	protected:
		Material*  m_material;	
};

class Sphere : public Primitive {
	public:
		virtual ~Sphere();
		virtual void rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img)
		{}
};

class Cube : public Primitive {
	public:
		virtual ~Cube();
		virtual void rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img){}
};

class NonhierSphere : public Primitive {
	public:
		NonhierSphere(const Point3D& pos, double radius)
			: m_pos(pos), m_radius(radius)
		{
		}
		virtual ~NonhierSphere();

		virtual void rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img);

		Point3D getPosition()
		{
			return m_pos;
		}

		double getRadius()
		{
			return m_radius;
		}


	private:
		Point3D m_pos;
		double m_radius;
};

class NonhierBox : public Primitive {
	public:
		NonhierBox(const Point3D& pos, double size);

		virtual ~NonhierBox();
		virtual void rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img);

	private:
		Point3D m_pos;
		double m_size;

		std::vector<Point3D> m_verts;
		std::vector< std::vector<int> > m_faces;
};

#endif
