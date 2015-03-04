-- A polygonal approximation to a cylinder
mat1 = gr.material({1.0, 0.0, 0.0}, {0.5, 0.7, 0.5}, 25)

scene_root = gr.node('root')

cyl = gr.mesh('cylinder', {
	{0.000000, 0.000000, 1.000000},
	{0.587785, 0.000000, 0.809017},
	{0.951057, 0.000000, 0.309017},
	{0.951057, 0.000000, -0.309017},
	{0.587785, 0.000000, -0.809017},
	{0.000000, 0.000000, -1.000000},
	{-0.587785, 0.000000, -0.809017},
	{-0.951057, 0.000000, -0.309017},
	{-0.951057, 0.000000, 0.309017},
	{-0.587785, 0.000000, 0.809017},
	{0.000000, 1.000000, 1.000000},
	{0.587785, 1.000000, 0.809017},
	{0.951057, 1.000000, 0.309017},
	{0.951057, 1.000000, -0.309017},
	{0.587785, 1.000000, -0.809017},
	{0.000000, 1.000000, -1.000000},
	{-0.587785, 1.000000, -0.809017},
	{-0.951057, 1.000000, -0.309017},
	{-0.951057, 1.000000, 0.309017},
	{-0.587785, 1.000000, 0.809017}
     }, {
	{0, 1, 11, 10},
	{1, 2, 12, 11},
	{2, 3, 13, 12},
	{3, 4, 14, 13},
	{4, 5, 15, 14},
	{5, 6, 16, 15},
	{6, 7, 17, 16},
	{7, 8, 18, 17},
	{8, 9, 19, 18},
	{9, 0, 10, 19},
	{9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	{10, 11, 12, 13, 14, 15, 16, 17, 18, 19}
     })
scene_root:add_child(cyl);
cyl:set_material(mat1);

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
orange_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})

gr.render(scene_root, 'cylinder.png', 500, 500, {-5, -5, -5}, {-1, -1, -1}, {-1, 1, -1}, 50, {0.3, 0.3, 0.3}, {white_light, orange_light}) 