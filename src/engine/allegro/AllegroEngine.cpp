#include "AllegroEngine.h"

using namespace std;

AllegroEngine* AllegroEngine::instance = nullptr;

AllegroEngine::AllegroEngine(const Rect& screen, const string& windowName){

	if (!al_install_system(ALLEGRO_VERSION_INT, nullptr))
		throw AllegroException("al_install_system");

	if (!al_install_keyboard())
		throw AllegroException("al_install_keyboard");

	if (!al_install_mouse())
		throw AllegroException("al_install_mouse");

	if (!al_init_image_addon())
		throw AllegroException("al_init_image_addon");

	if (!al_init_primitives_addon())
		throw AllegroException("al_init_primitives_addon");

	Logger::Write("Initialized Allegro " + string(ALLEGRO_VERSION_STR));

	display = al_create_display(screen.w, screen.h);
	if (display == nullptr)
		throw AllegroException("al_create_display");

	Logger::Write("Created display");

	al_set_window_position(display, screen.x, screen.y);

	SetWindowTitle(windowName);

	eventQueue = al_create_event_queue();
	if (eventQueue == nullptr)
		throw AllegroException("al_create_event_queue");
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	Logger::Write("Created event queue");

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);



}

AllegroEngine::~AllegroEngine(){

	if (eventQueue != nullptr){
		al_destroy_event_queue(eventQueue);
		Logger::Write("Destroyed event queue");
	}


	if (display != nullptr){
		al_destroy_display(display);
		Logger::Write("Destroyed display");
	}

	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_uninstall_mouse();
	al_uninstall_keyboard();
	al_uninstall_system();
	Logger::Write("Shut down Allegro");
}

ALLEGRO_DISPLAY* AllegroEngine::GetDisplay(){
	return display;
}

int AllegroEngine::GetScreenX() const{
	return al_get_display_width(display);
}

int AllegroEngine::GetScreenY() const{
	return al_get_display_height(display);
}

void AllegroEngine::ClearScene(){
	al_clear_to_color(al_map_rgba(0, 0, 0, 0xFF));
}

void AllegroEngine::SetColor(const RGBAColor& col){
	//TODO WILL BE REPLACED/REMOVED LATER
}

void AllegroEngine::ClearRenderTarget(){
	al_set_target_bitmap(al_get_backbuffer(display));
}

void AllegroEngine::SetWindowTitle(const string& title){
	al_set_window_title(display, title.c_str());
}

std::queue<Event> AllegroEngine::PollEvents(){
	queue<Event> events;

	ALLEGRO_EVENT event;

	while (al_get_next_event(eventQueue, &event)){
		switch (event.type){
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				events.emplace(EventType::QUIT);
				break;
			case ALLEGRO_EVENT_KEY_UP:
				events.emplace(EventType::KEY_PRESSED, (Key) (event.keyboard.keycode - 1));
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				events.emplace(	EventType::MOUSE_PRESSED,
				 				Mouse{(MouseButton)(event.mouse.button & 1 ? MouseButton::LEFT : MouseButton::RIGHT),
								Point{event.mouse.x, event.mouse.y}});
				break;
			default:
				break;
		}
	}
	return events;
}

void AllegroEngine::ShowScene(){
	al_flip_display();
}


void AllegroEngine::DrawRect(const Rect& rect){
	al_draw_rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, al_map_rgb(0xFF, 0, 0xFF), 1.0f);
}

void AllegroEngine::DrawFillRect(const Rect& rect){
	al_draw_filled_rectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, al_map_rgb(0xFF, 0, 0xFF));
}

void AllegroEngine::DrawLine(int startX, int startY, int stopX, int stopY){
	al_draw_line(startX, startY, stopX, stopY, al_map_rgb(0xFF, 0, 0xFF), 1.0f);
}

void AllegroEngine::Start(const Rect& screen, const string& windowName){
	if (instance == nullptr){
		instance = new AllegroEngine(screen, windowName);
		atexit([](){Stop(); });
	}
	else
		throw CivException("AllegroEngine::Start", "Engine already started!");
}

void AllegroEngine::Stop(){
	if (instance != nullptr)
		delete instance;
	instance = nullptr;
}
