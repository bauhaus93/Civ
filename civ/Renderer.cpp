#include "Renderer.h"

Renderer* Renderer::instance = nullptr;

Renderer::Renderer(){
	common::Log("Renderer wrapper created");
}




Renderer::~Renderer(){
	common::Log("Renderer wrapper destroyed");
}
