#pragma once


#include "SDLManager.h"
#include "Sprite.h"

class Renderer{
				Renderer();
	static Renderer* instance;
public:
	static Renderer& Instance(void);

	
				
				~Renderer();

	void		DrawRect(const Rect& rect);
	void		DrawFillRect(const Rect & rect);
	void		DrawLine(int startX, int startY, int stopX, int stopY);
	RGBAColor	SetColor(const RGBAColor& col);

	void		SetTarget(Sprite& sprite);
	void		SetStdTarget(void);
	void		Clear();
	void		Show();

};

inline Renderer& Renderer::Instance(void){
	if (instance == nullptr){
		instance = new Renderer();
		atexit([](){delete instance; });
	}
	return *instance;
}

inline void Renderer::DrawLine(int startX, int startY, int stopX, int stopY){

	if (SDL_RenderDrawLine(SDL::Instance().GetRenderer(), startX, startY, stopX, stopY) < 0)
		throw SDLException("SDL_RenderDrawLine");
}

inline void Renderer::DrawRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderDrawRect(SDL::Instance().GetRenderer(), &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

inline void Renderer::DrawFillRect(const Rect& rect){
	const SDL_Rect sdlRect{ rect.x, rect.y, rect.w, rect.h };

	if (SDL_RenderFillRect(SDL::Instance().GetRenderer(), &sdlRect) < 0)
		throw SDLException("SDL_RenderDrawRect");
}

inline RGBAColor Renderer::SetColor(const RGBAColor& col){
	RGBAColor old{ 0, 0, 0, 0 };

	if (SDL_GetRenderDrawColor(SDL::Instance().GetRenderer(), &old.r, &old.g, &old.b, &old.a) < 0)
		throw SDLException("SDL_GetRenderDrawColor");
	if (SDL_SetRenderDrawColor(SDL::Instance().GetRenderer(), col.r, col.g, col.b, col.a) < 0)
		throw SDLException("SDL_SetRenderDrawColor");
	return std::move(old);
}

inline void Renderer::SetTarget(Sprite& sprite){
	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), sprite.texture) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

inline void Renderer::SetStdTarget(void){
	if (SDL_SetRenderTarget(SDL::Instance().GetRenderer(), nullptr) == -1)
		throw SDLException("SDL_SetRenderTarget");
}

inline void Renderer::Clear(){
	if (SDL_RenderClear(SDL::Instance().GetRenderer()) < 0)
		throw SDLException("SDL_RenderClear");
}

inline void Renderer::Show(){
	SDL_RenderPresent(SDL::Instance().GetRenderer());
}

