#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include <list>
#include <vector>
#include "algebra.hpp"
#include "material.hpp"
#include "image.hpp"
#include "light.hpp"
#include "pixel.hpp"

class Primitive {
	public:
		virtual ~Primitive();
		void setMaterial(Material* m)
		{
			m_material = m;
		}
		virtual void transform(const Matrix4x4 t){}

		virtual int rayTracing(Point3D eye, Point3D p_world,  pixel& p) = 0;

	protected:
		Material*  m_material;	
};

class Sphere : public Primitive {
	public:
		virtual ~Sphere();
		virtual int rayTracing(Point3D eye, Point3D p_world,  pixel& p)
		{}
		std::vector<Point3D> m_verts;
		std::vector< std::vector<int> > m_faces;
};

class Cube : public Primitive {
	public:
		Cube();
		virtual ~Cube();
		virtual int rayTracing(Point3D eye, Point3D p_world,  pixel& p);
		virtual void transform(const Matrix4x4 t);
	private:
		std::vector<Point3D> m_trans_verts;
		std::vector<Point3D> m_verts;
		std::vector< std::vector<int> > m_faces;
};

class NonhierSphere : public Primitive {
	public:
		NonhierSphere(const Point3D& pos, double radius)
			: m_pos(pos), m_radius(radius)
		{
		}
		virtual ~NonhierSphere();

		virtual int rayTracing(Point3D eye, Point3D p_world,  pixel& p);

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
		virtual int rayTracing(Point3D eye, Point3D p_world,  pixel& p);

	private:
		Point3D m_pos;
		double m_size;

		std::vector<Point3D> m_verts;
		std::vector< std::vector<int> > m_faces;
};

#endif
