#include "scene.hpp"
#include <iostream>

SceneNode::SceneNode(const std::string& name)
: m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::rotate(char axis, double angle)
{
	std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << angle << std::endl;
	// Fill me in
}

void SceneNode::scale(const Vector3D& amount)
{
	std::cerr << "Stub: Scale " << m_name << " by " << amount << std::endl;
	// Fill me in
}

void SceneNode::translate(const Vector3D& amount)
{
	std::cerr << "Stub: Translate " << m_name << " by " << amount << std::endl;
	// Fill me in
}

bool SceneNode::is_joint() const
{
	return false;
}

int SceneNode::rayTracing(Point3D eye, Point3D p_world, pixel& p)
{
	pixel temp;
	int retVal = 0;
	for (std::list<SceneNode*>::const_iterator i = m_children.begin(); i != m_children.end(); ++i) {
		if ( (*i)->rayTracing(eye,  p_world, temp)) {
			retVal = 1;
			if ( p.z_buffer == 0 || p.z_buffer > temp.z_buffer ) {
				p = temp;
			}
		}
	}
	return retVal;
}

JointNode::JointNode(const std::string& name)
: SceneNode(name)
{
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
	return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
	m_joint_x.min = min;
	m_joint_x.init = init;
	m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
	m_joint_y.min = min;
	m_joint_y.init = init;
	m_joint_y.max = max;
}

	GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
: SceneNode(name),
	m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}

int GeometryNode::rayTracing(Point3D eye, Point3D p_world, pixel& p)
{
	int retVal = 0;
	pixel temp;
	m_primitive->setMaterial(m_material);
	if ( m_primitive->rayTracing(eye, p_world, temp)) {
		retVal = 1;
		p = temp;
	}
	if ( SceneNode::rayTracing(eye, p_world, temp)) {
		retVal = 1;
		if (p.z_buffer > temp.z_buffer) {
			p = temp;
		}
	}
	return retVal;
}
