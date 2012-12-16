#ifndef OPENGL_MACRO_H
#define OPENGL_MACRO_H

/**
 * Purpose:
 *		1) Maintain consistency naming convention with 
 *		   the standard library C++
 *		2) Remember OpenGL api 
 */


/**
 * GLUT API
 */
#define glut_init					glutInit
#define glut_init_display_mode		glutInitDisplayMode
#define glut_init_window_size		glutInitWindowSize
#define glut_init_window_position	glutInitWindowPosition
#define glut_create_window			glutCreateWindow
#define glut_create_menu			glutCreateMenu
#define glut_main_loop				glutMainLoop
#define glut_reshape_func			glutReshapeFunc
#define glut_special_func			glutSpecialFunc
#define glut_display_func			glutDisplayFunc
#define glut_idle_func				glutIdleFunc
#define glut_timer_func				glutTimerFunc
#define glut_keyboard_func			glutKeyboardFunc
#define glut_keyboard_up_func		glutKeyboardUpFunc
#define glut_mouse_func				glutMouseFunc
#define glut_get_modifiers			glutGetModifiers

#define glut_add_menu_entry			glutAddMenuEntry
#define glut_create_menu			glutCreateMenu
#define glut_attach_menu			glutAttachMenu
#define glut_swap_buffers			glutSwapBuffers

#define glut_solid_cone				glutSolidCone
#define glut_wire_cone				glutWireCone

#define glut_solid_torus			glutSolidTorus
#define glut_wire_torus				glutWireTorus

#define glut_solid_cube				glutSolidCube
#define glut_wire_cube				glutWireCube

#define glut_solid_sphere			glutSolidSphere
#define glut_wire_sphere			glutWireSphere

#define glut_solid_teapot			glutSolidTeapot
#define glut_wire_teapot			glutWireTeapot

#define glut_solid_dodecahedron		glutSolidDodecahedron
#define glut_wire_dodecahedron		glutWireDodecahedron

#define glut_solid_icosahedron		glutSolidIcosahedron
#define glut_wire_icosahedron		glutWireIcosahedron

#define glut_solid_octahedron		glutSolidOctahedron
#define glut_wire_octahedron		glutWireOctahedron

#define glut_post_redisplay			glutPostRedisplay

#define glut_set_window				glutSetWindow
#define glut_set_window_title		glutSetWindowTitle
#define glut_destroy_window			glutDestroyWindow

#define glut_create_sub_window		glutCreateSubWindow
#define glut_set_color				glutSetColor
#define glut_set_cursor				glutSetCursor
#define glut_set_icon_title			glutSetIconTitle
#define glut_set_key_repeat			glutSetKeyRepeat
#define glut_destroy_menu			glutDestroyMenu
#define glut_set_menu				glutSetMenu
#define glut_get_menu				glutGetMenu
#define glut_add_sub_menu			glutAddSubMenu
#define glut_menu_state_func		glutMenuStateFunc
#define glut_menu_status_func		glutMenuStatusFunc
#define glut_position_window		glutPositionWindow
#define glut_pop_window				glutPopWindow
#define glut_reshape_window			glutReshapeWindow
#define glut_full_screen			glutFullScreen

#define glut_stroke_character		glutStrokeCharacter
#define glut_stroke_length			glutStrokeLength
#define glut_stroke_width			glutStrokeWidth

#define	glut_bitmap_character		glutBitmapCharacter
#define	glut_bitmap_length			glutBitmapLength
#define	glut_bitmap_width			glutBitmapWidth



/**
 * GLU API
 */
#define glu_look_at					gluLookAt
#define glu_perspective				gluPerspective
#define glu_new_quadric				gluNewQuadric
#define glu_quadric_draw_style      gluQuadricDrawStyle
#define glu_quadric_texture         gluQuadricTexture
#define glu_quadric_normals         gluQuadricNormals
#define glu_sphere                  gluSphere
#define glu_pick_matrix			    gluPickMatrix
#define glu_ortho_2d				gluOrtho2D

/**
 * GL API
 */
#define gl_list_base				glListBase
#define gl_new_list					glNewList
#define gl_end_list					glEndList
#define gl_enable					glEnable
#define gl_enable_client_state		glEnableClientState
#define gl_disable					glDisable
#define gl_begin					glBegin
#define gl_end						glEnd
#define gl_viewport					glViewport
#define gl_matrix_mode				glMatrixMode
#define gl_load_identity			glLoadIdentity
#define	gl_push_matrix				glPushMatrix
#define gl_pop_matrix				glPopMatrix
#define gl_push_attrib				glPushAttrib
#define gl_pop_attrib				glPopAttrib
#define gl_mult_matrix_d			glMultMatrixd
#define gl_mult_matrix_f			glMultMatrixf
#define gl_call_list				glCallList
#define gl_call_lists				glCallLists
#define gl_clear					glClear
#define gl_clear_color				glClearColor
#define gl_clear_accum				glClearAccum
#define gl_clear_depth				glClearDepth
#define gl_clear_index				glClearIndex
#define gl_clear_stencil			glClearStencil

#define gl_color_mask				glColorMask
#define gl_color_material			glColorMaterial
#define gl_color_3f					glColor3f
#define gl_color_3fv				glColor3fv
#define gl_color_3d					glColor3d
#define gl_color_3dv				glColor3dv
#define gl_color_3ub				glColor3ub
#define gl_color_3ubv				glColor3ubv
#define gl_color_3i					glColor3i
#define gl_color_3iv				glColor3iv
#define gl_color_3ui				glColor3ui
#define gl_color_3uiv				glColor3uiv
#define gl_color_3s					glColor3s
#define gl_color_3sv				glColor3sv
#define gl_color_3b					glColor3b
#define gl_color_3bv				glColor3bv

