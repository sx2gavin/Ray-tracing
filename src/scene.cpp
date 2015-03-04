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

void SceneNode::rayTracing(Point3D eye, Point3D p_screen,  Point3D p_world, Image* img)
{
	for (std::list<SceneNode*>::const_iterator i = m_children.begin(); i != m_children.end(); ++i) {
		(*i)->rayTracing(eye, p_screen,  p_world, img);
	}
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

void GeometryNode::rayTracing(Point3D eye, Point3D p_screen, Point3D p_world, Image* img)
{
	m_primitive->setMaterial(m_material);
	m_primitive->rayTracing(eye, p_screen, p_world, img);	
	SceneNode::rayTracing(eye, p_screen, p_world, img);
}
