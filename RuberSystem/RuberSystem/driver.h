#ifndef PROGRAM_H
#define PROGRAM_H

#include "galaxy.h"
#include "texture.h"

namespace driver {
namespace gui_constants {
	// window with and height
	int wnd_width = 800;
	int wnd_height = 600;

	// windows' ids
	int main_wnd_id;
	int game_wnd_id;
	int top_wnd_id;
	int info_wnd_id;

	// timer
	int idle_timer = 1;
	int timer_delay = 40;
	int frame_count = 0;
	int timer_calls = 0;
	int base = 0;
	int fps = 0;
	int sound_timer = 0;
}

using namespace gui_constants;

// global 
auto_ptr<galaxy> controller;
auto_ptr<texture> texture_data;

void compile_text_list() {
	for (int i = 0; i < 256; i++) {  
		gl_new_list(base + i, GL_COMPILE);
		glut_bitmap_character(GLUT_BITMAP_8_BY_13, i);
		gl_end_list(); 
	}
	gl_list_base(base);  
}

void redisplay_all_wnd() {
	glut_set_window(game_wnd_id);
	glut_post_redisplay();
	glut_set_window(top_wnd_id);
	glut_post_redisplay();
}

void draw_main_window() {
	gl_clear_color(0.5, 0.5, 0.5, 0.0);
	gl_clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glut_swap_buffers();
}

void resize_main_window(int w, int h) {
	if (w != wnd_width && h != wnd_height) {
		glut_position_window(50, 50);
		glut_reshape_window(wnd_width, wnd_height);
	}
	gl_matrix_mode(GL_PROJECTION);
	gl_load_identity();
	gl_ortho(-w/2, w, -h/2, h, -1000, 1000.0);
}

void game_window_key_handler(unsigned char key, int x, int y) {
	controller->on_keyboard(key, x, y);
}

void game_window_special_key_handler(int key, int x, int y) {
	controller->on_special_key(key, x, y);
}

void draw_game_window() {
	glut_set_window(game_wnd_id);
	controller->draw();
	fps++;
}

void resize_game_window(int w, int h) {
	controller->set_viewing_volume(galaxy::viewing_mode::PERSPECTIVE, w, h);
}

void draw_top_window() {
	glut_set_window(top_wnd_id);
	controller->draw_top();
}

void resize_top_window(int w, int h) {
	controller->set_viewing_volume(galaxy::viewing_mode::PERSPECTIVE, w, h);
}

void draw_info_window() {
	glut_set_window(info_wnd_id);
	controller->draw_galaxy_info();
}

void resize_info_window(int w, int h) {
	controller->set_viewing_volume(galaxy::viewing_mode::ORTHO, w, h);
}

void spin() {
	controller->update();
	redisplay_all_wnd();
}

void interval_timer(int i) { 
	glut_timer_func(controller->get_time_quantum(), interval_timer, 1);
	// compute frames / second
	timer_calls++;
	if (timer_calls * timer_delay >= 1000) {
		glut_set_window(info_wnd_id);
		glut_post_redisplay();
		timer_calls = fps = 0;
	}      
	spin();  
}

void select_from_info_menu(int command) {
	controller->on_select_info_menu(command);
}

int build_info_popup_menu() {
	int menu;
	menu = glut_create_menu(select_from_info_menu);
	glut_add_menu_entry("How to Play", galaxy::information_mode::INFO_INTRODUCTION);
	glut_add_menu_entry("Planet Info", galaxy::information_mode::INFO_PLANET);
	glut_add_menu_entry("Camera Info", galaxy::information_mode::INFO_CAMERA);
	glut_add_menu_entry("Light Info", galaxy::information_mode::INFO_LIGHT);
	glut_add_menu_entry("Spaceship Info", galaxy::information_mode::INFO_SPACESHIP);
	glut_add_menu_entry("Game Info", galaxy::information_mode::INFO_GAME);
	glut_add_menu_entry("Gravity Info", galaxy::information_mode::INFO_GRAVITY);
	return menu;
}

void setup_windows() {
	glut_init_display_mode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glut_init_window_size(wnd_width, wnd_height);
	main_wnd_id = glut_create_window("Romulan Imperial War College");
	glut_position_window(50, 50);
	glut_reshape_func(resize_main_window);
	glut_display_func(draw_main_window);

	// make game window
	glut_init_display_mode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	game_wnd_id = glut_create_sub_window(main_wnd_id, 10, 10, 580, 580);
	glut_reshape_func(resize_game_window);
	glut_display_func(draw_game_window); 
	glut_keyboard_func(game_window_key_handler);
	glut_special_func(game_window_special_key_handler);

	glut_timer_func(timer_delay, interval_timer, 1);

	// make top window
	glut_init_display_mode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	top_wnd_id = glut_create_sub_window(main_wnd_id, 605, 0, 200, 200);
	glut_reshape_func(resize_top_window);
	glut_display_func(draw_top_window);

	// make info window
	glut_init_display_mode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	info_wnd_id = glut_create_sub_window(main_wnd_id, 605, 200, 200, 400);
	glut_reshape_func(resize_info_window);
	glut_display_func(draw_info_window);
	build_info_popup_menu();
	glut_attach_menu(GLUT_RIGHT_BUTTON);

	// must initialize here? why?
	compile_text_list();
	// we start with game window
	glut_set_window(game_wnd_id);
}

unordered_map<string, unsigned> load_all_textures() {
	vector<texture::texture_type> types;
	vector<pair<string, string> > filenames;

	string sun_texture = "suntexture.bmp";
	filenames.push_back(make_pair<string, string>(sun_texture, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture0 = "galaxy0.bmp";
	filenames.push_back(make_pair<string, string>(space_texture0, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture1 = "galaxy1.bmp";
	filenames.push_back(make_pair<string, string>(space_texture1, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture2 = "galaxy2.bmp";
	filenames.push_back(make_pair<string, string>(space_texture2, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture3 = "galaxy3.bmp";
	filenames.push_back(make_pair<string, string>(space_texture3, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture4 = "galaxy4.bmp";
	filenames.push_back(make_pair<string, string>(space_texture4, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture5 = "galaxy5.bmp";
	filenames.push_back(make_pair<string, string>(space_texture5, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture6 = "galaxy6.bmp";
	filenames.push_back(make_pair<string, string>(space_texture6, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture7 = "galaxy7.bmp";
	filenames.push_back(make_pair<string, string>(space_texture7, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture8 = "galaxy8.bmp";
	filenames.push_back(make_pair<string, string>(space_texture8, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture9 = "galaxy9.bmp";
	filenames.push_back(make_pair<string, string>(space_texture9, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture10 = "galaxy10.bmp";
	filenames.push_back(make_pair<string, string>(space_texture10, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string space_texture11 = "messi.bmp";
	filenames.push_back(make_pair<string, string>(space_texture11, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string planet_texture = "galaxy0.bmp";
	filenames.push_back(make_pair<string, string>(planet_texture, " "));
	types.push_back(texture::texture_type::TEXTURE_REGULAR);

	string particle_circle_texture = "circle.bmp";
	string particle_circle_alpha = "circlealpha.bmp";
	filenames.push_back(make_pair<string, string>(particle_circle_texture, particle_circle_alpha));
	types.push_back(texture::texture_type::TEXTURE_WITH_ALPHA);

	texture_data = auto_ptr<texture>(new texture());
	texture_data->load_all(filenames, types);
	return texture_data->get_textures_hashmap();
}

void run(int argc, char **argv) {
	glut_init(&argc, argv);
	setup_windows();
	controller = auto_ptr<galaxy>(new galaxy(load_all_textures()));
	controller->generate_models();
	glut_main_loop();
}
}
#endif