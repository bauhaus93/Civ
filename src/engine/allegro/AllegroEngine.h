#pragma once

#include <memory>
#include <queue>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "common/Color.h"
#include "common/Rect.h"
#include "exception/CivException.h"
#include "AllegroException.h"
#include "Log.h"
#include "event/Event.h"
#include "event/Key.h"

class AllegroEngine{

	static AllegroEngine*	instance;


	ALLEGRO_DISPLAY*		display;
	ALLEGRO_EVENT_QUEUE*	eventQueue;




							AllegroEngine(const Rect& screen, const std::string& windowName);
							~AllegroEngine();

public:
	ALLEGRO_DISPLAY*		GetDisplay();
	int						GetScreenX() const;
	int						GetScreenY() const;
	void					ClearScene();
	void					SetColor(const RGBAColor& col);
	void					ClearRenderTarget();
	void					SetWindowTitle(const std::string& title);
	std::queue<Event>		PollEvents();
	void					ShowScene();

	void					DrawRect(const Rect& rect);
	void					DrawFillRect(const Rect & rect);
	void					DrawLine(int startX, int startY, int stopX, int stopY);

	static					void Start(const Rect& screen, const std::string& windowName);
	static					void Stop();
	static AllegroEngine&	Instance();

};

inline AllegroEngine& AllegroEngine::Instance(){
	return *instance;
}
