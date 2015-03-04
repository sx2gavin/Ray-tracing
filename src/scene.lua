-- A polygonal approximation to a cylinder

mat1 = gr.material({1.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

triangle = gr.mesh('triangle', { {0.0000, 0.0000, 0.0000},
								 {0.0000, 1.0000, 0.0000},
								 {1.0000, 0.0000, 0.0000}},
							   { {0, 1, 2}})
scene_root:add_child(triangle);
triangle:set_material(mat1);

s1 = gr.nh_sphere('s1', {-1, 0, 0}, 0.5)
scene_root:add_child(s1)
s1:set_material(mat1)

s2 = gr.nh_box('s2', {0, -1, 0}, 0.5)
scene_root:add_child(s2)
s2:set_material(mat1)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})

gr.render(scene_root, 'triangle.png', 500, 500, {5, 5, 5}, {-1, -1, -1}, {-1, 1, -1}, 50, {0.3, 0.3, 0.3}, {white_light, orange_light}) 