#define gl_vertex_3f				glVertex3f
#define gl_vertex_3fv				glVertex3fv

#define gl_vertex_3d				glVertex3d
#define gl_vertex_3dv				glVertex3dv

#define gl_vertex_3i				glVertex3i
#define gl_vertex_3iv				glVertex3iv

#define gl_vertex_3s				glVertex3s
#define gl_vertex_3sv				glVertex3sv

#define gl_vertex_2f				glVertex2f
#define gl_vertex_2fv				glVertex2fv

#define gl_vertex_2d				glVertex2d
#define gl_vertex_2dv				glVertex2dv

#define gl_vertex_2i				glVertex2i
#define gl_vertex_2iv				glVertex2iv

#define gl_vertex_2s				glVertex2s
#define gl_vertex_2sv				glVertex2sv

#define gl_light_f					glLightf
#define gl_light_fv					glLightfv
#define gl_light_i					glLighti
#define gl_light_iv					glLightiv
#define gl_light_model_f			glLightModelf
#define gl_light_model_fv			glLightModelfv
#define gl_light_model_i			glLightModeli
#define gl_light_model_iv			glLightModeliv

#define gl_material_f				glMaterialf
#define gl_material_fv				glMaterialfv
#define gl_material_i				glMateriali
#define gl_material_iv				glMaterialiv


#define gl_shade_model				glShadeModel
#define gl_front_face				glFrontFace

#define gl_translate_f				glTranslatef
#define gl_translate_d				glTranslated
#define gl_rotate_f					glRotatef
#define gl_rotate_d					glRotated
#define gl_scale_f					glScalef
#define gl_scale_d					glScaled

#define gl_draw_arrays				glDrawArrays
#define gl_draw_buffer				glDrawBuffer
#define gl_draw_elements			glDrawElements
#define gl_draw_pixels				glDrawPixels

#define gl_gen_lists				glGenLists
#define gl_gen_textures				glGenTextures

#define gl_load_matrix_d			glLoadMatrixd
#define gl_load_matrix_f			glLoadMatrixf
#define gl_load_name				glLoadName

#define gl_ortho					glOrtho
#define gl_frustum					glFrustum
#define gl_line_width				glLineWidth
#define gl_line_stipple				glLineStipple

#define gl_normal_3f				glNormal3f
#define gl_normal_3fv				glNormal3fv

#define gl_normal_3b				glNormal3b
#define gl_normal_3bv				glNormal3bv

#define gl_normal_3d				glNormal3d
#define gl_normal_3dv				glNormal3dv

#define gl_normal_3i				glNormal3i
#define gl_normal_3iv				glNormal3iv

#define gl_normal_3s				glNormal3s
#define gl_normal_3sv				glNormal3sv

#define	gl_get_boolean_v			glGetBooleanv
#define	gl_get_double_v				glGetDoublev
#define	gl_get_float_v				glGetFloatv
#define	gl_get_integer_v			glGetIntegerv

#define	gl_get_light_fv				glGetLightfv
#define	gl_get_light_iv				glGetLightiv

#define	gl_get_map_dv				glGetMapdv
#define	gl_get_map_fv				glGetMapfv
#define	gl_get_map_iv				glGetMapiv

#define	gl_get_material_fv			glGetMaterialfv
#define	gl_get_material_iv			glGetMaterialiv

#define	gl_get_pixel_map_fv			glGetPixelMapfv
#define	gl_get_pixel_map_uiv		glGetPixelMapuiv
#define	gl_get_pixel_map_usv		glGetPixelMapusv

#define	gl_get_pointer_v			glGetPointerv
#define	gl_get_polygon_stipple		glGetPolygonStipple
#define	gl_get_string				glGetString
#define	gl_get_error				glGetError
#define	gl_get_clip_plane			glGetClipPlane

#define gl_polygon_mode				glPolygonMode
#define gl_flush					glFlush

#define gl_raster_pos_3i			glRasterPos3i
#define gl_raster_pos_3iv			glRasterPos3iv
#define gl_raster_pos_3d			glRasterPos3d
#define gl_raster_pos_3dv			glRasterPos3dv
#define gl_raster_pos_3f			glRasterPos3f
#define gl_raster_pos_3fv			glRasterPos3fv
#define gl_raster_pos_3s			glRasterPos3s
#define gl_raster_pos_3sv			glRasterPos3sv

#define gl_get_error				glGetError

#define gl_vertex_pointer			glVertexPointer
#define gl_normal_pointer			glNormalPointer
#define gl_cull_face				glCullFace

#define gl_gen_textures				glGenTextures
#define gl_bind_texture				glBindTexture
#define gl_tex_image_2d             glTexImage2D

#define gl_tex_parameter_i			glTexParameteri
#define gl_tex_parameter_iv			glTexParameteriv
#define gl_tex_parameter_f			glTexParameterf
#define gl_tex_parameter_fv			glTexParameterfv

#define gl_tex_coord_2f				glTexCoord2f
#define gl_tex_coord_2fv			glTexCoord2fv
#define gl_tex_coord_2d				glTexCoord2d
#define gl_tex_coord_2dv			glTexCoord2dv

#define gl_tex_coord_3f				glTexCoord3f
#define gl_tex_coord_3fv			glTexCoord3fv
#define gl_tex_coord_3d				glTexCoord3d
#define gl_tex_coord_3dv			glTexCoord3dv

#define gl_blend_func				glBlendFunc

#define gl_point_size				glPointSize

#define gl_select_buffer			glSelectBuffer

#define gl_init_names				glInitNames
#define gl_render_mode				glRenderMode
#define gl_push_name				glPushName
#define gl_pop_name					glPopName

#define gl_delete_textures          glDeleteTextures
#endif