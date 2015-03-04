#include "a4.hpp"
#include "image.hpp"

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights
               )
{
  // Fill in raytracing code here.

  std::cerr << "Stub: a4_render(" << root << ",\n     "
            << filename << ", " << width << ", " << height << ",\n     "
            << eye << ", " << view << ", " << up << ", " << fov << ",\n     "
            << ambient << ",\n     {";

  for (std::list<Light*>::const_iterator I = lights.begin(); I != lights.end(); ++I) {
    if (I != lights.begin()) std::cerr << ", ";
    std::cerr << **I;
  }
  std::cerr << "});" << std::endl;

  Image img(width, height, 3);

  Point3D p_world;

  for (int y = 0; y < height; y++) {
	 for (int x = 0; x < width; x++) {
		// for each pixel, find the p_world that is corresponding to the pixel (x, y).
		Point3D p_screen(x, y, 0);

		// step 1. translate
		p_screen[0] = (double)width / 2 - (double)x ;
		p_screen[1] = (double)height / 2 - (double)y;
		p_screen[2] = (double)1 / (double)std::tan(fov * M_PI / 180.0);


		// step 2. Scale
		p_screen[0] = p_screen[0] / (double)height / 2;
		p_screen[1] = p_screen[1] / (double)height / 2;


		// step 3. Rotate
		double l;
		// w
		Vector3D w = view;
		w.normalize();

		// m
		Vector3D m = up.cross(w);
		m.normalize();

		// v
		Vector3D v = w.cross(m);
		v.normalize();
		
		Vector4D w_4d(w[0], w[1], w[2], 0);
		Vector4D m_4d(m[0], m[1], m[2], 0);
		Vector4D v_4d(v[0], v[1], v[2], 0);

		Matrix4x4 rotation(m_4d, v_4d, w_4d, Vector4D(0, 0, 0, 1));
		rotation = rotation.transpose();

		p_screen = rotation * p_screen;

		// step 4.translate
		p_world[0] = p_screen[0] + eye[0];
		p_world[1] = p_screen[1] + eye[1];
		p_world[2] = p_screen[2] + eye[2];

		std::cerr << "p_world = " << p_world << std::endl;

		root->rayTracing(eye, Point3D(x, y, 0), p_world, &img);
	 }
  }

  img( 1, 1, 0) = 1;
  img.savePng(filename);  
  // For now, just make a sample image.

//  Image img(width, height, 3);
//
//  for (int y = 0; y < height; y++) {
//    for (int x = 0; x < height; x++) {
//      // Red: increasing from top to bottom
//      img(x, y, 0) = (double)y / height;
//      // Green: increasing from left to right
//      img(x, y, 1) = (double)x / width;
//      // Blue: in lower-left and upper-right corners
//      img(x, y, 2) = ((y < height/2 && x < height/2)
//                      || (y >= height/2 && x >= height/2)) ? 1.0 : 0.0;
//    }
//  }
//  img.savePng(filename);
  
}
