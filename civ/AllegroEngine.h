#pragma once

#include <memory>
#include <queue>

#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>

#include "Color.h"
#include "Rect.h"
#include "CivException.h"
#include "AllegroException.h"
#include "Log.h"
#include "Event.h"

class AllegroEngine{

	static AllegroEngine*	instance;


	ALLEGRO_DISPLAY*		display;
	ALLEGRO_EVENT_QUEUE*	eventQueue;




							AllegroEngine(const Rect& screen, std::string& windowName);
							~AllegroEngine(void);

public:
	ALLEGRO_DISPLAY*		GetDisplay(void);
	int						GetScreenX(void) const;
	int						GetScreenY(void) const;
	void					ClearScene(void);
	void					SetColor(const RGBAColor& col);
	void					ClearRenderTarget(void);
	void					SetWindowTitle(const std::string& title);
	std::queue<Event>		PollEvents(void);
	void					ShowScene(void);

	void					DrawRect(const Rect& rect);
	void					DrawFillRect(const Rect & rect);
	void					DrawLine(int startX, int startY, int stopX, int stopY);

	static					void Start(const Rect& screen, std::string& windowName);
	static					void Stop(void);
	static AllegroEngine&	Instance(void);

};

inline AllegroEngine& AllegroEngine::Instance(void){
	return *instance;
}

